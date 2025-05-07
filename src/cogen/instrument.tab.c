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
//#line 22 "instrument.y"


//#define _GNU_SOURCE
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "mccode.h"

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

// On Windows and using cl.exe, avoid
// unistd.h and map popen/pclose to fallback _ versions
#ifdef _WIN32
#ifdef _MSC_EXTENSIONS
#define YY_NO_UNISTD_H
#define popen _popen
#define pclose _pclose
#endif
#endif
//#line 45 "instrument.y"

/* Already typedef'ed in mccode.h:         */
/* typedef struct List_header * List;      */
/* typedef struct Symbol_table * Symtab;   */
/* typedef struct instr_def * instr_ptr_t; */
int yylex();
int yyerror(const char *s);
List list_cat(List, List);
Symtab symtab_cat(Symtab, Symtab);
void run_command_to_add_search_dir(char * input);
int metadata_construct_table(instr_ptr_t);
void metadata_assign_from_definition(List metadata);
void metadata_assign_from_instance(List metadata);


//#line 109 "instrument.tab.c"

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

#include "instrument.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_RESTRICTED = 3,             /* TOK_RESTRICTED  */
  YYSYMBOL_TOK_GENERAL = 4,                /* TOK_GENERAL  */
  YYSYMBOL_TOK_ABSOLUTE = 5,               /* "ABSOLUTE"  */
  YYSYMBOL_TOK_AT = 6,                     /* "AT"  */
  YYSYMBOL_TOK_COMPONENT = 7,              /* "COMPONENT"  */
  YYSYMBOL_TOK_DECLARE = 8,                /* "DECLARE"  */
  YYSYMBOL_TOK_USERVARS = 9,               /* "USERVARS"  */
  YYSYMBOL_TOK_DEFINE = 10,                /* "DEFINE"  */
  YYSYMBOL_TOK_DEFINITION = 11,            /* "DEFINITION"  */
  YYSYMBOL_TOK_END = 12,                   /* "END"  */
  YYSYMBOL_TOK_FINALLY = 13,               /* "FINALLY"  */
  YYSYMBOL_TOK_INITIALISE = 14,            /* "INITIALISE"  */
  YYSYMBOL_TOK_INSTRUMENT = 15,            /* "INSTRUMENT"  */
  YYSYMBOL_TOK_DISPLAY = 16,               /* "DISPLAY"  */
  YYSYMBOL_TOK_PRIVATE = 17,               /* "PRIVATE"  */
  YYSYMBOL_TOK_PARAMETERS = 18,            /* "PARAMETERS"  */
  YYSYMBOL_TOK_RELATIVE = 19,              /* "RELATIVE"  */
  YYSYMBOL_TOK_ROTATED = 20,               /* "ROTATED"  */
  YYSYMBOL_TOK_PREVIOUS = 21,              /* "PREVIOUS"  */
  YYSYMBOL_TOK_SETTING = 22,               /* "SETTING"  */
  YYSYMBOL_TOK_STATE = 23,                 /* "STATE"  */
  YYSYMBOL_TOK_POL = 24,                   /* "POLARISATION"  */
  YYSYMBOL_TOK_TRACE = 25,                 /* "TRACE"  */
  YYSYMBOL_TOK_SHARE = 26,                 /* "SHARE"  */
  YYSYMBOL_TOK_EXTEND = 27,                /* "EXTEND"  */
  YYSYMBOL_TOK_GROUP = 28,                 /* "GROUP"  */
  YYSYMBOL_TOK_SAVE = 29,                  /* "SAVE"  */
  YYSYMBOL_TOK_JUMP = 30,                  /* "JUMP"  */
  YYSYMBOL_TOK_WHEN = 31,                  /* "WHEN"  */
  YYSYMBOL_TOK_NEXT = 32,                  /* "NEXT"  */
  YYSYMBOL_TOK_ITERATE = 33,               /* "ITERATE"  */
  YYSYMBOL_TOK_MYSELF = 34,                /* "MYSELF"  */
  YYSYMBOL_TOK_COPY = 35,                  /* "COPY"  */
  YYSYMBOL_TOK_SPLIT = 36,                 /* "SPLIT"  */
  YYSYMBOL_TOK_REMOVABLE = 37,             /* "REMOVABLE"  */
  YYSYMBOL_TOK_CPUONLY = 38,               /* "CPU"  */
  YYSYMBOL_TOK_NOACC = 39,                 /* "NOACC"  */
  YYSYMBOL_TOK_DEPENDENCY = 40,            /* "DEPENDENCY"  */
  YYSYMBOL_TOK_SHELL = 41,                 /* "SHELL"  */
  YYSYMBOL_TOK_SEARCH = 42,                /* "SEARCH"  */
  YYSYMBOL_TOK_METADATA = 43,              /* "METADATA"  */
  YYSYMBOL_TOK_ID = 44,                    /* TOK_ID  */
  YYSYMBOL_TOK_STRING = 45,                /* TOK_STRING  */
  YYSYMBOL_TOK_NUMBER = 46,                /* TOK_NUMBER  */
  YYSYMBOL_TOK_CTOK = 47,                  /* TOK_CTOK  */
  YYSYMBOL_TOK_CODE_START = 48,            /* TOK_CODE_START  */
  YYSYMBOL_TOK_CODE_END = 49,              /* TOK_CODE_END  */
  YYSYMBOL_TOK_CODE_LINE = 50,             /* TOK_CODE_LINE  */
  YYSYMBOL_TOK_INVALID = 51,               /* TOK_INVALID  */
  YYSYMBOL_52_OUTPUT_ = 52,                /* "OUTPUT"  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '*'  */
  YYSYMBOL_57_ = 57,                       /* '='  */
  YYSYMBOL_58_ = 58,                       /* '/'  */
  YYSYMBOL_59_ = 59,                       /* '['  */
  YYSYMBOL_60_ = 60,                       /* ']'  */
  YYSYMBOL_61_ = 61,                       /* '{'  */
  YYSYMBOL_62_ = 62,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_main = 64,                      /* main  */
  YYSYMBOL_compdefs = 65,                  /* compdefs  */
  YYSYMBOL_compdef = 66,                   /* compdef  */
  YYSYMBOL_share = 67,                     /* share  */
  YYSYMBOL_trace = 68,                     /* trace  */
  YYSYMBOL_parameters = 69,                /* parameters  */
  YYSYMBOL_def_par = 70,                   /* def_par  */
  YYSYMBOL_set_par = 71,                   /* set_par  */
  YYSYMBOL_out_par = 72,                   /* out_par  */
  YYSYMBOL_state_par = 73,                 /* state_par  */
  YYSYMBOL_pol_par = 74,                   /* pol_par  */
  YYSYMBOL_comp_iformallist = 75,          /* comp_iformallist  */
  YYSYMBOL_comp_iformals = 76,             /* comp_iformals  */
  YYSYMBOL_comp_iformals1 = 77,            /* comp_iformals1  */
  YYSYMBOL_comp_iformal = 78,              /* comp_iformal  */
  YYSYMBOL_declare = 79,                   /* declare  */
  YYSYMBOL_uservars = 80,                  /* uservars  */
  YYSYMBOL_initialize = 81,                /* initialize  */
  YYSYMBOL_save = 82,                      /* save  */
  YYSYMBOL_finally = 83,                   /* finally  */
  YYSYMBOL_display = 84,                   /* display  */
  YYSYMBOL_instrument = 85,                /* instrument  */
  YYSYMBOL_86_1 = 86,                      /* $@1  */
  YYSYMBOL_instrpar_list = 87,             /* instrpar_list  */
  YYSYMBOL_instr_formals = 88,             /* instr_formals  */
  YYSYMBOL_instr_formals1 = 89,            /* instr_formals1  */
  YYSYMBOL_instr_formal = 90,              /* instr_formal  */
  YYSYMBOL_instr_trace = 91,               /* instr_trace  */
  YYSYMBOL_complist = 92,                  /* complist  */
  YYSYMBOL_instname = 93,                  /* instname  */
  YYSYMBOL_instref = 94,                   /* instref  */
  YYSYMBOL_removable = 95,                 /* removable  */
  YYSYMBOL_cpuonly = 96,                   /* cpuonly  */
  YYSYMBOL_component = 97,                 /* component  */
  YYSYMBOL_98_2 = 98,                      /* $@2  */
  YYSYMBOL_split = 99,                     /* split  */
  YYSYMBOL_actuallist = 100,               /* actuallist  */
  YYSYMBOL_actuals = 101,                  /* actuals  */
  YYSYMBOL_actuals1 = 102,                 /* actuals1  */
  YYSYMBOL_when = 103,                     /* when  */
  YYSYMBOL_place = 104,                    /* place  */
  YYSYMBOL_orientation = 105,              /* orientation  */
  YYSYMBOL_reference = 106,                /* reference  */
  YYSYMBOL_groupref = 107,                 /* groupref  */
  YYSYMBOL_groupdef = 108,                 /* groupdef  */
  YYSYMBOL_compref = 109,                  /* compref  */
  YYSYMBOL_coords = 110,                   /* coords  */
  YYSYMBOL_extend = 111,                   /* extend  */
  YYSYMBOL_metadata = 112,                 /* metadata  */
  YYSYMBOL_metadata1 = 113,                /* metadata1  */
  YYSYMBOL_metadatum = 114,                /* metadatum  */
  YYSYMBOL_jumps = 115,                    /* jumps  */
  YYSYMBOL_jumps1 = 116,                   /* jumps1  */
  YYSYMBOL_jump = 117,                     /* jump  */
  YYSYMBOL_jumpcondition = 118,            /* jumpcondition  */
  YYSYMBOL_jumpname = 119,                 /* jumpname  */
  YYSYMBOL_shell = 120,                    /* shell  */
  YYSYMBOL_search = 121,                   /* search  */
  YYSYMBOL_dependency = 122,               /* dependency  */
  YYSYMBOL_noacc = 123,                    /* noacc  */
  YYSYMBOL_exp = 124,                      /* exp  */
  YYSYMBOL_125_3 = 125,                    /* @3  */
  YYSYMBOL_topexp = 126,                   /* topexp  */
  YYSYMBOL_topatexp = 127,                 /* topatexp  */
  YYSYMBOL_genexp = 128,                   /* genexp  */
  YYSYMBOL_genatexp = 129,                 /* genatexp  */
  YYSYMBOL_codeblock = 130,                /* codeblock  */
  YYSYMBOL_code = 131                      /* code  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  323

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


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
      53,    54,    56,     2,    55,     2,     2,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    57,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    61,     2,    62,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   182,   182,   183,   188,   189,   193,   238,   285,   288,
     292,   301,   320,   323,   327,   336,   353,   363,   366,   373,
     376,   383,   386,   390,   397,   400,   408,   411,   419,   426,
     429,   435,   440,   447,   471,   489,   498,   508,   532,   554,
     557,   561,   570,   588,   591,   598,   601,   610,   625,   632,
     635,   639,   648,   666,   669,   673,   682,   700,   703,   707,
     716,   740,   738,   802,   809,   812,   818,   823,   830,   849,
     866,   876,   887,   908,   927,   947,   965,   976,   988,  1010,
    1034,  1037,  1043,  1106,  1110,  1116,  1122,  1128,  1134,  1140,
    1158,  1175,  1194,  1197,  1205,  1208,  1218,  1217,  1324,  1327,
    1331,  1338,  1345,  1348,  1354,  1360,  1369,  1372,  1378,  1386,
    1390,  1399,  1403,  1407,  1415,  1418,  1424,  1448,  1457,  1471,
    1488,  1498,  1501,  1508,  1511,  1517,  1522,  1531,  1542,  1557,
    1568,  1585,  1588,  1594,  1599,  1606,  1618,  1623,  1630,  1635,
    1640,  1645,  1650,  1654,  1663,  1665,  1677,  1681,  1708,  1710,
    1719,  1723,  1734,  1734,  1742,  1746,  1756,  1764,  1769,  1795,
    1800,  1805,  1810,  1814,  1818,  1822,  1831,  1839,  1848,  1856,
    1865,  1876,  1880,  1888,  1892,  1900,  1910,  1914
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
  "\"end of file\"", "error", "\"invalid token\"", "TOK_RESTRICTED",
  "TOK_GENERAL", "\"ABSOLUTE\"", "\"AT\"", "\"COMPONENT\"", "\"DECLARE\"",
  "\"USERVARS\"", "\"DEFINE\"", "\"DEFINITION\"", "\"END\"", "\"FINALLY\"",
  "\"INITIALISE\"", "\"INSTRUMENT\"", "\"DISPLAY\"", "\"PRIVATE\"",
  "\"PARAMETERS\"", "\"RELATIVE\"", "\"ROTATED\"", "\"PREVIOUS\"",
  "\"SETTING\"", "\"STATE\"", "\"POLARISATION\"", "\"TRACE\"", "\"SHARE\"",
  "\"EXTEND\"", "\"GROUP\"", "\"SAVE\"", "\"JUMP\"", "\"WHEN\"",
  "\"NEXT\"", "\"ITERATE\"", "\"MYSELF\"", "\"COPY\"", "\"SPLIT\"",
  "\"REMOVABLE\"", "\"CPU\"", "\"NOACC\"", "\"DEPENDENCY\"", "\"SHELL\"",
  "\"SEARCH\"", "\"METADATA\"", "TOK_ID", "TOK_STRING", "TOK_NUMBER",
  "TOK_CTOK", "TOK_CODE_START", "TOK_CODE_END", "TOK_CODE_LINE",
  "TOK_INVALID", "\"OUTPUT\"", "'('", "')'", "','", "'*'", "'='", "'/'",
  "'['", "']'", "'{'", "'}'", "$accept", "main", "compdefs", "compdef",
  "share", "trace", "parameters", "def_par", "set_par", "out_par",
  "state_par", "pol_par", "comp_iformallist", "comp_iformals",
  "comp_iformals1", "comp_iformal", "declare", "uservars", "initialize",
  "save", "finally", "display", "instrument", "$@1", "instrpar_list",
  "instr_formals", "instr_formals1", "instr_formal", "instr_trace",
  "complist", "instname", "instref", "removable", "cpuonly", "component",
  "$@2", "split", "actuallist", "actuals", "actuals1", "when", "place",
  "orientation", "reference", "groupref", "groupdef", "compref", "coords",
  "extend", "metadata", "metadata1", "metadatum", "jumps", "jumps1",
  "jump", "jumpcondition", "jumpname", "shell", "search", "dependency",
  "noacc", "exp", "@3", "topexp", "topatexp", "genexp", "genatexp",
  "codeblock", "code", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-154)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-100)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     129,     6,  -154,    18,    17,  -154,    55,  -154,    41,   105,
    -154,  -154,    47,    66,    95,    82,   108,   117,    92,   109,
     153,    93,   133,   108,  -154,   158,     3,   131,  -154,   135,
    -154,   108,    97,    99,   132,   140,  -154,   109,   164,   165,
     161,    15,   134,   130,  -154,   133,    50,   139,   142,  -154,
     133,   138,   138,   138,   138,  -154,   144,   148,  -154,   109,
     109,   176,   171,    96,   154,  -154,   155,  -154,   131,   140,
     150,   175,  -154,  -154,   135,   140,  -154,  -154,  -154,  -154,
    -154,  -154,  -154,   173,  -154,  -154,   109,   187,  -154,  -154,
     163,   110,  -154,   249,   152,  -154,   213,  -154,   166,  -154,
    -154,   148,   120,    29,   216,  -154,   109,  -154,   169,  -154,
     177,  -154,  -154,  -154,  -154,  -154,  -154,   102,  -154,  -154,
    -154,   157,   -11,   249,  -154,  -154,    31,   216,  -154,  -154,
     173,  -154,  -154,   183,  -154,   138,   213,  -154,  -154,  -154,
     172,  -154,  -154,  -154,   203,  -154,  -154,   231,  -154,    42,
    -154,  -154,   184,  -154,   217,  -154,   216,   205,  -154,   217,
    -154,  -154,  -154,  -154,  -154,  -154,   206,    48,   210,   213,
     138,   211,  -154,   138,   186,  -154,  -154,   209,   217,  -154,
      57,   209,  -154,   212,     1,    67,   227,   211,   197,  -154,
     227,   138,   229,  -154,    90,  -154,   204,  -154,  -154,   207,
    -154,    73,   241,   209,   228,   238,  -154,   218,  -154,  -154,
     230,   240,   225,  -154,  -154,   227,   138,    76,   259,  -154,
     265,   266,   138,   247,   238,  -154,   235,  -154,  -154,  -154,
      83,  -154,   138,   268,   254,  -154,   232,  -154,   242,  -154,
    -154,   138,   253,   -22,  -154,   244,   248,   250,  -154,  -154,
     -12,   256,  -154,   251,   258,  -154,   255,   257,   261,   262,
    -154,   298,   267,   250,  -154,  -154,   272,  -154,   269,   292,
     264,  -154,  -154,   263,  -154,     7,   269,   291,  -154,  -154,
     270,  -154,     9,  -154,     7,   277,   296,  -154,  -154,  -154,
    -154,  -154,  -154,  -154,   138,   294,   271,  -154,    46,   108,
     294,  -154,  -154,   274,   275,  -154,  -154,   -16,  -154,  -154,
     276,   283,   285,  -154,  -154,  -154,  -154,   278,   279,  -154,
    -154,  -154,  -154
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     4,     0,     0,     3,     0,     1,     0,     0,
       5,     2,    17,     0,     0,     0,   123,    19,     0,     0,
      17,     0,   144,   124,   125,     0,    21,    64,    61,    29,
      18,   123,     0,     0,     0,   148,   126,     0,     0,     0,
      24,    70,     0,    65,    66,   144,    35,     0,    30,    31,
     144,     0,     0,     0,     0,   145,     0,   150,    20,     0,
       0,     0,    26,    68,     0,   152,     0,    63,     0,   148,
      33,     0,   152,    28,     0,   148,   176,   127,   128,   129,
     130,   149,   151,     8,    23,    22,     0,     0,    16,   152,
       0,    69,    71,     0,    76,    67,    39,   152,    34,    36,
      32,   150,     0,     0,    43,    25,     0,    72,    74,   152,
       0,   156,   157,   158,   160,   159,   161,     0,   163,   162,
     164,     0,     0,   153,   154,   152,     0,    43,    37,   152,
       8,   175,   177,     0,     9,     0,    39,    27,   152,    73,
      75,   166,   174,   173,     0,   171,   168,     0,   170,     0,
     155,    77,     0,    40,    45,    38,    43,    10,    44,    45,
      78,   152,   165,   172,   167,   169,    41,     0,     0,    39,
       0,    12,    79,     0,     0,    48,    81,    49,    45,    11,
       0,    49,    42,    46,    80,     0,    53,    12,     0,    13,
      53,     0,     0,    93,     0,    83,    94,    82,    84,     0,
      50,     0,     0,    49,    14,    57,    47,     0,   146,    95,
      98,    51,     0,    54,    62,    53,     0,     0,     0,   147,
     152,     0,     0,    55,    57,    15,     0,    58,     6,   100,
       0,    52,     0,     0,    59,    86,    87,    88,     0,    56,
       7,     0,     0,     0,    60,     0,     0,     0,    96,    85,
       0,   102,    91,   106,   117,   119,     0,     0,     0,   103,
     152,     0,     0,    90,   152,   101,     0,   107,     0,   109,
       0,    89,   104,     0,   152,     0,     0,   114,   118,   152,
       0,   111,     0,   108,     0,     0,   121,   105,   152,   112,
     113,   110,   116,   115,     0,   131,     0,   122,     0,   123,
     132,   133,   152,   138,   141,   140,   143,     0,    97,   134,
       0,     0,     0,   152,   152,   135,   120,     0,     0,   136,
     137,   139,   142
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -154,  -154,  -154,   328,   208,   149,   315,  -154,  -154,  -154,
    -154,  -154,   -32,  -154,  -154,   273,  -129,   -96,  -153,  -112,
    -134,   113,   156,  -154,  -154,  -154,  -154,   280,  -154,  -154,
    -154,  -154,  -154,  -154,  -154,  -154,  -154,    78,  -154,  -154,
    -154,  -154,  -154,    58,  -154,  -154,    61,    63,  -154,   -31,
    -154,   321,  -154,  -154,    45,  -154,  -154,    64,  -154,    -7,
     245,   -68,  -154,  -154,   -74,    51,   -19,   -51,  -154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     3,     6,     5,   104,   181,    16,    17,    26,    40,
      62,    88,    30,    47,    48,    49,   127,   136,   168,   186,
     202,   218,    11,    45,    28,    42,    43,    44,   177,   184,
     238,   248,   196,   210,   197,   253,   221,   252,   258,   259,
     261,   269,   277,   283,   286,   293,   256,   275,   295,    22,
      23,    24,   299,   300,   301,   315,   307,    35,   198,    57,
      83,    92,    93,   123,   143,   144,   145,    77,   102
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,    78,    79,    80,    99,    58,   171,   159,   -92,   254,
     111,   192,   281,   246,   289,   313,     4,   314,     7,   124,
      38,   107,   247,   112,     8,   187,   282,    84,    85,   128,
     254,   154,   255,   113,   114,   115,   116,   -92,   193,   -92,
     178,   139,   117,   194,   142,   118,   119,   120,   121,   150,
     122,   148,   134,   255,   105,    39,   205,   151,    14,    63,
     169,   155,    96,   111,   133,     9,   152,   303,   101,   190,
     160,    64,    65,    66,   137,   153,   112,    76,   304,    76,
     305,   224,    15,   174,   158,    12,   113,   114,   115,   116,
     306,   215,   188,   172,    70,   117,    76,   142,   118,   119,
     120,   121,   199,   122,   165,    76,    71,    72,   212,    69,
      18,   226,     8,    19,    75,    76,   175,   235,   236,   179,
      13,    76,   182,   111,    76,   163,    20,   237,   163,   189,
     163,   207,     1,     2,   200,   208,   112,    32,    33,    25,
     206,    51,    52,    53,    54,    27,   113,   114,   115,   116,
     213,    21,   229,    89,    90,   117,   141,   142,   118,   119,
     120,   121,    29,   122,    14,   225,   227,   109,   110,   131,
     132,   231,   147,   149,    34,    41,    37,    55,   111,    46,
      56,   239,    59,    60,    61,    68,    76,    82,    67,    81,
     244,   112,   267,    73,    86,    87,   272,    74,    91,   103,
      94,   113,   114,   115,   116,   106,   280,    97,   108,   125,
     117,   287,   142,   118,   119,   120,   121,   146,   122,    98,
     296,   126,   140,   129,   111,   135,   138,   157,   166,   161,
     183,   167,   170,   173,   310,   176,   180,   112,   185,   191,
     201,   204,   209,   297,    13,   319,   320,   113,   114,   115,
     116,   211,   111,   214,   217,   216,   117,   162,   142,   118,
     119,   120,   121,   219,   122,   112,   220,   222,   308,   223,
     111,   228,   -99,   230,   232,   113,   114,   115,   116,   234,
     240,   241,   260,   112,   117,   242,   142,   118,   119,   120,
     121,   164,   122,   113,   114,   115,   116,   245,   249,   243,
     257,   250,   117,   251,   268,   118,   119,   120,   121,   263,
     122,   262,   276,   270,   264,   265,   273,   266,   278,   285,
     279,   292,   274,   294,   298,   288,   302,   311,   312,   317,
     316,   318,   321,   322,    10,    31,   203,   233,   156,   284,
     195,   271,   291,   290,    36,   309,   130,   100,    95
};

static const yytype_int16 yycheck[] =
{
      31,    52,    53,    54,    72,    37,   159,   136,     7,    21,
      21,    10,     5,    35,     5,    31,    10,    33,     0,    93,
      17,    89,    44,    34,     7,   178,    19,    59,    60,    97,
      21,   127,    44,    44,    45,    46,    47,    36,    37,    38,
     169,   109,    53,    42,    55,    56,    57,    58,    59,   123,
      61,    62,   103,    44,    86,    52,   190,   125,    11,    44,
     156,   129,    69,    21,    35,    10,    35,    21,    75,   181,
     138,    56,    57,    58,   106,   126,    34,    48,    32,    48,
      34,   215,    35,    35,   135,    44,    44,    45,    46,    47,
      44,   203,    35,   161,    44,    53,    48,    55,    56,    57,
      58,    59,    35,    61,    62,    48,    56,    57,    35,    45,
      44,    35,     7,    18,    50,    48,   167,    34,    35,   170,
      15,    48,   173,    21,    48,   144,    44,    44,   147,   180,
     149,    41,     3,     4,   185,    45,    34,    44,    45,    22,
     191,    44,    45,    44,    45,    53,    44,    45,    46,    47,
     201,    43,   220,    57,    58,    53,    54,    55,    56,    57,
      58,    59,    53,    61,    11,   216,   217,    57,    58,    49,
      50,   222,   121,   122,    41,    44,    18,    45,    21,    44,
      40,   232,    18,    18,    23,    55,    48,    39,    54,    45,
     241,    34,   260,    54,    18,    24,   264,    55,    44,    26,
      45,    44,    45,    46,    47,    18,   274,    57,    45,    57,
      53,   279,    55,    56,    57,    58,    59,    60,    61,    44,
     288,     8,    45,    57,    21,     9,    57,    44,    44,    57,
      44,    14,    27,    27,   302,    25,    25,    34,    29,    27,
      13,    44,    38,   294,    15,   313,   314,    44,    45,    46,
      47,    44,    21,    12,    16,    27,    53,    54,    55,    56,
      57,    58,    59,    45,    61,    34,    36,    27,   299,    44,
      21,    12,     7,     7,    27,    44,    45,    46,    47,    44,
      12,    27,    31,    34,    53,    53,    55,    56,    57,    58,
      59,    60,    61,    44,    45,    46,    47,    44,    54,    57,
      44,    53,    53,    53,     6,    56,    57,    58,    59,    54,
      61,    53,    20,    46,    57,    54,    44,    55,    54,    28,
      57,    44,    53,    27,    30,    55,    55,    53,    53,    46,
      54,    46,    54,    54,     6,    20,   187,   224,   130,   276,
     184,   263,   284,   282,    23,   300,   101,    74,    68
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    64,    10,    66,    65,     0,     7,    10,
      66,    85,    44,    15,    11,    35,    69,    70,    44,    18,
      44,    43,   112,   113,   114,    22,    71,    53,    87,    53,
      75,    69,    44,    45,    41,   120,   114,    18,    17,    52,
      72,    44,    88,    89,    90,    86,    44,    76,    77,    78,
     112,    44,    45,    44,    45,    45,    40,   122,    75,    18,
      18,    23,    73,    44,    56,    57,    58,    54,    55,   120,
      44,    56,    57,    54,    55,   120,    48,   130,   130,   130,
     130,    45,    39,   123,    75,    75,    18,    24,    74,    57,
      58,    44,   124,   125,    45,    90,   122,    57,    44,   124,
      78,   122,   131,    26,    67,    75,    18,   124,    45,    57,
      58,    21,    34,    44,    45,    46,    47,    53,    56,    57,
      58,    59,    61,   126,   127,    57,     8,    79,   124,    57,
     123,    49,    50,    35,   130,     9,    80,    75,    57,   124,
      45,    54,    55,   127,   128,   129,    60,   128,    62,   128,
     127,   124,    35,   130,    80,   124,    67,    44,   130,    79,
     124,    57,    54,   129,    60,    62,    44,    14,    81,    80,
      27,    81,   124,    27,    35,   130,    25,    91,    79,   130,
      25,    68,   130,    44,    92,    29,    82,    81,    35,   130,
      82,    27,    10,    37,    42,    85,    95,    97,   121,    35,
     130,    13,    83,    68,    44,    83,   130,    41,    45,    38,
      96,    44,    35,   130,    12,    82,    27,    16,    84,    45,
      36,    99,    27,    44,    83,   130,    35,   130,    12,   124,
       7,   130,    27,    84,    44,    34,    35,    44,    93,   130,
      12,    27,    53,    57,   130,    44,    35,    44,    94,    54,
      53,    53,   100,    98,    21,    44,   109,    44,   101,   102,
      31,   103,    53,    54,    57,    54,    55,   124,     6,   104,
      46,   100,   124,    44,    53,   110,    20,   105,    54,    57,
     124,     5,    19,   106,   110,    28,   107,   124,    55,     5,
     109,   106,    44,   108,    27,   111,   124,   130,    30,   115,
     116,   117,    55,    21,    32,    34,    44,   119,   112,   117,
     124,    53,    53,    31,    33,   118,    54,    46,    46,   124,
     124,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    67,    68,    68,    68,    68,    69,    70,    70,    71,
      71,    72,    72,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    79,    79,    80,    80,    81,    81,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    83,    84,    84,    84,
      84,    86,    85,    87,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      91,    92,    92,    92,    92,    93,    93,    93,    93,    94,
      94,    94,    95,    95,    96,    96,    98,    97,    99,    99,
      99,   100,   101,   101,   102,   102,   103,   103,   104,   105,
     105,   106,   106,   106,   107,   107,   108,   109,   109,   109,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   114,
     114,   115,   115,   116,   116,   117,   118,   118,   119,   119,
     119,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   125,   124,   126,   126,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   129,   129,   130,   131,   131
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,    17,    19,     0,     2,
       3,     5,     0,     2,     3,     5,     5,     0,     3,     0,
       3,     0,     3,     3,     0,     3,     0,     3,     3,     0,
       1,     1,     3,     2,     3,     1,     3,     4,     5,     0,
       2,     3,     5,     0,     2,     0,     3,     5,     2,     0,
       2,     3,     5,     0,     2,     3,     5,     0,     2,     3,
       5,     0,    14,     3,     0,     1,     1,     3,     2,     3,
       1,     3,     4,     5,     4,     5,     3,     5,     6,     7,
       2,     0,     2,     2,     2,     4,     1,     1,     1,     5,
       4,     2,     0,     1,     0,     1,     0,    15,     0,     1,
       2,     3,     0,     1,     3,     5,     0,     2,     3,     0,
       3,     1,     2,     2,     0,     2,     1,     1,     4,     1,
       7,     0,     2,     0,     1,     1,     2,     4,     4,     4,
       4,     0,     1,     1,     2,     3,     2,     2,     1,     4,
       1,     1,     4,     1,     0,     2,     2,     3,     0,     2,
       0,     1,     0,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     3,     2,     3,
       2,     1,     2,     1,     1,     3,     0,     2
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
  case 6: /* compdef: "DEFINE" "COMPONENT" TOK_ID parameters metadata shell dependency noacc share uservars declare initialize trace save finally display "END"  */
