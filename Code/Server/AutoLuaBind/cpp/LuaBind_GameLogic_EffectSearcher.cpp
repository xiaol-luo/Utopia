#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectConfigBase.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/Effects/EffectSearcher/EffectSearcherConfig.h"	
#include "GameLogic/Scene/Effects/EffectSearcher/EffectSearcher.h"	
#include "GameLogic/Scene/SceneModule/SceneEffects/SceneEffects.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectSearcher(lua_State *L)
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
                std::string name = "EffectSearcher";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectSearcher> meta_table(
						sol::constructors<				
						GameLogic::EffectSearcher(const GameLogic::EffectConfigBase *, GameLogic::SceneEffects *, uint64_t)
						>(),
						"__StructName__", sol::property([]() {return "EffectSearcher"; })				
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