/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"

#include <iostream>
#include <string>
#include <vector>
#include "ast.h"

using namespace std;

// External lexer function
extern int yylex();
// Error handling function
void yyerror(const char *s);

// Global root of the AST
Program* root = nullptr;

#line 88 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_FLOAT_LIT = 5,                  /* FLOAT_LIT  */
  YYSYMBOL_KW_INT = 6,                     /* KW_INT  */
  YYSYMBOL_KW_FLOAT = 7,                   /* KW_FLOAT  */
  YYSYMBOL_KW_RETURN = 8,                  /* KW_RETURN  */
  YYSYMBOL_KW_IF = 9,                      /* KW_IF  */
  YYSYMBOL_KW_ELSE = 10,                   /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 11,                  /* KW_WHILE  */
  YYSYMBOL_KW_PRINT = 12,                  /* KW_PRINT  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NEQ = 14,                       /* NEQ  */
  YYSYMBOL_LE = 15,                        /* LE  */
  YYSYMBOL_GE = 16,                        /* GE  */
  YYSYMBOL_ASSIGN = 17,                    /* ASSIGN  */
  YYSYMBOL_LT = 18,                        /* LT  */
  YYSYMBOL_GT = 19,                        /* GT  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MUL = 22,                       /* MUL  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_LPAREN = 26,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 27,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 28,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 29,                    /* RBRACE  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_program = 31,                   /* program  */
  YYSYMBOL_function_decl = 32,             /* function_decl  */
  YYSYMBOL_param_list = 33,                /* param_list  */
  YYSYMBOL_block = 34,                     /* block  */
  YYSYMBOL_statement_list = 35,            /* statement_list  */
  YYSYMBOL_statement = 36,                 /* statement  */
  YYSYMBOL_var_decl = 37,                  /* var_decl  */
  YYSYMBOL_assign_stmt = 38,               /* assign_stmt  */
  YYSYMBOL_return_stmt = 39,               /* return_stmt  */
  YYSYMBOL_if_stmt = 40,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 41,                /* while_stmt  */
  YYSYMBOL_print_stmt = 42,                /* print_stmt  */
  YYSYMBOL_expression = 43,                /* expression  */
  YYSYMBOL_term = 44,                      /* term  */
  YYSYMBOL_factor = 45,                    /* factor  */
  YYSYMBOL_arg_list = 46                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  100

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    66,    66,    67,    71,    72,    76,    77,    78,    79,
      80,    84,    88,    89,    93,    94,    95,    96,    97,    98,
      99,   103,   104,   108,   112,   116,   117,   121,   125,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   141,   142,
     143,   147,   148,   149,   150,   151,   155,   156,   157
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM",
  "FLOAT_LIT", "KW_INT", "KW_FLOAT", "KW_RETURN", "KW_IF", "KW_ELSE",
  "KW_WHILE", "KW_PRINT", "EQ", "NEQ", "LE", "GE", "ASSIGN", "LT", "GT",
  "PLUS", "MINUS", "MUL", "DIV", "SEMICOLON", "COMMA", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "$accept", "program", "function_decl", "param_list",
  "block", "statement_list", "statement", "var_decl", "assign_stmt",
  "return_stmt", "if_stmt", "while_stmt", "print_stmt", "expression",
  "term", "factor", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -86,     1,   -86,     6,    12,   -86,     2,    33,    -4,    -4,
      35,    39,     9,    10,   -86,   -86,    38,    51,    51,    66,
      86,   -86,   -86,   -86,   -86,   -86,    11,   114,   103,   115,
      28,   106,   107,   108,   -86,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,    28,   111,   112,   113,   -86,   -86,    28,
      77,    25,   -86,    28,    28,    28,    89,   -86,   -86,    28,
      37,    28,    28,    28,    28,    28,    28,    28,    28,   -86,
      28,    28,    47,    57,    67,   -86,   101,    16,   -86,    25,
      25,    25,    25,    25,    25,    25,    25,   -86,   -86,    18,
      18,   116,    28,   -86,   127,   -86,   -86,   101,    18,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     3,     0,     0,     6,     6,
       0,     0,     0,     0,     7,     8,     0,     0,     0,     0,
       0,    12,     4,     5,     9,    10,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    20,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,    43,    41,    42,     0,
       0,    37,    40,     0,     0,     0,     0,    21,    22,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    24,
       0,     0,     0,     0,     0,    23,    47,     0,    45,    31,
      32,    33,    34,    35,    36,    29,    30,    38,    39,     0,
       0,     0,     0,    44,    25,    27,    28,    48,     0,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   -86,   129,    82,   -86,   -85,   -86,   -86,   -86,
     -86,   -86,   -86,   -43,    62,    41,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     5,    12,    35,    26,    36,    37,    38,    39,
      40,    41,    42,    50,    51,    52,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      56,     2,    10,    11,    94,    95,    60,     3,     4,     6,
      72,    73,    74,    99,    27,     7,    76,    28,    29,    30,
      31,    27,    32,    33,    28,    29,    30,    31,     8,    32,
      33,    46,    47,    48,    16,    16,    17,    18,    14,    21,
      34,    92,    15,    93,    19,    20,    21,    70,    71,    97,
      61,    62,    63,    64,    49,    65,    66,    67,    68,     9,
      61,    62,    63,    64,    78,    65,    66,    67,    68,    24,
      61,    62,    63,    64,    89,    65,    66,    67,    68,    21,
      61,    62,    63,    64,    90,    65,    66,    67,    68,    25,
      61,    62,    63,    64,    91,    65,    66,    67,    68,    22,
      23,    69,    61,    62,    63,    64,    44,    65,    66,    67,
      68,    87,    88,    75,    61,    62,    63,    64,    45,    65,
      66,    67,    68,    79,    80,    81,    82,    83,    84,    85,
      86,    43,    53,    54,    55,    57,    58,    98,    13,    59,
      96
};

