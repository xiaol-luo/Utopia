#include "PlayerMsgHandler.h"
#include "Utils/PlatformCompat.h"
#include "Network/Protobuf/msg.pb.h"
#include "Network/Protobuf/test.pb.h"
#include "Network/Protobuf/ProtoId.pb.h"
#include "Network/Protobuf/Common.pb.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/Player.h"
#include "Network/Utils/NetworkAgent.h"
#include "Network/Protobuf/Battle.pb.h"
#include "Common/Utils/AutoReleaseUtil.h"
#include "Common/Macro/ServerLogicMacro.h"
#include "CommonModules/Log/LogModule.h"
#include <memory>
#include "Common/Geometry/Vector2.h"
#include "Common/Geometry/GeometryUtils.h"
#include "GameLogic/Scene/NewScene.h"
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSight.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitMove.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitAction/SceneHeroAction.h"
#include "GameLogic/Scene/SceneUnitModules/SceneUnitSkills/SceneUnitSkills.h"
#include "GameLogic/Scene/Skills/Skill.h"
#include "LuaHelps/LuaLoadFiles.h"

#define RegPlayerMsgHandler(id, msg_type, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientMsgHandlerDescript<msg_type>(this, (int)id, &PlayerMsgHandler::func))

#define RegPlayerHandler(id, func) \
	msg_handle_descripts.push_back(new GameLogic::ClientEmptyMsgHandlerDescript(this, (int)id, &PlayerMsgHandler::func))


static const char *NET_HANDLER_NAMESPACE = "net_handler";
static const char *NET_PLAYER_HANDLER_FN = "OnPlayerMsg";

namespace GameLogic
{
	PlayerMsgHandler::PlayerMsgHandler(GameLogicModule *logic_module)
	{
		m_logic_module = logic_module;
		m_protobuf_arena = MemoryUtil::NewArena();
	}

	PlayerMsgHandler::~PlayerMsgHandler()
	{
		delete m_protobuf_arena; 
		m_protobuf_arena = nullptr;
	}

	void PlayerMsgHandler::Init()
	{
		uint32_t malloc_size = sizeof(GameLogic::IClientMsgHandlerDescript *) * NetProto::PID_Max;
		m_client_msg_handler_descripts = (GameLogic::IClientMsgHandlerDescript **)malloc(malloc_size);
		memset(m_client_msg_handler_descripts, 0, malloc_size);

		std::vector<GameLogic::IClientMsgHandlerDescript *> msg_handle_descripts;
		RegPlayerMsgHandler(NetProto::PID_Ping, NetProto::Ping, OnHandlePlayerPingMsg);
		RegPlayerMsgHandler(NetProto::PID_Pong, NetProto::Pong, OnHandlePlayerPongMsg);
		RegPlayerHandler(NetProto::PID_QueryFreeHero, OnQueryFreeHero);
		RegPlayerMsgHandler(NetProto::PID_SelectHeroReq, NetProto::SelectHeroReq, OnSelectHeroReq);
		RegPlayerHandler(NetProto::PID_LoadSceneComplete, OnLoadSceneComplete);
		RegPlayerHandler(NetProto::PID_LeaveScene, OnLeaveScene);
		RegPlayerMsgHandler(NetProto::PID_MoveToPos, NetProto::MoveToPos, OnMoveToPos);
		RegPlayerHandler(NetProto::PID_StopMove, OnStopMove);
		RegPlayerMsgHandler(NetProto::PID_BattleOperaReq, NetProto::BattleOperation, OnHandleBattleOperation);
		RegPlayerMsgHandler(NetProto::PID_ReloadLuaScripts, NetProto::ReloadLuaScripts, OnReloadLuaScripts);

		for (auto desc : msg_handle_descripts)
		{
			assert(nullptr == m_client_msg_handler_descripts[desc->Id()]);
			m_client_msg_handler_descripts[desc->Id()] = desc;
		}

		sol::state_view lsv(LuaUtils::GetState());
		m_lua_msg_handler_fn = lsv[NET_HANDLER_NAMESPACE][NET_PLAYER_HANDLER_FN];
		assert(m_lua_msg_handler_fn.valid());
		m_lua_msg_handler_fn.error_handler = LuaUtils::ProtectFnErrorHandler();
	}

	void PlayerMsgHandler::Uninit()
	{
		if (nullptr != m_client_msg_handler_descripts)
		{
			for (int i = NetProto::PID_Min + 1; i < NetProto::PID_Max; ++i)
				delete m_client_msg_handler_descripts[i];
			free(m_client_msg_handler_descripts);
			m_client_msg_handler_descripts = nullptr;
		}
	}

