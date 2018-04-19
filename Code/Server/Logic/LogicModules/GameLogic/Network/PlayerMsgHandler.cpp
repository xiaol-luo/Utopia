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
			if (nullptr != handler_descript->Msg())
				handler_descript->Msg()->ParseFromArray(protobuf_data, data_len);
			handler_descript->Handle(protocol_id, handler_descript->Msg(), player);
			if (m_protobuf_arena->SpaceAllocated() > 1024 * 10)
				m_protobuf_arena->Reset();

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

	void PlayerMsgHandler::OnQueryFreeHero(int protocol_id, GameLogic::Player *player)
	{
		auto red_hero = m_logic_module->m_new_scene->red_su;
		auto blue_hero = m_logic_module->m_new_scene->blue_su;

		NetProto::RspFreeHero *rsp_msg = google::protobuf::Arena::CreateMessage<NetProto::RspFreeHero>(m_protobuf_arena);
		if (0 == red_hero->GetPlayerId())
			rsp_msg->set_red_hero_id(red_hero->GetId());
		if (0 == blue_hero->GetPlayerId())
			rsp_msg->set_blue_hero_id(blue_hero->GetId());

		GlobalServerLogic->GetNetAgent()->Send(player->GetNetId(), NetProto::PID_RspFreeHero, rsp_msg);
	}

	void PlayerMsgHandler::OnSelectHeroReq(int protocol_id, NetProto::SelectHeroReq *msg, GameLogic::Player *player)
	{
		auto red_hero = m_logic_module->m_new_scene->red_su;
		auto blue_hero = m_logic_module->m_new_scene->blue_su;
		NetProto::SelectHeroRsp *rsp_msg = google::protobuf::Arena::CreateMessage<NetProto::SelectHeroRsp>(m_protobuf_arena);
		
		auto hero = player->GetSu();
		if (nullptr == hero)
		{
			rsp_msg->set_hero_id(msg->hero_id());
			if (msg->hero_id() == red_hero->GetId())
			{
				if (0 == red_hero->GetPlayerId())
				{
					m_logic_module->m_new_scene->PlayerSelectHero(player, red_hero->GetId());
					rsp_msg->set_is_succ(true);
				}
			}
			if (msg->hero_id() == blue_hero->GetId())
			{
				if (0 == blue_hero->GetPlayerId())
				{
					m_logic_module->m_new_scene->PlayerSelectHero(player, blue_hero->GetId());
					rsp_msg->set_is_succ(true);
				}
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
		LuaUtils::LoadScripts_ReloadEffectScripts();
	}
}
