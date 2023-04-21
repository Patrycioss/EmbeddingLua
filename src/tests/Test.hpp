#pragma once

#include <string>
#include "lua.hpp"
#include "../lua_help.hpp"
#include "Timers.hpp"
#include <chrono>
#include <vector>

class Test
{
protected:
	lua_State* m_lua;
	NanoTimer m_luaTimer;
	NanoTimer m_cppTimer;
	
public:
	Test(lua_State* luaState, const char* filePath)
	{
		m_lua = luaState;
		std::string path = "lua_files/";
		path += filePath;
		
		CheckLua(m_lua,luaL_dofile(m_lua, path.c_str()));
	}
};