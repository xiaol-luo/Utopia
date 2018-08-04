#include "PlayerMsgHandler.h"
#include "ServerLogics/ServerLogic.h"
#include "Logic/LuaHelps/LuaLoadFiles.h"
#include "LogicModules/GameLogic/GameLogicModule.h"
#include "LogicModules/GameLogic/Defines/EGlobalEvent.h"

namespace GameLogic
{
	void PlayerMsgHandler::OnReloadConfig(int id, GameLogic::Player *player)
	{
		m_logic_module->ReloadConfig();
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
	}

	void PlayerMsgHandler::OnGmRecreateScene(int id, NetProto::RecreateSceneReq *msg, GameLogic::Player *player)
	{
		G_Event->Fire(EGE_GmRecreateScene, msg->scene_name());
	}
}
