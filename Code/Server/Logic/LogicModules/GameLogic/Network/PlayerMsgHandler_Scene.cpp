#include "PlayerMsgHandler.h"
#include "Utils/PlatformCompat.h"
#include "GameLogic/GameLogicModule.h"
#include "GameLogic/Player/Player.h"
#include "Network/Utils/NetworkAgent.h"
#include "Common/Utils/AutoReleaseUtil.h"
#include "Common/Macro/AllMacro.h"
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
#include "ServerLogics/ServerLogic.h"

namespace GameLogic
{
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
		G_NetAgent->Send(player->GetNetId(), NetProto::PID_RspFreeHero, rsp_msg);
	}

	void PlayerMsgHandler::OnSelectHeroReq(int protocol_id, NetProto::SelectHeroReq *msg, GameLogic::Player *player)
	{
		NetProto::SelectHeroRsp *rsp_msg = google::protobuf::Arena::CreateMessage<NetProto::SelectHeroRsp>(m_protobuf_arena);
		m_logic_module->m_new_scene->PlayerSelectHero(player, msg->hero_id());
		auto hero = player->GetSu();
		rsp_msg->set_is_succ(nullptr != hero);
		if (nullptr != hero)
			rsp_msg->set_hero_id(hero->GetId());
		G_NetAgent->Send(player->GetNetId(), NetProto::PID_SelectHeroRsp, rsp_msg);
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
		G_Log->Debug(LogModule::LOGGER_ID_STDOUT, "OnMoveToPos {0}, {1}", msg->pos().x(), msg->pos().y());
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
}
