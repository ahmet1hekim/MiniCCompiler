cmake_minimum_required(VERSION 3.16)
project(MiniC)

set(CMAKE_CXX_STANDARD 17)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Input files
set(LEXER_SRC "${CMAKE_SOURCE_DIR}/src/minicpl.lex")
set(PARSER_SRC "${CMAKE_SOURCE_DIR}/src/parser.y")
set(LEXER_MAIN "${CMAKE_SOURCE_DIR}/src/lexer_main.cpp")
# New source file for CodeGen
set(CODEGEN_SRC "${CMAKE_SOURCE_DIR}/src/minic_codegen.cpp")

# Output directories
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY "${OUTPUT_DIR}")

set(PARSER_CPP "${CMAKE_BINARY_DIR}/parser.cpp")
set(PARSER_HPP "${CMAKE_BINARY_DIR}/parser.hpp")
set(LEXER_CPP "${CMAKE_BINARY_DIR}/lex.yy.cc")

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

# Include directories
include_directories("${CMAKE_BINARY_DIR}") # For parser.hpp
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/src")

# Target: Parser
# Links the parser generated code and the lexer generated code.
# The parser.y contains the main() function for this target.
add_executable(parser 
    "${PARSER_CPP}"
    "${LEXER_CPP}"
    "${CODEGEN_SRC}"
)
set_target_properties(parser PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(parser ${llvm_libs})

# Target: Lexer
# Links the lexer generated code with our new lexer_main.cpp driver.
# Does NOT link parser.cpp, but relies on parser.hpp (header only) for token definitions.
add_executable(lexer
    "${LEXER_MAIN}"
    "${LEXER_CPP}"
)
# We need to make sure parser.hpp is generated before compiling lexer sources
add_dependencies(lexer parser)
set_target_properties(lexer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
