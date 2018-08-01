#include "SolLuaBindUtils.h"
#include <sol.hpp>	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneModule.h"	
#include "LogicModules/GameLogic/Scene/SceneUnit/SceneUnit.h"	
#include "Common/Geometry/Vector3.h"	
#include "Common/Geometry/GeometryDefine.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitQTree.h"	
#include "LogicModules/GameLogic/Scene/SceneModule/SceneUnitFilter/SceneUnitFilter.h"

namespace SolLuaBind
{
	void LuaBind_GameLogic_SceneUnitFilter(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				using TypeAlias_1 = GameLogic::EffectFilterShape;
				using TypeAlias_2 = std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > >;
				static TypeAlias_2 FilterSceneUnit1(GameLogic::SceneUnitFilter &cls, TypeAlias_1 p1)
				{
					return cls.FilterSceneUnit(p1);
				}
				using TypeAlias_3 = GameLogic::EffectFilterShape;
				using TypeAlias_4 = GameLogic::ESceneUnitFilterWayParams &;
				using TypeAlias_5 = std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > >;
				static TypeAlias_5 FilterSceneUnit2(GameLogic::SceneUnitFilter &cls, TypeAlias_3 p1, TypeAlias_4 p2)
				{
					return cls.FilterSceneUnit(p1, p2);
				}
				using TypeAlias_6 = GameLogic::EffectFilterShape;
				using TypeAlias_7 = std::shared_ptr<GameLogic::SceneUnit>;
				using TypeAlias_8 = int;
				using TypeAlias_9 = std::unordered_map<uint64_t, std::shared_ptr<GameLogic::SceneUnit>, std::hash<uint64_t>, std::equal_to<uint64_t>, std::allocator<std::pair<const uint64_t, std::shared_ptr<GameLogic::SceneUnit> > > >;
				static TypeAlias_9 FilterSceneUnit3(GameLogic::SceneUnitFilter &cls, TypeAlias_6 p1, TypeAlias_7 p2, TypeAlias_8 p3)
				{
					return cls.FilterSceneUnit(p1, p2, p3);
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
						,"FilterSceneUnit", sol::overload(ForOverloadFns::FilterSceneUnit1, ForOverloadFns::FilterSceneUnit2, ForOverloadFns::FilterSceneUnit3)				
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