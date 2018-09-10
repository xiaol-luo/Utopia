#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "GameLogic/Scene/Effects/EffectScript/LuaSubscribeEventDetail.h"	
#include "GameLogic/Scene/Skills/Skill.h"	
#include "GameLogic/Scene/Missile/SceneUnitBullet/Bullet.h"	
#include "GameLogic/Scene/Defines/ViewDefine.h"	
#include "GameLogic/Scene/Skills/SkillBase.h"	
#include "ShareCode/Common/Geometry/Vector2.h"	
#include "GameLogic/Scene/Defines/EffectDefine.h"	
#include "ShareCode/Common/Utils/Ticker.h"	
#include "GameLogic/Scene/Effects/EffectBase.h"	
#include "GameLogic/Scene/Defines/SceneDefine.h"	
#include "GameLogic/Scene/Effects/EffectScript/SceneEvents/LuaScribeEventFnDetail.h"	
#include "GameLogic/Scene/Skills/SkillConfig.h"	
#include "ShareCode/Common/EventDispatcher/EventDispacherProxy.h"	
#include "ShareCode/Common/Geometry/Vector3.h"	
#include "CsvConfigSets.h"	
#include "GameLogic/Scene/SceneModule/SceneView/ViewGrid.h"	
#include "google/protobuf/message.h"	
#include "GameLogic/Scene/Missile/SceneUnitMissile.h"	
#include "GameLogic/Scene/Skills/SkillConfigBase.h"	
#include "GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "GameLogic/Scene/SceneUnitModules/SceneUnitTransform.h"

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
					std::string name = "SELECT_SELF_FILTER_CONFIG_ID";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::SELECT_SELF_FILTER_CONFIG_ID);
				}				
				{
					std::string name = "SELECT_TARGET_FILTER_CONFIG_ID";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::SELECT_TARGET_FILTER_CONFIG_ID);
				}				
				{
					std::string name = "MAX_SKILL_LEVEL";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set(name, GameLogic::MAX_SKILL_LEVEL);
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
					std::string name = "StrToForceMoveAnchor";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::StrToForceMoveAnchor);
				}				
				{
					std::string name = "CalForceMoveDir";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::CalForceMoveDir);
				}				
				{
					std::string name = "AddBulletToScene";
					sol::object obj = ns_table.raw_get_or(name, sol::nil);
					assert(!obj.valid());
					ns_table.set_function(name, GameLogic::AddBulletToScene);
				}			
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}