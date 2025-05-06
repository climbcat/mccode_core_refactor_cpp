#ifndef __MCCODE_H__
#define __MCCODE_H__


/*******************************************************************************
*
* McCode, neutron/xray ray-tracing package
*         Copyright 1997-2002, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Kernel: mccode.h
*
* %Identification
* Written by: K.N.
* Date: Jul  1, 1997
* Origin: Risoe
* Release: @MCCODE_STRING@
* Version: $Revision$
*
* Main header file containing declarations of external functions and
* variables. This file is included by all modules.
*
* $Id$
*
*******************************************************************************/


// system
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// constants
#ifndef MCCODE_H
//#define MCCODE_H "$Revision$"
#define MCCODE_H "0.1.0"
#endif

/* the version string is replaced when building distribution with mkdist */
#ifndef MCCODE_STRING
//#define MCCODE_STRING "@MCCODE_STRING@"
#define MCCODE_STRING "TT_V0.1.0"
#endif

#ifndef MCCODE_DATE
//#define MCCODE_DATE "@MCCODE_DATE@"
#define MCCODE_DATE "Maj 5"
#endif

#ifndef MCCODE_VERSION
//#define MCCODE_VERSION "@MCCODE_VERSION@"
#define MCCODE_VERSION "TT_V0.1.0"
#endif

#ifndef MCCODE_NAME
//#define MCCODE_NAME "@MCCODE_NAME@"
#define MCCODE_NAME "TraceTool"
#endif

#ifndef MCCODE_PARTICLE
//#define MCCODE_PARTICLE "@MCCODE_PARTICLE@"
#define MCCODE_PARTICLE "Neutron"
#endif

#ifndef MCCODE_LIBENV
//#define MCCODE_LIBENV "@MCCODE_LIBENV@"
#define MCCODE_LIBENV "lnx"
#endif

#ifndef MCCODE_YEAR
//#define MCCODE_YEAR "@MCCODE_YEAR@"
#define MCCODE_YEAR "2025"
#endif


/* Stringification of defines - use mccode_xstr: */
#define mccode_str(s) #s
#define mccode_xstr(s) mccode_str(s)


#define MC_PATHSEP_S "/"
#define FLAVOR_UPPER "TT"


// utils
#include "mcmemory.h"
#include "mclist.h"
#include "mccexp.h"
#include "mccords.h"
#include "mcsymtab.h"
#include "mcfile.h"
#include "mcdebug.h"


// TODO: compile
// requires mccode runtime:
//#include "mcformat.h"






/*******************************************************************************
* Definitions for position
*******************************************************************************/

/*******************************************************************************
* A component position consists in a place and an orientation. Place is the
* location in 3D space of the origo of the components local coordinate
* system, and orientation is the rotation transformation that transforms the
* global coordinate system into the component local one.
*
* At runtime, place is a 3-vector and orientation is a 3-by-3
* matrix. However, at compile time the actual values are not known. Instead,
* code is generated to compute the actual values for the position at
* runtime.
*******************************************************************************/

struct comp_position
  {
    Coords_exp place;          /* (x,y,z) coordinate. */
    struct comp_inst *place_rel;       /* Instance relative to, or NULL. */
    Coords_exp orientation;        /* X/Y/Z rotation. */
    struct comp_inst *orientation_rel;
  };

/* During parsing, individual structures are used for place and orientation. */
struct comp_place
  {
    Coords_exp place;
    struct comp_inst *place_rel;
  };
struct comp_orientation
  {
    Coords_exp orientation;
    struct comp_inst *orientation_rel;
    int isdefault;  /* True if this is a default orientation, generated
         when no ROTATED modifier is given. */
  };


/*******************************************************************************
* Definitions in instrument.y
*******************************************************************************/

typedef struct instr_def * instr_ptr_t;

/* Name of the file currently being parsed. */
extern char *instr_current_filename;
/* Line number currently being scanned. */
extern int instr_current_line;
/* Result from parsing instrument definition. */
extern struct instr_def *instrument_definition;
/* Map from names to component instances. */
extern Symtab comp_instances;
/* List of component instances in declaration order. */
extern List comp_instances_list;
/* Map from names to component group instances. */
extern Symtab group_instances;
/* List of component group instances in declaration order. */
extern List group_instances_list;
/* Map from names to embedded libraries */
extern Symtab lib_instances;
/* Flag set to TRUE when scanning autoloaded component definitions. */
extern int parse_restricted;
/* Map of already-read components. */
extern Symtab read_components;
/* Verbose parsing/code generation */
extern char verbose;
/* Lint mode */
extern char lint;
/* Will store component instance for PREVIOUS reference */
extern char embed_instrument_file;
/* Will store component instance for PREVIOUS reference */
extern struct comp_inst *previous_comp;
extern struct comp_inst *myself_comp;
/* current instance index */
extern long comp_current_index;

/* Check that component definition and setting parameters are unique. */
void check_comp_formals(List deflist, List setlist, char *compname);
/* Check that instrument parameters are unique. */
void check_instrument_formals(List formallist, char *instrname);
/* Handle assignment of actual to formal component parameters. */
void comp_formals_actuals(struct comp_inst *comp, Symtab actuals);

