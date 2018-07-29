#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScript.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectScript/EffectScriptConfig.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "LogicModules/GameLogic/Scene/Effects/EffectBase.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectScript_LuaSubcribeItem(lua_State *L)
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
                std::string name = "LuaSubcribeItem";
				std::string name_space = "GameLogic.EffectScript";

				{
					sol::usertype<GameLogic::EffectScript::LuaSubcribeItem> meta_table(
						"__StructName__", sol::property([]() {return "LuaSubcribeItem"; })				
						,"id", &GameLogic::EffectScript::LuaSubcribeItem::id				
						,"fn", &GameLogic::EffectScript::LuaSubcribeItem::fn				
						,"event_handler_id", &GameLogic::EffectScript::LuaSubcribeItem::event_handler_id				
						,"next", &GameLogic::EffectScript::LuaSubcribeItem::next
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