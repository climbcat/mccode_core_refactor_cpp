/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INSTRUMENT_TAB_H_INCLUDED
# define YY_YY_INSTRUMENT_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_RESTRICTED = 258,          /* TOK_RESTRICTED  */
    TOK_GENERAL = 259,             /* TOK_GENERAL  */
    TOK_ABSOLUTE = 260,            /* "ABSOLUTE"  */
    TOK_AT = 261,                  /* "AT"  */
    TOK_COMPONENT = 262,           /* "COMPONENT"  */
    TOK_DECLARE = 263,             /* "DECLARE"  */
    TOK_USERVARS = 264,            /* "USERVARS"  */
    TOK_DEFINE = 265,              /* "DEFINE"  */
    TOK_DEFINITION = 266,          /* "DEFINITION"  */
    TOK_END = 267,                 /* "END"  */
    TOK_FINALLY = 268,             /* "FINALLY"  */
    TOK_INITIALISE = 269,          /* "INITIALISE"  */
    TOK_INSTRUMENT = 270,          /* "INSTRUMENT"  */
    TOK_DISPLAY = 271,             /* "DISPLAY"  */
    TOK_PRIVATE = 272,             /* "PRIVATE"  */
    TOK_PARAMETERS = 273,          /* "PARAMETERS"  */
    TOK_RELATIVE = 274,            /* "RELATIVE"  */
    TOK_ROTATED = 275,             /* "ROTATED"  */
    TOK_PREVIOUS = 276,            /* "PREVIOUS"  */
    TOK_SETTING = 277,             /* "SETTING"  */
    TOK_STATE = 278,               /* "STATE"  */
    TOK_POL = 279,                 /* "POLARISATION"  */
    TOK_TRACE = 280,               /* "TRACE"  */
    TOK_SHARE = 281,               /* "SHARE"  */
    TOK_EXTEND = 282,              /* "EXTEND"  */
    TOK_GROUP = 283,               /* "GROUP"  */
    TOK_SAVE = 284,                /* "SAVE"  */
    TOK_JUMP = 285,                /* "JUMP"  */
    TOK_WHEN = 286,                /* "WHEN"  */
    TOK_NEXT = 287,                /* "NEXT"  */
    TOK_ITERATE = 288,             /* "ITERATE"  */
    TOK_MYSELF = 289,              /* "MYSELF"  */
    TOK_COPY = 290,                /* "COPY"  */
    TOK_SPLIT = 291,               /* "SPLIT"  */
    TOK_REMOVABLE = 292,           /* "REMOVABLE"  */
    TOK_CPUONLY = 293,             /* "CPU"  */
    TOK_NOACC = 294,               /* "NOACC"  */
    TOK_DEPENDENCY = 295,          /* "DEPENDENCY"  */
    TOK_SHELL = 296,               /* "SHELL"  */
    TOK_SEARCH = 297,              /* "SEARCH"  */
    TOK_METADATA = 298,            /* "METADATA"  */
    TOK_ID = 299,                  /* TOK_ID  */
    TOK_STRING = 300,              /* TOK_STRING  */
    TOK_NUMBER = 301,              /* TOK_NUMBER  */
    TOK_CTOK = 302,                /* TOK_CTOK  */
    TOK_CODE_START = 303,          /* TOK_CODE_START  */
    TOK_CODE_END = 304,            /* TOK_CODE_END  */
    TOK_CODE_LINE = 305,           /* TOK_CODE_LINE  */
    TOK_INVALID = 306              /* TOK_INVALID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
//#line 74 "instrument.y"

  char *number;
  char *string;
  struct code_block       *ccode;         /* User-supplied C code block */
  CExp                     exp;           /* Expression datatype (for arguments) */
  int                      linenum;       /* Starting line number for code block */
  Coords_exp               coords;        /* Coordinates for location or rotation */
  List                     formals;       /* List of formal parameters */
  List                     iformals;      /* List of formal instrument parameters */
  List                     comp_iformals; /* List of formal comp. input parameters */
  struct instr_formal     *iformal;       /* Single formal instrument parameter */
  struct comp_iformal     *cformal;       /* Single formal component input parameter */
  Symtab                   actuals;       /* Values for formal parameters */
  struct {List def, set, out; } parms;    /* Parameter lists */
  struct instr_def        *instrument;    /* Instrument definition */
  struct comp_inst        *instance;      /* Component instance */
  struct comp_place        place;         /* Component place */
  struct comp_orientation  ori;           /* Component orientation */
  struct group_inst       *groupinst;     /* group instances */
  struct jump_struct      *jump;          /* jumps structures */
  List                     jumps;
  struct jump_condition    jumpcondition;
  struct jump_name         jumpname;
  struct metadata_struct   *metadatum;       /* one metadatum structure */
  List                     metadata;      /* list of metadatum structures */

//#line 142 "instrument.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INSTRUMENT_TAB_H_INCLUDED  */
