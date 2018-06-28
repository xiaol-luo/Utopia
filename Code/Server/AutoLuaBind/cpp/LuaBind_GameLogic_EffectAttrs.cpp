#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrsConfig.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"	
#include "GameLogic/Scene/Effects/EffectAttrs/EffectAttrs.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectAttrs(lua_State *L)
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
                std::string name = "EffectAttrs";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectAttrs> meta_table(
						sol::constructors<				
						GameLogic::EffectAttrs(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, unsigned long long)
						>(),
						"__StructName__", sol::property([]() {return "EffectAttrs"; })				
						, sol::base_classes, sol::bases<
							GameLogic::EffectBase 
						>()
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