//#line 194 "instrument.y"
      {
        struct comp_def *c;
        c = (comp_def*) palloc(c);
        c->name = (yyvsp[-14].string);
        c->source = str_quote(instr_current_filename);
        c->def_par = (yyvsp[-13].parms).def;
        c->set_par = (yyvsp[-13].parms).set;
        c->out_par = (yyvsp[-13].parms).out;
        c->metadata = list_create();


        // NOTE: metadata was disabled
        /*        
        if (list_len($5)) {
          metadata_assign_from_definition($5);
          list_cat(c->metadata, $5);
        }
        */

        c->flag_noacc   = (yyvsp[-9].linenum);
        c->share_code   = (yyvsp[-8].ccode);
        c->uservar_code = (yyvsp[-7].ccode);
        c->decl_code    = (yyvsp[-6].ccode);
        c->init_code    = (yyvsp[-5].ccode);
        c->trace_code   = (yyvsp[-4].ccode);
        c->save_code    = (yyvsp[-3].ccode);
        c->finally_code = (yyvsp[-2].ccode);
        c->display_code = (yyvsp[-1].ccode);
        c->flag_defined_structure=0;
        c->flag_defined_share=0;
        c->flag_defined_init=0;
        c->flag_defined_save=0;
        c->flag_defined_finally=0;
        c->flag_defined_display=0;
        c->flag_defined_trace=0;
        c->counter_instances=0;

        /* Check definition and setting params for uniqueness */
        check_comp_formals(c->def_par, c->set_par, c->name);
        /* Put component definition in table. */
        symtab_add(read_components, c->name, c);
        if (verbose) fprintf(stderr, "Embedding component %s from file %s\n", c->name, c->source);
      }
