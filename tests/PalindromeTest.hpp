#include "Test.hpp"

class PalindromeTest : Test
{
private:
	static bool check_if_palindrome_better(const int & a)
	{
		const std::string string = std::to_string(a);
		std::string string_reverse;

		for (int i = (int)(string.length()) - 1; i >= 0; i--)
			string_reverse.push_back(string[i]);

		return string == string_reverse;
	}

	static std::vector<int> get_palindromes_until(const int& pMax)
	{
		std::vector<int> palindromes;

		for (int i = 0; i < pMax; i++)
		{
			if (check_if_palindrome_better(i)) {
				palindromes.push_back(i);
			}
		}
		return palindromes;
	}
	
public:
	
	explicit PalindromeTest(lua_State* state) : Test(state,"palindrome.lua"){};
	
	std::chrono::nanoseconds cpp_test(const int& pMax) 
	{
		m_cppTimer.Start();
		std::vector<int> palindromes = get_palindromes_until(pMax);
		return m_cppTimer.Stop();
	}
	
	std::chrono::nanoseconds lua_test(const int& pMax)
	{
		m_luaTimer.Start();
		lua_getglobal(m_lua, "GetPalindromesUntil");
		lua_pushnumber(m_lua, pMax);
		
		if (CheckLua(m_lua, lua_pcall(m_lua, 1,1,0)))
		{
			lua_pushvalue(m_lua, -1);
			lua_pushnil(m_lua);
			
			std::vector<int> palindromes;
			
			while (lua_next(m_lua, -2))
			{
				lua_pushvalue(m_lua, -2);
				palindromes.push_back((int) lua_tonumber(m_lua,-2));
				lua_pop(m_lua, 2);
			}
			lua_pop(m_lua, 1);
		}
		return m_luaTimer.Stop();
	}

//				printf("%d-", (int)lua_tointeger(m_lua,-2));
	
};