	void PlayerMsgHandler::HandlePlayerMsg(char *data, uint32_t data_len, GameLogic::Player *player)
	{
		static const uint32_t PROTOCOL_LEN_DESCRIPT_SIZE = sizeof(int);
		assert(nullptr != player);

		bool is_ok = true;
		do
		{
			if (nullptr == data || data_len < PROTOCOL_LEN_DESCRIPT_SIZE)
			{
				is_ok = false;
				break;
			}
			int protocol_id = ntohl(*(int *)data);
			if (protocol_id <= NetProto::PID_Min || protocol_id >= NetProto::PID_Max)
			{
				is_ok = false;
				break;
			}
			GameLogic::IClientMsgHandlerDescript *handler_descript = m_client_msg_handler_descripts[protocol_id];
			if (nullptr == handler_descript)
			{
				is_ok = false;
				GlobalServerLogic->GetLogModule()->Error(LogModule::LOGGER_ID_STDERR + 1, "not handler function for protocol id {}", protocol_id);
				break;
			}
			char *protobuf_data = data + PROTOCOL_LEN_DESCRIPT_SIZE;
			uint32_t protobuf_len = data_len - PROTOCOL_LEN_DESCRIPT_SIZE;
			if (nullptr != handler_descript->Msg())
			{
				handler_descript->Msg()->Clear();
				if (!handler_descript->Msg()->ParsePartialFromArray(protobuf_data, protobuf_len))
					break;
			}
			handler_descript->Handle(protocol_id, handler_descript->Msg(), player);
			if (m_protobuf_arena->SpaceAllocated() > 1024 * 10)
				m_protobuf_arena->Reset();

			// for test
			m_tmp_lua_msg_buf.assign(protobuf_data, protobuf_len);
			std::string protobuf_type_name;
			if (handler_descript->Msg())
				protobuf_type_name = handler_descript->Msg()->GetTypeName();
			m_lua_msg_handler_fn(protocol_id, m_tmp_lua_msg_buf, player, protobuf_type_name);

		} while (false);
		if (!is_ok)
		{
			GlobalServerLogic->GetNetAgent()->Close(player->GetNetId());
		}
	}

	void PlayerMsgHandler::OnHandlePlayerPingMsg(int protocol_id, NetProto::Ping *msg, GameLogic::Player *player)
	{
		NetProto::Pong *pong = google::protobuf::Arena::CreateMessage<NetProto::Pong>(m_protobuf_arena);
		GlobalServerLogic->GetNetAgent()->Send(player->GetNetId(), NetProto::PID_Pong, pong);
	}

	void PlayerMsgHandler::OnHandlePlayerPongMsg(int protocol_id, NetProto::Pong *msg, GameLogic::Player *player)
	{
		
	}

	static std::vector<std::shared_ptr<SceneUnit> > FindSceneHerosByCamp(NetProto::ESceneUnitCamp camp)
	{
		std::vector<std::shared_ptr<SceneUnit> > ret;
		auto fn = [&](std::shared_ptr<SceneUnit> su, void *p) {
			if (0 == su->GetPlayerId() 
				&& NetProto::ESceneUnitType::EsceneUnitType_Hero == su->GetUnitType()
				&& camp == su->GetCamp())
			{
				ret.push_back(su);
			}
		};

		return std::move(ret);
	}

	void PlayerMsgHandler::OnQueryFreeHero(int protocol_id, GameLogic::Player *player)
	{
		std::vector<std::shared_ptr<SceneUnit> > redCampHeros;
		std::vector<std::shared_ptr<SceneUnit> > blueCampHeros;
		auto fn = [&](std::shared_ptr<SceneUnit> su, void *p) {
			if (0 == su->GetPlayerId() && NetProto::ESceneUnitType::EsceneUnitType_Hero == su->GetUnitType())
			{
				if (NetProto::ESceneUnitCamp_Blue == su->GetCamp())
					blueCampHeros.push_back(su);
				if (NetProto::ESceneUnitCamp_Red == su->GetCamp())
					redCampHeros.push_back(su);
			}
		};
		m_logic_module->m_new_scene->ForeachSceneUnit(fn, nullptr);

		NetProto::RspFreeHero *rsp_msg = google::protobuf::Arena::CreateMessage<NetProto::RspFreeHero>(m_protobuf_arena);
		if (redCampHeros.size() > 0)
			rsp_msg->set_red_hero_id(redCampHeros[0]->GetId());
		if (blueCampHeros.size() > 0)
			rsp_msg->set_blue_hero_id(blueCampHeros[0]->GetId());
		GlobalServerLogic->GetNetAgent()->Send(player->GetNetId(), NetProto::PID_RspFreeHero, rsp_msg);
	}

