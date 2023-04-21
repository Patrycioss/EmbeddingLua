cmake_minimum_required(VERSION 3.24.2)
project(LuaTesting)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lua-5.4.4)

set(src/tests
        "src/tests/PalindromeTest.hpp"
        src/tests/Timers.hpp src/tests/Test.hpp src/tests/ObjectTest.hpp src/tests/CPP_FunctionTest.hpp src/lua_tests.hpp)


add_executable(LuaTesting main.cpp ${TESTS})

file(COPY lua_files DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(LuaTesting LuaLib)