//#line 1510 "instrument.tab.c"
    break;

  case 7: /* compdef: "DEFINE" "COMPONENT" TOK_ID "COPY" TOK_ID parameters metadata shell dependency noacc share uservars declare initialize trace save finally display "END"  */
//#line 239 "instrument.y"
      {
        /* create a copy of a comp, and initiate it with given blocks */
        /* all redefined blocks override */
        struct comp_def *def;
        def = read_component((yyvsp[-14].string));
        if (def) {
          struct comp_def *c;
          palloc(c);
          c->name = (yyvsp[-16].string);
          c->source = str_quote(instr_current_filename);
          /* only catenate if defined as non empty  */
          c->def_par   = list_create(); list_cat(c->def_par, def->def_par);
          if (list_len((yyvsp[-13].parms).def)) list_cat(c->def_par,(yyvsp[-13].parms).def);

          c->set_par   = list_create(); list_cat(c->set_par, def->set_par);
          if (list_len((yyvsp[-13].parms).set)) list_cat(c->set_par,(yyvsp[-13].parms).set);

          c->out_par   = list_create(); list_cat(c->out_par, def->out_par);
          if (list_len((yyvsp[-13].parms).out)) list_cat(c->out_par,(yyvsp[-13].parms).out);

          c->metadata = list_create(); if (list_len(def->metadata)) list_cat(c->metadata, def->metadata);
          if (list_len((yyvsp[-12].metadata))) list_cat(c->metadata, (yyvsp[-12].metadata));

          c->flag_noacc = (yyvsp[-9].linenum);
	  
          c->share_code   = ((yyvsp[-8].ccode)->linenum ? (yyvsp[-8].ccode) : def->share_code);
          c->uservar_code = ((yyvsp[-7].ccode)->linenum ? (yyvsp[-7].ccode) : def->uservar_code);
          c->decl_code    = ((yyvsp[-6].ccode)->linenum ? (yyvsp[-6].ccode) : def->decl_code);
          c->init_code    = ((yyvsp[-5].ccode)->linenum ? (yyvsp[-5].ccode) : def->init_code);
          c->trace_code   = ((yyvsp[-4].ccode)->linenum ? (yyvsp[-4].ccode) : def->trace_code);
          c->save_code    = ((yyvsp[-3].ccode)->linenum ? (yyvsp[-3].ccode) : def->save_code);
          c->finally_code = ((yyvsp[-2].ccode)->linenum ? (yyvsp[-2].ccode) : def->finally_code);
          c->display_code = ((yyvsp[-1].ccode)->linenum ? (yyvsp[-1].ccode) : def->display_code);

          /* Check definition and setting params for uniqueness */
          check_comp_formals(c->def_par, c->set_par, c->name);
          /* Put component definition in table. */
          symtab_add(read_components, c->name, c);
          if (verbose) fprintf(stderr, "Embedding component %s from file %s\n", c->name, c->source);
        }

      }
//#line 1557 "instrument.tab.c"
    break;

  case 8: /* share: %empty  */
//#line 285 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 1565 "instrument.tab.c"
    break;

  case 9: /* share: "SHARE" codeblock  */
//#line 289 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 1573 "instrument.tab.c"
    break;

  case 10: /* share: "SHARE" "COPY" TOK_ID  */
//#line 293 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->share_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 1586 "instrument.tab.c"
    break;

  case 11: /* share: "SHARE" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 302 "instrument.y"
      {
        struct comp_def *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->share_code->filename;
          cb->quoted_filename = def->share_code->quoted_filename;
          cb->linenum         = def->share_code->linenum;
          list_cat(cb->lines, def->share_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 1605 "instrument.tab.c"
    break;

  case 12: /* trace: %empty  */
//#line 320 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 1613 "instrument.tab.c"
    break;

  case 13: /* trace: "TRACE" codeblock  */
//#line 324 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 1621 "instrument.tab.c"
    break;

  case 14: /* trace: "TRACE" "COPY" TOK_ID  */
//#line 328 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->trace_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 1634 "instrument.tab.c"
    break;

  case 15: /* trace: "TRACE" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 337 "instrument.y"
      {
        struct comp_def *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->trace_code->filename;
          cb->quoted_filename = def->trace_code->quoted_filename;
          cb->linenum         = def->trace_code->linenum;
          list_cat(cb->lines, def->trace_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 1653 "instrument.tab.c"
    break;

  case 16: /* parameters: def_par set_par out_par state_par pol_par  */
//#line 354 "instrument.y"
      {
        (yyval.parms).def = (yyvsp[-4].formals);
        (yyval.parms).set = (yyvsp[-3].formals);
        (yyval.parms).out = (yyvsp[-2].formals);
      }
//#line 1663 "instrument.tab.c"
    break;

  case 17: /* def_par: %empty  */
//#line 363 "instrument.y"
      {
        (yyval.formals) = list_create();
      }
//#line 1671 "instrument.tab.c"
    break;

  case 18: /* def_par: "DEFINITION" "PARAMETERS" comp_iformallist  */
//#line 367 "instrument.y"
      {
        (yyval.formals) = (yyvsp[0].comp_iformals);
      }
//#line 1679 "instrument.tab.c"
    break;

  case 19: /* set_par: %empty  */
//#line 373 "instrument.y"
      {
        (yyval.formals) = list_create();
      }
//#line 1687 "instrument.tab.c"
    break;

  case 20: /* set_par: "SETTING" "PARAMETERS" comp_iformallist  */
//#line 377 "instrument.y"
      {
        (yyval.formals) = (yyvsp[0].comp_iformals);
      }
//#line 1695 "instrument.tab.c"
    break;

  case 21: /* out_par: %empty  */
//#line 383 "instrument.y"
      {
        (yyval.formals) = list_create();
      }
//#line 1703 "instrument.tab.c"
    break;

  case 22: /* out_par: "OUTPUT" "PARAMETERS" comp_iformallist  */
//#line 387 "instrument.y"
      {
        (yyval.formals) = (yyvsp[0].comp_iformals);
      }
//#line 1711 "instrument.tab.c"
    break;

  case 23: /* out_par: "PRIVATE" "PARAMETERS" comp_iformallist  */
//#line 391 "instrument.y"
      {
        (yyval.formals) = (yyvsp[0].comp_iformals);
      }
//#line 1719 "instrument.tab.c"
    break;

  case 24: /* state_par: %empty  */
//#line 397 "instrument.y"
      {
        /* Do nothing */
      }
//#line 1727 "instrument.tab.c"
    break;

  case 25: /* state_par: "STATE" "PARAMETERS" comp_iformallist  */
//#line 401 "instrument.y"
      {
        /* Issue warning */
        print_error("ERROR: %s is using STATE PARAMETERS\n    %s %s does NOT support this keyword. Please remove line %d.\n", instr_current_filename, MCCODE_NAME,MCCODE_VERSION, instr_current_line);
      }
//#line 1736 "instrument.tab.c"
    break;

  case 26: /* pol_par: %empty  */
//#line 408 "instrument.y"
      {
        /* Do nothing */
      }
//#line 1744 "instrument.tab.c"
    break;

  case 27: /* pol_par: "POLARISATION" "PARAMETERS" comp_iformallist  */
//#line 412 "instrument.y"
      {
        /* Issue warning */
        print_error("ERROR: %s is using POLARISATION PARAMETERS\n    %s %s does NOT support this keyword. Please remove line %d.\n", instr_current_filename, MCCODE_NAME,MCCODE_VERSION, instr_current_line);
      }
//#line 1753 "instrument.tab.c"
    break;

  case 28: /* comp_iformallist: '(' comp_iformals ')'  */
//#line 420 "instrument.y"
      {
        (yyval.comp_iformals) = (yyvsp[-1].comp_iformals);
      }
//#line 1761 "instrument.tab.c"
    break;

  case 29: /* comp_iformals: %empty  */
//#line 426 "instrument.y"
      {
        (yyval.comp_iformals) = list_create();
      }
//#line 1769 "instrument.tab.c"
    break;

  case 30: /* comp_iformals: comp_iformals1  */
//#line 430 "instrument.y"
      {
        (yyval.comp_iformals) = (yyvsp[0].comp_iformals);
      }
//#line 1777 "instrument.tab.c"
    break;

  case 31: /* comp_iformals1: comp_iformal  */
//#line 436 "instrument.y"
      {
        (yyval.comp_iformals) = list_create();
        list_add((yyval.comp_iformals), (yyvsp[0].cformal));
      }
//#line 1786 "instrument.tab.c"
    break;

  case 32: /* comp_iformals1: comp_iformals1 ',' comp_iformal  */
//#line 441 "instrument.y"
      {
        list_add((yyvsp[-2].comp_iformals), (yyvsp[0].cformal));
        (yyval.comp_iformals) = (yyvsp[-2].comp_iformals);
      }
//#line 1795 "instrument.tab.c"
    break;

  case 33: /* comp_iformal: TOK_ID TOK_ID  */
//#line 448 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        if(!strcmp((yyvsp[-1].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-1].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-1].string), "string")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-1].string), "vector")) {
          formal->type = instr_type_vector;
          formal->isoptional = 1;
          formal->default_value = exp_number("NULL");
        } else if(!strcmp((yyvsp[-1].string), "symbol")) {
          formal->type = instr_type_symbol;
        } else {
          print_error("ERROR: Illegal type %s for component "
          "parameter %s at line %s:%d.\n", (yyvsp[-1].string), (yyvsp[0].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[0].string);
        (yyval.cformal) = formal;
      }
//#line 1823 "instrument.tab.c"
    break;

  case 34: /* comp_iformal: TOK_ID '*' TOK_ID  */
//#line 472 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        if(!strcmp((yyvsp[-2].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-2].string), "double")) {
          formal->type = instr_type_vector;
          formal->isoptional = 1;
          formal->default_value = exp_number("NULL");
        } else {
          print_error("ERROR: Illegal type %s* for component "
          "parameter %s at line %s:%d.\n", (yyvsp[-2].string), (yyvsp[0].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[0].string);
        (yyval.cformal) = formal;
      }
//#line 1845 "instrument.tab.c"
    break;

  case 35: /* comp_iformal: TOK_ID  */
//#line 490 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        formal->id = str_dup((yyvsp[0].string));
        formal->isoptional = 0; /* No default value */
        formal->type = instr_type_double;
        (yyval.cformal) = formal;
      }
//#line 1858 "instrument.tab.c"
    break;

  case 36: /* comp_iformal: TOK_ID '=' exp  */
//#line 499 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        formal->type = instr_type_double;
        (yyval.cformal) = formal;
      }
//#line 1872 "instrument.tab.c"
    break;

  case 37: /* comp_iformal: TOK_ID TOK_ID '=' exp  */