	void PlayerMsgHandler::OnSelectHeroReq(int protocol_id, NetProto::SelectHeroReq *msg, GameLogic::Player *player)
	{
		NetProto::SelectHeroRsp *rsp_msg = google::protobuf::Arena::CreateMessage<NetProto::SelectHeroRsp>(m_protobuf_arena);
		auto hero = player->GetSu();
		if (nullptr == hero)
		{
			rsp_msg->set_hero_id(msg->hero_id());
			auto su = m_logic_module->m_new_scene->GetUnit(msg->hero_id());
			if (nullptr != su && 0 == su->GetPlayerId())
			{
				m_logic_module->m_new_scene->PlayerSelectHero(player, su->GetId());
				rsp_msg->set_is_succ(true);
			}
		}
		GlobalServerLogic->GetNetAgent()->Send(player->GetNetId(), NetProto::PID_SelectHeroRsp, rsp_msg);
	}

	void PlayerMsgHandler::OnLoadSceneComplete(int id, GameLogic::Player * player)
	{
		auto scene_view = player->GetSu()->GetModule<SceneUnitSight>();
		if (nullptr != scene_view)
		{
			player->GetScene()->SetPlayerViewCamp(player, scene_view->GetViewCamp());
		}
	}

	void PlayerMsgHandler::OnLeaveScene(int id, GameLogic::Player * player)
	{
		NewScene *scene = player->GetScene();
		if (nullptr != scene)
			scene->OnPlayerQuit(player);
		player->SetSu(nullptr);
		player->SetScene(nullptr);
	}

	void PlayerMsgHandler::OnMoveToPos(int protocol_id, NetProto::MoveToPos *msg, GameLogic::Player * player)
	{
		auto hero = player->GetSu();
		if (nullptr == hero)
			return;
		auto su_move = hero->GetModule<SceneUnitMove>();
		if (nullptr == su_move)
			return;
		su_move->TryMoveToPos(Vector3(msg->pos().x(), 0, msg->pos().y()));
		GlobalServerLogic->GetLogModule()->Debug(LogModule::LOGGER_ID_STDOUT, "OnMoveToPos {0}, {1}", msg->pos().x(), msg->pos().y());
	}
	
	void PlayerMsgHandler::OnStopMove(int id, GameLogic::Player * player)
	{
		auto hero = player->GetSu();
		if (nullptr == hero)
			return;
		auto su_move = hero->GetModule<SceneUnitMove>();
		if (nullptr == su_move)
			return;
		su_move->CancelMove();
	}
	void PlayerMsgHandler::OnHandleBattleOperation(int protocol_id, NetProto::BattleOperation * msg, GameLogic::Player * player)
	{
		auto hero = player->GetSu();
		if (nullptr == hero)
			return;
		std::shared_ptr<SceneHeroAction> su_action = hero->GetModule<SceneHeroAction>();
		if (nullptr == su_action)
			return;

		switch (msg->opera())
		{
		case NetProto::EPO_Move:
			su_action->MoveTo(Vector3(msg->pos().x(), 0, msg->pos().y()), MOVE_TO_POS_IGNORE_DISTANCE);
			break;

		case NetProto::EPO_Stop:
			su_action->CancelMove();
			su_action->CancelSkill();
			break;

		case NetProto::EPO_Trace:
			su_action->Trace(msg->target_id(), MOVE_TO_POS_IGNORE_DISTANCE);
			break;

		case NetProto::EPO_CastSkill:
		{
			std::shared_ptr<SceneUnitSkills> su_skills = su_action->GetModule<SceneUnitSkills>();
			std::shared_ptr<Skill> skill = su_skills->GetSlotActiveSkill(msg->skill_slot());
			if (nullptr != skill)
				su_action->UseSkill(skill->GetSkillId(), msg->target_id(), Vector2(msg->pos().x(), msg->pos().y()), msg->dir());
		}
		break;

		default:
			break;
		}
	}

	void PlayerMsgHandler::OnReloadLuaScripts(int id, NetProto::ReloadLuaScripts * msg, GameLogic::Player * player)
	{
		std::set<std::string> scripts;
		for (auto item : msg->scripts())
		{
			std::string script = item;
			scripts.insert(script);
		}
		LuaUtils::LoadScripts_DoLoadScript(true, scripts);
		m_logic_module->ReloadConfig();
	}
}
