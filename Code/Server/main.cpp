#include <stdio.h>
#include "Utils/ConfigUtil.h"
#include "ServerLogics/Game/GameServerLogic.h"
#include "event2/event.h"
// #include <vld.h>
#include <signal.h>
#include "MemoryPool/MemoryPoolMgr.h"
#include "Common/Utils/MemoryUtil.h"
#include "ShareCode/Network/Utils/LenCtxStreamParserEx.h"
#include <stdint.h>
#include "MemoryPool/StlAllocator.h"
#include "Common/Utils/TupleUtil.h"

#include <sol.hpp>

extern ServerLogic *server_logic;

void QuitGame(int signal)
{
	if (nullptr != server_logic)
		server_logic->Quit();
}

lua_State *L;

void TestSol(lua_State *l)
{
	sol::state_view lua(l);
	sol::protected_function_result ret;
	lua.open_libraries(sol::lib::base, sol::lib::debug);
	{
		int x = 0;
		lua.set_function("beep", [&x] { ++x; });
		lua.script("beep()");
		printf("c++ beep result %d\n", x);
	}
	
	ret = lua.script_file("LuaScript/test_sol.lua");
}

#include "Common/Geometry/GeometryUtils.h"
void test(int a, float b)
{
	Vector2 axis_point = Vector2(10, 10);
	Vector2 axis_dir = Vector2(1, 1);
	Vector2 test_world_point = Vector2(11, 12);
	Vector2 test_object_point = Vector2(2, 3);

	Axis2 axis_1; axis_1.original_point = axis_point; axis_1.direction = axis_dir;
	Axis2 axis_2; axis_2.original_point = axis_point + Vector2(1, 2); axis_2.direction = axis_dir + Vector2(1, 2);
	{
		GeometryUtils::DeltaAngle(Vector2(1, 1), Vector2(1, 1));
		float ret = GeometryUtils::DeltaAngle(Vector2(1, 1), Vector2(-1, -1));
		printf("%f", ret);
		GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(0, -1));
		GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(1, 1));
		GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(-1, 1));
		GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(-1, -1));
		GeometryUtils::DeltaAngle(Vector2(0, 1), Vector2(1, -1));
	}
	{
		Vector2 ret3;
		Axis2 y_axis; y_axis.direction = Vector2::up;
		GeometryUtils::AxisPointMoveRotate(y_axis, axis_1, test_world_point, ret3);
		Vector2 ret4;
		GeometryUtils::AxisPointRotateMove(axis_1, y_axis, ret3, ret4);
		int a = 0;
		++a;
	}
	{
		Vector2 ret;
		Vector2 *p_ret = &ret;
		GeometryUtils::AxisPointMoveRotate(axis_1, axis_2, &test_world_point, 1, &p_ret, 1);
		int a = 0;
		++a;
	}
	{
		Vector2 ret;
		Vector2 *p_ret = &ret;
		GeometryUtils::AxisPointMoveRotate(axis_1, axis_2, test_world_point, ret);
		int a = 0;
		++a;
	}

	{
		OBB2 obb2 = OBB2(Vector2(0, 0), Vector2(0.01, 0.95), 10, 20);
		float f1, f2;
		GeometryUtils::ProjectOBB2OnAxis(Axis2::y_axis, obb2, &f1, &f2);
		
		float f3, f4;
		GeometryUtils::ProjectOBB2OnAxis(axis_2, obb2, &f3, &f4);
		++f4;

	}
}

int main(int argc, char **argv)
{
	{
		auto t = std::make_tuple(1, 2);
		Tuple::Apply(test, t);
	}

	L = luaL_newstate();
	TestSol(L);
	lua_close(L); L = nullptr;

	if (argc <= 2)
	{
		printf("cmd foramt : executable log_cfg_file cfg_dir\n");
		exit(1);
	}

	MemoryUtil::Init();

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
	signal(SIGINT, QuitGame);
	signal(SIGBREAK, QuitGame);
#else
	signal(SIGINT, QuitGame);
	signal(SIGPIPE, SIG_IGN);
#endif

	std::srand(time(NULL));
	std::vector<std::string, StlAllocator<std::string>> params;
	params.push_back(argv[1]);
	params.push_back(argv[2]);


	server_logic = new GameServerLogic();
	server_logic->SetInitParams(&params);
	server_logic->Loop();
	delete server_logic;
	MemoryUtil::Destroy();
}