//#line 509 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        if(!strcmp((yyvsp[-3].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-3].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-3].string), "string")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-3].string), "vector")) {
          formal->type = instr_type_vector;
        } else if(!strcmp((yyvsp[-3].string), "symbol")) {
          formal->type = instr_type_symbol;
        } else {
          print_error("ERROR: Illegal type %s for component "
          "parameter %s at line %s:%d.\n", (yyvsp[-3].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        (yyval.cformal) = formal;
      }
//#line 1900 "instrument.tab.c"
    break;

  case 38: /* comp_iformal: TOK_ID '*' TOK_ID '=' exp  */
//#line 533 "instrument.y"
      {
        struct comp_iformal *formal;
        formal = (comp_iformal*) palloc(formal);
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        if(!strcmp((yyvsp[-4].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-4].string), "double")) {
          formal->type = instr_type_vector;
        } else {
          print_error("ERROR: Illegal type %s* for component "
          "parameter %s at line %s:%d.\n", (yyvsp[-4].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        (yyval.cformal) = formal;
      }
//#line 1922 "instrument.tab.c"
    break;

  case 39: /* declare: %empty  */
//#line 554 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 1930 "instrument.tab.c"
    break;

  case 40: /* declare: "DECLARE" codeblock  */
//#line 558 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 1938 "instrument.tab.c"
    break;

  case 41: /* declare: "DECLARE" "COPY" TOK_ID  */
//#line 562 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->decl_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 1951 "instrument.tab.c"
    break;

  case 42: /* declare: "DECLARE" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 571 "instrument.y"
      {
        struct comp_def   *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->decl_code->filename;
          cb->quoted_filename = def->decl_code->quoted_filename;
          cb->linenum         = def->decl_code->linenum;
          list_cat(cb->lines, def->decl_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 1970 "instrument.tab.c"
    break;

  case 43: /* uservars: %empty  */
//#line 588 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 1978 "instrument.tab.c"
    break;

  case 44: /* uservars: "USERVARS" codeblock  */
//#line 592 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 1986 "instrument.tab.c"
    break;

  case 45: /* initialize: %empty  */
//#line 598 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 1994 "instrument.tab.c"
    break;

  case 46: /* initialize: "INITIALISE" "COPY" TOK_ID  */
//#line 602 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->init_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 2007 "instrument.tab.c"
    break;

  case 47: /* initialize: "INITIALISE" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 611 "instrument.y"
      {
        struct comp_def   *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->init_code->filename;
          cb->quoted_filename = def->init_code->quoted_filename;
          cb->linenum         = def->init_code->linenum;
          list_cat(cb->lines, def->init_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 2026 "instrument.tab.c"
    break;

  case 48: /* initialize: "INITIALISE" codeblock  */
//#line 626 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 2034 "instrument.tab.c"
    break;

  case 49: /* save: %empty  */
//#line 632 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 2042 "instrument.tab.c"
    break;

  case 50: /* save: "SAVE" codeblock  */
//#line 636 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 2050 "instrument.tab.c"
    break;

  case 51: /* save: "SAVE" "COPY" TOK_ID  */
//#line 640 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->save_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 2063 "instrument.tab.c"
    break;

  case 52: /* save: "SAVE" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 649 "instrument.y"
      {
        struct comp_def *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->save_code->filename;
          cb->quoted_filename = def->save_code->quoted_filename;
          cb->linenum         = def->save_code->linenum;
          list_cat(cb->lines, def->save_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 2082 "instrument.tab.c"
    break;

  case 53: /* finally: %empty  */
//#line 666 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 2090 "instrument.tab.c"
    break;

  case 54: /* finally: "FINALLY" codeblock  */
//#line 670 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 2098 "instrument.tab.c"
    break;

  case 55: /* finally: "FINALLY" "COPY" TOK_ID  */
//#line 674 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->finally_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 2111 "instrument.tab.c"
    break;

  case 56: /* finally: "FINALLY" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 683 "instrument.y"
      {
        struct comp_def *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->finally_code->filename;
          cb->quoted_filename = def->finally_code->quoted_filename;
          cb->linenum         = def->finally_code->linenum;
          list_cat(cb->lines, def->finally_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 2130 "instrument.tab.c"
    break;

  case 57: /* display: %empty  */
//#line 700 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 2138 "instrument.tab.c"
    break;

  case 58: /* display: "DISPLAY" codeblock  */
//#line 704 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 2146 "instrument.tab.c"
    break;

  case 59: /* display: "DISPLAY" "COPY" TOK_ID  */
//#line 708 "instrument.y"
      {
        struct comp_def *def;
        def = read_component((yyvsp[0].string));
        if (def)
          (yyval.ccode) = def->display_code;
        else
          (yyval.ccode) = codeblock_new();
      }
//#line 2159 "instrument.tab.c"
    break;

  case 60: /* display: "DISPLAY" "COPY" TOK_ID "EXTEND" codeblock  */
//#line 717 "instrument.y"
      {
        struct comp_def *def;
        struct code_block *cb;
        cb = codeblock_new();
        def = read_component((yyvsp[-2].string));
        if (def) {
          cb->filename        = def->display_code->filename;
          cb->quoted_filename = def->display_code->quoted_filename;
          cb->linenum         = def->display_code->linenum;
          list_cat(cb->lines, def->display_code->lines);
          list_cat(cb->lines, (yyvsp[0].ccode)->lines);
        }
        (yyval.ccode) = cb;
      }
//#line 2178 "instrument.tab.c"
    break;

  case 61: /* $@1: %empty  */
//#line 740 "instrument.y"
      {
        if (!instrument_definition->formals) instrument_definition->formals = (yyvsp[0].iformals);
        else { if (list_len((yyvsp[0].iformals))) list_cat(instrument_definition->formals,(yyvsp[0].iformals)); }
        if (!instrument_definition->name)    instrument_definition->name = (yyvsp[-1].string);
        else {
          if (verbose) fprintf(stderr, "Catenate instrument %s to master instrument %s\n", (yyvsp[-1].string), instrument_definition->name);
          instrument_definition->has_included_instr++;
        }
      }
//#line 2192 "instrument.tab.c"
    break;

  case 62: /* instrument: "DEFINE" "INSTRUMENT" TOK_ID instrpar_list $@1 shell dependency declare uservars initialize instr_trace save finally "END"  */
//#line 766 "instrument.y"
      {
        if (!instrument_definition->decls) instrument_definition->decls = (yyvsp[-6].ccode);
        else list_cat(instrument_definition->decls->lines, (yyvsp[-6].ccode)->lines);
        if (!instrument_definition->vars) instrument_definition->vars = (yyvsp[-5].ccode);
        else list_cat(instrument_definition->vars->lines, (yyvsp[-5].ccode)->lines);
        if (!instrument_definition->inits) instrument_definition->inits = (yyvsp[-4].ccode);
        else list_cat(instrument_definition->inits->lines, (yyvsp[-4].ccode)->lines);
        if (!instrument_definition->saves) instrument_definition->saves = (yyvsp[-2].ccode);
        else list_cat(instrument_definition->saves->lines, (yyvsp[-2].ccode)->lines);
        if (!instrument_definition->finals) instrument_definition->finals = (yyvsp[-1].ccode);
        else list_cat(instrument_definition->finals->lines, (yyvsp[-1].ccode)->lines);

        instrument_definition->compmap = comp_instances;
        instrument_definition->groupmap = group_instances;
        instrument_definition->complist = comp_instances_list;
        instrument_definition->grouplist = group_instances_list;

        instrument_definition->metadata = list_create();
        if (verbose) fprintf(stderr, "Combine metadata blocks into table\n");


        // NOTE: metadata was disabled
        //if (metadata_construct_table(instrument_definition)) {
        //  print_error(MCCODE_NAME ": Combining metadata blocks into table failed for %s\n", instr_current_filename);
        //  exit(1);
        //}
        //if (verbose) fprintf(stderr, "Processed %d metadata blocks\n", list_len(instrument_definition->metadata));

        /* Check instrument parameters for uniqueness */
        check_instrument_formals(instrument_definition->formals, instrument_definition->name);
        if (verbose && !error_encountered) fprintf(stderr, "Creating instrument '%s' (with %li component instances)\n", (yyvsp[-11].string), comp_current_index);
      }
//#line 2229 "instrument.tab.c"
    break;

  case 63: /* instrpar_list: '(' instr_formals ')'  */
//#line 803 "instrument.y"
      {
        (yyval.iformals) = (yyvsp[-1].iformals);
      }
//#line 2237 "instrument.tab.c"
    break;

  case 64: /* instr_formals: %empty  */
//#line 809 "instrument.y"
      {
        (yyval.iformals) = list_create();
      }
//#line 2245 "instrument.tab.c"
    break;

  case 65: /* instr_formals: instr_formals1  */
//#line 813 "instrument.y"
      {
        (yyval.iformals) = (yyvsp[0].iformals);
      }
//#line 2253 "instrument.tab.c"
    break;

  case 66: /* instr_formals1: instr_formal  */
//#line 819 "instrument.y"
      {
        (yyval.iformals) = list_create();
        list_add((yyval.iformals), (yyvsp[0].iformal));
      }
//#line 2262 "instrument.tab.c"
    break;

  case 67: /* instr_formals1: instr_formals1 ',' instr_formal  */
//#line 824 "instrument.y"
      {
        list_add((yyvsp[-2].iformals), (yyvsp[0].iformal));
        (yyval.iformals) = (yyvsp[-2].iformals);
      }
//#line 2271 "instrument.tab.c"
    break;

  case 68: /* instr_formal: TOK_ID TOK_ID  */
//#line 831 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-1].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-1].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-1].string), "string")) {
          formal->type = instr_type_string;
        } else {
          print_error("ERROR: Illegal type %s for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-1].string), (yyvsp[0].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[0].string);
        formal->hasunit = 0;
        (yyval.iformal) = formal;
      }
//#line 2294 "instrument.tab.c"
    break;

  case 69: /* instr_formal: TOK_ID '*' TOK_ID  */
//#line 850 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-2].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-2].string), "double")) {
          formal->type = instr_type_vector;
        } else {
          print_error("ERROR: Illegal type $s* for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-2].string), (yyvsp[0].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[0].string);
        formal->hasunit = 0;
        (yyval.iformal) = formal;
      }
//#line 2315 "instrument.tab.c"
    break;

  case 70: /* instr_formal: TOK_ID  */
//#line 867 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->type = instr_type_double;
        formal->id = (yyvsp[0].string);
        formal->isoptional = 0; /* No default value */
        formal->hasunit = 0;
        (yyval.iformal) = formal;
      }
//#line 2329 "instrument.tab.c"
    break;

  case 71: /* instr_formal: TOK_ID '=' exp  */
//#line 877 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        formal->type = instr_type_double;
        formal->hasunit = 0;
        (yyval.iformal) = formal;
      }
//#line 2344 "instrument.tab.c"
    break;

  case 72: /* instr_formal: TOK_ID TOK_ID '=' exp  */
//#line 888 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-3].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-3].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-3].string), "string")) {
          formal->type = instr_type_string;
        } else {
          print_error("ERROR: Illegal type %s for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-3].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        formal->hasunit = 0;
        (yyval.iformal) = formal;
      }
//#line 2369 "instrument.tab.c"
    break;

  case 73: /* instr_formal: TOK_ID '*' TOK_ID '=' exp  */
//#line 909 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp);
        if(!strcmp((yyvsp[-4].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-4].string), "double")) {
          formal->type = instr_type_vector;
        } else {
          print_error("ERROR: Illegal type %s* for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-4].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
          formal->hasunit = 0;
        }
        (yyval.iformal) = formal;
      }
//#line 2392 "instrument.tab.c"
    break;

  case 74: /* instr_formal: TOK_ID TOK_ID '/' TOK_STRING  */
//#line 928 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-3].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-3].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-3].string), "string")) {
          formal->type = instr_type_string;
        } else {
          print_error("ERROR: Illegal type %s for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-3].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[-2].string);
        formal->hasunit = 1;
        formal->unit = (yyvsp[0].string);
        (yyval.iformal) = formal;
      }
//#line 2416 "instrument.tab.c"
    break;

  case 75: /* instr_formal: TOK_ID '*' TOK_ID '/' TOK_STRING  */
//#line 948 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-4].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-4].string), "double")) {
          formal->type = instr_type_vector;
        } else {
          print_error("ERROR: Illegal type $s* for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-4].string), (yyvsp[-2].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[-2].string);
        formal->hasunit = 1;
        formal->unit = (yyvsp[0].string);
        (yyval.iformal) = formal;
      }
//#line 2438 "instrument.tab.c"
    break;

  case 76: /* instr_formal: TOK_ID '/' TOK_STRING  */
//#line 966 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->type = instr_type_double;
        formal->id = (yyvsp[-2].string);
        formal->isoptional = 0; /* No default value */
        formal->hasunit = 1;
        formal->unit = (yyvsp[0].string);
        (yyval.iformal) = formal;
      }
//#line 2453 "instrument.tab.c"
    break;

  case 77: /* instr_formal: TOK_ID '/' TOK_STRING '=' exp  */
//#line 977 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->id = (yyvsp[-4].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp); //$6;
        formal->type = instr_type_double;
        formal->hasunit = 1;
        formal->unit = (yyvsp[-2].string);
        (yyval.iformal) = formal;
      }
//#line 2469 "instrument.tab.c"
    break;

  case 78: /* instr_formal: TOK_ID TOK_ID '/' TOK_STRING '=' exp  */
