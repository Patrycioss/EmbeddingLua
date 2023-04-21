#pragma once
#include "Test.hpp"
#include "cstring"

class Player
{
public:
	int number = 0;
	explicit Player(int pNumber){
		number = pNumber;
	};
};

class PlayerTest : Test
{
public:
	explicit PlayerTest(lua_State* lua) : Test(lua, "player.lua"){};
	
	std::chrono::nanoseconds cpp_test(const int& pCount)
	{
		m_luaTimer.Start();
		
		std::vector<Player> players;
		
		for (int i = 0; i < pCount; i++)
		{
			players.emplace_back(i);
		}
		
//		for (Player& player : players)
//		{
//			printf("%d, ", player.number);
//		}
//		printf("\n");
		
		return m_luaTimer.Stop();
	}
	
	std::chrono::nanoseconds lua_test(const int& pCount)
	{
		m_luaTimer.Start();
		lua_getglobal(m_lua, "SpawnPlayers");
		lua_pushnumber(m_lua, pCount);
		
		if (CheckLua(m_lua, lua_pcall(m_lua, 1,1,0)))
		{
			
			lua_pushvalue(m_lua, -1); //-1=> objectTable;

			lua_pushnil(m_lua); //-1 => nil, -2 => objectTable;
			
			
			std::vector<int> numbers;
			
			while (lua_next(m_lua, -2)) // -1 => objectValue, -2 => objectKey, -3 => objectTable
			{
				if (lua_istable(m_lua, -1))
				{
					lua_pushnil(m_lua); // -1 => nil, -2 => objectValue, -3 => objectKey, -4 => objectTable
					
					while(lua_next(m_lua,-2)) // -1 => varValue, -2 => varKey, -3 => objectValue, -4 => objectKey, -5 => objectTable 
					{
						numbers.push_back(lua_tonumber(m_lua,-1));
						lua_pop(m_lua,1); // -1 => varKey, -2 => objectValue, -3 => objectKey, -4 => objectTable
					}//Pops varKey
				}
				lua_pop(m_lua, 1); // -1 => objectKey, -2 => objectTable 
			}//Pops objectKey
			
			lua_pop(m_lua, 1); // Pops objectTable
			
			for (int& i : numbers)
			{
				std::cout << i << ", ";
			}
		}
		
		return m_luaTimer.Stop();
	}
};