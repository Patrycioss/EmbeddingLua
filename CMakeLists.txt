cmake_minimum_required(VERSION 3.24.2)
project(LuaTesting)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lua-5.4.4)

set(TESTS
        "tests/PalindromeTest.hpp"
        tests/Timers.hpp tests/Test.hpp tests/ObjectTest.hpp)


add_executable(LuaTesting main.cpp ${TESTS})

file(COPY lua_files DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(LuaTesting LuaLib)