/* Get component definition, reading from file if necessary. */
struct comp_def *read_component(char *name);


/*******************************************************************************
* Definitions in instrument.l
*******************************************************************************/

/* Prepare to run lexical analysis on new file. */
void lex_new_file(FILE *file);
/* Handle a new autoincluded file (uses recursive parser call). */
void push_autoload(FILE *file);


/*******************************************************************************
* Definitions for file.c
*******************************************************************************/

extern char *component_pathname;

/* Open file, searching the full search path. */
FILE *open_file_search(char *name);
/* Open component definition, searching the full search path. */
FILE *open_component_search(char *name);
/* Open file, searching only the system directory. */
FILE *open_file_search_sys(char *name);
/* Add a directory to the search path. */
void add_search_dir(char *name);
/* get default system directory (where libraries are) */
char *get_sys_dir(void);


/*******************************************************************************
* Definitions in re.c (added jg-20190312 via github.com/kokke)
*******************************************************************************/

/* Typedef'd pointer to get abstract datatype. */
typedef struct regex_t* re_t;

/* Compile regex string pattern to a regex_t-array. */
re_t re_compile(const char* pattern);

/* Find matches of the compiled pattern inside text. */
int  re_matchp(re_t pattern, const char* text);

/* Find matches of the txt pattern inside text (will compile automatically first). */
int  re_match(const char* pattern, const char* text);


/*******************************************************************************
* Definitions for cogen.c
*******************************************************************************/

/* Allocate a new, empty codeblock. */
struct code_block *codeblock_new(void);
/* Generate code for instrument definition. */
void cogen(char *output_name, struct instr_def *instr);


/*******************************************************************************
* Functions and variables defined in debug.c
*******************************************************************************/

extern int error_encountered; /* Set to 1 when print_error called. */

void print_error(char *, ...);  /* Normal error messages. */
void print_warn(int *flag, char *format, ...); /* Warning. */
void fatal_error(char *, ...);  /* Report a fatal error and exit the program. */

/*
#ifdef DEBUG

void debug_printf(char *, ...); /* Internal; use debug macro instead.
void debugn_printf(int, char *, ...); /* Internal; use debugn macro instead.

//*******************************************************************************
* Debugging information. When the preprosessor flag DEBUG is defined,
* debugging messages are printed to stderr. This uses the 'debug' macro. A
* statement of the form debug((format, ...)) (note the double parenthesis)
* does nothing when debugging is disabled, and outputs debugging information
* printf-style when debigging is enabled. The macro 'debugn' takes an
* additional argument LEVEL; a compile-time option can be used to select
* output only up to a certain level.
*******************************************************************************

#define debug(msg) debug_printf msg
#define debugn(msg) debugn_printf msg

/* 'Standard' debugging levels.
#define DEBUG_ALWAYS  0   /* Always shown (if debugging enabled).
#define DEBUG_HIGH   10
#define DEBUG_MEDIUM 20
#define DEBUG_LOW    30   /* Only shown at high debugging level.

/*******************************************************************************
* Macro used to change the current debugging level. Useful to enable
* high-volume debugging output in a specific part of the program.
******************************************************************************
extern int debug_current_level;
#define debug_level(n) (debug_current_level = (n))

#else  /* !defined(DEBUG) 

#define debug(msg)
#define debugn(msg)
#define DEBUG_ALWAYS
#define DEBUG_HIGH
#define DEBUG_MEDIUM
#define DEBUG_LOW
#define debug_level(n)


#endif /* !defined(DEBUG)

*/


/*******************************************************************************
* Common structure definitions.
*******************************************************************************/

/* Code blocks. */
struct code_block
  {
    char *filename;   /* Name of origin source file. */
    char *quoted_filename;  /* Same, quoted for inclusion in C code. */
    int linenum;    /* Line number of first line. */
    List lines;     /* List of lines (strings with \n at end). */
  };

/* Note: the enum instr_formal_types definition MUST be kept
   synchronized with the one in mccode-r.h. */
enum instr_formal_types
  {
    instr_type_int,
    instr_type_string,
    instr_type_char,
    instr_type_vector,
    instr_type_double,
    instr_type_symbol,
    instr_type_custom
  };

/* Component formal input parameters. */
struct comp_iformal
  {
    enum instr_formal_types type; /* Type (string, int, double) */
    char *id;                     /* Parameter name */
    char *type_custom;            /* custom type string, in which case
                                     instr_formal_types takes value # 6, custom */
    int isoptional;               /* True if default value is available */
    CExp default_value;           /* Default value if isoptional is true */
  };

