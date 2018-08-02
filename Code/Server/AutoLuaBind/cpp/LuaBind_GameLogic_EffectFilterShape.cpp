#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/LogicModules/GameLogic/Scene/Effects/EffectBase.h"	
#include "Logic/LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "Common/Geometry/Vector2.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_EffectFilterShape(lua_State *L)
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
                std::string name = "EffectFilterShape";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::EffectFilterShape> meta_table(
						"__StructName__", sol::property([]() {return "EffectFilterShape"; })				
						,"pos", &GameLogic::EffectFilterShape::pos				
						,"dir", &GameLogic::EffectFilterShape::dir				
						,"shape", &GameLogic::EffectFilterShape::shape				
						,"shape_param", &GameLogic::EffectFilterShape::shape_param
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