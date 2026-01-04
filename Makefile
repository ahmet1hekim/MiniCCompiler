CXX = g++
CXXFLAGS = -std=c++17 -Wno-register -Iinclude -Ibuild

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = minic

all: $(TARGET)

$(TARGET): $(BUILDDIR)/lex.yy.c $(BUILDDIR)/parser.tab.c
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(BUILDDIR)/parser.tab.c $(BUILDDIR)/lex.yy.c

$(BUILDDIR)/parser.tab.c $(BUILDDIR)/parser.tab.h: $(SRCDIR)/parser.y
	mkdir -p $(BUILDDIR)
	bison -d $(SRCDIR)/parser.y -o $(BUILDDIR)/parser.tab.c

$(BUILDDIR)/lex.yy.c: $(SRCDIR)/lexer.l $(BUILDDIR)/parser.tab.h
	mkdir -p $(BUILDDIR)
	flex -o $(BUILDDIR)/lex.yy.c $(SRCDIR)/lexer.l

clean:
	rm -rf $(BUILDDIR) $(TARGET) ast.dot ast.png