//#line 989 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        if(!strcmp((yyvsp[-5].string), "double")) {
          formal->type = instr_type_double;
        } else if(!strcmp((yyvsp[-5].string), "int")) {
          formal->type = instr_type_int;
        } else if(!strcmp((yyvsp[-5].string), "string")) {
          formal->type = instr_type_string;
        } else {
          print_error("ERROR: Illegal type %s for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-5].string), (yyvsp[-4].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->id = (yyvsp[-4].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp); // $7;
        formal->hasunit = 1;
        formal->unit = (yyvsp[-2].string);
        (yyval.iformal) = formal;
      }
//#line 2495 "instrument.tab.c"
    break;

  case 79: /* instr_formal: TOK_ID '*' TOK_ID '/' TOK_STRING '=' exp  */
//#line 1011 "instrument.y"
      {
        struct instr_formal *formal;
        formal = (instr_formal*) palloc(formal);
        formal->id = (yyvsp[-4].string);
        formal->isoptional = 1; /* Default value available */
        formal->default_value = (yyvsp[0].exp); // $8;
        if(!strcmp((yyvsp[-6].string), "char")) {
          formal->type = instr_type_string;
        } else if(!strcmp((yyvsp[-6].string), "double")) {
          formal->type = instr_type_vector;
        } else {
          print_error("ERROR: Illegal type %s* for instrument "
          "parameter %s at line %s:%d.\n", (yyvsp[-6].string), (yyvsp[-4].string), instr_current_filename, instr_current_line);
          formal->type = instr_type_double;
        }
        formal->hasunit = 1;
        formal->unit = (yyvsp[-2].string);
        (yyval.iformal) = formal;
      }
//#line 2519 "instrument.tab.c"
    break;

  case 81: /* complist: %empty  */
//#line 1037 "instrument.y"
      {
        if (!comp_instances)      comp_instances      = symtab_create();
        if (!comp_instances_list) comp_instances_list = list_create();
        if (!group_instances)     group_instances     = symtab_create();
        if (!group_instances_list)group_instances_list= list_create();
      }
//#line 2530 "instrument.tab.c"
    break;

  case 82: /* complist: complist component  */
//#line 1044 "instrument.y"
      {
        if (!(yyvsp[0].instance)->removable) { /* must not be a REMOVABLE COMPONENT after %include instr */
          /* Check that the component instance name has not been used before. */
          if(symtab_lookup(comp_instances, (yyvsp[0].instance)->name))
          {
            print_error("ERROR: Multiple use of component instance name "
            "'%s' at line %s:%d.\nPlease change the instance name.\n", (yyvsp[0].instance)->name, instr_current_filename, instr_current_line);
            /* Since this is an error condition, we do not
              worry about freeing the memory allocated for
              the component instance. */
          }
          /* check that instance name does not match any OUTPUT/SETTING/DEFINITION parameter */
          else
          {
            if ((yyvsp[0].instance)->def) {
              List_handle          liter;
              char                *par;
              struct comp_iformal *formal;

              liter = list_iterate((yyvsp[0].instance)->def->out_par);
              while((par = (char*) list_next(liter))) {
                if (!strcmp((yyvsp[0].instance)->name, par))
                  print_error("ERROR: Component instance name "
              "'%s' matches an internal OUTPUT parameter of component class %s at "
              "line %s:%d.\nPlease change the instance name.\n",
              (yyvsp[0].instance)->name, (yyvsp[0].instance)->def->name, instr_current_filename, instr_current_line);
              }
              list_iterate_end(liter);

              liter = list_iterate((yyvsp[0].instance)->def->set_par);
              while((formal = (comp_iformal*) list_next(liter))) {
                if (!strcmp((yyvsp[0].instance)->name, formal->id))
                  print_error("ERROR: Component instance name "
                  "'%s' matches an internal SETTING parameter of component class %s at "
                  "line %s:%d.\nPlease change the instance name.\n",
                  (yyvsp[0].instance)->name, (yyvsp[0].instance)->def->name, instr_current_filename, instr_current_line);
              }
              list_iterate_end(liter);

              liter = list_iterate((yyvsp[0].instance)->def->def_par);
              while((formal = (comp_iformal*) list_next(liter))) {
                if (!strcmp((yyvsp[0].instance)->name, formal->id))
                  print_error("ERROR: Component instance name "
                  "'%s' matches an internal DEFINITION parameter of component class %s at "
                  "line %s:%d.\nPlease change the instance name.\n",
                  (yyvsp[0].instance)->name, (yyvsp[0].instance)->def->name, instr_current_filename, instr_current_line);
              }
              list_iterate_end(liter);
            }

            /* if we come there, instance is not an OUTPUT name */
            symtab_add(comp_instances, (yyvsp[0].instance)->name, (yyvsp[0].instance));
            list_add(comp_instances_list, (yyvsp[0].instance));
            if (verbose && (yyvsp[0].instance)->def)
              fprintf(stderr, "Component[%li]: %s = %s().\n", comp_current_index, (yyvsp[0].instance)->name, (yyvsp[0].instance)->def->name);
          }
        } /* if shared */
        else
        {
          if (verbose && (yyvsp[0].instance)->def) fprintf(stderr, "Component[%li]: %s = %s() SKIPPED (REMOVABLE COMPONENT when included)\n", comp_current_index, (yyvsp[0].instance)->name, (yyvsp[0].instance)->def->name);
        }
      }
//#line 2597 "instrument.tab.c"
    break;

  case 83: /* complist: complist instrument  */
//#line 1107 "instrument.y"
    {
      /* included instrument */
    }
//#line 2605 "instrument.tab.c"
    break;

  case 84: /* complist: complist search  */
//#line 1111 "instrument.y"
    {
      /* extend the search path inside of trace */
    }
//#line 2613 "instrument.tab.c"
    break;

  case 85: /* instname: "COPY" '(' TOK_ID ')'  */
//#line 1117 "instrument.y"
      {
        char str_index[64];
        sprintf(str_index, "_%li", comp_current_index+1);
        (yyval.string) = str_cat((yyvsp[-1].string), str_index, NULL);
      }
//#line 2623 "instrument.tab.c"
    break;

  case 86: /* instname: "MYSELF"  */
//#line 1123 "instrument.y"
      {
        char str_index[64];
        sprintf(str_index, "_%li", comp_current_index+1);
        (yyval.string) = str_cat("Comp", str_index, NULL);
      }
//#line 2633 "instrument.tab.c"
    break;

  case 87: /* instname: "COPY"  */
//#line 1129 "instrument.y"
      {
        char str_index[64];
        sprintf(str_index, "_%li", comp_current_index+1);
        (yyval.string) = str_cat("Comp", str_index, NULL);
      }
//#line 2643 "instrument.tab.c"
    break;

  case 88: /* instname: TOK_ID  */
//#line 1135 "instrument.y"
      {
        (yyval.string) = (yyvsp[0].string);
      }
//#line 2651 "instrument.tab.c"
    break;

  case 89: /* instref: "COPY" '(' compref ')' actuallist  */
//#line 1141 "instrument.y"
      {
        struct comp_inst *comp_src;
        struct comp_inst *comp;
        comp_src = (yyvsp[-2].instance);
        comp = (comp_inst*) palloc(comp);
        comp->def    = comp_src->def;
        comp->extend = comp_src->extend;
        comp->group  = comp_src->group;
        comp->jump   = comp_src->jump;
        comp->when   = comp_src->when;
        /* now catenate src and actual parameters */
        comp->actuals= symtab_create();
        symtab_cat(comp->actuals, (yyvsp[0].actuals));
        symtab_cat(comp->actuals, comp_src->actuals);
        //comp->metadata = metadata_list_copy(comp_src->metadata);
        (yyval.instance) = comp;
      }
//#line 2673 "instrument.tab.c"
    break;

  case 90: /* instref: "COPY" '(' compref ')'  */
//#line 1159 "instrument.y"
      {
        struct comp_inst *comp_src;
        struct comp_inst *comp;
        comp_src = (yyvsp[-1].instance);
        comp = (comp_inst*) palloc(comp);
        comp->defpar = comp_src->defpar;
        comp->setpar = comp_src->setpar;
        comp->def    = comp_src->def;
        comp->extend = comp_src->extend;
        comp->group  = comp_src->group;
        comp->jump   = comp_src->jump;
        comp->when   = comp_src->when;
        comp->actuals= comp_src->actuals;
        //comp->metadata = metadata_list_copy(comp_src->metadata);
        (yyval.instance) = comp;
      }
//#line 2694 "instrument.tab.c"
    break;

  case 91: /* instref: TOK_ID actuallist  */
//#line 1176 "instrument.y"
      {
        struct comp_def *def;
        struct comp_inst *comp;
        def = (comp_def*) read_component((yyvsp[-1].string));
        comp = (comp_inst*) palloc(comp);

        comp->def          = def;
        comp->extend = codeblock_new();
        comp->group  = NULL;
        comp->jump   = list_create();
        comp->when   = NULL;
        comp->actuals= (yyvsp[0].actuals);
        //comp->metadata = metadata_list_copy(def->metadata);
        (yyval.instance) = comp;
      }
//#line 2714 "instrument.tab.c"
    break;

  case 92: /* removable: %empty  */
//#line 1194 "instrument.y"
      {
        (yyval.linenum) = 0;
      }
//#line 2722 "instrument.tab.c"
    break;

  case 93: /* removable: "REMOVABLE"  */
//#line 1198 "instrument.y"
      {
        (yyval.linenum) = instrument_definition->has_included_instr; /* ignore comp if included from other instrument */
      }
//#line 2730 "instrument.tab.c"
    break;

  case 94: /* cpuonly: %empty  */
//#line 1205 "instrument.y"
      {
        (yyval.linenum) = 0;
      }
//#line 2738 "instrument.tab.c"
    break;

  case 95: /* cpuonly: "CPU"  */
//#line 1209 "instrument.y"
      {
        (yyval.linenum) = 1;
	if (strstr(instrument_definition->dependency," -DFUNNEL ") == NULL) {
	  strncat(instrument_definition->dependency, " -DFUNNEL ", 1024);
	}
      }
//#line 2749 "instrument.tab.c"
    break;

  case 96: /* $@2: %empty  */
//#line 1218 "instrument.y"
      {
        struct comp_inst *comp;
        myself_comp = comp = (yyvsp[0].instance);

        // Trying to check or assign metadata before the previous line is accessing a null pointer!
        if (comp->metadata == NULL || list_undef(comp->metadata)) comp->metadata = list_create();
        if (myself_comp->metadata == NULL || list_undef(myself_comp->metadata)) myself_comp->metadata = list_create();

        comp->name  = (yyvsp[-2].string);
        comp->split = (yyvsp[-4].exp);
        comp->cpuonly = (yyvsp[-5].linenum);


        // NOTE: cpu-only; this hack causes problems during parsing, with comp->def being NULL
        //if (!comp->cpuonly) {
        //  comp->cpuonly = comp->def->flag_noacc;
        //}

        comp->removable = (yyvsp[-6].linenum);
        comp->index = ++comp_current_index;     /* index of comp instance */
        
        if(comp->def != NULL)
        {
          /* Check actual parameters against definition and
                         setting parameters. */
          comp_formals_actuals(comp, comp->actuals);
        }
      }
//#line 2778 "instrument.tab.c"
    break;

  case 97: /* component: removable cpuonly split "COMPONENT" instname '=' instref $@2 when place orientation groupref extend jumps metadata  */
//#line 1243 "instrument.y"
      {
        struct comp_inst *comp = myself_comp;

        if ((yyvsp[-6].exp)) comp->when  = (yyvsp[-6].exp);

        comp->pos = (comp_position*) palloc(comp->pos);
        comp->pos->place           = (yyvsp[-5].place).place;
        comp->pos->place_rel       = (yyvsp[-5].place).place_rel;
        comp->pos->orientation     = (yyvsp[-4].ori).orientation;
        comp->pos->orientation_rel =
            (yyvsp[-4].ori).isdefault ? (yyvsp[-5].place).place_rel : (yyvsp[-4].ori).orientation_rel;

        if ((yyvsp[-3].groupinst)) {
          comp->group = (yyvsp[-3].groupinst);    /* component is part of an exclusive group */
          /* store first and last comp of group. Check if a SPLIT is inside */
          if (!comp->group->first_comp) {
             comp->group->first_comp       = comp->name;
             comp->group->first_comp_index = comp->index;
          }
          comp->group->last_comp      =comp->name;
          comp->group->last_comp_index=comp->index;
          if (comp->split) {
	    if (strcmp(comp->name, comp->group->first_comp)) {
	      print_error("FATAL ERROR:\n\tComponent %s=%s() at line %s:%d is in GROUP %s and has a SPLIT.\n"
			  "\tOnly the first component of a GROUP may impose SPLIT, so please only include \n"
			  "\tSPLIT on %s (first in GROUP) or better yet to an earlier component!\n\n",
			  comp->name, comp->def->name, instr_current_filename, instr_current_line, (yyvsp[-3].groupinst)->name,
			  comp->group->first_comp);
	      exit(-1);
	    } else {
	      print_warn(NULL," Component %s=%s() at line %s:%d is 1st in GROUP %s and has a SPLIT.\n"
			  "\tBest practice is to move the SPLIT to an earlier component.\n\n",
			  comp->name, comp->def->name, instr_current_filename, instr_current_line, (yyvsp[-3].groupinst)->name);
	    }
	  }
        }
        if ((yyvsp[-2].ccode)->linenum) {
	  if (comp->extend->linenum>0) {
	    fprintf(stderr, "\n-----------------------------------------------------------\n");
	    fprintf(stderr, "WARNING: Existing (COPY) EXTEND block in COMPONENT %s:\n", comp->name);
	    List_handle liter = list_iterate(comp->extend->lines);
	    List_handle liter2 = list_iterate((yyvsp[-2].ccode)->lines);
	    char *line, *line2;
	    fprintf(stderr, "  EXTEND %%{\n");
	    while((line = (char*) list_next(liter))) {
	      fprintf(stderr, "  %s",line);
	    }
	    list_iterate_end(liter);
	    fprintf(stderr, "  %%}\n");
	    fprintf(stderr, "\nis overwritten by:\n");
	    fprintf(stderr, "  EXTEND %%{\n");
	    while((line2 = (char*) list_next(liter2))) {
	      fprintf(stderr, "  %s",line2);
	    }
	    list_iterate_end(liter2);
	    fprintf(stderr, "  %%}\n-----------------------------------------------------------\n");
	  }
	  comp->extend= (yyvsp[-2].ccode);  /* EXTEND block*/
	}
        if (list_len((yyvsp[-1].jumps)))  comp->jump  = (yyvsp[-1].jumps);

        /* one or more metadata statements -- the Component definition *can also* add to this list */
        /* So the list *was* created above and should not be re-created now! */
        //if (list_len($15)){
        // metadata_assign_from_instance($15);
        // list_cat(comp->metadata, $15);
        //}


        // TODO: define debugn
        //debugn((DEBUG_HIGH, "Component[%i]: %s = %s().\n", comp_current_index, $5, $7->def->name));


        /* this comp will be 'previous' for the next, except if removed at include */
        if (!comp->removable) previous_comp = comp;
        (yyval.instance) = comp;

      }
//#line 2861 "instrument.tab.c"
    break;

  case 98: /* split: %empty  */
//#line 1324 "instrument.y"
      {
        (yyval.exp) = NULL;
      }
//#line 2869 "instrument.tab.c"
    break;

  case 99: /* split: "SPLIT"  */
//#line 1328 "instrument.y"
      {
        (yyval.exp) = exp_number("10");
      }
//#line 2877 "instrument.tab.c"
    break;

  case 100: /* split: "SPLIT" exp  */
//#line 1332 "instrument.y"
      {
        (yyval.exp) = (yyvsp[0].exp);
      }
//#line 2885 "instrument.tab.c"
    break;

  case 101: /* actuallist: '(' actuals ')'  */
//#line 1339 "instrument.y"
      {
        (yyval.actuals) = (yyvsp[-1].actuals);
      }
//#line 2893 "instrument.tab.c"
    break;

  case 102: /* actuals: %empty  */
//#line 1345 "instrument.y"
      {
        (yyval.actuals) = symtab_create();
      }
//#line 2901 "instrument.tab.c"
    break;

  case 103: /* actuals: actuals1  */
//#line 1349 "instrument.y"
      {
        (yyval.actuals) = (yyvsp[0].actuals);
      }
//#line 2909 "instrument.tab.c"
    break;

  case 104: /* actuals1: TOK_ID '=' exp  */
//#line 1355 "instrument.y"
      {
        (yyval.actuals) = symtab_create();
        symtab_add((yyval.actuals), (yyvsp[-2].string), (yyvsp[0].exp));
        str_free((yyvsp[-2].string));
      }
//#line 2919 "instrument.tab.c"
    break;

  case 105: /* actuals1: actuals1 ',' TOK_ID '=' exp  */
//#line 1361 "instrument.y"
      {
        symtab_add((yyvsp[-4].actuals), (yyvsp[-2].string), (yyvsp[0].exp));
        str_free((yyvsp[-2].string));
        (yyval.actuals) = (yyvsp[-4].actuals);
      }
//#line 2929 "instrument.tab.c"
    break;

  case 106: /* when: %empty  */
//#line 1369 "instrument.y"
    {
      (yyval.exp) = NULL;
    }
//#line 2937 "instrument.tab.c"
    break;

  case 107: /* when: "WHEN" exp  */
//#line 1373 "instrument.y"
    {
      (yyval.exp) = (yyvsp[0].exp);
    }
//#line 2945 "instrument.tab.c"
    break;

  case 108: /* place: "AT" coords reference  */
//#line 1379 "instrument.y"
      {
        (yyval.place).place = (yyvsp[-1].coords);
        (yyval.place).place_rel = (yyvsp[0].instance);
      }
//#line 2954 "instrument.tab.c"
    break;

  case 109: /* orientation: %empty  */
//#line 1386 "instrument.y"
      {
        (yyval.ori).orientation = coords_exp_origo(); /* Default to (0,0,0). */
        (yyval.ori).isdefault = 1; /* No ROTATED modifier was present */
      }
//#line 2963 "instrument.tab.c"
    break;

  case 110: /* orientation: "ROTATED" coords reference  */
//#line 1391 "instrument.y"
      {
        (yyval.ori).orientation = (yyvsp[-1].coords);
        (yyval.ori).orientation_rel = (yyvsp[0].instance);
        (yyval.ori).isdefault = 0;
      }
//#line 2973 "instrument.tab.c"
    break;

  case 111: /* reference: "ABSOLUTE"  */
//#line 1400 "instrument.y"
      {
        (yyval.instance) = NULL;
      }
//#line 2981 "instrument.tab.c"
    break;

  case 112: /* reference: "RELATIVE" "ABSOLUTE"  */
//#line 1404 "instrument.y"
      {
        (yyval.instance) = NULL; /* tolerate this reference error */
      }
//#line 2989 "instrument.tab.c"
    break;

  case 113: /* reference: "RELATIVE" compref  */
//#line 1408 "instrument.y"
      {
        (yyval.instance) = (yyvsp[0].instance);
      }
//#line 2997 "instrument.tab.c"
    break;

  case 114: /* groupref: %empty  */
//#line 1415 "instrument.y"
      {
        (yyval.groupinst) = NULL;
      }
//#line 3005 "instrument.tab.c"
    break;

  case 115: /* groupref: "GROUP" groupdef  */
//#line 1419 "instrument.y"
      {
        (yyval.groupinst) = (yyvsp[0].groupinst);
      }
//#line 3013 "instrument.tab.c"
    break;

  case 116: /* groupdef: TOK_ID  */
//#line 1425 "instrument.y"
      {
        struct group_inst *group;
        struct Symtab_entry *ent;

        ent = symtab_lookup(group_instances, (yyvsp[0].string));
        if(ent == NULL)
        {
          group = (group_inst*) palloc(group);    /* create new group instance */
          group->name       = (yyvsp[0].string);
          group->index      = 0;
          group->first_comp = NULL;
          group->last_comp  = NULL;
          group->first_comp_index = 0;
          group->last_comp_index  = 0;
          symtab_add(group_instances, (yyvsp[0].string), group);
          list_add(group_instances_list, group);
        }
        else
          group = (group_inst*) ent->val;
        (yyval.groupinst) = group;
      }
//#line 3039 "instrument.tab.c"
    break;

  case 117: /* compref: "PREVIOUS"  */
//#line 1449 "instrument.y"
      {
        if (previous_comp) {
          (yyval.instance) = previous_comp;
        } else {
          print_warn(NULL, "Found invalid PREVIOUS reference at line %s:%d. Using ABSOLUTE.\n", instr_current_filename, instr_current_line);
          (yyval.instance) = NULL;
        }
      }
//#line 3052 "instrument.tab.c"
    break;

  case 118: /* compref: "PREVIOUS" '(' TOK_NUMBER ')'  */
//#line 1458 "instrument.y"
      {
        /* get the $3 previous item in comp_instances */
        struct Symtab_entry *entry;
        int index;
        index = atoi((yyvsp[-1].number));
        entry = symtab_previous(comp_instances, index);
        if (!index || !entry) { /* invalid index reference */
          print_warn(NULL, "Found invalid PREVIOUS(%i) reference at line %s:%d. Using ABSOLUTE.\n", index, instr_current_filename, instr_current_line);
          (yyval.instance) = NULL;
        } else {
          (yyval.instance) = (comp_inst*) entry->val;
        }
      }
//#line 3070 "instrument.tab.c"
    break;

  case 119: /* compref: TOK_ID  */
//#line 1472 "instrument.y"
      {
        struct comp_inst *comp;
        struct Symtab_entry *ent;

        ent = symtab_lookup(comp_instances, (yyvsp[0].string));
        comp = NULL;
        if(ent == NULL)
          print_error("ERROR: Reference to undefined component instance %s at line %s:%d.\n",
          (yyvsp[0].string), instr_current_filename, instr_current_line);
        else
          comp = (comp_inst*) ent->val;
        str_free((yyvsp[0].string));
        (yyval.instance) = comp;
      }
//#line 3089 "instrument.tab.c"
    break;

  case 120: /* coords: '(' exp ',' exp ',' exp ')'  */
//#line 1489 "instrument.y"
      {
        (yyval.coords).x = (yyvsp[-5].exp);
        (yyval.coords).y = (yyvsp[-3].exp);
        (yyval.coords).z = (yyvsp[-1].exp);
      }
//#line 3099 "instrument.tab.c"
    break;

  case 121: /* extend: %empty  */
//#line 1498 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 3107 "instrument.tab.c"
    break;

  case 122: /* extend: "EXTEND" codeblock  */
//#line 1502 "instrument.y"
      {
        (yyval.ccode) = (yyvsp[0].ccode);
      }
//#line 3115 "instrument.tab.c"
    break;

  case 123: /* metadata: %empty  */
//#line 1508 "instrument.y"
{
  (yyval.metadata) = list_create();
}
//#line 3123 "instrument.tab.c"
    break;

  case 124: /* metadata: metadata1  */
//#line 1512 "instrument.y"
{
  (yyval.metadata) = (yyvsp[0].metadata);
}
//#line 3131 "instrument.tab.c"
    break;

  case 125: /* metadata1: metadatum  */
//#line 1518 "instrument.y"
{
  (yyval.metadata) = list_create();
  list_add((yyval.metadata), (yyvsp[0].metadatum));
}
//#line 3140 "instrument.tab.c"
    break;

  case 126: /* metadata1: metadata1 metadatum  */
//#line 1523 "instrument.y"
{
  list_add((yyvsp[-1].metadata), (yyvsp[0].metadatum));
  (yyval.metadata) = (yyvsp[-1].metadata);
}
//#line 3149 "instrument.tab.c"
    break;

  case 127: /* metadatum: "METADATA" TOK_ID TOK_ID codeblock  */
//#line 1532 "instrument.y"
{
  struct metadata_struct * metadatum;
  metadatum = (metadata_struct*) palloc(metadatum);
  metadatum->source = NULL;
  metadatum->type = str_dup((yyvsp[-2].string));
  metadatum->name = str_dup((yyvsp[-1].string));
  metadatum->lines = list_create(); if (list_len((yyvsp[0].ccode)->lines)) list_cat(metadatum->lines, (yyvsp[0].ccode)->lines);
  (yyval.metadatum) = metadatum; // This would be very bad to omit. Don't do that!
}
//#line 3163 "instrument.tab.c"
    break;

  case 128: /* metadatum: "METADATA" TOK_ID TOK_STRING codeblock  */
//#line 1543 "instrument.y"
{
  struct metadata_struct * metadatum;
  metadatum = (metadata_struct*) palloc(metadatum);
  metadatum->source = NULL;
  metadatum->type = str_dup((yyvsp[-2].string));
  char * tmp_key = (char*) malloc(((strlen((yyvsp[-1].string))+3)*sizeof(char)));
  sprintf(tmp_key, "\"%s\"", (yyvsp[-1].string));
  metadatum->name = str_quote(tmp_key);
  free(tmp_key);
  metadatum->lines = list_create(); if (list_len((yyvsp[0].ccode)->lines)) list_cat(metadatum->lines, (yyvsp[0].ccode)->lines);
  (yyval.metadatum) = metadatum; // This would be very bad to omit. Don't do that!
}
//#line 3180 "instrument.tab.c"
    break;

  case 129: /* metadatum: "METADATA" TOK_STRING TOK_ID codeblock  */
//#line 1558 "instrument.y"
{
  struct metadata_struct * metadatum;
  metadatum = (metadata_struct*) palloc(metadatum);
  metadatum->source = NULL;
  metadatum->type = str_dup((yyvsp[-2].string));
  metadatum->name = str_dup((yyvsp[-1].string));
  metadatum->lines = list_create(); if (list_len((yyvsp[0].ccode)->lines)) list_cat(metadatum->lines, (yyvsp[0].ccode)->lines);
  (yyval.metadatum) = metadatum; // This would be very bad to omit. Don't do that!
}
//#line 3194 "instrument.tab.c"
    break;

  case 130: /* metadatum: "METADATA" TOK_STRING TOK_STRING codeblock  */
//#line 1569 "instrument.y"
{
  struct metadata_struct * metadatum;
  metadatum = (metadata_struct*) palloc(metadatum);
  metadatum->source = NULL;
  metadatum->type = str_dup((yyvsp[-2].string));
  char * tmp_key = (char*) malloc(((strlen((yyvsp[-1].string))+3)*sizeof(char)));
  sprintf(tmp_key, "\"%s\"", (yyvsp[-1].string));
  metadatum->name = str_quote(tmp_key);
  free(tmp_key);
  metadatum->lines = list_create(); if (list_len((yyvsp[0].ccode)->lines)) list_cat(metadatum->lines, (yyvsp[0].ccode)->lines);
  (yyval.metadatum) = metadatum; // This would be very bad to omit. Don't do that!
}
//#line 3211 "instrument.tab.c"
    break;

  case 131: /* jumps: %empty  */
//#line 1585 "instrument.y"
    {
      (yyval.jumps) = list_create();
    }
//#line 3219 "instrument.tab.c"
    break;

  case 132: /* jumps: jumps1  */
//#line 1589 "instrument.y"
    {
      (yyval.jumps) = (yyvsp[0].jumps);
    }
//#line 3227 "instrument.tab.c"
    break;

  case 133: /* jumps1: jump  */
//#line 1595 "instrument.y"
    {
      (yyval.jumps) = list_create();
      list_add((yyval.jumps), (yyvsp[0].jump));
    }
//#line 3236 "instrument.tab.c"
    break;

  case 134: /* jumps1: jumps1 jump  */
//#line 1600 "instrument.y"
    {
      list_add((yyvsp[-1].jumps), (yyvsp[0].jump));
      (yyval.jumps) = (yyvsp[-1].jumps);
    }
//#line 3245 "instrument.tab.c"
    break;

  case 135: /* jump: "JUMP" jumpname jumpcondition  */
//#line 1607 "instrument.y"
    {
      struct jump_struct *jump;
      jump = (jump_struct*) palloc(jump);
      jump->target      =(yyvsp[-1].jumpname).name;
      jump->target_index=(yyvsp[-1].jumpname).index;
      jump->condition  = (yyvsp[0].jumpcondition).condition;
      jump->iterate    = (yyvsp[0].jumpcondition).iterate;
      (yyval.jump)=jump;
    }
//#line 3259 "instrument.tab.c"
    break;

  case 136: /* jumpcondition: "WHEN" exp  */
//#line 1619 "instrument.y"
    {
      (yyval.jumpcondition).condition = (yyvsp[0].exp);
      (yyval.jumpcondition).iterate   = 0;
    }
//#line 3268 "instrument.tab.c"
    break;

  case 137: /* jumpcondition: "ITERATE" exp  */
//#line 1624 "instrument.y"
    {
      (yyval.jumpcondition).condition = (yyvsp[0].exp);
      (yyval.jumpcondition).iterate   = 1;
    }
//#line 3277 "instrument.tab.c"
    break;

  case 138: /* jumpname: "PREVIOUS"  */
//#line 1631 "instrument.y"
    {
      (yyval.jumpname).name  = str_dup("PREVIOUS");
      (yyval.jumpname).index = -1;
    }
//#line 3286 "instrument.tab.c"
    break;

  case 139: /* jumpname: "PREVIOUS" '(' TOK_NUMBER ')'  */
//#line 1636 "instrument.y"
    {
      (yyval.jumpname).name  = str_cat("PREVIOUS_", (yyvsp[-1].number), NULL);
      (yyval.jumpname).index = -atoi((yyvsp[-1].number));
    }
//#line 3295 "instrument.tab.c"
    break;

  case 140: /* jumpname: "MYSELF"  */
//#line 1641 "instrument.y"
    {
      (yyval.jumpname).name  = str_dup("MYSELF");
      (yyval.jumpname).index = 0;
    }
//#line 3304 "instrument.tab.c"
    break;

  case 141: /* jumpname: "NEXT"  */
//#line 1646 "instrument.y"
    {
      (yyval.jumpname).name  = str_dup("NEXT");;
      (yyval.jumpname).index = +1;
    }
//#line 3313 "instrument.tab.c"
    break;

  case 142: /* jumpname: "NEXT" '(' TOK_NUMBER ')'  */
//#line 1651 "instrument.y"
    {
      (yyval.jumpname).name  = str_cat("NEXT_", (yyvsp[-1].number), NULL);
      (yyval.jumpname).index = +atoi((yyvsp[-1].number));    }
//#line 3321 "instrument.tab.c"
    break;

  case 143: /* jumpname: TOK_ID  */
//#line 1655 "instrument.y"
    {
      (yyval.jumpname).name  = str_dup((yyvsp[0].string));
      (yyval.jumpname).index = 0;
    }
//#line 3330 "instrument.tab.c"
    break;

  case 144: /* shell: %empty  */
//#line 1663 "instrument.y"
    {
    }
//#line 3337 "instrument.tab.c"
    break;

  case 145: /* shell: "SHELL" TOK_STRING  */
//#line 1666 "instrument.y"
    {
      printf("Executing: %s ... ",(yyvsp[0].string));
      int ret_val = system((yyvsp[0].string));
      if (ret_val != 0) {
	printf("FAILED!\n");
	exit(-1);
      } else {
	printf("success!\n");
      }
    }
//#line 3352 "instrument.tab.c"
    break;

  case 146: /* search: "SEARCH" TOK_STRING  */
//#line 1678 "instrument.y"
    {
      add_search_dir((yyvsp[0].string));
    }
//#line 3360 "instrument.tab.c"
    break;

  case 147: /* search: "SEARCH" "SHELL" TOK_STRING  */
//#line 1682 "instrument.y"
    {
      FILE *sfp;
      char svalue[1025];
      sfp = popen((yyvsp[0].string), "r");
      if (sfp == NULL) {
        printf("FAILED to run search path command\n");
        exit(-1);
      }
      while (fgets(svalue, sizeof(svalue), sfp) != NULL){
        // Make a copy of the char array -- We can't free this memory until the program is done, so we're going to leak it :/
        char * path = (char*) calloc(strlen(svalue)+1, sizeof(char));
        strcpy(path, svalue);
        // Remove the trailing newline (and/or carriage return) which is almost-certainly present
        path[strcspn(path, "\r\n")] = 0;
        // Ensure the path specification *ends* in a PATHSEP character
        char * last = strrchr(path, MC_PATHSEP_S[0]);
        unsigned int last_sep = last - path + 1;
        if ((last - path) < strlen(path)) strcat(path, MC_PATHSEP_S);
        // Add the specified path to the search list
        add_search_dir(path);
      }
      pclose(sfp);
    }
//#line 3388 "instrument.tab.c"
    break;

  case 148: /* dependency: %empty  */
//#line 1708 "instrument.y"
    {
    }
//#line 3395 "instrument.tab.c"
    break;

  case 149: /* dependency: "DEPENDENCY" TOK_STRING  */
//#line 1711 "instrument.y"
    {
      if (strstr(instrument_definition->dependency,(yyvsp[0].string)) == NULL) {
	strncat(instrument_definition->dependency, " ", 1024);
	strncat(instrument_definition->dependency, (yyvsp[0].string), 1023); // 1023 because we already appended a space
      }
    }
//#line 3406 "instrument.tab.c"
    break;

  case 150: /* noacc: %empty  */
//#line 1719 "instrument.y"
    {
      /* Comp class should work on GPU */
      (yyval.linenum) = 0;
    }
//#line 3415 "instrument.tab.c"
    break;

  case 151: /* noacc: "NOACC"  */
//#line 1724 "instrument.y"
    {
      /* Comp class is CPU only */
      (yyval.linenum) = 1;
      if (strstr(instrument_definition->dependency," -DFUNNEL ") == NULL) {
	strncat(instrument_definition->dependency, " -DFUNNEL ", 1024);
      }
    }
//#line 3427 "instrument.tab.c"
    break;

  case 152: /* @3: %empty  */
//#line 1734 "instrument.y"
          { (yyval.linenum) = instr_current_line; }
//#line 3433 "instrument.tab.c"
    break;

  case 153: /* exp: @3 topexp  */
//#line 1735 "instrument.y"
      {
        CExp e = (yyvsp[0].exp);
        exp_setlineno(e, (yyvsp[-1].linenum) );
        (yyval.exp) = e;
      }
//#line 3443 "instrument.tab.c"
    break;

  case 154: /* topexp: topatexp  */
//#line 1743 "instrument.y"
      {
        (yyval.exp) = (yyvsp[0].exp);
      }
//#line 3451 "instrument.tab.c"
    break;

  case 155: /* topexp: topexp topatexp  */
//#line 1747 "instrument.y"
      {
        (yyval.exp) = exp_compound(2, (yyvsp[-1].exp), (yyvsp[0].exp));
        exp_free((yyvsp[0].exp));
        exp_free((yyvsp[-1].exp));
      }
//#line 3461 "instrument.tab.c"
    break;

  case 156: /* topatexp: "PREVIOUS"  */
//#line 1757 "instrument.y"
      {
        if (previous_comp) {
          (yyval.exp) = exp_ctoken(previous_comp->name);
        } else {
          print_error("ERROR: Found invalid PREVIOUS reference at line %s:%d. Please fix (add a component instance before).\n", instr_current_filename, instr_current_line);
        }
      }
//#line 3473 "instrument.tab.c"
    break;

  case 157: /* topatexp: "MYSELF"  */
//#line 1765 "instrument.y"
      {
        (yyval.exp) = exp_ctoken(myself_comp->name);
      }
//#line 3481 "instrument.tab.c"
    break;

  case 158: /* topatexp: TOK_ID  */
//#line 1770 "instrument.y"
      {
        List_handle liter=NULL;
        struct instr_formal *formal;
        /* Check if this is an instrument parameter or not. */
        /* ToDo: This will be inefficient if the number of
                       instrument parameters is really huge. */
        /* check if instrument parameters have been defined */
        if (instrument_definition->formals)
          liter = list_iterate(instrument_definition->formals);
        if (liter)
	          while((formal = (instr_formal*) list_next(liter)))
        {
          if((yyvsp[0].string) && formal->id && strcmp((yyvsp[0].string), "NULL") && !strcmp((yyvsp[0].string), formal->id))
          {
            /* It was an instrument parameter */
            (yyval.exp) = exp_id((yyvsp[0].string)); /* convert to instrument parameter */
            goto found;
          }
        }
        if (liter) list_iterate_end(liter);
        /* It was an external id. */
        (yyval.exp) = exp_extern_id((yyvsp[0].string));
      found:
        str_free((yyvsp[0].string));
      }
//#line 3511 "instrument.tab.c"
    break;

  case 159: /* topatexp: TOK_NUMBER  */
//#line 1796 "instrument.y"
      {
        (yyval.exp) = exp_number((yyvsp[0].number));
        str_free((yyvsp[0].number));
      }
//#line 3520 "instrument.tab.c"
    break;

  case 160: /* topatexp: TOK_STRING  */
//#line 1801 "instrument.y"
      {
        (yyval.exp) = exp_string((yyvsp[0].string));
        str_free((yyvsp[0].string));
      }
//#line 3529 "instrument.tab.c"
    break;

  case 161: /* topatexp: TOK_CTOK  */
//#line 1806 "instrument.y"
      {
        (yyval.exp) = exp_ctoken((yyvsp[0].string));
        str_free((yyvsp[0].string));
      }
//#line 3538 "instrument.tab.c"
    break;

  case 162: /* topatexp: '='  */
//#line 1811 "instrument.y"
      {
        (yyval.exp) = exp_ctoken("=");
      }
//#line 3546 "instrument.tab.c"
    break;

  case 163: /* topatexp: '*'  */
//#line 1815 "instrument.y"
      {
        (yyval.exp) = exp_ctoken("*");
      }
//#line 3554 "instrument.tab.c"
    break;

  case 164: /* topatexp: '/'  */
//#line 1819 "instrument.y"
      {
        (yyval.exp) = exp_ctoken("/");
      }
//#line 3562 "instrument.tab.c"
    break;

  case 165: /* topatexp: '(' genexp ')'  */
//#line 1823 "instrument.y"
      {
        CExp p1 = exp_ctoken("(");
        CExp p2 = exp_ctoken(")");
        (yyval.exp) = exp_compound(3, p1, (yyvsp[-1].exp), p2);
        exp_free(p2);
        exp_free(p1);
        exp_free((yyvsp[-1].exp));
      }
//#line 3575 "instrument.tab.c"
    break;

  case 166: /* topatexp: '(' ')'  */
//#line 1832 "instrument.y"
      {
        CExp p1 = exp_ctoken("(");
        CExp p2 = exp_ctoken(")");
        (yyval.exp) = exp_compound(2, p1, p2);
        exp_free(p2);
        exp_free(p1);
      }
//#line 3587 "instrument.tab.c"
    break;

  case 167: /* topatexp: '[' genexp ']'  */
//#line 1840 "instrument.y"
      {
        CExp p1 = exp_ctoken("[");
        CExp p2 = exp_ctoken("]");
        (yyval.exp) = exp_compound(3, p1, (yyvsp[-1].exp), p2);
        exp_free(p2);
        exp_free(p1);
        exp_free((yyvsp[-1].exp));
      }
//#line 3600 "instrument.tab.c"
    break;

  case 168: /* topatexp: '[' ']'  */
//#line 1849 "instrument.y"
      {
        CExp p1 = exp_ctoken("[");
        CExp p2 = exp_ctoken("]");
        (yyval.exp) = exp_compound(2, p1, p2);
        exp_free(p2);
        exp_free(p1);
      }
//#line 3612 "instrument.tab.c"
    break;

  case 169: /* topatexp: '{' genexp '}'  */
//#line 1857 "instrument.y"
      {
        CExp p1 = exp_ctoken("{");
        CExp p2 = exp_ctoken("}");
        (yyval.exp) = exp_compound(3, p1, (yyvsp[-1].exp), p2);
        exp_free(p2);
        exp_free(p1);
        exp_free((yyvsp[-1].exp));
      }
//#line 3625 "instrument.tab.c"
    break;

  case 170: /* topatexp: '{' '}'  */
//#line 1866 "instrument.y"
      {
        CExp p1 = exp_ctoken("{");
        CExp p2 = exp_ctoken("}");
        (yyval.exp) = exp_compound(2, p1, p2);
        exp_free(p2);
        exp_free(p1);
      }
//#line 3637 "instrument.tab.c"
    break;

  case 171: /* genexp: genatexp  */
//#line 1877 "instrument.y"
      {
        (yyval.exp) = (yyvsp[0].exp);
      }
//#line 3645 "instrument.tab.c"
    break;

  case 172: /* genexp: genexp genatexp  */
//#line 1881 "instrument.y"
      {
        (yyval.exp) = exp_compound(2, (yyvsp[-1].exp), (yyvsp[0].exp));
        exp_free((yyvsp[0].exp));
        exp_free((yyvsp[-1].exp));
      }
//#line 3655 "instrument.tab.c"
    break;

  case 173: /* genatexp: topatexp  */
//#line 1889 "instrument.y"
      {
        (yyval.exp) = (yyvsp[0].exp);
      }
//#line 3663 "instrument.tab.c"
    break;

  case 174: /* genatexp: ','  */
//#line 1893 "instrument.y"
      {
        (yyval.exp) = exp_ctoken(",");
      }
//#line 3671 "instrument.tab.c"
    break;

  case 175: /* codeblock: TOK_CODE_START code TOK_CODE_END  */
//#line 1901 "instrument.y"
      {
        (yyvsp[-1].ccode)->filename = instr_current_filename;
        (yyvsp[-1].ccode)->quoted_filename = str_quote(instr_current_filename);
        (yyvsp[-1].ccode)->linenum = (yyvsp[-2].linenum);
        (yyval.ccode) = (yyvsp[-1].ccode);
      }
//#line 3682 "instrument.tab.c"
    break;

  case 176: /* code: %empty  */
//#line 1910 "instrument.y"
      {
        (yyval.ccode) = codeblock_new();
      }
//#line 3690 "instrument.tab.c"
    break;

  case 177: /* code: code TOK_CODE_LINE  */
//#line 1915 "instrument.y"
      {
        list_add((yyvsp[-1].ccode)->lines, (yyvsp[0].string));
        (yyval.ccode) = (yyvsp[-1].ccode);
      }
//#line 3699 "instrument.tab.c"
    break;


//#line 3703 "instrument.tab.c"

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

//#line 1921 "instrument.y"


/* end of grammar *********************************************************** */


static Pool parser_pool = NULL; /* Pool of parser allocations. */

static int mc_yyparse(void)
{
  int ret;
  Pool oldpool;
  oldpool = parser_pool;
  parser_pool = pool_create();
  ret = yyparse();
  pool_free(parser_pool);
  parser_pool = oldpool;
  return ret;
}

// Separate identical parser to make debugging a bit easier
static int mc_yyparse_component(void){
  int ret;
  Pool old;
  old = parser_pool;
  parser_pool = pool_create();
  ret = yyparse();
  pool_free(parser_pool);
  parser_pool = old;
  return ret;
}

/* Name of the file currently being parsed. */
char *instr_current_filename = NULL;
/* Number of the line currently being parsed. */
int instr_current_line = 0;
/* current instance index */
long comp_current_index=0;

/* Result from parsing instrument definition. */
struct instr_def *instrument_definition;

/* Map from names to component instances. */
Symtab comp_instances;

/* Will store component instance for PREVIOUS and MYSELF reference */
struct comp_inst *previous_comp=NULL;
struct comp_inst *myself_comp=NULL;

/* Map from names to component group instances. */
Symtab group_instances;

/* Map from names to embedded libraries */
Symtab lib_instances;

/* List of components, in the order they where declared in the instrument
   definition. */
List comp_instances_list;

/* List of component groups, in the order they where declared in the instrument
   definition. */
List group_instances_list;

List metadata_list;

/* Filename for outputting generated simulation program ('-' means stdin). */
static char *output_filename;

/* Verbose parsing/code generation */
char verbose = 0;

/* include instrument source code in executable ? */
char embed_instrument_file = 0;

/* Map of already-read components. */
Symtab read_components = NULL;

/* name of executable, e.g. mcstas or mcxtrace */
char *executable_name=NULL;

/* Print a summary of the command usage. */
static void
print_usage(void)
{
  fprintf(stderr, MCCODE_NAME " version " MCCODE_VERSION " (" MCCODE_DATE ")\n");
  fprintf(stderr, "Compiler of the " MCCODE_NAME " ray-trace simulation package\n");
  fprintf(stderr, "Usage:\n"
    "  %s [-o file] [-I dir1 ...] [-t] [-p] [-v] "
    "[--no-main] [--no-runtime] [--verbose] file\n", executable_name);
  fprintf(stderr, "      -o FILE --output-file=FILE Place C output in file FILE.\n");
  fprintf(stderr, "      -I DIR  --search-dir=DIR   Append DIR to the component search list. \n");
  fprintf(stderr, "      -t      --trace            Enable 'trace' mode for instrument display.\n");
  fprintf(stderr, "      -v      --version          Prints " MCCODE_NAME " version.\n");
  fprintf(stderr, "      --no-main                  Do not create main(), for external embedding.\n");
  fprintf(stderr, "      --no-runtime               Do not embed run-time libraries.\n");
  fprintf(stderr, "      --verbose                  Display compilation process steps.\n");
  fprintf(stderr, "      --source                   Embed the instrument source code in executable.\n");
  fprintf(stderr, "  The instrument description file will be processed and translated into a C code program.\n");
  fprintf(stderr, "  If run-time libraries are not embedded, you will have to pre-compile\n");
  fprintf(stderr, "    them (.c -> .o) before assembling the program.\n");
  /* fixme: should use get_sys_dir here? And update the text? */
  fprintf(stderr, "  The default component search list is usually defined by the environment\n");
  
  // TODO: was this string important?
  /*
  fprintf(stderr, "    variable '" MCCODE_LIBENV "' %s (default is "
  
  #if MCCODE_PROJECT == 1
    MCSTAS
  #elif MCCODE_PROJECT == 2
    MCXTRACE
  #endif
  ") \n", getenv(MCCODE_LIBENV) ? getenv(MCCODE_LIBENV) : "");
  */
  
  fprintf(stderr, "  Use 'run' to both run " MCCODE_NAME " and the C compiler.\n");
  fprintf(stderr, "  Use 'gui' to run the " MCCODE_NAME " GUI.\n");
  fprintf(stderr, "SEE ALSO: mcrun, mcplot, mcdisplay, mcresplot, mcstas2vitess, mcgui, mcformat, mcdoc\n");
  fprintf(stderr, "DOC:      Please visit <" MCCODE_BUGREPORT ">\n");
}

/* Print a summary of the command usage and exit with error. */
static void
print_usage_error(void)
{
  print_usage();
  exit(1);
}

/* Print McCode version and copyright. */
static void
print_version(void)
{
  printf(MCCODE_NAME " code generator version " MCCODE_VERSION " (" MCCODE_DATE ")\n"
    "Copyright (C) DTU Physics and Risoe National Laboratory, 1997-" MCCODE_YEAR "\n"
    "Additions (C) Institut Laue Langevin, 2003-2019\n"
    "All rights reserved\n\nComponents are (C) their authors, see component headers.\n");
  exit(0);
}

/* Construct default filename for simulation output from instrument file
   name. Strip any leading directory path and trailing .instr, and add .c to
   the end. */
static char *
make_output_filename(char *name)
{
  char *p;
  int l;

  /* Find basename */
  p = strrchr(name, '/');
  if(p == NULL)
    p = name;     /* No initial path. */
  else
    p++;      /* Point past last '/' character. */

  /* Check for trailing .instr suffix. */
  l = strlen(p);
  if(l > 6 && !strcmp(&p[l - 6], ".instr"))
  {
    char *tmp = str_dup(p);
    tmp[l - 6] = '\0';
    p = str_cat(tmp, ".c", NULL);
    str_free(tmp);
  }
  else
    p = str_cat(p, ".c", NULL);
  return p;
}


static void
set_output_filename(char *name)
{
  output_filename = str_dup(name);
}

/* Parse command line options. */
static void
parse_command_line(int argc, char *argv[])
{
  int i;

  output_filename                        = NULL;
  verbose                                = 0;
  instr_current_filename                 = NULL;
  instrument_definition->use_default_main= 1;
  instrument_definition->include_runtime = 1;
  instrument_definition->enable_trace    = 0;
  instrument_definition->portable        = 0;
  strcmp(instrument_definition->dependency, "-lm");
  executable_name                        = argv[0];
  for(i = 1; i < argc; i++)
  {
    if(!strcmp("-o", argv[i]) && (i + 1) < argc)
      set_output_filename(argv[++i]);
    else if(!strncmp("-o", argv[i], 2))
      set_output_filename(&argv[i][2]);
    else if(!strcmp("--output-file", argv[i]) && (i + 1) < argc)
      set_output_filename(argv[++i]);
    else if(!strncmp("--output-file=", argv[i], 14))
      set_output_filename(&argv[i][14]);
    else if(!strcmp("-I", argv[i]) && (i + 1) < argc)
      add_search_dir(argv[++i]);
    else if(!strncmp("-I", argv[i], 2))
      add_search_dir(&argv[i][2]);
    else if(!strcmp("--search-dir", argv[i]) && (i + 1) < argc)
      add_search_dir(argv[++i]);
    else if(!strncmp("--search-dir=", argv[i], 13))
      add_search_dir(&argv[i][13]);
    else if(!strcmp("-t", argv[i]))
      instrument_definition->enable_trace = 1;
    else if(!strcmp("--trace", argv[i]))
      instrument_definition->enable_trace = 1;
    else if(!strcmp("-p", argv[i]))
      instrument_definition->portable = 1;
    else if(!strcmp("--portable", argv[i]))
      instrument_definition->portable = 1;
    else if(!strcmp("-v", argv[i]))
      print_version();
    else if(!strcmp("--version", argv[i]))
      print_version();
    else if(!strcmp("-h", argv[i]))
      { print_usage(); exit(0); }
    else if(!strcmp("--help", argv[i]))
      { print_usage(); exit(0); }
    else if(!strcmp("--verbose", argv[i]))
      verbose = 1;
    else if(!strcmp("--source", argv[i]))
      embed_instrument_file = 1;
    else if(!strcmp("--no-main", argv[i]))
      instrument_definition->use_default_main = 0;
    else if(!strcmp("--no-runtime", argv[i]))
      instrument_definition->include_runtime = 0;
    else if(argv[i][0] != '-')
    {
      if(instr_current_filename != NULL)
        print_usage_error();    /* Multiple instruments given. */
      instr_current_filename = str_dup(argv[i]);
    }
    else
      print_usage_error();
  }

  /* Instrument filename must be given. */
  if(instr_current_filename == NULL)
    print_usage_error();
  /* If no '-o' option was given for INSTR.instr, default to INSTR.c  */
  if(output_filename == NULL)
    output_filename = make_output_filename(instr_current_filename);
}


/*
int
main(int argc, char *argv[])
{
  FILE *file;
  int err;

#ifdef MAC
  argc = ccommand(&argv);
#endif

  yydebug = 0;      // If 1, then bison gives verbose parser debug info.

  instrument_definition = (instr_def*) palloc(instrument_definition); // Allocate instrument def. structure.
  // init root instrument to NULL
  instrument_definition->formals   = NULL;
  instrument_definition->name      = NULL;
  instrument_definition->decls     = NULL;
  instrument_definition->inits     = NULL;
  instrument_definition->saves     = NULL;
  instrument_definition->finals    = NULL;
  instrument_definition->compmap   = NULL;
  instrument_definition->groupmap  = NULL;
  instrument_definition->complist  = NULL;
  instrument_definition->grouplist = NULL;
  instrument_definition->metadata  = NULL;
  instrument_definition->has_included_instr=0;
  comp_instances      = NULL;
  comp_instances_list = NULL;
  group_instances     = NULL;
  group_instances_list= NULL;
  parse_command_line(argc, argv);
  if(!strcmp(instr_current_filename, "-"))
  {
    instrument_definition->source = str_dup("<stdin>");
    file = fdopen(0, "r");  // Lone '-' designates stdin.
  }
  else
  {
    instrument_definition->source = str_dup(instr_current_filename);
    file = fopen(instr_current_filename, "r");
  }
  if(file == NULL)
    fatal_error(MCCODE_NAME ": Instrument definition file `%s' not found\n",
    instr_current_filename);
  instrument_definition->quoted_source =
    str_quote(instrument_definition->source);
  if (verbose) {
    fprintf(stderr, MCCODE_NAME " version " MCCODE_VERSION "\n");
    fprintf(stderr, "Analyzing file            %s\n", instrument_definition->quoted_source);
  }
  instr_current_line = 1;
  lex_new_file(file);
  read_components = symtab_create(); // Create table of components.
  lib_instances   = symtab_create(); // Create table of libraries.
  err = mc_yyparse();
  if (err != 0 && !error_encountered) error_encountered++;
  if(error_encountered != 0)
  {
    print_error(MCCODE_NAME ": %i Errors encountered during parse of %s.\n",
      error_encountered, instr_current_filename);
    if (verbose) {
      fprintf(stderr, "Please check the usual grammar:\n");
      fprintf(stderr, "DEFINE INSTRUMENT\n");
      fprintf(stderr, "DECLARE\n");
      fprintf(stderr, "INITIALIZE\n");
      fprintf(stderr, "TRACE\n");
      fprintf(stderr, "  {SPLIT} COMPONENT name = comp(parameters) {WHEN condition}\n");
      fprintf(stderr, "  AT (...) [RELATIVE [reference|PREVIOUS] | ABSOLUTE]\n");
      fprintf(stderr, "  {ROTATED {RELATIVE [reference|PREVIOUS] | ABSOLUTE} }\n");
      fprintf(stderr, "  {GROUP group_name}\n");
      fprintf(stderr, "  {EXTEND C_code}\n");
      fprintf(stderr, "  {JUMP [reference|PREVIOUS|MYSELF|NEXT] [ITERATE number_of_times | WHEN condition]\n");
      fprintf(stderr, "END\n");
      fprintf(stderr, "as well as '%%{ ... %%}' blocks.\n\n");
    }
    exit(1);
  }
  fclose(file);

  if (verbose) fprintf(stderr, "Starting to create C code %s\n", output_filename);
  cogen(output_filename, instrument_definition);
  if (verbose) fprintf(stderr, "Generated          C code %s from %s\n",
                       output_filename, instrument_definition->source);
  fprintf(stderr, "CFLAGS=%s\n", instrument_definition->dependency);
  exit(0);
}
*/ // main()


int
yyerror(const char *s)
{
  print_error("ERROR: %s at line %d.\n", s, instr_current_line);
  return 0;
}


/*******************************************************************************
* Check that all formal parameters of a component definition are unique.
*******************************************************************************/
void
check_comp_formals(List deflist, List setlist, char *compname)
{
  Symtab formals;
  struct comp_iformal *formal;
  struct Symtab_entry *entry;
  List_handle liter;

  /* We check the uniqueness by adding all the formals to a symbol table with
     a dummy pointer value. Any formal parameter that already appears in the
     symbol table is an error. */
  formals = symtab_create();
  liter = list_iterate(deflist);
  while((formal = (comp_iformal*) list_next(liter)))
  {
    if (!formal->id || !strlen(formal->id))
      print_error("ERROR: Definition parameter name %s is empty (length=0) "
      "in component %s\n", formal->id, compname);
    entry = symtab_lookup(formals, formal->id);
    if(entry != NULL)
      print_error("ERROR: Definition parameter name %s is used multiple times "
      "in component %s\n", formal->id, compname);
    else
      symtab_add(formals, formal->id, NULL);
  }
  list_iterate_end(liter);
  liter = list_iterate(setlist);
  while((formal = (comp_iformal*) list_next(liter)))
  {
    if (!formal->id || !strlen(formal->id))
      print_error("ERROR: Setting parameter name %s is empty (length=0) "
      "in component %s\n", formal->id, compname);
    entry = symtab_lookup(formals, formal->id);
    if(entry != NULL)
      print_error("ERROR: Setting parameter name %s is used multiple times "
      "in component %s\n", formal->id, compname);
    else
      symtab_add(formals, formal->id, NULL);
  }
  list_iterate_end(liter);
  symtab_free(formals, NULL);
}


/*******************************************************************************
* Check that all formal parameters of an instrument definition are unique.
*******************************************************************************/
void
check_instrument_formals(List formallist, char *instrname)
{
  struct instr_formal *formal;
  List_handle liter;

  /* We check the uniqueness. Any formal parameter that already appears in the
     formal list is reported. */
  liter = list_iterate(formallist);
  while((formal = (instr_formal*) list_next(liter))) {
    if (!formal->id || !strlen(formal->id))
      continue;
      // print_error("ERROR: Instrument parameter name %s is empty (length=0) "
      // "in instrument %s\n", formal->id, instrname);
    if (strcmp(formal->id,"")) {
        /* find first definition of parameter */
        List_handle liter2;
        struct instr_formal *formal2;

        liter2 = list_iterate(formallist);
        while((formal2 = (instr_formal*) list_next(liter2))) {
        	if (formal != formal2 && strlen(formal2->id) && !strcmp(formal->id, formal2->id)) {
        		strcpy(formal2->id, "");  /* inactivate recurrent previous definition */
        		if (verbose) print_warn(NULL, "Instrument parameter name %s is used multiple times "
              "in instrument %s. Using last definition %s\n", formal->id, instrname,
              	formal->isoptional ? exp_tostring(formal->default_value) : "");
            break;
        	}
        }
    }
  }
  list_iterate_end(liter);
}

/*******************************************************************************
* Check the actual parameters to a component against the formal parameters.
*******************************************************************************/
void
comp_formals_actuals(struct comp_inst *comp, Symtab actuals)
{
  List_handle liter;
  struct comp_iformal *formal;
  struct Symtab_entry *entry;
  Symtab defpar, setpar;
  Symtab_handle siter;

  /* We need to check
     1. That all actual parameters correspond to formal parameters.
     2. That all formal parameters are assigned actual parameters. */

  /* First check the formal parameters one by one. */
  defpar = symtab_create();
  setpar = symtab_create();
  if (!comp || !comp->def) return;

  /* definition parameters */
  liter = list_iterate(comp->def->def_par);
  while((formal = (comp_iformal*) list_next(liter)))
  {
    entry = symtab_lookup(actuals, formal->id);
    if(entry == NULL)
    {
      if(formal->isoptional)
      {
        /* Use default value for unassigned optional parameter */
        symtab_add(defpar, formal->id, formal->default_value);
      } else {
        print_error("ERROR: Unassigned DEFINITION parameter %s for component %s=%s() at line %s:%d. Please set its value.\n",
              formal->id, comp->name, comp->def->name,
              instr_current_filename, instr_current_line);
        symtab_add(defpar, formal->id, exp_number("0.0"));
      }
    } else {
      symtab_add(defpar, formal->id, entry->val);
      /* Ensure that the actual DEFINITION parameters are all values
         (identifiers, constant numbers, and constant strings). This is
         necessary to avoid duplication of computations or side effects in the
         expressions for the actual parameters, since DEFINITION parameters
         are assigned using #define's. */
      if(!exp_isvalue((cexp*) entry->val))
      {
        print_warn(NULL, "Warning: Using DEFINITION parameter of component %s() (potential syntax error) at line %s:%d\n"
          "  %s=%s\n",
          comp->def->name, instr_current_filename, instr_current_line,
          formal->id, exp_tostring((cexp*) entry->val));
      }
    }
  }
  list_iterate_end(liter);

  /* setting parameters */
  liter = list_iterate(comp->def->set_par);
  while((formal = (comp_iformal*) list_next(liter)))
  {
    entry = symtab_lookup(actuals, formal->id);
    if(entry == NULL)
    {
      if(formal->isoptional)
      {
        /* Use default value for unassigned optional parameter */
        symtab_add(setpar, formal->id, formal->default_value);
      } else {
        print_error("ERROR: Unassigned SETTING parameter %s for component %s=%s() at line %s:%d. Please set its value.\n",
              formal->id, comp->name, comp->def->name,
              instr_current_filename, instr_current_line);
        symtab_add(setpar, formal->id, exp_number("0.0"));
      }
    } else {
      symtab_add(setpar, formal->id, entry->val);
    }
  }
  list_iterate_end(liter);

  /* Now check the actual parameters one by one. */
  siter = symtab_iterate(actuals);
  while((entry = symtab_next(siter)))
  {
    if(symtab_lookup(defpar, entry->name) == NULL &&
       symtab_lookup(setpar, entry->name) == NULL)
    {
      Symtab_handle siter2;
      struct Symtab_entry *entry2;

      fprintf(stderr, "\nERROR: Unmatched actual parameter %s for component %s=%s() at line %s:%d."
        "Please change its name to a valid one:\n",
        entry->name, comp->name, comp->def->name,
        instr_current_filename, instr_current_line);
      siter2 = symtab_iterate(defpar);
      fprintf(stderr,"  Definition parameters: ");
      char misspelled[256];
      strcpy(misspelled, "");
      while((entry2 = symtab_next(siter2))) {
        fprintf(stderr, "%s ", entry2->name);
        if (!strlen(misspelled) && (!strcasecmp(entry->name, entry2->name)
         ||  strcasestr(entry->name, entry2->name)
         ||  strcasestr(entry2->name, entry->name))) strcpy(misspelled, entry2->name);
      }
      symtab_iterate_end(siter2);
      siter2 = symtab_iterate(setpar);
      fprintf(stderr,"\n  Setting parameters: ");
      while((entry2 = symtab_next(siter2))) {
        fprintf(stderr, "%s ", entry2->name);
        if (!strlen(misspelled) && (!strcasecmp(entry->name, entry2->name)
         ||  strcasestr(entry->name, entry2->name)
         ||  strcasestr(entry2->name, entry->name))) strcpy(misspelled, entry2->name);
      }
      symtab_iterate_end(siter2);
      print_error("\n");
      if (strlen(misspelled))
      	fprintf(stderr, "Info:    '%s' parameter name used in instrument matches\n"
                        "         component %s=%s() parameter '%s' from library but\n"
                        "         may be misspelled. Check component instance.\n",
                        entry->name, comp->name, comp->def->name, misspelled);
    }
  }
  symtab_iterate_end(siter);
  comp->defpar = defpar;
  comp->setpar = setpar;
}


/*******************************************************************************
* This is the main entry point for reading a component. When a component
* definition is needed, this function is called with the name of the
* component. A map of previously read components is maintained. If a
* component definition (struct comp)def) is found, it is returned. Otherwise
* an attempt is made to read the component definition from a file with the
* same name as the component with added file extension ".com".
* If for some reasons the component cannot be read, NULL is returned; else a
* pointer to a struct comp_def is returned. Since components definitions can
* be used multiple times, the returned structure is shared and should not be
* modified.
*******************************************************************************/
struct comp_def *
read_component(char *name)
{
  struct Symtab_entry *entry;

  /* Look for an existing definition for the component. */
  entry = symtab_lookup(read_components, name);
  if(entry != NULL)
  {
    return (comp_def*) entry->val;    /* Return it if found. */
  }
  else
  {
    FILE *file;
    int err;

    /* Attempt to read definition from file components/<name>.com. */
    file = open_component_search(name);
    if(file == NULL)
    {
      print_error(
        "ERROR: Cannot find file containing definition of component '%s'.\n"
        "  Check the " MCCODE_LIBENV " library installation and environment variable\n"
        "  or copy the component definition file locally.\n  Current library search path: %s\n", name, get_sys_dir());
      return NULL;
    }
    push_autoload(file);
    /* Note: the str_dup copy of the file name is stored in codeblocks, and
       must not be freed. */
    instr_current_filename = component_pathname;
    instr_current_line = 1;
    err = mc_yyparse_component();   /* Read definition from file. */
    if(err != 0)
      fatal_error("Errors encountered during autoload of component %s. The component definition has syntax errors.\n",
        name);
    fclose(file);
    /* Now check if the file contained the required component definition. */
    entry = symtab_lookup(read_components, name);
    if(entry != NULL)
    {
      return (comp_def*) entry->val;
    }
    else
    {
      print_error("ERROR: Definition of component %s not found (file was found but does not contain the component definition).\n", name);
      return NULL;
    }
  }
}
