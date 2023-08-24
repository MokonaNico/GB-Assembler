cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(GB-Assembler VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(GB-Assembler src/main.cpp
        src/CommandLineParser.cpp
        src/CommandLineParser.hpp
        src/Lexer.cpp
        src/Lexer.hpp
        src/Assembler.cpp
        src/Assembler.hpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
