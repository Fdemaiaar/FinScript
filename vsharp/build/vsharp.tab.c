/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "src/vsharp.y"

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
int yylex(void);
extern int yylineno;
void yyerror(const char *s);
Node *program_root;

#line 81 "build/vsharp.tab.c"

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

#include "vsharp.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_DATE = 6,                       /* DATE  */
  YYSYMBOL_BOOL_LITERAL = 7,               /* BOOL_LITERAL  */
  YYSYMBOL_ENTITY = 8,                     /* ENTITY  */
  YYSYMBOL_CAP_TABLE = 9,                  /* CAP_TABLE  */
  YYSYMBOL_DEAL = 10,                      /* DEAL  */
  YYSYMBOL_DEBT_INSTRUMENT = 11,           /* DEBT_INSTRUMENT  */
  YYSYMBOL_COST_OF_DEBT = 12,              /* COST_OF_DEBT  */
  YYSYMBOL_COST_OF_EQUITY = 13,            /* COST_OF_EQUITY  */
  YYSYMBOL_VALUATION = 14,                 /* VALUATION  */
  YYSYMBOL_PRINT = 15,                     /* PRINT  */
  YYSYMBOL_VAR = 16,                       /* VAR  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_FOR = 20,                       /* FOR  */
  YYSYMBOL_NPV = 21,                       /* NPV  */
  YYSYMBOL_IRR = 22,                       /* IRR  */
  YYSYMBOL_WACC = 23,                      /* WACC  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NE = 25,                        /* NE  */
  YYSYMBOL_GT = 26,                        /* GT  */
  YYSYMBOL_LT = 27,                        /* LT  */
  YYSYMBOL_GE = 28,                        /* GE  */
  YYSYMBOL_LE = 29,                        /* LE  */
  YYSYMBOL_AND = 30,                       /* AND  */
  YYSYMBOL_OR = 31,                        /* OR  */
  YYSYMBOL_NOT = 32,                       /* NOT  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 34,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 35,                     /* COMMA  */
  YYSYMBOL_COLON = 36,                     /* COLON  */
  YYSYMBOL_LPAREN = 37,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 38,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 39,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 40,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 41,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 42,                  /* RBRACKET  */
  YYSYMBOL_43_ = 43,                       /* '+'  */
  YYSYMBOL_44_ = 44,                       /* '-'  */
  YYSYMBOL_45_ = 45,                       /* '*'  */
  YYSYMBOL_46_ = 46,                       /* '/'  */
  YYSYMBOL_UMINUS = 47,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_block = 50,                     /* block  */
  YYSYMBOL_statement_list = 51,            /* statement_list  */
  YYSYMBOL_statement = 52,                 /* statement  */
  YYSYMBOL_var_decl = 53,                  /* var_decl  */
  YYSYMBOL_entity_decl = 54,               /* entity_decl  */
  YYSYMBOL_cap_table_decl = 55,            /* cap_table_decl  */
  YYSYMBOL_cap_item_list = 56,             /* cap_item_list  */
  YYSYMBOL_cap_item = 57,                  /* cap_item  */
  YYSYMBOL_deal_decl = 58,                 /* deal_decl  */
  YYSYMBOL_debt_decl = 59,                 /* debt_decl  */
  YYSYMBOL_cost_debt_decl = 60,            /* cost_debt_decl  */
  YYSYMBOL_cost_equity_decl = 61,          /* cost_equity_decl  */
  YYSYMBOL_valuation_decl = 62,            /* valuation_decl  */
  YYSYMBOL_metric_call = 63,               /* metric_call  */
  YYSYMBOL_print_stmt = 64,                /* print_stmt  */
  YYSYMBOL_print_args = 65,                /* print_args  */
  YYSYMBOL_if_stmt = 66,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 67,                /* while_stmt  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_for_init = 69,                  /* for_init  */
  YYSYMBOL_expression_opt = 70,            /* expression_opt  */
  YYSYMBOL_expression = 71,                /* expression  */
  YYSYMBOL_array_lit = 72,                 /* array_lit  */
  YYSYMBOL_expr_list_opt = 73,             /* expr_list_opt  */
  YYSYMBOL_expr_list = 74,                 /* expr_list  */
  YYSYMBOL_date_lit = 75,                  /* date_lit  */
  YYSYMBOL_arg_list_opt = 76,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 77                   /* arg_list  */
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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if 1

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
#endif /* 1 */

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
#define YYLAST   491

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
       2,     2,    45,    43,     2,    44,     2,    46,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    49,    49,    50,    54,    55,    59,    60,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    85,    86,    90,    94,    98,    99,
     102,   105,   106,   107,   108,   109,   113,   114,   115,   119,
     121,   122,   127,   128,   131,   133,   137,   138,   139,   142,
     143,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   172,   173,
     174,   175,   176,   177,   178,   179,   183,   184,   185,   186,
     187,   190,   193,   194,   195,   196
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "NUMBER",
  "STRING", "DATE", "BOOL_LITERAL", "ENTITY", "CAP_TABLE", "DEAL",
  "DEBT_INSTRUMENT", "COST_OF_DEBT", "COST_OF_EQUITY", "VALUATION",
  "PRINT", "VAR", "IF", "ELSE", "WHILE", "FOR", "NPV", "IRR", "WACC", "EQ",
  "NE", "GT", "LT", "GE", "LE", "AND", "OR", "NOT", "ASSIGN", "SEMICOLON",
  "COMMA", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "program",
  "block", "statement_list", "statement", "var_decl", "entity_decl",
  "cap_table_decl", "cap_item_list", "cap_item", "deal_decl", "debt_decl",
  "cost_debt_decl", "cost_equity_decl", "valuation_decl", "metric_call",
  "print_stmt", "print_args", "if_stmt", "while_stmt", "for_stmt",
  "for_init", "expression_opt", "expression", "array_lit", "expr_list_opt",
  "expr_list", "date_lit", "arg_list_opt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    43,    45,    42,    47,   298
};
#endif