/* Component definitions. */
struct comp_def
  {
    char *name;                     /* Component name. */
    char *source;                   /*  Name of source file for definition */
    int  flag_defined_structure;    /* set to 1 when the parameter block is generated */
    int  flag_defined_share;        /* set to 1 when the SHARE block is generated */
    int  flag_defined_init;         /* set to 1 when a common INIT block is generated */
    int  flag_defined_save;         /* set to 1 when a common SAVE block is generated */
    int  flag_defined_finally;      /* set to 1 when a common FINALLY block is generated */
    int  flag_defined_display;      /* set to 1 when a common DISPLAY block is generated */
    int  flag_defined_trace;        /* set to 1 when a common TRACE block is generated */
    int  counter_instances;         /* number of instances using the same definition/class */
    int  flag_noacc;                /* Component type not available on GPU */
    struct List_header * def_par, * set_par, * out_par, * decl_par; /* Formal parameters. */
    struct List_header * metadata;
    struct code_block *share_code;  /* Unique Declaration code (shared). */
    struct code_block *uservar_code; /* To be injected in particlce struct */
    struct code_block *decl_code;   /* Declaration code. */
    struct code_block *init_code;   /* Initializeation code. */
    struct code_block *trace_code;  /* Ray-trace simulation code. */
    struct code_block *save_code;   /* Code executed to save data */
    struct code_block *finally_code;    /* Code for simulation end. */
    struct code_block *display_code;  /* Code for drawing components. */
  };

/* Component group instances */
struct group_inst
  {
    char *name;
    int   index;
    char *first_comp;
    char *last_comp;
    int   first_comp_index;
    int   last_comp_index;
    // CExp  split;
  };

struct when_condition {
  CExp condition;

};
/* Component instance. */
struct comp_inst
  {
    char *name;     /* Instance name. */
    char *type;     /* type of component */
    struct comp_def *def;           /* Pointer to definition. */
    struct comp_position *pos;      /* Component position (place & orientation). */
    struct code_block *extend;      /* NULL or code following comp instance */
    int    index;   /* index of comp instance */
    struct group_inst *group;       /* NULL or group name in which comp is */
    Symtab defpar, setpar;          /* Parameter values. */
    List metadata;  /* NULL or list of metadata code blocks after extend */
    List jump;      /* NULL or list of jumps to execute after trace/extend */
    CExp when;      /* NULL or condition to execute TRACE */
    Symtab actuals; /* save actual/given parameters for COPY */
    CExp split;     /* NULL or number of SPLITs as an Expr */
    int removable;  /* this comp is removed when included from an %include "instr" */
    int cpuonly;    /* this comp should be executed CPU only */
    int skip_transform;   /* if 1 coordinate transform is skipped */
  };

/* Instrument formal parameters. */
struct instr_formal
  {
    enum instr_formal_types type; /* Type (string, int, double) */
    char *id;                     /* Parameter name */
    int isoptional;               /* True if default value is available */
    CExp default_value;           /* Default value if isoptional is true */
    int hasunit;                  /* Flag to indicate if unit was provided */
    char *unit;                   /* (Informational) parameter unit */
  };

/* Instrument definition. */
struct instr_def
  {
    char *name;     /* Instrument name */
    char *source;   /* Name of source file for definition */
    char *quoted_source;      /* File name quoted for inclusion in C */
    struct code_block *decls; /* Code for declarations */
    struct code_block *vars;  /* Code for particle variables */
    struct code_block *inits; /* Code for initializations */
    struct code_block *saves; /* Code executed to save data */
    struct code_block *finals;/* Code for simulation end */
    List formals;             /* List of formal parameters */
    Symtab compmap;           /* Map of component names to instances */
    Symtab groupmap;          /* Map of component group names */
    List complist;            /* List of components in declaration order */
    List grouplist;           /* List of component groups in declaration order */
    int use_default_main;     /* If set, output a main() function */
    int include_runtime;      /* If set, include runtime in output */
    int enable_trace;         /* If set, enable output of ray traces */
    int portable;             /* If set, emit strictly portable ANSI C */
    int has_included_instr;   /* Flag set when instruments are %included in instr */
    char dependency[1024];    /* stores all dependencies needed to compile, from comps and instr */
    List user_vars;           /* stores custom particle user variables */
    List user_vars_types;     /* stores custom particle user variable types */
    List metadata;            /* stores all components' literal code blocks */
  };

struct metadata_struct
{
  int instance;
  char* source; // TODO abuse this field? "__definition__" and "__instance__"?
  char* name;
  char* type;
  List lines;
  //struct code_block* code;
};

struct jump_struct
{
  char *target;        /* name of component to jump to */
  int   target_index;  /* index of component to jump to */
  CExp  condition;     /* condition for jump or number of iterations */
  char  iterate;       /* 1:iteration, 0:single conditional jump */
  int   index;
};

struct jump_condition
{
  CExp  condition;     /* condition for jump or number of iterations */
  char  iterate;       /* true for iteration, false for single conditional jump */
};

struct jump_name
  {
    char *name;
    int  index;
  };

int metadata_construct_table(instr_ptr_t);
void metadata_assign_source(List, char *);
void metadata_overwrite_source(List, char *);
Symtab metadata_separate_by_source(List metadata, int source_type);
struct metadata_struct * metadata_copy(struct metadata_struct *);
List metadata_list_copy(List from);


#endif
