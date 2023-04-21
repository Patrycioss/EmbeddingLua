#include <iostream>
#include <functional>
#include <chrono>
#include "lua.hpp"

#include "lua_help.hpp"
#include "tests/PalindromeTest.hpp"
#include "tests/ObjectTest.hpp"


int main() {
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);

	int count;
	std::cin >> count;
	//Add 2 because will remove first and last result because better for tests
	count += 2;

	ObjectTest test(lua);
	std::chrono::nanoseconds lua_total{};
	std::chrono::nanoseconds cpp_total{};
	
	int max = (10);
	
	for (int i = 0; i < count; i++)
	{
		std::chrono::nanoseconds cpp_time = test.cpp_test(max);
		std::chrono::nanoseconds lua_time = test.lua_test(max);

		//Ignore first and last result
		if (i != 0 && i != count-1)
		{
			cpp_total += cpp_time;
			lua_total += lua_time;
		}
		else std::cout << "!!IGNORED!! ";
		
		std::cout<<"CPP: " << cpp_time.count() << " ns , LUA: " << lua_time.count() << " ns" << std::endl;
	}
	
	auto cpp_average = cpp_total/(count-2);
	auto lua_average = lua_total/(count-2);
	
	printf("\n \n");
	std::cout << "CPP average: " << cpp_average.count() << " ns --- LUA average: " << lua_average.count() << " ns" << std::endl; 
	std::cout << "CPP total: " << cpp_total.count() << " ns --- LUA total: " << lua_total.count() << " ns" << std::endl;
	
//	const std::function lua_test = lua_test_calculation2;
//	const std::function cpp_test = cpp_test_calculation2;
//
//
//


//	NanoTimer lua_timer;
//	NanoTimer cpp_timer;
//
//	for (int i = 0; i < count; i++)
//	{
//		lua_timer.Start();
//		const auto lua_val = lua_test(lua);
//		const std::chrono::nanoseconds lua_time = lua_timer.Stop();
//		lua_pop(lua, lua_gettop(lua));
//
//		cpp_timer.Start();
//		const auto cpp_val = cpp_test();
//		const auto cpp_time = cpp_timer.Stop();
//
//
//
//		if (i != 0 && i != count - 1)
//		{
//			lua_total += lua_time;
//			cpp_total += cpp_time;
//
//			std::cout << "LUA: " << lua_time << ", CPP: " << cpp_time << std::endl;
//		}
//
//	}
//
//	const auto average_lua = lua_total / (count-2);
//	const auto average_cpp = cpp_total / (count - 2);
//
//
//	std::cout << "Lua average: " << average_lua << " nanoseconds" << std::endl;
//	std::cout << "CPP average: " << average_cpp << " nanoseconds" << std::endl;

	lua_close(lua);
	return 0;
}


