#include <iostream>
#include <functional>
#include <chrono>
#include "lua.hpp"

#include "lua_help.hpp"
#include "tests/PalindromeTest.hpp"
#include "tests/ObjectTest.hpp"
#include "tests/CPP_FunctionTest.hpp"


int main() {
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);

	int count;
	std::cin >> count;
	//Add 2 because will remove first and last result because better for tests
	count += 2;

	CPP_FunctionTest test(lua);
	std::chrono::nanoseconds lua_total{};
	std::chrono::nanoseconds cpp_total{};
	
	int max = (1000);
	
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
//		else std::cout << "!!IGNORED!! ";
//		
//		std::cout<<"CPP: " << cpp_time.count() << " ns , LUA: " << lua_time.count() << " ns" << std::endl;
	}
	
	auto cpp_average = cpp_total/(count-2);
	auto lua_average = lua_total/(count-2);
	
	printf("\n \n");
	std::cout << "CPP average: " << cpp_average.count() << " ns --- LUA average: " << lua_average.count() << " ns" << std::endl; 
	std::cout << "CPP total: " << cpp_total.count() << " ns --- LUA total: " << lua_total.count() << " ns" << std::endl;
	

	lua_close(lua);
	return 0;
}