#define YYPACT_NINF (-59)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -59,   157,   -59,   -31,   -59,   -25,   -59,   -59,     2,    10,
      13,    16,    27,    28,    29,    -4,    31,    -2,     5,     6,
       8,    12,    19,   307,   307,   199,   307,   307,   -59,   -59,
      24,   -59,   -59,   -59,   -59,   -59,   -59,   -59,    30,    32,
     -59,   -59,   -59,   328,   -59,   -59,   307,   307,   -59,   307,
      -3,     0,    -3,    -3,    -3,    -3,    -3,   307,    11,   307,
     307,    82,   307,   307,   307,   -30,   -59,   -59,   339,   -59,
     241,   -59,   408,    23,    33,   -59,   -59,   -59,   -59,   307,
     307,   307,   307,   307,   307,   307,   307,   -59,   307,   307,
     307,   307,   -23,   408,     9,    43,   408,   -59,    64,   -59,
     -59,   -59,   -59,   -59,   -26,   408,   307,   362,   385,   -59,
      49,   408,    46,    52,    53,   -59,   -59,   -59,   -59,   307,
     439,   439,   439,   439,   439,   439,   445,   416,   -17,   -17,
     -59,   -59,   -59,   307,    -3,     1,   -59,   307,   -59,   408,
     283,   283,   307,   -59,   -59,   -59,   408,   408,   -59,   -59,
     -59,   408,    74,   -59,    59,   408,   283,   307,   -59,    56,
     283,   -59
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    72,    67,    69,    81,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    77,     0,    23,     3,
       0,     9,    10,    11,    12,    13,    14,    15,    74,     0,
      20,    21,    22,     0,    71,    70,     0,    82,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,    48,    82,    82,    82,    72,    74,    64,     0,     4,
       0,     6,    79,     0,    78,    65,     8,    16,    17,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,    63,    84,     0,    83,    75,    26,     0,    31,
      32,    33,    34,    35,     0,    40,     0,     0,     0,    46,
       0,    47,     0,     0,     0,    66,     5,     7,    76,     0,
      55,    56,    57,    58,    59,    60,    61,    62,    51,    52,
      53,    54,    73,     0,     0,     0,    28,     0,    39,    25,
       0,     0,    50,    36,    37,    38,    80,    85,    30,    27,
      29,    41,    42,    44,     0,    49,     0,    50,    43,     0,
       0,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -59,   -59,     7,   -59,   -24,    34,   -59,   -59,   -59,   -39,
     -59,   -59,   -59,   -59,   -59,    -1,   -59,   -59,   -59,   -59,
     -59,   -59,   -58,    -9,   -59,   -59,   -59,   -59,   -37,   -59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    28,    70,    29,    30,    31,    32,   135,   136,
      33,    34,    35,    36,    37,    66,    39,   104,    40,    41,
      42,   110,   154,    43,    44,    73,    74,    45,    94,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,    71,    46,    46,   134,    50,    47,    47,    25,   137,
      48,    49,   138,    51,    67,    68,    52,    72,    75,    53,
      88,    89,    90,    91,    38,   112,   113,   114,    90,    91,
      54,    55,    56,    57,    58,    59,    25,    92,    93,    98,
      96,   149,    60,    61,   106,    62,   117,   132,   105,    63,
     107,   108,   111,    93,    93,    93,    64,    97,    76,    99,
     100,   101,   102,   103,    77,   118,    78,   134,   119,    38,
     120,   121,   122,   123,   124,   125,   126,   127,   133,   128,
     129,   130,   131,   142,   143,    65,     4,     5,     6,     7,
     144,   145,   156,   157,   160,   109,   150,   139,    16,   159,
       0,     0,     0,    20,    21,    22,     0,     0,     0,     0,
     146,     0,     0,     0,    23,     0,   152,   153,     0,    24,
       0,     0,     0,    26,   147,     0,    27,     0,   151,     0,
       0,     0,   158,   155,     0,     0,   161,     0,     0,    38,
      38,   148,     0,     0,     0,     0,     0,     0,   155,     0,
       0,     0,     0,     0,     0,    38,     0,     2,     0,    38,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,    18,    19,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,     0,    24,     0,    25,     0,    26,     0,
       0,    27,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,    18,    19,
      20,    21,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    23,     0,     0,     0,     0,    24,     0,    25,    69,
      26,     0,     0,    27,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     0,
      18,    19,    20,    21,    22,     0,     0,     0,     0,     0,
       0,     0,     0,    23,     0,     0,     0,     0,    24,     0,
      25,   116,    26,     0,     0,    27,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     0,    18,    19,    20,    21,    22,     0,     0,     0,
      65,     4,     5,     6,     7,    23,     0,     0,     0,     0,
      24,     0,    25,     0,    26,     0,     0,    27,    20,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,     0,    24,     0,     0,     0,    26,     0,
       0,    27,    79,    80,    81,    82,    83,    84,    85,    86,
       0,     0,    87,    79,    80,    81,    82,    83,    84,    85,
      86,    88,    89,    90,    91,     0,     0,   115,     0,     0,
       0,     0,    88,    89,    90,    91,    79,    80,    81,    82,
      83,    84,    85,    86,     0,     0,     0,     0,     0,     0,
     140,     0,     0,     0,     0,    88,    89,    90,    91,    79,
      80,    81,    82,    83,    84,    85,    86,     0,     0,     0,
       0,     0,     0,   141,     0,     0,     0,     0,    88,    89,
      90,    91,    79,    80,    81,    82,    83,    84,    85,    86,
      79,    80,    81,    82,    83,    84,    85,     0,     0,     0,
       0,    88,    89,    90,    91,     0,     0,     0,     0,    88,
      89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    83,    84,     0,     0,     0,     0,     0,
       0,     0,    88,    89,    90,    91,     0,     0,    88,    89,
      90,    91
};

