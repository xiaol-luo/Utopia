#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "Logic/ShareCode/Common/Geometry/Vector3.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "Logic/LogicModules/GameLogic/Scene/Defines/EffectDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Logic/ShareCode/Common/Geometry/GeometryDefine.h"	
#include "Logic/LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFilter(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = const GameLogic::SceneUnitFilterWayParams &;
				using TypeAlias_2 = const std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > > &;
				using TypeAlias_3 = std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > >;
				static TypeAlias_3 ExtractSceneUnit1(GameLogic::SceneUnitFilter &cls, TypeAlias_1 p1, TypeAlias_2 p2)
				{
					return cls.ExtractSceneUnit(p1, p2);
				}
				using TypeAlias_4 = const GameLogic::SceneUnitFilterWayParams &;
				using TypeAlias_5 = const std::vector<std::shared_ptr<GameLogic::SceneUnit>, std::allocator<std::shared_ptr<GameLogic::SceneUnit> > > &;
				using TypeAlias_6 = std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > >;
				static TypeAlias_6 ExtractSceneUnit2(GameLogic::SceneUnitFilter &cls, TypeAlias_4 p1, TypeAlias_5 p2)
				{
					return cls.ExtractSceneUnit(p1, p2);
				}
			};
			
			struct ForPropertyField
			{
			};			
			

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "SceneUnitFilter";
				std::string name_space = "GameLogic";

				{
					sol::usertype<GameLogic::SceneUnitFilter> meta_table(
						sol::constructors<				
						GameLogic::SceneUnitFilter()
						>(),
						"__StructName__", sol::property([]() {return "SceneUnitFilter"; })				
						,"FindSceneUnit", &GameLogic::SceneUnitFilter::FindSceneUnit				
						,"ExtractSceneUnit", sol::overload(ForOverloadFns::ExtractSceneUnit1, ForOverloadFns::ExtractSceneUnit2)				
						, sol::base_classes, sol::bases<
							GameLogic::SceneModule 
						>()
					);
					SolLuaBindUtils::BindLuaUserType(sol::state_view(L), meta_table, name, name_space);
				}
            
				{
					sol::table ns_table = SolLuaBindUtils::GetOrNewLuaNameSpaceTable(sol::state_view(L), name_space)[name];				
					{
						std::string var_name = "MODULE_TYPE";
						sol::object obj = ns_table.raw_get_or(var_name, sol::nil);
						assert(!obj.valid());
						ns_table.set(var_name, GameLogic::SceneUnitFilter::MODULE_TYPE);
					}
				}
			}
		};

		LuaBindImpl::DoLuaBind(L);
	}
}