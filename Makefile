# Makefile for Mini C Compiler (Project 3 with LLVM)

CXX = g++
LLVM_CONFIG = llvm-config
CXXFLAGS = -std=c++17 -Wno-register -Iinclude -Ibuild `$(LLVM_CONFIG) --cxxflags`
LDFLAGS = `$(LLVM_CONFIG) --ldflags --system-libs --libs core native`

SRCS = src/lexer.l src/parser.y src/codegen.cpp src/ast_codegen.cpp
OBJS = build/lex.yy.o build/parser.tab.o build/codegen.o build/ast_codegen.o

TARGET = minic

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build/parser.tab.c build/parser.tab.h: src/parser.y
	mkdir -p build
	bison -d src/parser.y -o build/parser.tab.c

build/lex.yy.c: src/lexer.l build/parser.tab.h
	mkdir -p build
	flex -o build/lex.yy.c src/lexer.l

build/parser.tab.o: build/parser.tab.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/lex.yy.o: build/lex.yy.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/codegen.o: src/codegen.cpp include/codegen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/ast_codegen.o: src/ast_codegen.cpp include/ast.h include/codegen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET) ast.dot ast.png program program.ll program.s outputs