static const yytype_int8 yycheck[] =
{
      43,     0,     6,     7,    89,    90,    49,     6,     7,     3,
      53,    54,    55,    98,     3,     3,    59,     6,     7,     8,
       9,     3,    11,    12,     6,     7,     8,     9,    26,    11,
      12,     3,     4,     5,    25,    25,    27,    27,     3,    28,
      29,    25,     3,    27,     6,     7,    28,    22,    23,    92,
      13,    14,    15,    16,    26,    18,    19,    20,    21,    26,
      13,    14,    15,    16,    27,    18,    19,    20,    21,     3,
      13,    14,    15,    16,    27,    18,    19,    20,    21,    28,
      13,    14,    15,    16,    27,    18,    19,    20,    21,     3,
      13,    14,    15,    16,    27,    18,    19,    20,    21,    17,
      18,    24,    13,    14,    15,    16,     3,    18,    19,    20,
      21,    70,    71,    24,    13,    14,    15,    16,     3,    18,
      19,    20,    21,    61,    62,    63,    64,    65,    66,    67,
      68,    17,    26,    26,    26,    24,    24,    10,     9,    26,
      24
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,     0,     6,     7,    32,     3,     3,    26,    26,
       6,     7,    33,    33,     3,     3,    25,    27,    27,     6,
       7,    28,    34,    34,     3,     3,    35,     3,     6,     7,
       8,     9,    11,    12,    29,    34,    36,    37,    38,    39,
      40,    41,    42,    17,     3,     3,     3,     4,     5,    26,
      43,    44,    45,    26,    26,    26,    43,    24,    24,    26,
      43,    13,    14,    15,    16,    18,    19,    20,    21,    24,
      22,    23,    43,    43,    43,    24,    43,    46,    27,    44,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    27,
      27,    27,    25,    27,    36,    36,    24,    43,    10,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    31,    32,    32,    33,    33,    33,    33,
      33,    34,    35,    35,    36,    36,    36,    36,    36,    36,
      36,    37,    37,    38,    39,    40,    40,    41,    42,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    44,    44,
      44,    45,    45,    45,    45,    45,    46,    46,    46
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     6,     6,     0,     2,     2,     4,
       4,     3,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     4,     3,     5,     7,     5,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     1,     1,     1,     4,     3,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 66 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { root = new Program(); (yyval.prog) = root; }
#line 1185 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 3: /* program: program function_decl  */
#line 67 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                            { (yyvsp[-1].prog)->addFunction((yyvsp[0].func)); root = (yyvsp[-1].prog); (yyval.prog) = (yyvsp[-1].prog); }
#line 1191 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 4: /* function_decl: KW_INT ID LPAREN param_list RPAREN block  */
#line 71 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                             { (yyval.func) = new FunctionDecl("int", (yyvsp[-4].sval), (yyvsp[-2].params), (yyvsp[0].block)); free((yyvsp[-4].sval)); }
#line 1197 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 5: /* function_decl: KW_FLOAT ID LPAREN param_list RPAREN block  */
#line 72 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                                 { (yyval.func) = new FunctionDecl("float", (yyvsp[-4].sval), (yyvsp[-2].params), (yyvsp[0].block)); free((yyvsp[-4].sval)); }
#line 1203 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 6: /* param_list: %empty  */
#line 76 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { (yyval.params) = nullptr; }
#line 1209 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 7: /* param_list: KW_INT ID  */
#line 77 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { (yyval.params) = new vector<Parameter*>(); (yyval.params)->push_back(new Parameter("int", (yyvsp[0].sval))); free((yyvsp[0].sval)); }
#line 1215 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 8: /* param_list: KW_FLOAT ID  */
#line 78 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                  { (yyval.params) = new vector<Parameter*>(); (yyval.params)->push_back(new Parameter("float", (yyvsp[0].sval))); free((yyvsp[0].sval)); }
#line 1221 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 9: /* param_list: param_list COMMA KW_INT ID  */
#line 79 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                 { (yyval.params) = (yyvsp[-3].params); (yyval.params)->push_back(new Parameter("int", (yyvsp[0].sval))); free((yyvsp[0].sval)); }
#line 1227 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 10: /* param_list: param_list COMMA KW_FLOAT ID  */
#line 80 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                   { (yyval.params) = (yyvsp[-3].params); (yyval.params)->push_back(new Parameter("float", (yyvsp[0].sval))); free((yyvsp[0].sval)); }
#line 1233 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 11: /* block: LBRACE statement_list RBRACE  */
#line 84 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                 { (yyval.block) = (yyvsp[-1].block); }
#line 1239 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 12: /* statement_list: %empty  */
#line 88 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { (yyval.block) = new Block(); }
#line 1245 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 13: /* statement_list: statement_list statement  */
#line 89 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                               { (yyvsp[-1].block)->addStatement((yyvsp[0].stmt)); (yyval.block) = (yyvsp[-1].block); }
#line 1251 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 14: /* statement: var_decl  */
#line 93 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1257 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 15: /* statement: assign_stmt  */
#line 94 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1263 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 16: /* statement: return_stmt  */
#line 95 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1269 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 17: /* statement: if_stmt  */
#line 96 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1275 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 18: /* statement: while_stmt  */
#line 97 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1281 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 19: /* statement: print_stmt  */
#line 98 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1287 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 20: /* statement: block  */
#line 99 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
            { (yyval.stmt) = (yyvsp[0].block); }
#line 1293 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 21: /* var_decl: KW_INT ID SEMICOLON  */
#line 103 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                        { (yyval.stmt) = new VarDecl("int", (yyvsp[-1].sval)); free((yyvsp[-1].sval)); }
#line 1299 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 22: /* var_decl: KW_FLOAT ID SEMICOLON  */
#line 104 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                            { (yyval.stmt) = new VarDecl("float", (yyvsp[-1].sval)); free((yyvsp[-1].sval)); }
#line 1305 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 23: /* assign_stmt: ID ASSIGN expression SEMICOLON  */
#line 108 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                   { (yyval.stmt) = new AssignStmt((yyvsp[-3].sval), (yyvsp[-1].expr)); free((yyvsp[-3].sval)); }
#line 1311 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 24: /* return_stmt: KW_RETURN expression SEMICOLON  */
#line 112 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                   { (yyval.stmt) = new ReturnStmt((yyvsp[-1].expr)); }
#line 1317 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 25: /* if_stmt: KW_IF LPAREN expression RPAREN statement  */
#line 116 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                             { (yyval.stmt) = new IfStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1323 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 26: /* if_stmt: KW_IF LPAREN expression RPAREN statement KW_ELSE statement  */
#line 117 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                                                 { (yyval.stmt) = new IfStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt)); }
#line 1329 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 27: /* while_stmt: KW_WHILE LPAREN expression RPAREN statement  */
#line 121 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                                { (yyval.stmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt)); }
#line 1335 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 28: /* print_stmt: KW_PRINT LPAREN expression RPAREN SEMICOLON  */
#line 125 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                                { (yyval.stmt) = new PrintStmt((yyvsp[-2].expr)); }
#line 1341 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 29: /* expression: expression PLUS term  */
#line 129 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "+", (yyvsp[0].expr)); }
#line 1347 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 30: /* expression: expression MINUS term  */
#line 130 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                            { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "-", (yyvsp[0].expr)); }
#line 1353 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 31: /* expression: expression EQ term  */
#line 131 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "==", (yyvsp[0].expr)); }
#line 1359 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 32: /* expression: expression NEQ term  */
#line 132 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                          { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "!=", (yyvsp[0].expr)); }
#line 1365 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 33: /* expression: expression LE term  */
#line 133 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "<=", (yyvsp[0].expr)); }
#line 1371 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 34: /* expression: expression GE term  */
#line 134 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), ">=", (yyvsp[0].expr)); }
#line 1377 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 35: /* expression: expression LT term  */
#line 135 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "<", (yyvsp[0].expr)); }
#line 1383 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 36: /* expression: expression GT term  */
#line 136 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                         { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), ">", (yyvsp[0].expr)); }
#line 1389 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 37: /* expression: term  */
#line 137 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1395 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 38: /* term: term MUL factor  */
#line 141 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                    { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "*", (yyvsp[0].expr)); }
#line 1401 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 39: /* term: term DIV factor  */
#line 142 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                      { (yyval.expr) = new BinaryExpr((yyvsp[-2].expr), "/", (yyvsp[0].expr)); }
#line 1407 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 40: /* term: factor  */
#line 143 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 1413 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 41: /* factor: NUM  */
#line 147 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
        { (yyval.expr) = new Number((yyvsp[0].ival)); }
#line 1419 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 42: /* factor: FLOAT_LIT  */
#line 148 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { (yyval.expr) = new Float((yyvsp[0].fval)); }
#line 1425 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 43: /* factor: ID  */
#line 149 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
         { (yyval.expr) = new Variable((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1431 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 44: /* factor: ID LPAREN arg_list RPAREN  */
#line 150 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                { (yyval.expr) = new CallExpr((yyvsp[-3].sval), (yyvsp[-1].args)); free((yyvsp[-3].sval)); }
#line 1437 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 45: /* factor: LPAREN expression RPAREN  */
#line 151 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                               { (yyval.expr) = (yyvsp[-1].expr); }
#line 1443 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 46: /* arg_list: %empty  */
#line 155 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                { (yyval.args) = nullptr; }
#line 1449 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 47: /* arg_list: expression  */
#line 156 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                 { (yyval.args) = new vector<Expression*>(); (yyval.args)->push_back((yyvsp[0].expr)); }
#line 1455 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;

  case 48: /* arg_list: arg_list COMMA expression  */
#line 157 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"
                                { (yyval.args) = (yyvsp[-2].args); (yyval.args)->push_back((yyvsp[0].expr)); }
#line 1461 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"
    break;


#line 1465 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/out/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 160 "/home/ghirahim/Documents/Dersler/Compiler Design/Proje/MiniCCompiler/src/parser.y"


void yyerror(const char *s) {
    cerr << "Error: " << s << endl;
}

int main(int argc, char** argv) {
    bool dotOutput = false;
    if (argc > 1 && string(argv[1]) == "-dot") {
        dotOutput = true;
    }

    if (!dotOutput) cout << "Starting parse..." << endl;
    
    if (yyparse() == 0) {
        if (!dotOutput) cout << "Parse successful" << endl;
        if (root) {
            if (dotOutput) {
                int count = 0;
                root->generateDOT(cout, count);
            } else {
                cout << "Printing AST..." << endl;
                root->print();
            }
            delete root; 
        } else {
            if (!dotOutput) cout << "Root is null" << endl;
        }
    } else {
        if (!dotOutput) cout << "Parse failed" << endl;
    }
    return 0;
}
