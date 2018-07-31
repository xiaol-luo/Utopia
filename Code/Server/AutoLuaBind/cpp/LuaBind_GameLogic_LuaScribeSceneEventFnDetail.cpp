#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Common/EventDispatcher/EventDispacherProxy.h"	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_LuaScribeSceneEventFnDetail(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "LuaScribeSceneEventFnDetail";
				std::string name_space = "GameLogic";
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}