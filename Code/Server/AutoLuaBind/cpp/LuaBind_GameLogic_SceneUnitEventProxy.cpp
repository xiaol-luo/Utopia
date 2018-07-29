#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnitEventProxy.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacher.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitEventProxy(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = int;
				using TypeAlias_2 = std::function<void ()>;
				using TypeAlias_3 = int64_t;
				static TypeAlias_3 Subscribe1(GameLogic::SceneUnitEventProxy &cls, TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return cls.Subscribe(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneUnitEventProxy";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitEventProxy> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitEventProxy(EventDispacher *, EventDispacherProxy *, std::shared_ptr<GameLogic::SceneUnit>)
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitEventProxy"; })				
						,"Cancel", &GameLogic::SceneUnitEventProxy::Cancel				
						,"CancelAll", &GameLogic::SceneUnitEventProxy::CancelAll				
						,"Subscribe", sol::overload(ForOverloadFns::Subscribe1)
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}