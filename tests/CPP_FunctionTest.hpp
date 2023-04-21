#pragma once

#include "Test.hpp"


int function(lua_State* pState)
{
	return 0;
}

class CPP_FunctionTest : Test
{
public:
	explicit CPP_FunctionTest(lua_State* lua) : Test(lua, "cpp_function_test.lua")
	{
		lua_register(lua, "cpp_function", function);
	}
	
	std::chrono::nanoseconds cpp_test(const int& pTimes)
	{
		m_cppTimer.Start();
		for (int i = 0; i < pTimes; i++) function(m_lua);
		return m_cppTimer.Stop();
	}
	
	std::chrono::nanoseconds lua_test(const int& pTimes)
	{
		m_luaTimer.Start();
		lua_getglobal(m_lua, "call_cpp_function");
		lua_pushnumber(m_lua, pTimes);
		CheckLua(m_lua, lua_pcall(m_lua, 1,1,0));
		return m_luaTimer.Stop();
	}
};