static const yytype_int16 yycheck[] =
{
       1,    25,    33,    33,     3,     3,    37,    37,    39,    35,
       3,    36,    38,     3,    23,    24,     3,    26,    27,     3,
      43,    44,    45,    46,    25,    62,    63,    64,    45,    46,
       3,     3,     3,    37,     3,    37,    39,    46,    47,    39,
      49,    40,    37,    37,    33,    37,    70,    38,    57,    37,
      59,    60,    61,    62,    63,    64,    37,    50,    34,    52,
      53,    54,    55,    56,    34,    42,    34,     3,    35,    70,
      79,    80,    81,    82,    83,    84,    85,    86,    35,    88,
      89,    90,    91,    34,    38,     3,     4,     5,     6,     7,
      38,    38,    18,    34,    38,    61,   135,   106,    16,   157,
      -1,    -1,    -1,    21,    22,    23,    -1,    -1,    -1,    -1,
     119,    -1,    -1,    -1,    32,    -1,   140,   141,    -1,    37,
      -1,    -1,    -1,    41,   133,    -1,    44,    -1,   137,    -1,
      -1,    -1,   156,   142,    -1,    -1,   160,    -1,    -1,   140,
     141,   134,    -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,
      -1,    -1,    -1,    -1,    -1,   156,    -1,     0,    -1,   160,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    37,    -1,    39,    -1,    41,    -1,
      -1,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    37,    -1,    39,    40,
      41,    -1,    -1,    44,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,    -1,    -1,    44,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    32,    -1,    -1,    -1,    -1,
      37,    -1,    39,    -1,    41,    -1,    -1,    44,    21,    22,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    -1,
      -1,    44,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    34,    24,    25,    26,    27,    28,    29,    30,
      31,    43,    44,    45,    46,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    46,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    24,    25,    26,    27,    28,    29,    30,    31,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    24,    25,    26,    27,    28,    29,    24,
      25,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    -1,    -1,    43,    44,
      45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    49,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    19,    20,
      21,    22,    23,    32,    37,    39,    41,    44,    50,    52,
      53,    54,    55,    58,    59,    60,    61,    62,    63,    64,
      66,    67,    68,    71,    72,    75,    33,    37,    50,    36,
       3,     3,     3,     3,     3,     3,     3,    37,     3,    37,
      37,    37,    37,    37,    37,     3,    63,    71,    71,    40,
      51,    52,    71,    73,    74,    71,    34,    34,    34,    24,
      25,    26,    27,    28,    29,    30,    31,    34,    43,    44,
      45,    46,    71,    71,    76,    77,    71,    50,    39,    50,
      50,    50,    50,    50,    65,    71,    33,    71,    71,    53,
      69,    71,    76,    76,    76,    38,    40,    52,    42,    35,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    38,    35,     3,    56,    57,    35,    38,    71,
      38,    38,    34,    38,    38,    38,    71,    71,    50,    40,
      57,    71,    52,    52,    70,    71,    18,    34,    52,    70,
      38,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    51,    51,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    53,    53,    54,    55,    56,    56,
      57,    58,    59,    60,    61,    62,    63,    63,    63,    64,
      65,    65,    66,    66,    67,    68,    69,    69,    69,    70,
      70,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    72,    73,    73,    74,
      74,    75,    76,    76,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     2,     4,     3,     5,     1,     2,
       2,     3,     3,     3,     3,     3,     4,     4,     4,     4,
       1,     3,     5,     7,     5,     9,     1,     1,     0,     1,
       0,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     1,     1,     1,
       1,     1,     1,     4,     1,     3,     3,     0,     1,     1,
       3,     1,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 49 "src/vsharp.y"
                                { program_root = new_block(); }
#line 1589 "build/vsharp.tab.c"
    break;

  case 3: /* program: program statement  */
#line 50 "src/vsharp.y"
                                { block_add(program_root,(yyvsp[0].node)); }
#line 1595 "build/vsharp.tab.c"
    break;

  case 4: /* block: LBRACE RBRACE  */
#line 54 "src/vsharp.y"
                                { (yyval.node) = new_block(); }
#line 1601 "build/vsharp.tab.c"
    break;

  case 5: /* block: LBRACE statement_list RBRACE  */
#line 55 "src/vsharp.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1607 "build/vsharp.tab.c"
    break;

  case 6: /* statement_list: statement  */
#line 59 "src/vsharp.y"
                                { (yyval.node) = new_block(); block_add((yyval.node),(yyvsp[0].node)); }
#line 1613 "build/vsharp.tab.c"
    break;

  case 7: /* statement_list: statement_list statement  */
#line 60 "src/vsharp.y"
                                { block_add((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1619 "build/vsharp.tab.c"
    break;

  case 8: /* statement: var_decl SEMICOLON  */
#line 65 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[-1].node); }
#line 1625 "build/vsharp.tab.c"
    break;

  case 9: /* statement: entity_decl  */
#line 66 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1631 "build/vsharp.tab.c"
    break;

  case 10: /* statement: cap_table_decl  */
#line 67 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1637 "build/vsharp.tab.c"
    break;

  case 11: /* statement: deal_decl  */
#line 68 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1643 "build/vsharp.tab.c"
    break;

  case 12: /* statement: debt_decl  */
#line 69 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1649 "build/vsharp.tab.c"
    break;

  case 13: /* statement: cost_debt_decl  */
#line 70 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1655 "build/vsharp.tab.c"
    break;

  case 14: /* statement: cost_equity_decl  */
#line 71 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1661 "build/vsharp.tab.c"
    break;

  case 15: /* statement: valuation_decl  */
#line 72 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1667 "build/vsharp.tab.c"
    break;

  case 16: /* statement: metric_call SEMICOLON  */
#line 73 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[-1].node); }
#line 1673 "build/vsharp.tab.c"
    break;

  case 17: /* statement: print_stmt SEMICOLON  */
#line 74 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[-1].node); }
#line 1679 "build/vsharp.tab.c"
    break;

  case 18: /* statement: IDENTIFIER block  */
#line 75 "src/vsharp.y"
                                                { (yyval.node) = new_nop(); }
#line 1685 "build/vsharp.tab.c"
    break;

  case 19: /* statement: expression SEMICOLON  */
#line 76 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[-1].node); }
#line 1691 "build/vsharp.tab.c"
    break;

  case 20: /* statement: if_stmt  */
#line 77 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1697 "build/vsharp.tab.c"
    break;

  case 21: /* statement: while_stmt  */
#line 78 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1703 "build/vsharp.tab.c"
    break;

  case 22: /* statement: for_stmt  */
#line 79 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1709 "build/vsharp.tab.c"
    break;

  case 23: /* statement: block  */
#line 80 "src/vsharp.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 1715 "build/vsharp.tab.c"
    break;

  case 24: /* var_decl: VAR IDENTIFIER  */
#line 85 "src/vsharp.y"
                                                { (yyval.node) = new_vardecl((yyvsp[0].id),NULL); }
#line 1721 "build/vsharp.tab.c"
    break;

  case 25: /* var_decl: VAR IDENTIFIER ASSIGN expression  */
#line 86 "src/vsharp.y"
                                                { (yyval.node) = new_vardecl((yyvsp[-2].id),(yyvsp[0].node)); }
#line 1727 "build/vsharp.tab.c"
    break;

  case 26: /* entity_decl: ENTITY IDENTIFIER block  */
#line 90 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1733 "build/vsharp.tab.c"
    break;

  case 27: /* cap_table_decl: CAP_TABLE IDENTIFIER LBRACE cap_item_list RBRACE  */
#line 94 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1739 "build/vsharp.tab.c"
    break;

  case 30: /* cap_item: IDENTIFIER block  */
#line 102 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1745 "build/vsharp.tab.c"
    break;

  case 31: /* deal_decl: DEAL IDENTIFIER block  */
#line 105 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1751 "build/vsharp.tab.c"
    break;

  case 32: /* debt_decl: DEBT_INSTRUMENT IDENTIFIER block  */
#line 106 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1757 "build/vsharp.tab.c"
    break;

  case 33: /* cost_debt_decl: COST_OF_DEBT IDENTIFIER block  */
#line 107 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1763 "build/vsharp.tab.c"
    break;

  case 34: /* cost_equity_decl: COST_OF_EQUITY IDENTIFIER block  */
#line 108 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1769 "build/vsharp.tab.c"
    break;

  case 35: /* valuation_decl: VALUATION IDENTIFIER block  */
#line 109 "src/vsharp.y"
                                                                    { (yyval.node) = new_nop(); }
#line 1775 "build/vsharp.tab.c"
    break;

  case 36: /* metric_call: NPV LPAREN arg_list_opt RPAREN  */
#line 113 "src/vsharp.y"
                                        { (yyval.node) = new_call(new_ident("npv"), (yyvsp[-1].node)->v.array.elems, (yyvsp[-1].node)->v.array.count); }
#line 1781 "build/vsharp.tab.c"
    break;

  case 37: /* metric_call: IRR LPAREN arg_list_opt RPAREN  */
#line 114 "src/vsharp.y"
                                        { (yyval.node) = new_call(new_ident("irr"), (yyvsp[-1].node)->v.array.elems, (yyvsp[-1].node)->v.array.count); }
#line 1787 "build/vsharp.tab.c"
    break;

  case 38: /* metric_call: WACC LPAREN arg_list_opt RPAREN  */
#line 115 "src/vsharp.y"
                                        { (yyval.node) = new_call(new_ident("wacc"),(yyvsp[-1].node)->v.array.elems, (yyvsp[-1].node)->v.array.count); }
#line 1793 "build/vsharp.tab.c"
    break;

  case 39: /* print_stmt: PRINT LPAREN print_args RPAREN  */
#line 119 "src/vsharp.y"
                                                      { (yyval.node) = (yyvsp[-1].node); }
#line 1799 "build/vsharp.tab.c"
    break;

  case 40: /* print_args: expression  */
#line 121 "src/vsharp.y"
                                                      { (yyval.node) = new_print((yyvsp[0].node)); }
#line 1805 "build/vsharp.tab.c"
    break;

  case 41: /* print_args: print_args COMMA expression  */
#line 122 "src/vsharp.y"
                                                      { print_add((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 1811 "build/vsharp.tab.c"
    break;

  case 42: /* if_stmt: IF LPAREN expression RPAREN statement  */
#line 127 "src/vsharp.y"
                                                                     { (yyval.node) = new_if((yyvsp[-2].node),(yyvsp[0].node),new_nop()); }
#line 1817 "build/vsharp.tab.c"
    break;

  case 43: /* if_stmt: IF LPAREN expression RPAREN statement ELSE statement  */
#line 128 "src/vsharp.y"
                                                                     { (yyval.node) = new_if((yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1823 "build/vsharp.tab.c"
    break;

  case 44: /* while_stmt: WHILE LPAREN expression RPAREN statement  */
#line 131 "src/vsharp.y"
                                                                     { (yyval.node) = new_while((yyvsp[-2].node),(yyvsp[0].node)); }
#line 1829 "build/vsharp.tab.c"
    break;

  case 45: /* for_stmt: FOR LPAREN for_init SEMICOLON expression_opt SEMICOLON expression_opt RPAREN statement  */
#line 134 "src/vsharp.y"
        { (yyval.node) = new_for((yyvsp[-6].node),(yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1835 "build/vsharp.tab.c"
    break;

  case 46: /* for_init: var_decl  */
#line 137 "src/vsharp.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1841 "build/vsharp.tab.c"
    break;

  case 47: /* for_init: expression  */
#line 138 "src/vsharp.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1847 "build/vsharp.tab.c"
    break;

  case 48: /* for_init: %empty  */
#line 139 "src/vsharp.y"
                                    { (yyval.node) = new_nop(); }
#line 1853 "build/vsharp.tab.c"
    break;

  case 49: /* expression_opt: expression  */
#line 142 "src/vsharp.y"
                                    { (yyval.node) = (yyvsp[0].node); }
#line 1859 "build/vsharp.tab.c"
    break;

  case 50: /* expression_opt: %empty  */
#line 143 "src/vsharp.y"
                                    { (yyval.node) = new_nop(); }
#line 1865 "build/vsharp.tab.c"
    break;

  case 51: /* expression: expression '+' expression  */
#line 148 "src/vsharp.y"
                                                    { (yyval.node) = new_bin('+',(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1871 "build/vsharp.tab.c"
    break;

  case 52: /* expression: expression '-' expression  */
#line 149 "src/vsharp.y"
                                                    { (yyval.node) = new_bin('-',(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1877 "build/vsharp.tab.c"
    break;

  case 53: /* expression: expression '*' expression  */
#line 150 "src/vsharp.y"
                                                    { (yyval.node) = new_bin('*',(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1883 "build/vsharp.tab.c"
    break;

  case 54: /* expression: expression '/' expression  */
#line 151 "src/vsharp.y"
                                                    { (yyval.node) = new_bin('/',(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1889 "build/vsharp.tab.c"
    break;

  case 55: /* expression: expression EQ expression  */
#line 152 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(EQ,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1895 "build/vsharp.tab.c"
    break;

  case 56: /* expression: expression NE expression  */
#line 153 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(NE,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1901 "build/vsharp.tab.c"
    break;

  case 57: /* expression: expression GT expression  */
#line 154 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(GT,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1907 "build/vsharp.tab.c"
    break;

  case 58: /* expression: expression LT expression  */
#line 155 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(LT,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1913 "build/vsharp.tab.c"
    break;

  case 59: /* expression: expression GE expression  */
#line 156 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(GE,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1919 "build/vsharp.tab.c"
    break;

  case 60: /* expression: expression LE expression  */
#line 157 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(LE,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1925 "build/vsharp.tab.c"
    break;

  case 61: /* expression: expression AND expression  */
#line 158 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(AND,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1931 "build/vsharp.tab.c"
    break;

  case 62: /* expression: expression OR expression  */
#line 159 "src/vsharp.y"
                                                    { (yyval.node) = new_bin(OR,(yyvsp[-2].node),(yyvsp[0].node)); }
#line 1937 "build/vsharp.tab.c"
    break;

  case 63: /* expression: IDENTIFIER ASSIGN expression  */
#line 160 "src/vsharp.y"
                                                    { (yyval.node) = new_assign((yyvsp[-2].id),(yyvsp[0].node)); }
#line 1943 "build/vsharp.tab.c"
    break;

  case 64: /* expression: NOT expression  */
#line 161 "src/vsharp.y"
                                                    { (yyval.node) = new_un(NOT,(yyvsp[0].node)); }
#line 1949 "build/vsharp.tab.c"
    break;

  case 65: /* expression: '-' expression  */
#line 162 "src/vsharp.y"
                                                    { (yyval.node) = new_un('-', (yyvsp[0].node)); }
#line 1955 "build/vsharp.tab.c"
    break;

  case 66: /* expression: LPAREN expression RPAREN  */
#line 163 "src/vsharp.y"
                                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1961 "build/vsharp.tab.c"
    break;

  case 67: /* expression: NUMBER  */
#line 164 "src/vsharp.y"
             {
        /* se tem parte fracionária, vira NODE_FLOAT; senão NODE_NUM */
        long as_int = (long)(yyvsp[0].num);
        if ( (double)as_int == (yyvsp[0].num) )
            (yyval.node) = new_num  (as_int);   /* 42 -> int  */
        else
            (yyval.node) = new_float((yyvsp[0].num));       /* 3.14, 0.05 */
      }
#line 1974 "build/vsharp.tab.c"
    break;

  case 68: /* expression: BOOL_LITERAL  */
#line 172 "src/vsharp.y"
                                                    { (yyval.node) = new_bool((int)(yyvsp[0].num)); }
#line 1980 "build/vsharp.tab.c"
    break;

  case 69: /* expression: STRING  */
#line 173 "src/vsharp.y"
                                                    { (yyval.node) = new_str((yyvsp[0].str)); }
#line 1986 "build/vsharp.tab.c"
    break;

  case 70: /* expression: date_lit  */
#line 174 "src/vsharp.y"
                                                    { (yyval.node) = (yyvsp[0].node); }
#line 1992 "build/vsharp.tab.c"
    break;

  case 71: /* expression: array_lit  */
#line 175 "src/vsharp.y"
                                                    { (yyval.node) = (yyvsp[0].node); }
#line 1998 "build/vsharp.tab.c"
    break;

  case 72: /* expression: IDENTIFIER  */
#line 176 "src/vsharp.y"
                                                    { (yyval.node) = new_ident((yyvsp[0].id)); }
#line 2004 "build/vsharp.tab.c"
    break;

  case 73: /* expression: IDENTIFIER LPAREN arg_list_opt RPAREN  */
#line 177 "src/vsharp.y"
                                                    { (yyval.node) = new_call(new_ident((yyvsp[-3].id)),(yyvsp[-1].node)->v.array.elems,(yyvsp[-1].node)->v.array.count); }
#line 2010 "build/vsharp.tab.c"
    break;

  case 74: /* expression: metric_call  */
#line 178 "src/vsharp.y"
                                                    { (yyval.node) = (yyvsp[0].node); }
#line 2016 "build/vsharp.tab.c"
    break;

  case 75: /* expression: STRING COLON expression  */
#line 179 "src/vsharp.y"
                                                    { (yyval.node) = new_pair((yyvsp[-2].str),(yyvsp[0].node)); }
#line 2022 "build/vsharp.tab.c"
    break;

  case 76: /* array_lit: LBRACKET expr_list_opt RBRACKET  */
#line 183 "src/vsharp.y"
                                                                   { (yyval.node) = (yyvsp[-1].node); }
#line 2028 "build/vsharp.tab.c"
    break;

  case 77: /* expr_list_opt: %empty  */
#line 184 "src/vsharp.y"
                                                                  { (yyval.node) = new_array(NULL,0); }
#line 2034 "build/vsharp.tab.c"
    break;

  case 79: /* expr_list: expression  */
#line 186 "src/vsharp.y"
                                                                  { (yyval.node) = new_array_one((yyvsp[0].node)); }
#line 2040 "build/vsharp.tab.c"
    break;

  case 80: /* expr_list: expr_list COMMA expression  */
#line 187 "src/vsharp.y"
                                                                  { array_append((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2046 "build/vsharp.tab.c"
    break;

  case 81: /* date_lit: DATE  */
#line 190 "src/vsharp.y"
                                                                  { (yyval.node) = new_date((yyvsp[0].str)); }
#line 2052 "build/vsharp.tab.c"
    break;

  case 82: /* arg_list_opt: %empty  */
#line 193 "src/vsharp.y"
                                                                  { (yyval.node) = new_array(NULL,0); }
#line 2058 "build/vsharp.tab.c"
    break;

  case 84: /* arg_list: expression  */
#line 195 "src/vsharp.y"
                                                                  { (yyval.node) = new_array_one((yyvsp[0].node)); }
#line 2064 "build/vsharp.tab.c"
    break;

  case 85: /* arg_list: arg_list COMMA expression  */
#line 196 "src/vsharp.y"
                                                                  { array_append((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-2].node); }
#line 2070 "build/vsharp.tab.c"
    break;


#line 2074 "build/vsharp.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 199 "src/vsharp.y"

void yyerror(const char *s){fprintf(stderr,"Erro de sintaxe na linha %d: %s\n",yylineno,s);}
