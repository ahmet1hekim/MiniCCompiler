cmake_minimum_required(VERSION 3.16)
project(MiniC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

find_package(FLEX REQUIRED)

# Input lexer file
set(LEXER_SRC ${CMAKE_SOURCE_DIR}/src/minicpl.lex)

# Generated lexer output file paths (in out/)
set(LEXER_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/out)
set(LEXER_CPP ${LEXER_OUTPUT_DIR}/lex.yy.cc)
set(LEXER_HPP ${LEXER_OUTPUT_DIR}/lexer.hpp)  # if you generate header, else ignore

# Use FLEX_TARGET to generate lexer files in out/
FLEX_TARGET(MiniCLexer ${LEXER_SRC} ${LEXER_CPP} COMPILE_FLAGS --outfile=${LEXER_CPP})

# Add executable
add_executable(minic ${LEXER_CPP})

# Include directory for lexer.hpp if needed
target_include_directories(minic PRIVATE ${LEXER_OUTPUT_DIR})

# Link libraries if needed (usually none for flex++ basic lexer)
# target_link_libraries(minic ...)
