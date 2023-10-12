cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(GB-Assembler VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(ASSEMBLER_SOURCE_FILES
        src/CommandLineParser.cpp
        src/CommandLineParser.hpp
        src/Lexer.cpp
        src/Lexer.hpp
        src/Assembler.cpp
        src/Assembler.hpp
)

add_executable(GB-Assembler src/main.cpp ${ASSEMBLER_SOURCE_FILES})

set(ASSEMBLER_TEST_FILES
        tests/Tests.cpp
        tests/Tests.h
        tests/GeneratedTests.h
)

add_executable(GB-Tests ${ASSEMBLER_TEST_FILES} ${ASSEMBLER_SOURCE_FILES} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
