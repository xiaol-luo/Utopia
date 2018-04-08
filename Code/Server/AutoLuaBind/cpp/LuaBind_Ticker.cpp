#include "SolLuaBindUtils.h"
#include <sol.hpp>

#include "Logic/ShareCode/Common/Utils/Ticker.h"

namespace SolLuaBind
{
	void LuaBind_Ticker(lua_State *L)
	{
		struct LuaBindImpl
		{
			struct ForOverloadFns
			{
				static void Restart1(Ticker &cls)
				{
					return cls.Restart();
				}
				static void Restart2(Ticker &cls, float p1)
				{
					return cls.Restart(p1);
				}
			};

			static void DoLuaBind(lua_State *L)
			{
                std::string name = "Ticker";
				std::string name_space = "";

				{
					sol::usertype<Ticker> meta_table(
						sol::constructors<				
						Ticker()
						>(),
					"__StructName__", sol::property([]() {return "Ticker"; })				
						,"SetTimeFunc", &Ticker::SetTimeFunc				
						,"RestartWithEndTimestamp", &Ticker::RestartWithEndTimestamp				
						,"SetCd", &Ticker::SetCd				
						,"GetCd", &Ticker::GetCd				
						,"GetStart", &Ticker::GetStart				
						,"LeftTime", &Ticker::LeftTime				
						,"ElaspeTime", &Ticker::ElaspeTime				
						,"EndTimestamp", &Ticker::EndTimestamp				
						,"InCd", &Ticker::InCd				
						,"Restart", sol::overload(ForOverloadFns::Restart1, ForOverloadFns::Restart2)
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