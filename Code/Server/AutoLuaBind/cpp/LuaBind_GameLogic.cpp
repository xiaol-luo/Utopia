#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "LogicModules/GameLogic/Scene/Skills/Skill.h"	
#include "LogicModules/GameLogic/Scene/Skills/SkillBase.h"	
#include "LogicModules/GameLogic/Scene/Defines/SceneDefine.h"	
#include "protobuf/include/google/protobuf/message.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "LogicModules/GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"	
#include "LogicModules/GameLogic/Scene/Missile/SceneUnitGuidedMissile/SceneUnitGuidedMissile.h"	
#include "LogicModules/GameLogic/Scene/Defines/ViewDefine.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
			};

			static void DoLuaBind(lua_State *L)
			{
				std::string name_space = "GameLogic";

				sol::state_view lua(L);

				sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(lua, name_space);				
				{
					std::string name = "InvalidViewPos";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::InvalidViewPos);
				}				
				{
					std::string name = "VIEW_GRID_INVALID_IDX";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::VIEW_GRID_INVALID_IDX);
				}				
				{
					std::string name = "SCENE_UNIT_INVALID_ID";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::SCENE_UNIT_INVALID_ID);
				}				
				{
					std::string name = "MOVE_TO_POS_IGNORE_DISTANCE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::MOVE_TO_POS_IGNORE_DISTANCE);
				}				
				{
					std::string name = "MOVE_TO_POS_IGNORE_SQR_DISTANCE";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::MOVE_TO_POS_IGNORE_SQR_DISTANCE);
				}				
				{
					std::string name = "GenerateEndEffectIdVec";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::GenerateEndEffectIdVec);
				}				
				{
					std::string name = "StrToEffectFilterAnchor";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::StrToEffectFilterAnchor);
				}				
				{
					std::string name = "AddGuidedMissileToScene";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::AddGuidedMissileToScene);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}