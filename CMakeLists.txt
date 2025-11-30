cmake_minimum_required(VERSION 3.16)
project(MiniC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out/bin")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Input files
set(LEXER_SRC "${CMAKE_SOURCE_DIR}/src/minicpl.lex")
set(PARSER_SRC "${CMAKE_SOURCE_DIR}/src/parser.y")

# Output directories
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/out")
file(MAKE_DIRECTORY "${OUTPUT_DIR}")

set(PARSER_CPP "${OUTPUT_DIR}/parser.cpp")
set(PARSER_HPP "${OUTPUT_DIR}/parser.hpp")
set(LEXER_CPP "${OUTPUT_DIR}/lex.yy.cc")

# Generate Parser
add_custom_command(
    OUTPUT "${PARSER_CPP}" "${PARSER_HPP}"
    COMMAND ${BISON_EXECUTABLE} --defines=${PARSER_HPP} -o ${PARSER_CPP} ${PARSER_SRC}
    DEPENDS "${PARSER_SRC}"
    COMMENT "Generating parser.cpp and parser.hpp"
    VERBATIM
)

# Generate Lexer
add_custom_command(
    OUTPUT "${LEXER_CPP}"
    COMMAND ${FLEX_EXECUTABLE} -o ${LEXER_CPP} ${LEXER_SRC}
    DEPENDS "${LEXER_SRC}" "${PARSER_HPP}"
    COMMENT "Generating lex.yy.cc"
    VERBATIM
)

# Add executable
add_executable(minic 
    "${PARSER_CPP}"
    "${LEXER_CPP}"
)

# Include directories
target_include_directories(minic PRIVATE "${OUTPUT_DIR}" "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/include")
