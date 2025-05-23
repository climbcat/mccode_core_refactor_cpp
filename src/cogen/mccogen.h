#ifndef __MC_COGEN_H__
#define __MC_COGEN_H__


/*******************************************************************************
*
* McCode system component cogen.c.in:
* McStas/McXtrace, neutron/xray ray-tracing package
*         Copyright (C) 1997-2020, All rights reserved
*         DTU Physics, Kgs. Lyngby, Denmark
*         Institut Laue Langevin, Grenoble, France
*         Synchrotron SOLEIL, Saint-Aubin, France
*         Copenhagen University, Copenhagen, Denmark
*
* Kernel: cogen.c
*
* %Identification
* Written by: K.N.
* Modified for X-rays by E.K.
* Modified for cogen3 by E.F. 2017-18
* Modified for o.o. approach by J.G. 2018-19
* Date: Jan 2020
* Origin: DTU
* Release: McStas 3.0
* Version: $Revision$
*
* Code generation from instrument definition.
*
*******************************************************************************/


#include <stdarg.h>
#include <string.h>
#include <stdio.h>


/*******************************************************************************
* General comments on code generation.
*
* Code is output in the form of strings using the following functions:
*   cout();                        (one line at a time)
*   coutf();                       (with printf-style formatting)
*
* The type of numbers used in the generated code is given by the macro MCNUM
* (defined in mccode-r.h).
*
* Symbols.
*
* Symbols are exposed using defines around sections or functions, e.g.
*   #define x _particle->x
* where _particle is a local variable in a trace function.
*
* Generic symbols beside _particle are _comp (also local) and instrument, a
* global. The global _particle is used for RNG during the init stage - as the
* rand state is now tied to a particle instance - but otherwise overridden by
* the local version. A few other variables carry meta information.
*
* Generation of declarations.
*
* The following declarations are generated:
* 1. Header file #include - mccode-r.h/c and mcstas/mcxtrace-r.c/h for
*    declarations for the mcstas runtime. The former contains geometry, I/O and
*    other generic functionality, while mcstas/mcxtrace-r.c/h contains nautron
*    or x-ray specific propagation functionality and data structures.
* 2. Declarations of global variables to hold instrument state. This is
*    organized as a generic struct, a parameters-struct, and associated
*    variables.
* 3. User declarations copied verbatim from the instrument definition file.
* 4. User-vars declarations copied to the particle struct definition.
* 5. Declarations and global variables for the component types. This uses
*    a generic struct containing index, pos/rot and more, and a parameter
*    struct for every component type. A variable is written for every
*    component instance, named _<compname>.
* 6. Setpos functions for every component instance.
* 7. Init, trace, save, finally and display class functions for every component
*    type (when defined in the component). The TRACE functions contain
*    additions for any EXTEND blocks, which uses a comp index switch. Iterative
*    functions that call these, are also generated.
* 8. Raytrace funtions for propagating the instrument.
* 9. Additional code bits for macro support.
*******************************************************************************/

/* PROJECT=1 for McStas, 2 for McXtrace. Now using @MCCODE_PARTICLE@ @MCCODE_NAME@ */
#ifndef MCCODE_PROJECT
//#define MCCODE_PROJECT @MCCODE_PROJECT@
#define MCCODE_PROJECT 1
#endif

#ifndef MCCODE_LIBENV
#define MCCODE_LIBENV @MCCODE_LIBENV@
#endif

int get_codeblock_vars_allcustom(struct code_block *code, List custom_vars,
   char* block_name, char* movetoblock_name);

int get_codeblock_vars(struct code_block *code, List vars, List types,
         char* block_name, char* movetoblock_name);

int parse_curlybrackets_vector(char* string, double* values) {
  char* s = string;
  int vidx = 0;
  char* r;
  while(*s != '\0') {
    // jump to a non-trivial position
    if (*s == ' ' || *s == ',' || *s == '{') {
      ++s;
      continue;
    }
    if (*s == '}') return vidx;

    // extract a value
    double val = strtod(s, &r);
    if (values!=NULL) values[vidx] = val;
    ++vidx;

    // iterate
    if (*r == '\0') return vidx;
    s = r + 1;
  }
  return vidx;
}

/* Functions for outputting code. */

/* Handle for output file. */
static FILE *output_handle           = NULL;  /* Handle for output file. */
static int   num_next_output_line    = 1;     /* Line number for next output line. */
static char *quoted_output_file_name = NULL;  /* str_quote()'ed name of output file. */

/* Convert instrument formal parameter type numbers to their enum name. */
char *instr_formal_type_names[] =
  { (char*) "instr_type_int", (char*) "instr_type_string", (char*) "instr_type_char", (char*) "instr_type_vector", (char*) "instr_type_double", (char*) "instr_type_symbol" };

/* 'char' and 'MCNUM' are for static array allocations */
char *instr_formal_type_names_real[] =
  { (char*) "int", (char*) "char*", (char*) "char", (char*) "MCNUM", (char*) "MCNUM", (char*) "double"};

/*******************************************************************************
* Output a single line of code
* Assumes that the output does not contain newlines.
*******************************************************************************/
static void
cout(char *s)
{
    fprintf(output_handle, "%s\n", s);
    num_next_output_line++;
}

static void
cout(const char *s)
{
    fprintf(output_handle, "%s\n", s);
    num_next_output_line++;
}

/*******************************************************************************
* Output a single line of code using printf-style format string.
* Assumes that the output does not contain newlines.
*******************************************************************************/
static void
coutf(char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vfprintf(output_handle, format, ap);
    va_end(ap);
    fprintf(output_handle, "\n");
    num_next_output_line++;
}
static void
coutf(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vfprintf(output_handle, format, ap);
    va_end(ap);
    fprintf(output_handle, "\n");
    num_next_output_line++;
}

/*******************************************************************************
* Output #line directive to handle code coming from a different file.
* The filename is assumed to be already properly quoted for special chars.
*******************************************************************************/
static void
code_set_source(char *filename, int linenum)
{
    // jg-20190307: We have disabled line pragmas for now
    //if(linenum > 0)
    //  coutf("#line %d \"%s\"", linenum, filename);
}

/*******************************************************************************
* Output #line directive to reset back to the generated output C file.
*******************************************************************************/
static void
code_reset_source(void)
{
    // jg-20190307: We have disabled line pragmas for now
    /* Note: the number after #line refers to the line AFTER the directive. */
    //coutf("//#line %d \"%s\"", num_next_output_line + 1, quoted_output_file_name);
}

/*******************************************************************************
* Output a list of lines of code
*******************************************************************************/
static void
codeblock_out(struct code_block *code)
{
    List_handle liter;                /* For list iteration. */
    char *line;                       /* Single code line. */

    if(list_len(code->lines) <= 0) return;

    code_set_source(code->quoted_filename, code->linenum + 1);
    liter = list_iterate(code->lines);
    while((line = (char*) list_next(liter)))
    {
      fprintf(output_handle, "%s", line);
      num_next_output_line++;
    }
    list_iterate_end(liter);
    code_reset_source();
}

/*******************************************************************************
* Output a list of lines of code, embraced in { ... }
*******************************************************************************/
static void
codeblock_out_brace(struct code_block *code)
{
    List_handle liter;                /* For list iteration. */
    char *line;                       /* Single code line. */

    if(list_len(code->lines) <= 0) return;

    code_set_source(code->quoted_filename, code->linenum);
    coutf("{");
    liter = list_iterate(code->lines);
    while((line = (char*) list_next(liter)))
    {
        fprintf(output_handle, "%s", line);
        num_next_output_line++;
    }
    list_iterate_end(liter);
    coutf("}");
    code_reset_source();
}

/** Output the lines of a literal block, encased in double quotes, and with any contained double quotes escaped.
 *
 * This form allows for automatic line-breaking string concatenation
 */
static void
escaped_lines_out(List lines) {
    List_handle liter;                /* For list iteration. */
    char *line;                       /* Single code line. */
    char * escaped_line;
    if (list_undef(lines) || list_len(lines) <= 0) {
        fprintf(output_handle, (char*) "\"\"");
    }
    else {
        liter = list_iterate(lines);
        while((line = (char*) list_next(liter)))
        {
            //escaped_line = escaped_string(line);
            escaped_line = str_quote(line);
            fprintf(output_handle, "\"%s\"\n", escaped_line);
            memfree(escaped_line); // a copy was made even if nothing was changed
            num_next_output_line++;
        }
        list_iterate_end(liter);
    }
}

/*******************************************************************************
* Create an empty code list
*******************************************************************************/
struct code_block *
codeblock_new(void)
{
  struct code_block *cb;

  cb = (code_block*) palloc(cb);
  cb->filename = NULL;
  cb->quoted_filename = NULL;
  cb->linenum  = -1;
  cb->lines    = list_create();
  return cb;
}

/*******************************************************************************
* Read a file and output it to the generated simulation code. Uses a
* fixed-size buffer, and will silently and arbitrarily break long lines.
*******************************************************************************/
static void
embed_file(char *name)
{
  char buf[4096];
  FILE *f;
  int last;

  coutf( "/* embedding file \"%s\" */", name);

  if (!symtab_lookup(lib_instances, name))
  {
    /* First look in the system directory. */
    f = open_file_search_sys(name);
    /* If not found, look in the full search path. */
    if(f == NULL) {
      f = open_file_search(name);
      /* If still not found, abort. */
      if(f == NULL)
        fatal_error("Could not find file '%s'\n", name);
      else if (verbose) fprintf(stderr, "Embedding file      %s (user path)\n", name);
    } else if (verbose) fprintf(stderr, "Embedding file      %s (%s)\n", name, get_sys_dir());

    coutf("");
    code_set_source(name, 1);
    /* Now loop, reading lines and outputting them in the code. */
    while(!feof(f))
    {
      if(fgets(buf, 4096, f) == NULL)
        break;
      last = strlen(buf) - 1;
      if(last >= 0 && (buf[last] == '\n' || buf[last] == '\r'))
        buf[last--] = '\0';
      if(last >= 0 && (buf[last] == '\n' || buf[last] == '\r'))
        buf[last--] = '\0';
      cout(buf);
    }
    fclose(f);
    coutf( "/* End of file \"%s\". */", name);
    coutf("");
    code_reset_source();
    symtab_add(lib_instances, name, NULL);
  } /* else file has already been embedded */
} /* embed_file */

/* *****************************************************************************
* cogen_defundef: define/undefine a symbol from a List
* input:  a list
*         a flag: GLOBAL_INSTANCE_PAR_VALUE=define with component name,
*                 LOCAL_INSTANCE_PAR_VALUE =define with 'comp' as structure name,
*                 INSTRUMENT_PAR_VALUE     =define with 'instrument_name' as structure name
*                 GLOBAL_INSTANCE_PAR_REF  =define with component name pointer,
*                 PAR_UNDEF                =un-define
*
* code is generated in function [comp]_[section=init/save/finally/display]
* called by: cogen_comp_[section]
***************************************************************************** */
enum DEFINITION_TYPE {
  INSTRUMENT_PAR_VALUE,
  GLOBAL_INSTANCE_PAR_REF,
  LOCAL_INSTANCE_PAR_REF,
  PAR_UNDEF
};

static void cogen_defundef(struct comp_inst *comp, List l, char define_it)
{
  if(list_len(l) > 0) {
    List_handle liter;
    struct comp_iformal *c_formal;/* Name of component formal input parameter */

    liter = list_iterate(l);
    while((c_formal = (comp_iformal*) list_next(liter))) {
      int flag_noconflict=1;

      if (!c_formal->id || !strlen(c_formal->id))
        continue; // skip invalid parameter names
      switch (define_it) {
      case GLOBAL_INSTANCE_PAR_REF:
        coutf( "  #define %s (_%s_var._parameters.%s)",
          c_formal->id, comp->name, c_formal->id);
        break;
      case LOCAL_INSTANCE_PAR_REF:
        coutf( "  #define %s (_comp->_parameters.%s)",
          c_formal->id, c_formal->id);
        break;
      case INSTRUMENT_PAR_VALUE:
        /* instrument parameters, only when no conflict with component */
        if (comp) {
          int index=0;
          for (index=0; index <3; index++) {
            List l;
            if (index ==0)      l = comp->def->set_par ;
            else if (index ==1) l = comp->def->out_par ;
            else                l = comp->def->def_par ;

            if(list_len(l) > 0)
            {
              List_handle liter = (List_handle) list_iterate(l);
              struct comp_iformal *ci_formal=NULL;/* Name of component formal input parameter */

              while((ci_formal = (comp_iformal*) list_next(liter)))
                if (!strcmp(c_formal->id, ci_formal->id)) {
                  flag_noconflict=0; break;
                }
            }
          } /* for List */
        }
        if (flag_noconflict && strlen(c_formal->id))
          coutf( "  #define %s (instrument->_parameters.%s)",
            c_formal->id, c_formal->id);
        break;
      case PAR_UNDEF:
      default:
        coutf( "  #undef %s", c_formal->id);

      } /* switch */
    } /* while */
    list_iterate_end(liter);
  }
} /* cogen_defundef */

/* *****************************************************************************
* Looks for comp_iformal id (varname) matches, assumes lst elements are of this
* type.
***************************************************************************** */
int var_in_list(List lst, struct comp_iformal* var) {
  int retval = 0;
  List_handle liter;
  liter = list_iterate(lst);
  struct comp_iformal* lst_var;
  while((lst_var = (comp_iformal*) list_next(liter))) {
    if (!strcmp(lst_var->id, var->id)) {
      retval = 1;
      break;
    }
  }
  list_iterate_end(liter);
  return retval;
}

/* *****************************************************************************
* cogen_comp_declare: write the declaration part from the component instance
*   that is, the component parameter structure and positioning code.
* input:  a component instance structure pointer (not modified)
* output: number of warning/errors to fix.
*
* code is generated at root level of C file: only C definitions, no initialisers!
* called by: cogen_decls
***************************************************************************** */
int cogen_comp_declare(struct comp_inst *comp)
{
    int warnings = 0;
    int nb_parameters = 0;

    if (!comp->def->flag_defined_structure) {
        // only once
        comp->def->flag_defined_structure = 1;

        // a comment
        coutf( "/* component %s=%s() [%i] DECLARE */", comp->name, comp->def->name, comp->index);
        coutf( "/* Parameter definition for component type '%s' */", comp->def->name);
        // start outputting the parameters struct
        coutf( "struct _struct_%s_parameters {", comp->def->name);

        //
        // Mix declare vars with output pars: Declare overrides OUTPUT, because the
        // type of the former are free, while the type of the latter must be part of
        // the mccode officially recognized parameter types.
        //

        // -- step Ia: get vars from declare block
        comp->def->decl_par = list_create();
        get_codeblock_vars_allcustom(
          comp->def->decl_code,  // source
          comp->def->decl_par,   // type list
          (char*) "DECLARE",
          (char*) "INITIALIZE"); // warning context

        // -- step IIa: transfer all <output minus decl> pars to a new list
        List new_out_pars;
        new_out_pars = list_create();

        // Annihilation of OUTPUT/PRIVATE parameter generation
        /*    List_handle outputiter;
        outputiter = list_iterate(comp->def->out_par);
        struct comp_iformal* outpar;
        while(outpar = list_next(outputiter)) {
          if (!var_in_list(comp->def->decl_par, outpar)) {
            list_add(new_out_pars, outpar);
          }
        } */

        // -- step IIb: transfer all decl vars to the new list
        List_handle decliter;
        decliter = list_iterate(comp->def->decl_par);
        struct comp_iformal* declvar;
        while((declvar = (comp_iformal*) list_next(decliter))) {
          list_add(new_out_pars, declvar);
        }
        list_iterate_end(decliter);

        // -- step III: replace previous output pars list with the new (patched) list
        // TODO: free the previous list first?
        comp->def->out_par = new_out_pars;

        // now add setting and (patched) output vars to comp struct
        int index = 0;
        for (index=0; index<2; index++) {
          List l = (index == 0 ? comp->def->set_par : comp->def->out_par);
          if(list_len(l) > 0)
          {
            List_handle liter;
            liter = list_iterate(l);

            struct comp_iformal *c_formal;
            coutf( "  /* Component type '%s' %s parameters */",
              comp->def->name, index == 0 ? "setting" : "private");

            // write variable to comp struct
            while((c_formal = (comp_iformal*) list_next(liter)))
            {
              nb_parameters++;
              if (c_formal->type == instr_type_custom) {
                coutf( "  %s %s;", c_formal->type_custom, c_formal->id);
          int len = re_match("\\[",c_formal->id);
          if (len>=0) {
            c_formal->id[len]='\0';
          }
              } else if (c_formal->type ==instr_type_vector) {
          struct Symtab_entry *entry;
          entry = symtab_lookup(comp->setpar, c_formal->id);
          char *val = exp_tostring((cexp*) entry->val); /* replaced by instrument parameter when exists */
          if (val[0] == '{') {
            int vl = parse_curlybrackets_vector(val, NULL);
      printf("\nWARNING:\n The parameter %s of %s is initialized \n using a static {,,,} vector.\n",c_formal->id,comp->name);
      printf("  -> Such static vectors support literal numbers ONLY.\n");
      printf("  -> Any vector use of variables or defines must happen via a \n");
      printf("     DECLARE/INITIALIZE pointer.\n\n");
            coutf( "  %s %s[%i];", instr_formal_type_names_real[c_formal->type], c_formal->id, vl);
          } else {
            coutf( "  %s* %s;", instr_formal_type_names_real[c_formal->type], c_formal->id);
          }
              } else if (c_formal->type != instr_type_string) {
                coutf( "  %s %s;", instr_formal_type_names_real[c_formal->type], c_formal->id);
              }
              else  /* array parameter */ {
                coutf( "  %s %s[16384];", instr_formal_type_names_real[c_formal->type+1], c_formal->id);
              }
            } /* while c_formal */

            list_iterate_end(liter);
          } /* if(list_len(l) > 0) */
        } /* for List in (setpar outpar declpar) */

        // jg-200203: NOTE that we no longer copy-paste DECLARE block to comp pars struct

        // output a comment noting a lack of parameters
        if (!nb_parameters)
          coutf( "  char %s_has_no_parameters;", comp->def->name);

        // comp parameters struct end
        coutf( "}; /* _struct_%s_parameters */", comp->def->name);
        coutf( "typedef struct _struct_%s_parameters _class_%s_parameters;",
          comp->def->name, comp->def->name);
        cout("");

        coutf( "/* Parameters for component type '%s' */", comp->def->name);
        coutf( "struct _struct_%s {", comp->def->name);
        /* make struct: set, pos, rot, declare block */
        coutf( "  char     _name[256]; /* e.g. %s */", comp->name);
        coutf( "  char     _type[256]; /* %s */", comp->def->name);
        coutf( "  long     _index; /* e.g. %i index in TRACE list */", index);
        cout(  "  Coords   _position_absolute;");
        cout(  "  Coords   _position_relative; /* wrt PREVIOUS */");
        cout(  "  Rotation _rotation_absolute;");
        cout(  "  Rotation _rotation_relative; /* wrt PREVIOUS */");
        cout(  "  int      _rotation_is_identity;");
        cout(  "  int      _position_relative_is_zero;");
        coutf( "  _class_%s_parameters _parameters;", comp->def->name);
        cout("};");
        coutf("typedef struct _struct_%s _class_%s;", comp->def->name, comp->def->name);
    } /* define class type parameter structure when not done yet (only once) */

    /* instantiate one structure per component instance */
    coutf("_class_%s _%s_var;", comp->def->name, comp->name);
    coutf("#pragma acc declare create ( _%s_var )", comp->name);
    coutf("");

    return(warnings);
} /* cogen_comp_declare */

/* *****************************************************************************
* cogen_comp_init_par: write the setting/output parameter allocation in [section]
* input:  a component instance structure pointer (not modified)
*         an instrument structure pointer (not modified)
*         a section as "SETTING" or "PRIVATE"/"OUTPUT"
*
* code is generated in function [comp]_[section=init/save/display/finally]
* called by: cogen_comp_section
***************************************************************************** */
static void cogen_comp_init_par(struct comp_inst *comp, struct instr_def *instr,
                                char *section)
{
  List l = !strcmp(section, "SETTING") ? comp->def->set_par : comp->def->out_par;

  if(list_len(l) > 0)
  {
    List_handle list_par = list_iterate(l);
    struct comp_iformal *par;

    while((par = (comp_iformal*) list_next(list_par)) != NULL)
    {
      char *val=NULL;

      if (!strcmp(section, "SETTING")) {
        struct Symtab_entry *entry;
        entry = symtab_lookup(comp->setpar, par->id);
        val   = exp_tostring((cexp*) entry->val); /* replaced by instrument parameter when exists */
        code_set_source(instr->quoted_source, exp_getlineno((cexp*) entry->val));
      } else {
        val =  par->isoptional ? exp_tostring(par->default_value) : NULL;
      }

      if (val) {
        if (par->type == instr_type_string) {
          if (strcmp(val, "0") && strcmp(val, "NULL")) { /* when value is not NULL (avoid warning at compile) */
            coutf("  if(%s && strlen(%s))", val, val);
            coutf("    stracpy(_%s_var._parameters.%s, %s ? %s : \"\", 16384);", comp->name, par->id, val, val);
            coutf("  else ");
          }
          coutf("  _%s_var._parameters.%s[0]='\\0';", comp->name, par->id);
        }
        else if (par->type == instr_type_vector) {
          if (val[0] == '{') {
      double values[100];
      int vl = parse_curlybrackets_vector(val, values);
      int i;
      for (i=0; i<vl; i++) {
        coutf("  _%s_var._parameters.%s[%i] = %g;", comp->name, par->id, i, values[i]);
      }
    } else
            coutf("  _%s_var._parameters.%s = %s; // default pointer allocation", comp->name, par->id, val);
        }
        else if (par->type == instr_type_symbol) {
          // the user vars value is particle specific, init to null
          coutf("  _%s_var._parameters.%s = \'\\0\';", comp->name, par->id);
        } else
          coutf("  _%s_var._parameters.%s = %s;", comp->name, par->id, val);

        str_free(val);
      }
      /* define the symbol right after assignment so that we can use it in further parameters */
      //coutf("  #define %s (_%s_var._parameters.%s)", par->id, comp->name, par->id);
    }
    list_iterate_end(list_par);
    if(list_len(l) > 0 && !strcmp(section, "SETTING"))
      code_reset_source();
    coutf("");
  }
} /* cogen_comp_init_par */

/* *****************************************************************************
* cogen_comp_init_position: write the position/rotation data
* input:  a component instance structure pointer (not modified)
*         previous component pointer or NULL (for relative stuff)
*         the instrument structure
*
* code is generated in function [comp]_setpos
* called by: cogen_comp_setpos
***************************************************************************** */
static void cogen_comp_init_position(
  struct comp_inst *comp,
  struct comp_inst *last,
  struct instr_def *instr)
{
  char d2r[] = "DEG2RAD";
  struct comp_inst *relcomp; /* Component relative to. */
  char *x, *y, *z;

  /* compute coordinates. Can use current instance parameters */
  /* Absolute rotation. */
  x = exp_tostring(comp->pos->orientation.x);
  y = exp_tostring(comp->pos->orientation.y);
  z = exp_tostring(comp->pos->orientation.z);
  relcomp = comp->pos->orientation_rel;
  coutf("  /* component %s=%s() AT ROTATED */",
    comp->name, comp->def->name);
  coutf("  {");
  coutf("    Coords tc1, tc2;");
  coutf("    tc1 = coords_set(0,0,0);");
  coutf("    tc2 = coords_set(0,0,0);");
  coutf("    Rotation tr1;");
  coutf("    rot_set_rotation(tr1,0,0,0);");

  if(relcomp == NULL)
  {                                /* Absolute orientation. */
    coutf("    rot_set_rotation(_%s_var._rotation_absolute,", comp->name);
    code_set_source(instr->quoted_source,
                    exp_getlineno(comp->pos->orientation.x));
    coutf("      (%s)*%s, (%s)*%s, (%s)*%s);", x, d2r, y, d2r, z, d2r);
    code_reset_source();
  }
  else
  {
    coutf("    rot_set_rotation(tr1,");
    code_set_source(instr->quoted_source,
                    exp_getlineno(comp->pos->orientation.x));
    coutf("      (%s)*%s, (%s)*%s, (%s)*%s);", x, d2r, y, d2r, z, d2r);
    code_reset_source();
    coutf("    rot_mul(tr1, _%s_var._rotation_absolute, _%s_var._rotation_absolute);", relcomp->name, comp->name);
  }
  str_free(z);
  str_free(y);
  str_free(x);

  /* Relative rotation. */
  if(last == NULL)
  {
    /* First component. */
    coutf("    rot_copy(_%s_var._rotation_relative, _%s_var._rotation_absolute);", comp->name, comp->name);
  }
  else
  {
    coutf("    rot_transpose(_%s_var._rotation_absolute, tr1);", last->name);
    coutf("    rot_mul(_%s_var._rotation_absolute, tr1, _%s_var._rotation_relative);", comp->name, comp->name);
  }
  coutf("    _%s_var._rotation_is_identity =  rot_test_identity(_%s_var._rotation_relative);", comp->name, comp->name);

  /* Absolute position. */
  x = exp_tostring(comp->pos->place.x);
  y = exp_tostring(comp->pos->place.y);
  z = exp_tostring(comp->pos->place.z);
  relcomp = comp->pos->place_rel;
  if(relcomp == NULL)
  {
    coutf("    _%s_var._position_absolute = coords_set(", comp->name);
    code_set_source(instr->quoted_source, exp_getlineno(comp->pos->place.x));
    coutf("      %s, %s, %s);", x, y, z);
    code_reset_source();
  }
  else
  {
    coutf("    tc1 = coords_set(");
    code_set_source(instr->quoted_source, exp_getlineno(comp->pos->place.x));
    coutf("      %s, %s, %s);", x, y, z);
    code_reset_source();
    coutf("    rot_transpose(_%s_var._rotation_absolute, tr1);", relcomp->name);
    coutf("    tc2 = rot_apply(tr1, tc1);");
    coutf("    _%s_var._position_absolute = coords_add(_%s_var._position_absolute, tc2);", comp->name, relcomp->name);
  }

  str_free(z);
  str_free(y);
  str_free(x);

  /* Relative position. */
  if(last == NULL)
    coutf("    tc1 = coords_neg(_%s_var._position_absolute);", comp->name);
  else
    coutf("    tc1 = coords_sub(_%s_var._position_absolute, _%s_var._position_absolute);", last->name, comp->name);
  coutf("    _%s_var._position_relative = rot_apply(_%s_var._rotation_absolute, tc1);", comp->name, comp->name);
  coutf("  } /* %s=%s() AT ROTATED */", comp->name, comp->def->name);

  coutf("  DEBUG_COMPONENT(\"%s\", _%s_var._position_absolute, _%s_var._rotation_absolute);", comp->name, comp->name, comp->name);
  coutf("  instrument->_position_absolute[%i] = _%s_var._position_absolute;", comp->index, comp->name);
  coutf("  instrument->_position_relative[%i] = _%s_var._position_relative;", comp->index, comp->name);

  coutf("    _%s_var._position_relative_is_zero =  coords_test_zero(_%s_var._position_relative);", comp->name, comp->name);

} /* cogen_comp_init_position */

/* *****************************************************************************
* cogen_comp_section_class: write a common/shared section part for component
*   types, generates an class_[comptype]_[section](*comp) function.
*
* input:  a component instance structure pointer
*         section can be INITIALISE SAVE FINALLY DISPLAY TRACE
* output: 0 when all is fine, non-0 when error found
*
* called by: cogen_[section]
***************************************************************************** */
int cogen_comp_section_class(
  struct comp_inst *comp,
  struct instr_def *instr,
  char *section,
  char *section_lower,
  struct code_block *code,
  int *flag_defined_common)
{
  int warnings = 0;
  List_handle liter;
  struct comp_inst *extendcomp = NULL;

  // in case of TRACE, count EXTEND blocks for this component type
  int cnt_extend = 0;
  if (!strcmp(section, "TRACE")) {
    liter = list_iterate(instr->complist);
    while((extendcomp = (comp_inst*) list_next(liter)) != NULL) {
      if (list_len(extendcomp->extend->lines) > 0 && (!strcmp(extendcomp->def->name, comp->def->name)))
        cnt_extend++;
    }
    list_iterate_end(liter);
  }

  // proceed if comp type has trace code or EXTEND
  if ((!code || list_len(code->lines) <= 0) && cnt_extend == 0)
    return(0);

  /* generate class functions (unless flagged already done) */
  if (!*flag_defined_common) {

    // set flag so that definition [section] is done only once
    *flag_defined_common = 1;

    // write class fct footprint

    // TRACE only compile gpu variant
    if (!strcmp(section, "TRACE")) {
      if (!comp->def->flag_noacc)
	coutf("#pragma acc routine");
        coutf("void class_%s_%s(_class_%s *_comp", comp->def->name, section_lower, comp->def->name);
    } else {
      coutf("_class_%s *class_%s_%s(_class_%s *_comp", comp->def->name, comp->def->name, section_lower, comp->def->name);
    }

    // TRACE add particle parameter to footprint
    if (!strcmp(section, "TRACE")) /* TRACE: need to define particle state */
    {
      coutf("  , _class_particle *_particle) {",
        comp->def->name, comp->def->name, section_lower, comp->def->name);
      coutf("  ABSORBED=SCATTERED=RESTORE=0;");
    } else
      coutf(") {");

    // def-undef component pars
    cogen_defundef(comp, comp->def->set_par, LOCAL_INSTANCE_PAR_REF); // [par] -> comp->parameters.[par]
    cogen_defundef(comp, comp->def->out_par, LOCAL_INSTANCE_PAR_REF);

    coutf("  SIG_MESSAGE(\"[_%s_%s] component %s=%s() %s [%s:%i]\");",
      comp->name, section_lower, comp->name, comp->def->name, section,
      code && code->quoted_filename ? code->quoted_filename : comp->def->name,
      code && code->linenum > 0 ? code->linenum : 0);
    coutf("");

    // TRACE assign user var values, instance specific switch
    // NOTE: These are the user1, user2, ... component vars,
    //       not the USERVARs/particle vars handled below for EXTEND
    if (!strcmp(section, "TRACE"))
    {
      List_handle piter;
      struct comp_iformal *par;
      struct Symtab_entry *entry;

      // Determine if user vars are activated
      int has_user_vars = 0;
      char *val=NULL;
      piter = list_iterate(comp->def->set_par);
      while((par = (comp_iformal*) list_next(piter)) != NULL) {
        // get parameter value from component parameters name-value structure
        entry = symtab_lookup(comp->setpar, par->id);
        val = exp_tostring((cexp*) entry->val);

        if (par->type == instr_type_symbol
          && strcmp(val, "\0")
          && strcmp(val, "NULL"))
        {
          has_user_vars = 1;
          break;
        }
      }
      list_iterate_end(piter);

      List_handle citer;
      struct comp_inst *loopcomp;
      if (has_user_vars) {
        // loop components
        citer = list_iterate(instr->complist);
        while((loopcomp = (comp_inst*) list_next(citer)) != NULL) {
          if ((!strcmp(comp->def->name, loopcomp->def->name))) {
            coutf("  /* Check if this is component '%s' */ ", loopcomp->name);
      	    coutf("  if(_comp->_index == %i) { ", loopcomp->index);

            // loop pars
            piter = list_iterate(loopcomp->def->set_par);
            while((par = (comp_iformal*) list_next(piter))) {
              if (par->type == instr_type_symbol) {
                entry = symtab_lookup(loopcomp->setpar, par->id);
                val = exp_tostring((cexp*) entry->val);
                coutf("    // HEST!");
                coutf("    %s = %s;", par->id, val);
              }
            }
            list_iterate_end(piter);

            coutf("  }");
          }
        }
        list_iterate_end(citer);

        coutf("");
      } // comp type has activated user vars (user1, user2, ...)

    }
    if (!strcmp(section, "DISPLAY"))
      coutf("  printf(\"MCDISPLAY: component %s\\n\", _comp->_name);");

    // shared comp [section] code here
    //if (!strcmp(section, "TRACE")) cout("{"); // scope it to avoid EXTEND clashes
    codeblock_out(code); // component definition code common to all instances, needs defines
    if (!strcmp(section, "TRACE")) {
      coutf("#ifndef NOABSORB_INF_NAN");
      coutf("  /* Check for nan or inf particle parms */ ");
#if MCCODE_PROJECT == 1     /* neutron */
      coutf("  if(isnan(p + t + vx + vy + vz + x + y + z)) ABSORB;");
      coutf("  if(isinf(fabs(p) + fabs(t) + fabs(vx) + fabs(vy) + fabs(vz) + fabs(x) + fabs(y) + fabs(z))) ABSORB;");
#elif MCCODE_PROJECT == 2   /* xray */
      cout("  if(isnan(p + t + kx + ky + kz + x + y + z + phi)) ABSORB;");
      cout("  if(isinf(fabs(p) + fabs(t) + fabs(kx) + fabs(ky) + fabs(kz) + fabs(x) + fabs(y) + fabs(z) + fabs(phi))) ABSORB;");
#endif
      coutf("#else");
      coutf("  if(isnan(p)  ||  isinf(p)) printf(\"NAN or INF found in p,  %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("  if(isnan(t)  ||  isinf(t)) printf(\"NAN or INF found in t,  %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
#if MCCODE_PROJECT == 1     /* neutron */
      coutf("  if(isnan(vx) || isinf(vx)) printf(\"NAN or INF found in vx, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("  if(isnan(vy) || isinf(vy)) printf(\"NAN or INF found in vy, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("  if(isnan(vz) || isinf(vz)) printf(\"NAN or INF found in vz, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
#elif MCCODE_PROJECT == 2   /* xray */
      cout("  if(isnan(phi)  ||  isinf(phi)) printf(\"NAN or INF found in phi, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      cout("  if(isnan(kx) || isinf(kx)) printf(\"NAN or INF found in kx, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      cout("  if(isnan(ky) || isinf(ky)) printf(\"NAN or INF found in ky, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      cout("  if(isnan(kz) || isinf(kz)) printf(\"NAN or INF found in kz, %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
#endif
      coutf("  if(isnan(x)  ||  isinf(x)) printf(\"NAN or INF found in x,  %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("  if(isnan(y)  ||  isinf(y)) printf(\"NAN or INF found in y,  %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("  if(isnan(z)  ||  isinf(z)) printf(\"NAN or INF found in z,  %s (particle %lld)\\n\",_comp->_name,_particle->_uid);");
      coutf("#endif");
      //cout("}");
    }

    // EXTEND blocks written here, as component name switch, if any
    if (!strcmp("TRACE", section) && cnt_extend > 0) {
      // define symbols for USERVARS particle struct members:
      coutf("");
      List_handle uservarsiter = list_iterate(instr->user_vars);
      char *var;
      while((var = (char*) list_next(uservarsiter))) {
        coutf("  #define %s (_particle->%s)", var, var);
      }
      list_iterate_end(uservarsiter);

      liter = list_iterate(instr->complist);
      while((extendcomp = (comp_inst*) list_next(liter)) != NULL) {
        if (list_len(extendcomp->extend->lines) > 0
          && (!strcmp(extendcomp->def->name, comp->def->name))
          ) {
            coutf("if (_comp->_index == %i) { // EXTEND '%s'", extendcomp->index, extendcomp->name);
            codeblock_out(extendcomp->extend);
            coutf("}");
        }
      }
      list_iterate_end(liter);

      // define symbols for partilce USERVARS for extend section only:
      uservarsiter = list_iterate(instr->user_vars);
      while((var = (char*) list_next(uservarsiter))) {
        coutf("  #undef %s", var);
      }
      list_iterate_end(uservarsiter);
      coutf("");
    }
    /* undefine aliases */
    cogen_defundef(comp, comp->def->set_par, PAR_UNDEF);
    cogen_defundef(comp, comp->def->out_par, PAR_UNDEF);
    if (!strcmp(section, "TRACE")) {    
      coutf("  return;");
    } else {
      coutf("  return(_comp);");
    }
    coutf("} /* class_%s_%s */", comp->def->name, section_lower);
    coutf("");

  } /* generated SHARED [section] for component given type */

  return(*flag_defined_common);

} /* cogen_comp_section_class */

/*******************************************************************************
*
* Generates the only comp instance function, setpos.
*
*******************************************************************************/
int cogen_comp_setpos(
  struct comp_inst *comp,
  struct comp_inst *last,
  struct instr_def *instr)
{
  int warnings=0;
  coutf("/* component %s=%s() %s */",
    comp->name, comp->def->name, "SETTING, POSITION/ROTATION");

  /* the set+pos/rot instance function **************************************** */
  coutf("int _%s_setpos(void)", comp->name);
  coutf("{ /* sets initial component parameters, position and rotation */");

  /* init parameters. These can then be used in position/rotation syntax */
  /* all these parameters have a #define pointing to the real name space in structure */
  coutf("  SIG_MESSAGE(\"[_%s_%s] component %s=%s() %s [%s:%i]\");",
    comp->name, "setpos", comp->name, comp->def->name, "SETTING",
    comp->def->init_code && comp->def->init_code->quoted_filename ? comp->def->init_code->quoted_filename : comp->def->name,
    comp->def->init_code && comp->def->init_code->linenum > 0 ? comp->def->init_code->linenum : 0);

  // set comp name, comp type-name
  coutf("  stracpy(_%s_var._name, \"%s\", 16384);", comp->name, comp->name);
  coutf("  stracpy(_%s_var._type, \"%s\", 16384);", comp->name, comp->def->name);
  coutf("  _%s_var._index=%i;", comp->name, comp->index);
  coutf("  int current_setpos_index = %d;", comp->index);

  /* setting & output parameters of the component */
  cogen_comp_init_par(comp, instr, (char*) "SETTING");  // specific to each instance
  cogen_comp_init_par(comp, instr, (char*) "PRIVATE");  // specific to each instance

  /* undef aliases */
  //cogen_defundef(comp, comp->def->set_par, PAR_UNDEF);
  //cogen_defundef(comp, comp->def->out_par, PAR_UNDEF);

  /* position/rotation */
  cogen_comp_init_position(comp, last, instr); // specific to each instance

  char pref[5];
  if (comp->index-1 < 10) {
    sprintf(pref, "000");
  } else if (comp->index-1 < 100) {
    sprintf(pref, "00");
  } else if (comp->index-1 < 1000) {
    sprintf(pref, "0");
  } else if (comp->index-1 < 10000) {
    //sprintf(pref, (char*) "");
  } else {
    fprintf(stderr,"Error, no support for > 10000 comps at the moment!\n");
    exit(-1);
  }

  coutf("  instrument->counter_N[%i]  = instrument->counter_P[%i] = instrument->counter_P2[%i] = 0;",
        comp->index, comp->index, comp->index);
  coutf("  instrument->counter_AbsorbProp[%i]= 0;", comp->index);
  coutf("  #ifdef USE_NEXUS");
  coutf("  if(nxhandle) {");
  coutf("    if ((!mcdotrace) && mcformat && strcasestr(mcformat, \"NeXus\")) {");
  coutf("    MPI_MASTER(");
  coutf("        mccomp_placement_type_nexus(nxhandle,\"%s%d_%s\", _%s_var._position_absolute, _%s_var._rotation_absolute, \"%s\");", pref, comp->index-1, comp->name, comp->name, comp->name, comp->def->name);

  List_handle piter;
  struct comp_iformal *par;
  struct Symtab_entry *entry;
  char *val, *defval;
  piter = list_iterate(comp->def->set_par);
  while((par = (comp_iformal*) list_next(piter)) != NULL) {
    // get parameter value from component parameters name-value structure
    entry = symtab_lookup(comp->setpar, par->id);
    val = exp_tostring((cexp*) entry->val);
    if (!par->isoptional) {
      if (par->type==instr_type_string) {
	      defval = (char*) "\"NONE\"";
      } else {
      	defval = (char*) "NONE";
      }
    } else {
      defval = exp_tostring(par->default_value);
    }
    if (par->type == instr_type_string) { // value and defval "come with quotes" or are symbolic
      coutf("        mccomp_param_nexus(nxhandle,\"%s%d_%s\", \"%s\", %s, %s, \"%s\");", pref, comp->index-1, comp->name, par->id, defval, val, instr_formal_type_names_real[par->type]);
    } else {                            // both need quoting
      coutf("        mccomp_param_nexus(nxhandle,\"%s%d_%s\", \"%s\", \"%s\", \"%s\",\"%s\");", pref, comp->index-1, comp->name, par->id, defval,val, instr_formal_type_names_real[par->type]);
    }
  }
  list_iterate_end(piter);

  coutf( "      );");
  coutf( "    }");
  coutf( "  } else {");
  coutf( "    // fprintf(stderr,\"NO NEXUS FILE\");");
  coutf( "  }");
  coutf( "  #endif");
  coutf("  return(0);");

  coutf( "} /* _%s_%s */", comp->name, "setpos");
  coutf("");

  return(warnings);
} /* cogen_comp_setpos */

/*******************************************************************************
* Generates the function that returns (a void pointer to) a component instance,
* based on the component name as a string. Used by GETPAR macros.
*******************************************************************************/
void cogen_getvarpars_fct(struct instr_def *instr)
{
  cout("void* _getvar_parameters(char* compname)");
  cout("/* enables settings parameters based use of the GETPAR macro */");
  cout("{");

  cout("  #ifdef OPENACC");
  cout("    #define strcmp(a,b) str_comp(a,b)");
  cout("  #endif");

  List_handle iter;
  iter = list_iterate(instr->complist);
  struct comp_inst *comp;

  while((comp = (comp_inst*) list_next(iter)) != NULL) {
    coutf((char *) "  if (!strcmp(compname, \"%s\")) return (void *) &(_%s_var._parameters);", comp->name, comp->name);
  }
  list_iterate_end(iter);

  cout("  return 0;"); /* return a nullptr if case is not handled in the loop above */
  cout("}");
  cout("");
}

/*
 * Generates the function that returns the index of a named component or -1 if 
 * it does not exist in the instrument
 */
void cogen_getcompindex_fct(struct instr_def *instr){
  cout("int _getcomp_index(char* compname)");
  cout("/* Enables retrieving the component position & rotation when the index is not known.");
  cout(" * Component indexing into MACROS, e.g., POS_A_COMP_INDEX, are 1-based! */");
  cout("{");
  List_handle iter;
  iter = list_iterate(instr->complist);
  struct comp_inst *comp;
  int index=1;
  while ((comp = (comp_inst*) list_next(iter)) != NULL) {
    coutf("  if (!strcmp(compname, \"%s\")) return %i;", comp->name, index++);
  }
  cout("  return -1;");
  cout("}");
  cout("");
}

void cogen_getdistance_fct(){
  cout("double index_getdistance(int first_index, int second_index)");
  cout("/* Calculate the distance two components from their indexes*/");
  cout("{");
  cout("  return coords_len(coords_sub(POS_A_COMP_INDEX(first_index), POS_A_COMP_INDEX(second_index)));");
  cout("}");
  cout("");

  cout("double getdistance(char* first_component, char* second_component)");
  cout("/* Calculate the distance between two named components */");
  cout("{");
  cout("  int first_index = _getcomp_index(first_component);");
  cout("  int second_index = _getcomp_index(second_component);");
  cout("  return index_getdistance(first_index, second_index);");
  cout("}");
  cout("");

  cout("double checked_setpos_getdistance(int current_index, char* first_component, char* second_component)");
  cout("/* Calculate the distance between two named components at *_setpos() time, with component index checking */");
  cout("{");
  cout("  int first_index = _getcomp_index(first_component);");
  cout("  int second_index = _getcomp_index(second_component);");
  cout("  if (first_index >= current_index || second_index >= current_index) {");
  cout("    printf(\"setpos_getdistance can only be used with the names of components before the current one!\\n\");");
  cout("    return 0;");
  cout("  }");
  cout("  return index_getdistance(first_index, second_index);");
  cout("}");
  cout("#define setpos_getdistance(first, second) checked_setpos_getdistance(current_setpos_index, first, second)");
  cout("");
}

/*******************************************************************************
* Generates the function that returns a particle var ptr of type void*,
* based on the variable name as a string.
*
* Required for GET_PARTICLE_VAR macros used in component code.
*******************************************************************************/
void cogen_getparticlevar_fct(struct instr_def *instr)
{
  cout("void* _get_particle_var(char *token, _class_particle *p)");
  cout("/* enables setpars based use of GET_PARTICLE_DVAR macro and similar */");
  cout("{");

  List_handle iter;
  iter = list_iterate(instr->user_vars);
  char *varname;

  while((varname = (char*) list_next(iter))) {
    coutf("  if (!strcmp(token, \"%s\")) return (void *) &(p->%s);", varname, varname);
  }
  list_iterate_end(iter);

  cout("  return 0;");
  cout("}");
  cout("");
}

/*******************************************************************************
* cogen_decls: write the declaration part from the instrument description
*   that is the particle definition, the instrument parameters, the DECLARE part,
*   and all SHARE sections from components.
* input:  an instrument definition structure
* output: number of warnings/errors to fix.
*
* code is generated at root level of C file: only C definitions, no initialisers !
* calls: cogen_comp_declare
*******************************************************************************/
int cogen_decls(struct instr_def *instr)
{
  List_handle liter;             /* For list iteration. */
  struct comp_inst *comp;        /* Component instance. */
  struct instr_formal *i_formal; /* Name of instrument formal parameter. */
  long index = 0;
  int  warnings = 0;

  /* a previous call to cogen_header writes the file header */

  if (verbose) fprintf(stderr, "Writing instrument '%s' and components DECLARE\n", instr->name);

  cout("");
  cout("/* *****************************************************************************");
  coutf("* instrument '%s' and components DECLARE", instr->name);
  cout("***************************************************************************** */");
  cout("");

  /* 1. particle definition */
  /* moved to cogen_header, as this is needed in mccode-r */

  /* 2. Global variables for instrument parameters. */
  cout("/* Instrument parameters: structure and a table for the initialisation");
  cout("   (Used in e.g. inputparse and I/O function (e.g. detector_out) */");
  cout("");

  int numipar=0;
  cout("struct _struct_instrument_parameters {");

  if (!list_len(instr->formals)) {
    coutf("  char %s_has_no_parameter;", instr->name);
  } else {

    liter = list_iterate(instr->formals);
    while((i_formal = (instr_formal*) list_next(liter)))
    {
      if (i_formal->id && strlen(i_formal->id)) {
        coutf("  %s %s;", instr_formal_type_names_real[i_formal->type], i_formal->id);
        numipar++;
      }
    }
    list_iterate_end(liter);
  }
  cout("};");
  cout("typedef struct _struct_instrument_parameters _class_instrument_parameters;");
  cout("");

  /* check if we have GROUP, SPLIT and JUMP */
  index = list_len(instr->grouplist); // count GROUP
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    if (comp->split) index++;         // count SPLIT
  }
  list_iterate_end(liter);

  /* 2a. output an instrument logic structure to hold control statement logic */
  if (index > 0) {
    cout("/* instrument SPLIT and GROUP control logic */");
    cout("struct instrument_logic_struct {");

    if (list_len(instr->grouplist)) {
      struct group_inst *group;
      liter = list_iterate(instr->grouplist);
      while((group = (group_inst*) list_next(liter)))
        coutf("  long Group_%s; /* equals index of scattering comp when in group */", group->name);
      list_iterate_end(liter);
    }
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {
      if (comp->split) {
        coutf("  long Split_%s; /* this is the SPLIT counter decremented down to 0 */", comp->name);
        coutf("  _class_particle Split_%s_particle; /* this is the particle to duplicate */", comp->name);
      }
    }
    cout("};");
    list_iterate_end(liter);
    cout("");
  }

  /* 2b. instrument structure */
  cout("struct _instrument_struct {");
  coutf("  char   _name[256]; /* the name of this instrument e.g. '%s' */", instr->name);
  cout( "/* Counters per component instance */");
  coutf("  double counter_AbsorbProp[%i]; /* absorbed events in PROP routines */", list_len(instr->complist)+2);
  coutf("  double counter_N[%i], counter_P[%i], counter_P2[%i]; /* event counters after each component instance */",
    list_len(instr->complist)+2, list_len(instr->complist)+2, list_len(instr->complist)+2);
  coutf("  _class_particle _trajectory[%i]; /* current trajectory for STORE/RESTORE */", list_len(instr->complist)+2);
  cout( "/* Components position table (absolute and relative coords) */");
  coutf("  Coords _position_relative[%i]; /* positions of all components */",
    list_len(instr->complist)+2);
  coutf("  Coords _position_absolute[%i];",
    list_len(instr->complist)+2);
  cout( "  _class_instrument_parameters _parameters; /* instrument parameters */");
  if (index)
    cout( "  struct instrument_logic_struct logic; /* instrument logic */");
  cout( "} _instrument_var;");
  cout("struct _instrument_struct *instrument = & _instrument_var;");
  cout("#pragma acc declare create ( _instrument_var )");
  cout("#pragma acc declare create ( instrument )");
  cout("");

  /* 3. Table of instrument parameters. Used in mcparseoptions and various output functions */
  coutf("int numipar = %d;", numipar);
  coutf("struct mcinputtable_struct mcinputtable[] = {");
  liter = list_iterate(instr->formals);
  while((i_formal = (instr_formal*) list_next(liter)))
  {
    if (strlen(i_formal->id)) {
      if (i_formal->isoptional  // needed to avoid double quotes in strings
          && !strcmp(instr_formal_type_names[i_formal->type],"instr_type_string"))
        coutf("  \"%s\", &(_instrument_var._parameters.%s), %s, %s, \"%s\",", i_formal->id,
              i_formal->id, instr_formal_type_names[i_formal->type],
              exp_tostring(i_formal->default_value),
              i_formal->hasunit ? i_formal->unit : "");
      else
        coutf("  \"%s\", &(_instrument_var._parameters.%s), %s, \"%s\", \"%s\",", i_formal->id,
              i_formal->id, instr_formal_type_names[i_formal->type],
              i_formal->isoptional ? exp_tostring(i_formal->default_value) : "",
              i_formal->hasunit ? i_formal->unit : "");
    }
  }
  list_iterate_end(liter);
  coutf("  NULL, NULL, instr_type_double, \"\"");
  coutf("};");
  cout("");

  /* 3.5 Table of component-defined literal strings. */
  coutf("struct metadata_table_struct metadata_table[] = {");
  int num_metadata = 0;
  liter = list_iterate(instr->metadata);
  struct metadata_struct * metadata;
  while ((metadata = (metadata_struct*) list_next(liter))){
    coutf("\"%s\", \"%s\", \"%s\",", metadata->source, metadata->name, metadata->type);
    escaped_lines_out(metadata->lines);
    coutf(","); // terminates the line-broken concatenated strings
    ++num_metadata;
  }
  list_iterate_end(liter);
  coutf("  \"\", \"\", \"\", \"\"");
  coutf("};");
  coutf("int num_metadata = %d;", num_metadata);

  /* 4. Component SHAREs. */
  liter = list_iterate(instr->complist);
  index=0;
  while((comp = (comp_inst*) list_next(liter)))
  {
    if((list_len(comp->def->share_code->lines) > 0) && (!comp->def->flag_defined_share))
    {
      if (!index) {
        cout("");
        cout("/* ************************************************************************** */");
        cout("/*             SHARE user declarations for all components                     */");
        cout("/* ************************************************************************** */");
        cout("");
      }
      coutf("/* Shared user declarations for all components types '%s'. */", comp->def->name);
      codeblock_out(comp->def->share_code);
      comp->def->flag_defined_share = 1; /* flag the component so that SHARE outputs only once */
      cout("");
      index++;
    }
  }
  list_iterate_end(liter);
  if (index) {
    cout("");
    cout("");
    cout("/* ************************************************************************** */");
    cout("/*             End of SHARE user declarations for all components              */");
    cout("/* ************************************************************************** */");
    cout("");
  }

  /* 5. write component declares */
  cout("");
  cout("/* ********************** component definition declarations. **************** */");
  cout("");
  liter = list_iterate(instr->complist);
  index=0;
  while((comp = (comp_inst*) list_next(liter))) {
    comp->index=++index;        /* comp index starts at 1, as in instrument.y */
    // NOTE: "counter_instances" no longer matters, due to class functions
    comp->def->counter_instances++;
    warnings += cogen_comp_declare(comp);
  }

  list_iterate_end(liter);
  coutf("int mcNUMCOMP = %d;", list_len(instr->complist));
  coutf("");

  /* 6. User's declarations from the instrument definition file. */
  cout("/* User declarations from instrument definition. Can define functions. */");

  codeblock_out(instr->decls);
  cout("");

  /* undefines */
  coutf("#undef compcurname");
  coutf("#undef compcurtype");
  coutf("#undef compcurindex");

  coutf("/* end of instrument '%s' and components DECLARE */", instr->name);
  cout("");

  return(warnings);
} /* cogen_decls */


/* *****************************************************************************
* cogen_section: write a section part from the instrument description
*   and calls all component definition sections
* input:  an instrument definition structure
*         a section as "INITIALISE", "SAVE", "FINALLY", "DISPLAY"
*
* generates the mc[section] function, called by mccode_main
***************************************************************************** */
int cogen_section(struct instr_def *instr, char *section, char *section_lower,
  struct code_block *code)
{
  int warnings = 0;
  List_handle liter;
  struct comp_inst *comp=NULL, *last=NULL;

  /* instrument section comment */
  if (verbose) fprintf(stderr, "Writing instrument '%s' and components %s\n",
    instr->name, section);

  cout("/* *****************************************************************************");
  coutf("* instrument '%s' and components %s", instr->name, section);
  cout("***************************************************************************** */");
  cout("");

  if (!strcmp(section, "DISPLAY")) {
    /* User DECLARE code from component definitions (for each instance). */
    cout("  #define magnify     mcdis_magnify");
    cout("  #define line        mcdis_line");
    cout("  #define dashed_line mcdis_dashed_line");
    cout("  #define multiline   mcdis_multiline");
    cout("  #define rectangle   mcdis_rectangle");
    cout("  #define box         mcdis_box");
    cout("  #define circle      mcdis_circle");
    cout("  #define cylinder    mcdis_cylinder");
    cout("  #define sphere      mcdis_sphere");
    cout("  #define cone        mcdis_cone");
    cout("  #define polygon     mcdis_polygon");
    cout("  #define polyhedron  mcdis_polyhedron");
  }

  /* generate setpos instance functions */
  if (!strcmp(section, "INITIALISE")) {
    cogen_getdistance_fct();

    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {
      warnings += cogen_comp_setpos(comp, last, instr);
      if (comp->skip_transform == 0) {
        // Ensure useless components skipped
        last = comp;
      }
    }
  }

  /* generate class functions */
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL)
  {
    if (!strcmp(section, "INITIALISE"))
      warnings += cogen_comp_section_class(comp, instr, (char*) "INITIALISE", (char*) "init", comp->def->init_code, &(comp->def->flag_defined_init));
    else if (!strcmp(section, "SAVE"))
      warnings += cogen_comp_section_class(comp, instr, (char*) "SAVE", (char*) "save", comp->def->save_code, &(comp->def->flag_defined_save));
    else if (!strcmp(section, "FINALLY"))
      warnings += cogen_comp_section_class(comp, instr, (char*) "FINALLY", (char*) "finally", comp->def->finally_code, &(comp->def->flag_defined_finally));
    else if (!strcmp(section, "DISPLAY"))
      warnings += cogen_comp_section_class(comp, instr, (char*) "DISPLAY", (char*) "display", comp->def->display_code, &(comp->def->flag_defined_display));
  }
  list_iterate_end(liter);
  cout("");

  if (!strcmp(section, "DISPLAY")) {
    cout("  #undef magnify");
    cout("  #undef line");
    cout("  #undef dashed_line");
    cout("  #undef multiline");
    cout("  #undef rectangle");
    cout("  #undef box");
    cout("  #undef circle");
    cout("  #undef cylinder");
    cout("  #undef sphere");
  }
  cout("");

  /* then write the instrument main code, which calls component ones */
  coutf("int %s(%s) { /* called by mccode_main for %s:%s */",
    section_lower,
    !strcmp(section, "SAVE") ? "FILE *handle" : "void",
    instr->name,
    section);

  if (!strcmp(section, "INITIALISE"))
  {
    cout("  DEBUG_INSTR();");
    cout("");
    /* default values for instrument parameters are set in mcreadparams */
    cout("  /* code_main/parseoptions/readparams "
      "sets instrument parameters value */");
    coutf("  stracpy(instrument->_name, \"%s\", 256);", instr->name);
  }
  else if (!strcmp(section, "SAVE"))
    coutf("  if (!handle) siminfo_init(NULL);");
  else if (!strcmp(section, "FINALLY")) {
    // OpenACC update components on host (e.g. copy back GPU-generated changes)
    // (first thing to do in "finally")
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {
      coutf("#pragma acc update host(_%s_var)", comp->name);
    }
    // attach instrument
    cout("#pragma acc update host(_instrument_var)");
    cout("");

    coutf("  siminfo_init(NULL);");
    coutf("  save(siminfo_file); /* save data when simulation ends */");
  }
  else if (!strcmp(section, "DISPLAY"))
    cout("  printf(\"MCDISPLAY: start\\n\");");
  cout("");

  /* User code from instrument definition. */
  if (code && list_len(code->lines) > 0) {
    coutf("  /* Instrument '%s' %s */", instr->name, section);
    coutf("  SIG_MESSAGE(\"[%s] %s [%s:%i]\");",
      instr->name, section, code->quoted_filename, code->linenum);
    /* defines for the instrument parameters */
    cogen_defundef(NULL, instr->formals, INSTRUMENT_PAR_VALUE);
    codeblock_out_brace(code);
    /* un-defines for the instrument parameters */
    cogen_defundef(NULL, instr->formals, PAR_UNDEF);
  }

  /* generate setpos() calls, one pr. component instance */
  if (!strcmp(section, "INITIALISE")) {
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL)
    {
      coutf("  _%s_%s(); /* type %s */", comp->name, "setpos", comp->def->name);
    }
    list_iterate_end(liter);
    cout("");
  }

  /* component calls: one call for each component instance */
  coutf("  /* call iteratively all components %s */", section);
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL)
  {
    /* get the component code: no call to it when no code exists (except INIT) */
    struct code_block *comp_code=NULL;

    if (!strcmp(section, "INITIALISE"))
      comp_code = comp->def->init_code;
    else if (!strcmp(section, "SAVE"))
      comp_code = comp->def->save_code;
    else if (!strcmp(section, "FINALLY"))
      comp_code = comp->def->finally_code;
    else if (!strcmp(section, "DISPLAY"))
      comp_code = comp->def->display_code;

    if (list_len(comp_code->lines) > 0) {
      /* each component is called once, iteratively */
      coutf("  class_%s_%s(&_%s_var);", comp->def->name, section_lower, comp->name);
    }
    cout("");
  }
  list_iterate_end(liter);

  /* end the instrument sequential comps calls section */
  if (!strcmp(section, "INITIALISE")) {
    /* Output graphics representation of components. */
    coutf("  if (mcdotrace) display();");
    cout("  DEBUG_INSTR_END();");

    // call acc_attach for OpenACC (last thing to do in init)
    cout("");
    cout("#ifdef OPENACC");
    cout("#include <openacc.h>");
    // update component instances on device (e.g. push "managed" data structures)
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {
      coutf("#pragma acc update device(_%s_var)", comp->name);
    }
    // update instrument
    cout("#pragma acc update device(_instrument_var)");
    cout("#endif");
  }
  else if (!strcmp(section, "SAVE"))
    coutf("  if (!handle) siminfo_close(); ");
  else if (!strcmp(section, "FINALLY")) {
    coutf("  siminfo_close(); ");
  }
  else if (!strcmp(section, "DISPLAY"))
    cout("  printf(\"MCDISPLAY: end\\n\");");
  cout("");
  cout("  return(0);");
  coutf("} /* %s */", section_lower);
  cout("");

  return(warnings);
} /* cogen_section */


/*******************************************************************************
* def_trace_section: #define symbols for entire TRACE section
*******************************************************************************/
void def_trace_section(struct instr_def *instr)
{
  List_handle liter;
  int i = 0;
  static char *statepars_all[] =
  { /* particle state parameter names are used for defines */
  #if MCCODE_PROJECT == 1     /* neutron */
  #define NUM_STATE_PARS 17
          (char*) "x", (char*) "y", (char*) "z", (char*) "vx", (char*) "vy", (char*) "vz",
          (char*) "t", (char*) "sx", (char*) "sy", (char*) "sz", (char*) "p", (char*) "mcgravitation", (char*) "mcMagnet", (char*) "allow_backprop", (char*) "_mctmp_a", (char*) "_mctmp_b", (char*) "_mctmp_c"
  #elif MCCODE_PROJECT == 2   /* xray */
  #define NUM_STATE_PARS 15
          "x", "y", "z", "kx", "ky", "kz",
          "phi", "t", "Ex", "Ey","Ez", "p", "_mctmp_a", "_mctmp_b", "_mctmp_c"
  #endif
  };

  cout("/*******************************************************************************");
  coutf("* components %s", "TRACE");
  cout("*******************************************************************************/");
  cout("");

  /* define state parameters for all TRACE*/
  for(i=0; i<NUM_STATE_PARS; i++)
    coutf("#define %s (_particle->%s)", statepars_all[i], statepars_all[i]);

  cout("/* if on GPU, globally nullify sprintf,fprintf,printfs   */");
  cout("/* (Similar defines are available in each comp trace but */");
  cout("/*  those are not enough to handle external libs etc. )  */");
  cout("#ifdef OPENACC");
  cout("#define fprintf(stderr,...) printf(__VA_ARGS__)");
  cout("#define sprintf(string,...) printf(__VA_ARGS__)");
  cout("#define exit(...) noprintf()");
  cout("#define strcmp(a,b) str_comp(a,b)");
  cout("#define strlen(a) str_len(a)");
  cout("#endif");

  /* define SCATTERED, ABSORB and RESTORE macros for all TRACE */
  coutf("#define %s (_particle->%s)", "SCATTERED", "_scattered");
  coutf("#define %s (_particle->%s)", "RESTORE"  , "_restore");
#if MCCODE_PROJECT == 1     /* neutron */
  coutf("#define RESTORE_NEUTRON(_index, ...) _particle->_restore = _index;");
  cout( "#define ABSORB0 do { DEBUG_STATE(); DEBUG_ABSORB(); MAGNET_OFF; ABSORBED++; return; } while(0)");
#elif MCCODE_PROJECT == 2   /* xray */
  coutf("#define RESTORE_XRAY(_index, ...) _particle->_restore = _index;");
  cout( "#define ABSORB0 do { DEBUG_STATE(); DEBUG_ABSORB(); ABSORBED++; return; } while(0)");
#endif
  coutf("#define %s (_particle->%s)", "ABSORBED" , "_absorbed");
  /* define mcget_run_num within trace scope to refer to the particle */
  coutf("#define mcget_run_num() _particle->_uid");
  cout( "#define ABSORB ABSORB0");
} /* def_trace_section */


/*******************************************************************************
* undef_trace_section: #undef TRACE section symbols
*******************************************************************************/
void undef_trace_section(struct instr_def *instr)
{
  List_handle liter;
  int i = 0;
  static char *statepars_all[] =
    { /* particle state parameter names are used for defines */
    #if MCCODE_PROJECT == 1     /* neutron */
    #define NUM_STATE_PARS 17
          (char*) "x", (char*) "y", (char*) "z", (char*) "vx", (char*) "vy", (char*) "vz",
          (char*) "t", (char*) "sx", (char*) "sy", (char*) "sz", (char*) "p", (char*) "mcgravitation", (char*) "mcMagnet", (char*) "allow_backprop", (char*) "_mctmp_a", (char*) "_mctmp_b", (char*) "_mctmp_c"
    #elif MCCODE_PROJECT == 2   /* xray */
    #define NUM_STATE_PARS 15
            "x", "y", "z", "kx", "ky", "kz",
            "phi", "t", "Ex", "Ey","Ez", "p", "_mctmp_a", "_mctmp_b", "_mctmp_c"
    #endif
    };
  List l;

  // undef everything after the "raytrace" function
  for(i = 0; i < NUM_STATE_PARS; i++)
    coutf("#undef %s", statepars_all[i]);

  cout("#ifdef OPENACC");
  cout("#undef strlen");
  cout("#undef strcmp");
  cout("#undef exit");
  cout("#undef printf");
  cout("#undef sprintf");
  cout("#undef fprintf");
  cout("#endif");
  cout("#undef SCATTERED");
  cout("#undef RESTORE"  );
#if MCCODE_PROJECT == 1     /* neutron */
  cout("#undef RESTORE_NEUTRON"  );
  cout("#undef STORE_NEUTRON"  );
#elif MCCODE_PROJECT == 2   /* xray */
  cout("#undef RESTORE_XRAY"  );
  cout("#undef STORE_XRAY"  );
#endif
  cout("#undef ABSORBED" );
  cout("#undef ABSORB");
  cout("#undef ABSORB0");
} /* undef_trace_section */

/*******************************************************************************
* undef_uservars: #define symbols for particle struct USERVARS.
*******************************************************************************/
void def_uservars(struct instr_def *instr)
{
  List_handle uservarsiter = list_iterate(instr->user_vars);
  char *var;
  while((var = (char*) list_next(uservarsiter))) {
    coutf("#define %s (_particle->%s)", var, var);
  }
  list_iterate_end(uservarsiter);
}

/*******************************************************************************
* undef_uservars: #undef symbols for particle struct USERVARS.
*******************************************************************************/
void undef_uservars(struct instr_def *instr)
{
  List_handle uservarsiter = list_iterate(instr->user_vars);
  char *var;
  while((var = (char*) list_next(uservarsiter))) {
    coutf("#undef %s", var);
  }
  list_iterate_end(uservarsiter);
}

/*******************************************************************************
* cogen_trace_functions: Generate the component TRACE functions.
*******************************************************************************/
int cogen_trace_functions(struct instr_def *instr)
{
  List_handle liter;
  struct comp_inst *comp = NULL;
  int warnings = 0;

  /* instrument section comment */
  if (verbose) fprintf(stderr, "Writing components %s\n",
    "TRACE");

  /* generate trace class fcs */
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    warnings += cogen_comp_section_class(comp, instr, (char*) "TRACE", (char*) "trace",
      comp->def->trace_code, &(comp->def->flag_defined_trace));
  }
  list_iterate_end(liter);

  return(warnings);
}

/* *****************************************************************************
* cogen_raytrace: Generate the main raytrace function.
* Extended Grammar:
*   WHEN: the trace section of comp is embraced in a: if (when) { ...  }
*   GROUP: defines a global Group_<name> flag which gets true when one of the
*          comps SCATTER. Rest of GROUP is then skipped.
*          ABSORB _particle are sent to label absorbComp at the end of component
*          and next comp in GROUP is tested.
*   JUMP:  sends _particle to the JumpTrace labels, either with condition
*          or condition is (counter < iterations)
*   SPLIT: loops from comp/group TRACE to END, incrementing mcrun_num
***************************************************************************** */
int cogen_raytrace(struct instr_def *instr)
{
  List_handle liter;
  struct comp_inst *comp = NULL;
  int warnings = 0;
  int i = 0;
  int split_counts = 0;
  static char *statepars_all[] =
    { /* particle state parameter names are used for defines */
    #if MCCODE_PROJECT == 1     /* neutron */
    #define NUM_STATE_PARS 17
          (char*) "x", (char*) "y", (char*) "z", (char*) "vx", (char*) "vy", (char*) "vz",
          (char*) "t", (char*) "sx", (char*) "sy", (char*) "sz", (char*) "p", (char*) "mcgravitation", (char*) "mcMagnet", (char*) "allow_backprop", (char*) "_mctmp_a", (char*) "_mctmp_b", (char*) "_mctmp_c"
    #elif MCCODE_PROJECT == 2   /* xray */
    #define NUM_STATE_PARS 15
            "x", "y", "z", "kx", "ky", "kz",
            "phi", "t", "Ex", "Ey","Ez", "p", "_mctmp_a", "_mctmp_b", "_mctmp_c"
    #endif
    };
  List l;
    
  //
  // write the raytrace function
  //

  cout("/* *****************************************************************************");
  coutf("* instrument '%s' %s", instr->name, "TRACE");
  cout("***************************************************************************** */");
  cout("");
  cout("#ifndef FUNNEL");
  cout("#pragma acc routine");
  coutf("int raytrace(_class_particle* _particle) { /* single event propagation, called by mccode_main for %s:%s */", instr->name, "TRACE");
  cout("");

  cout("  /* init variables and counters for TRACE */");

  // we need this override, since "comp" is not defined in raytrace() - see section-wide define
  cout("  #undef ABSORB0");
  cout("  #undef ABSORB");
  cout("  #define ABSORB0 do { DEBUG_ABSORB(); MAGNET_OFF; ABSORBED++;} while(0)");
  cout("  #define ABSORB ABSORB0");

  /* Debugging (initial state). */
  cout("  DEBUG_ENTER();");
  cout("  DEBUG_STATE();");
  printf("\n-----------------------------------------------------------\n");
  printf("\nGenerating single GPU kernel or single CPU section layout: \n");
  /* intialize JUMP counters */
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    if (list_len(comp->jump) > 0) { // JUMP ITERATE counters
      struct jump_struct *this_jump;
      List_handle liter2;
      liter2 = list_iterate(comp->jump);
      while((this_jump = (jump_struct*) list_next(liter2))) {
        /* create counter for JUMP iteration */
        if (this_jump->iterate)
          coutf("  _particle->_logic.Jump_%s_%s=0;", comp->name, this_jump->target);
        /* check that the target_index is defined, else search for the target comp index */
        if (!this_jump->target_index) {
          List_handle liter3 = list_iterate(instr->complist);
          struct comp_inst *target=NULL;
          while((target = (comp_inst*) list_next(liter3)) != NULL) {
            if (!strcmp(target->name, this_jump->target))
              this_jump->target_index = target->index;
          }
          list_iterate_end(liter3);
        }
        if (!this_jump->target_index) /* JUMP e.g. PREVIOUS/NEXT is relative -> absolute */
          this_jump->target_index += comp->index;
      }
      list_iterate_end(liter2);
    }
  }
  list_iterate_end(liter);

  cout("  _particle->flag_nocoordschange=0; /* Init */");
  cout("  _class_particle _particle_save=*_particle;");
  cout("  /* the main iteration loop for one incoming event */");
  cout("  while (!ABSORBED) { /* iterate event until absorbed */");
  cout("    /* send particle event to component instance, one after the other */");

  /* now we produce the list of statements for each component index, with the attached logic */
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    List_handle liter2;

    /* the SPLIT loop must be set before we enter further component blocks */
    if (comp->split) {
      char *exp=exp_tostring(comp->split);
      printf("-> SPLIT N at component %s\n",comp->name);
      coutf("#ifndef NOSPLIT");
      coutf("    /* start SPLIT at %s */", comp->name);
      coutf("    if (!ABSORBED) {");
      coutf("    _class_particle Split_%s_particle=*_particle;", comp->name); // store incoming particle state at SPLIT
      coutf("    int Split_%s_counter;", comp->name);
      coutf("    int SplitS_%s = %s;", comp->name, exp);
      coutf("    #pragma acc loop independent");
      coutf("    for (" "Split_%s_counter = 0; "
                        "Split_%s_counter< SplitS_%s; "
                        "Split_%s_counter++) {",
      comp->name, comp->name, comp->name, comp->name);
      coutf("      randstate_t randbackup = *_particle->randstate;");
      coutf("      *_particle=Split_%s_particle;", comp->name); // restore particle for SPLIT loop
      coutf("      *_particle->randstate = randbackup;");
      // Experimentally taking out the following line of code following discussions with Milan Klausz:
      // It seems that especially for the _uid=0 particle we get strange repetitions in the rng.
      // coutf("      srandom(_hash(_particle->_uid* %lu *(1+Split_%s_counter)));", comp->index, comp->name);
      coutf("      p /= SplitS_%s > 0 ? SplitS_%s : 1;", comp->name, comp->name);
      coutf("#endif");
      str_free(exp);
    }
    // coordinate transformations (wrt to PREVIOUS)
    coutf("    /* begin component %s=%s() [%i] */", comp->name, comp->def->name, comp->index);
    if (comp->skip_transform == 0) {
      cout( "    if (!_particle->flag_nocoordschange) { // flag activated by JUMP to pass coords change");
      coutf("      if (_%s_var._rotation_is_identity) {", comp->name);
      coutf("        if(!_%s_var._position_relative_is_zero) {", comp->name);
      coutf("          coords_get("
            "coords_add(coords_set(x,y,z), _%s_var._position_relative),"
            "&x, &y, &z);", comp->name);
      cout( "        }");
      cout( "      } else {");
      coutf("          mccoordschange(_%s_var._position_relative, _%s_var._rotation_relative, _particle);", comp->name, comp->name);
      cout( "      }");
      cout( "    }");
    }
    coutf("    if (!ABSORBED && _particle->_index == %i) {", comp->index);
    coutf("      _particle->flag_nocoordschange=0; /* Reset if we came here from a JUMP */");
    if (!comp->group || (comp->group && comp->group->first_comp_index == comp->index)) {
      if (comp->skip_transform == 0) {
        cout( "      _particle_save = *_particle;");
      }
    } else {
      coutf("      // 2nd or higher GROUP member, \"reuse\" coordinate-changed _particle_save from 1st GROUP element.");
      coutf("      mccoordschange(_%s_var._position_relative, _%s_var._rotation_relative, &_particle_save);", comp->name, comp->name);
    }
    if (comp->skip_transform == 0) {
      coutf("      DEBUG_COMP(_%s_var._name);", comp->name);
      cout ("      DEBUG_STATE();");
    }
    /* call the component when there are TRACE and/or EXTEND lines */
    if (list_len(comp->def->trace_code->lines) > 0 || list_len(comp->extend->lines) > 0) {
      // WHEN
      if (comp->when) {
        char *exp=exp_tostring(comp->when);
        coutf("      if ((%s)) // conditional WHEN execution", exp);
        str_free(exp);
      }
      coutf("      class_%s_trace(&_%s_var, _particle);%s",
        comp->def->name,
        comp->name,
        list_len(comp->extend->lines) ? " /* contains EXTEND code */" : "");

      cout( "      if (_particle->_restore)");
      coutf("        particle_restore(_particle, &_particle_save);");
    };

    /* if we have a JUMP, change the index */
    // JUMP
    if(list_len(comp->jump) > 0) {
      struct jump_struct *this_jump;
      List_handle literJ = list_iterate(comp->jump);
      while((this_jump = (jump_struct*) list_next(literJ))) {
        char *exp = exp_tostring(this_jump->condition);
        /* as there will be a neutron->index++, we subtract 1 to the target */
        if (this_jump->iterate) {
          coutf("      if (++_particle->_logic.Jump_%s_%s < %s) { /* test for iteration */",
            comp->name, this_jump->target, exp);
          coutf("        _particle->_index = %i;", this_jump->target_index-1);
          cout( "        _particle->flag_nocoordschange=1; /* pass corrdinate transformations when jumping */");
          coutf("      } else\n" "          _particle->_logic.Jump_%s_%s=0; /* reset Jump loop and go forward */",
            comp->name, this_jump->target);
        } else {
          coutf("      if (%s) {/* conditional JUMP to %s */", exp, this_jump->target);
          coutf("        _particle->_index=%i;", this_jump->target_index-1);
          cout( "        _particle->flag_nocoordschange=1; /* pass corrdinate transformations when jumping */");
          cout( "      }");
        }
      }
      list_iterate_end(literJ);
    }
    /* if we are in a group:
       if (SCATTERED) index = last comp in group
       if (!SCATTERED && index == last_comp in group) ABSORB; */
    // GROUP
    if (comp->group) {
      coutf("      // GROUP %s: from %s [%i] to %s [%i]", comp->group->name,
        comp->group->first_comp, comp->group->first_comp_index,
        comp->group->last_comp,  comp->group->last_comp_index);
      // skip_following_when_scattered (to end of group)
      coutf("      if (SCATTERED) _particle->_index = %i; // when SCATTERED in GROUP: reach exit of GROUP after %s",
        comp->group->last_comp_index, comp->group->last_comp);
      // final_absorb_when_all_not_scattered
      if (comp->index == comp->group->last_comp_index)
        coutf("      else ABSORBED=1;     // not SCATTERED at end of GROUP: removes left events", comp->group->last_comp);
      else // comp_absorb_sends_to_next
        coutf("      else particle_restore(_particle, &_particle_save); // not SCATTERED in GROUP, restore");
    }

    coutf("      _particle->_index++;");
    if (comp->skip_transform == 0) {
      coutf("      if (!ABSORBED) { DEBUG_STATE(); }");
    }
    coutf("    } /* end component %s [%i] */", comp->name, comp->index);

  } /* end while comp list (case) */
  list_iterate_end(liter);

  /* handle ABSORB when no more comp, go to next comp, and RESTORE */

  /* now we close the SPLIT loops, unrolled from last to 1st */
  liter = list_iterate_back(instr->complist);
  while((comp = (comp_inst*) list_previous(liter)) != NULL) {
    if (comp && comp->split) {
      coutf("#ifndef NOSPLIT");
      coutf( "    } /* end SPLIT at %s */", comp->name);
      coutf( "    } /* if (!ABSORBED) relating to SPLIT at %s */", comp->name);
      coutf("#endif");
    }
  }
  list_iterate_end(liter);
  /*   propagate to next component */
  coutf("    if (_particle->_index > %d)", list_len(instr->complist));
  /* if we reach the last component, and nothing happened, ABSORB */
  cout( "      ABSORBED++; /* absorbed when passed all components */");

  cout("  } /* while !ABSORBED */");
  cout("");
  cout("  DEBUG_LEAVE()");
  cout("  particle_restore(_particle, &_particle_save);");
  /* Debugging (final state). */
  cout("  DEBUG_STATE()");

  cout("");
  cout("  return(_particle->_index);");
  coutf("} /* raytrace */");

  // write the "raytrace_all()" code (for loop previously in mccode_main.c).
  cout("");
  coutf("/* loop to generate events and call raytrace() propagate them */");
  coutf("void raytrace_all(unsigned long long ncount, unsigned long seed) {");
  coutf("");

  coutf("  /* CPU-loop */");
  coutf("  unsigned long long loops;");
  coutf("  loops = ceil((double)ncount/gpu_innerloop);");
  coutf("  /* if on GPU, printf has been globally nullified, re-enable here */");
  cout("  #ifdef OPENACC");
  cout("  #undef strlen");
  cout("  #undef strcmp");
  cout("  #undef exit");
  cout("  #undef printf");
  cout("  #undef sprintf");
  cout("  #undef fprintf");
  cout("  #endif");
  coutf("");
  coutf("  #ifdef OPENACC");
  coutf("  if (ncount>gpu_innerloop) {");
  coutf("    printf(\"Defining %%llu CPU loops around GPU kernel and adjusting ncount\\n\",loops);");
  coutf("    mcset_ncount(loops*gpu_innerloop);");
  coutf("  } else {");
  coutf("    #endif");
  coutf("    loops=1;");
  coutf("    gpu_innerloop = ncount;");
  coutf("    #ifdef OPENACC");
  coutf("  }");
  coutf("    #endif");
  coutf("");
  coutf("  for (unsigned long long cloop=0; cloop<loops; cloop++) {");
  coutf("    #ifdef OPENACC");
  coutf("    if (loops>1) fprintf(stdout, \"%%d..\", (int)cloop); fflush(stdout);");
  coutf("    #endif");
  coutf("");
  coutf("    /* if on GPU, re-nullify printf */");
  cout("     #ifdef OPENACC");
  cout("     #undef strlen");
  cout("     #undef strcmp");
  cout("     #undef exit");
  cout("     #undef printf");
  cout("     #undef sprintf");
  cout("     #undef fprintf");
  cout("     #endif");
  coutf("");
  coutf("    #pragma acc parallel loop num_gangs(numgangs) vector_length(vecsize)");
  coutf("    for (unsigned long pidx=0 ; pidx < gpu_innerloop ; pidx++) {");
  coutf("      _class_particle particleN = mcgenstate(); // initial particle");
  coutf("      _class_particle* _particle = &particleN;");
  coutf("      particleN._uid = pidx;");
  coutf("      #ifdef USE_MPI");
  coutf("      particleN._uid += mpi_node_rank * ncount; ");
  coutf("      #endif");
  coutf("");
  coutf("      srandom(_hash((pidx+1)*(seed+1)));");
  coutf("      particle_uservar_init(_particle);");
  coutf("");
  coutf("      raytrace(_particle);");
  coutf("    } /* inner for */");
  coutf("    seed = seed+gpu_innerloop;");
  coutf("  } /* CPU for */");
  coutf("  /* if on GPU, printf has been globally nullified, re-enable here */");
  cout("     #ifdef OPENACC");
  cout("     #undef strlen");
  cout("     #undef strcmp");
  cout("     #undef exit");
  cout("     #undef printf");
  cout("     #undef sprintf");
  cout("     #undef fprintf");
  cout("     #endif");
  coutf("  MPI_MASTER(");
  coutf("  printf(\"*** TRACE end *** \\n\");");
  coutf("  );");
  coutf("} /* raytrace_all */");
  coutf("");
  coutf("#endif //no-FUNNEL");

  return(warnings);
} /* cogen_raytrace */

/*******************************************************************************
* cogen_rt_funnel : Cogen raytrace_funnel function, an alternative, and more
*     parallel, raytrace iteration.
*
*******************************************************************************/
int cogen_rt_funnel(struct instr_def *instr)
{
  List_handle liter;
  struct comp_inst *comp = NULL;
  int warnings = 0;
  int i = 0;
  int split_counts = 0;
  static char *statepars_all[] =
    { /* particle state parameter names are used for defines */
    #if MCCODE_PROJECT == 1     /* neutron */
    #define NUM_STATE_PARS 17
          (char*) "x", (char*) "y", (char*) "z", (char*) "vx", (char*) "vy", (char*) "vz",
          (char*) "t", (char*) "sx", (char*) "sy", (char*) "sz", (char*) "p", (char*) "mcgravitation", (char*) "mcMagnet", (char*) "allow_backprop", (char*) "_mctmp_a", (char*) "_mctmp_b", (char*) "_mctmp_c"
    #elif MCCODE_PROJECT == 2   /* xray */
    #define NUM_STATE_PARS 15
            "x", "y", "z", "kx", "ky", "kz",
            "phi", "t", "Ex", "Ey","Ez", "p", "_mctmp_a", "_mctmp_b", "_mctmp_c"
    #endif
    };
  List l;

  printf("\n-----------------------------------------------------------\n");
  printf("\nGenerating GPU/CPU -DFUNNEL layout:\n");
  
  coutf("");
  coutf("#ifdef FUNNEL");
  coutf("// Alternative raytrace algorithm which iterates all particles through");
  coutf("// one component at the time, can remove absorbs from the next loop and");
  coutf("// switch between cpu/gpu.");

  coutf("void raytrace_all_funnel(unsigned long long ncount, unsigned long seed) {");
  coutf("");
  coutf("  // set up outer (CPU) loop / particle batches");
  coutf("  unsigned long long loops;");
  coutf("");
  coutf("  /* if on GPU, printf has been globally nullified, re-enable here */");
  cout("   #ifdef OPENACC");
  cout("   #undef strlen");
  cout("   #undef strcmp");
  cout("   #undef exit");
  cout("   #undef printf");
  cout("   #undef sprintf");
  cout("   #undef fprintf");
  cout("   #endif");
  /* Check if instrument uses JUMPS */
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    if (list_len(comp->jump) > 0) { // JUMP ITERATE counters
        printf("\nWARNING:\n --> JUMP found at COMPONENT %i, %s \n", comp->index, comp->name);
	printf(" --> JUMPS are not supported in FUNNEL mode and are ignored\n");
	printf(" --> Your instrument may give different output with FUNNEL\n");
        coutf("printf(\"\\nWARNING:\\n --> JUMP found at COMPONENT %i, %s\\n\");", comp->index, comp->name);
	coutf("printf(\" --> JUMPS are not supported in FUNNEL mode and are ignored\\n\");");
	coutf("printf(\" --> Your instrument may give different output with FUNNEL\\n\");");
    }
  }
  coutf("  #ifdef OPENACC");
  coutf("  loops = ceil((double)ncount/gpu_innerloop);");
  coutf("  if (ncount>gpu_innerloop) {");
  coutf("    printf(\"Defining %%llu CPU loops around kernel and adjusting ncount\\n\",loops);");
  coutf("    mcset_ncount(loops*gpu_innerloop);");
  coutf("  } else {");
  coutf("  #endif");
  coutf("    loops=1;");
  coutf("    gpu_innerloop = ncount;");
  coutf("  #ifdef OPENACC");
  coutf("  }");
  coutf("  #endif");
  coutf("");
  coutf("  // create particles struct and pointer arrays (same memory used by all batches)");
  coutf("  _class_particle* particles = malloc(gpu_innerloop*sizeof(_class_particle));");
  coutf("  _class_particle* pbuffer = malloc(gpu_innerloop*sizeof(_class_particle));");
  coutf("  long livebatchsize = gpu_innerloop;");
  coutf("");

  // we need this override, since "comp" is not defined in raytrace() - see section-wide define
  cout("  #undef ABSORB0");
  cout("  #undef ABSORB");
  cout("  #define ABSORB0 do { DEBUG_ABSORB(); MAGNET_OFF; ABSORBED++; } while(0)");
  cout("  #define ABSORB ABSORB0");

  // batches
  coutf("  // outer loop / particle batches");
  coutf("  for (unsigned long long cloop=0; cloop<loops; cloop++) {");
  coutf("    if (loops>1) fprintf(stdout, \"%%d..\", (int)cloop); fflush(stdout);");
  coutf("");

  // init batch
  coutf("    // init particles");
  coutf("    #pragma acc parallel loop present(particles[0:livebatchsize])");
  coutf("    for (unsigned long pidx=0 ; pidx < livebatchsize ; pidx++) {");
  coutf("      // generate particle state, set loop index and seed");
  coutf("      particles[pidx] = mcgenstate();");
  coutf("      _class_particle* _particle = particles + pidx;");
  coutf("      _particle->_uid = pidx;");
  coutf("      #ifdef USE_MPI");
  coutf("      _particle->_uid += mpi_node_rank * ncount; ");
  coutf("      #endif");
  coutf("      srandom(_hash((pidx+1)*(seed+1))); // _particle->state usage built into srandom macro");
  coutf("      particle_uservar_init(_particle);");
  coutf("    }");
  cout( "");

  // iterate batch through the component list
  cout("    // iterate components");
  int cpuonly_last=-1;
  int first=1;
  int do_split=0;
  liter = list_iterate(instr->complist);
  // iterate component list
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    List_handle liter2;
    if (comp->def->flag_noacc) {
      printf("Component %s is NOACC, CPUONLY=%i\n",comp->name,comp->cpuonly);
      printf("-> FUNNEL mode enabled, SPLIT within buffer.\n");
      coutf("        #define JUMP_FUNNEL");
      
    }

    if (!first && ((comp->cpuonly != cpuonly_last) || comp->split)) { // Terminate loop if we are shifting between processing units
      coutf("    }");
      if (comp->split) {
        coutf("");
        coutf("    // SPLIT with available livebatchsize ");
        coutf("    long mult_%s;",comp->name);
        coutf("    livebatchsize = sort_absorb_last(particles, pbuffer, livebatchsize, gpu_innerloop, 1, &mult_%s);",comp->name);
        coutf("    //printf(\"livebatchsize: %cld, split: %cld\\n\",  livebatchsize, mult);", '%', '%');
      }
      if (comp->split) {
        printf("-> SPLIT within buffer at component %s\n",comp->name);
	} else if (comp->cpuonly) {
        printf("-> CPU section from component %s\n",comp->name);
      } else {
        printf("-> GPU kernel from component %s\n",comp->name);
      }
    }

    if (first || (comp->cpuonly != cpuonly_last) || comp->split) {
      coutf("");
      if (comp->cpuonly == 0) {
        coutf("    #pragma acc parallel loop present(particles[0:livebatchsize])");
      } else {
	coutf("    #ifdef MULTICORE");
	coutf("    #pragma acc parallel loop device_type(host)");
	coutf("    #endif");
      }
      coutf("    for (unsigned long pidx=0 ; pidx < livebatchsize ; pidx++) {");
      coutf("      _class_particle* _particle = &particles[pidx];");
      coutf("      _class_particle _particle_save;");
    }
    coutf("");
    coutf("      // %s", comp->name);
    coutf("    if (!ABSORBED && _particle->_index == %i) {", comp->index);

    // coordinate transformations (wrt to PREVIOUS)
    if (comp->skip_transform == 0) {
      coutf("#ifndef MULTICORE");
      coutf("        if (_%s_var._rotation_is_identity)", comp->name);
      coutf("          coords_get("
    	"coords_add(coords_set(x,y,z), _%s_var._position_relative),"
    	"&x, &y, &z);", comp->name);
      cout( "        else");
      coutf("#endif");
      coutf("          mccoordschange(_%s_var._position_relative, _%s_var._rotation_relative, _particle);", comp->name, comp->name);
      cout( "        _particle_save = *_particle;");
    }
    // call the component with TRACE and/or EXTEND lines
    if (list_len(comp->def->trace_code->lines) > 0 || list_len(comp->extend->lines) > 0) {
      // WHEN
      if (comp->when) {
        char *exp=exp_tostring(comp->when);
        coutf("        if ((%s)) // conditional WHEN", exp);
        str_free(exp);
      }
      // TRACE
      coutf("        class_%s_trace(&_%s_var, _particle);%s",
      comp->def->name,
      comp->name,
      list_len(comp->extend->lines) ? " /* contains EXTEND code */" : "");

      cout( "        if (_particle->_restore)");
      coutf("        particle_restore(_particle, &_particle_save);");
    };
    // GROUP
    if (comp->group) {
      if (comp->group->first_comp_index == comp->group->last_comp_index) {
	fprintf(stderr,"\n!!! WARNING: GROUP %s seems to include only one COMPONENT: \n!!!   --> %s <-- \n!!! This may lead to unphysical simulation behaviour!\n",comp->group->name,comp->name);
      }
      coutf("      // GROUP %s: from %s [%i] to %s [%i]", comp->group->name,
        comp->group->first_comp, comp->group->first_comp_index,
        comp->group->last_comp,  comp->group->last_comp_index);
      // skip_following_when_scattered (to end of group)
      coutf("      if (SCATTERED) _particle->_index = %i; // when SCATTERED in GROUP: reach exit of GROUP after %s",
        comp->group->last_comp_index, comp->group->last_comp);
      // final_absorb_when_all_not_scattered
      if (comp->index == comp->group->last_comp_index)
        coutf("      else ABSORBED=1;     // not SCATTERED at end of GROUP: removes left events", comp->group->last_comp);
      else // comp_absorb_sends_to_next
        coutf("      else ABSORBED=0; // not SCATTERED within GROUP: always tries next");
    }
    coutf("        _particle->_index++;");
    coutf("      }");
    first=0;
    cpuonly_last = comp->cpuonly;
  } /* end while comp list (case) */
  coutf("");
  coutf("    }");
  cout( "");
  list_iterate_end(liter);

  coutf("    // jump to next viable seed");
  coutf("    seed = seed + gpu_innerloop;");
  coutf("  } // outer loop / particle batches");
  cout( "");
  coutf("  free(particles);");
  coutf("  free(pbuffer);");
  cout( "");
  coutf("  printf(\"\\n\");");

  coutf("} /* raytrace_all_funnel */");
  coutf("#endif // FUNNEL");
  coutf("");
  printf("\n-----------------------------------------------------------\n");

  return 0;
} /* cogen_rt_funnel */

/*******************************************************************************
* Output code for the mcstas/mcxtrace runtime system. Default is to copy the runtime
* code into the generated executable, to minimize problems with finding the
* right files during compilation and linking, but this may be changed using
* the --no-runtime compiler switch.
*******************************************************************************/
static void
cogen_header(struct instr_def *instr, char *output_name)
{
  char *sysdir_orig;
  char *sysdir_new;
  char  pathsep[3];
  int   i,j=0;
  time_t t;
  char  date[128];
  long  index=0;

  time(&t);
  strcpy(date, ctime(&t));
  if (strlen(date)) date[strlen(date)-1] = '\0';

  /* the file header */
  cout("/* Automatically generated file. Do not edit. ");
  cout(" * Format:     ANSI C source code");
#if MCCODE_PROJECT == 1     /* neutron */
  cout(" * Creator:    McStas <http://www.mcstas.org>");
#elif MCCODE_PROJECT == 2   /* xray */
  cout(" * Creator:    McXtrace <http://www.mcxtrace.org>");
#endif
  coutf(" * Instrument: %s (%s)", instr->source, instr->name);
  coutf(" * Date:       %s", date);
  coutf(" * File:       %s", output_name);
  coutf(" * CFLAGS=%s", instr->dependency);
  cout(" */");
  cout("");

  /* Enable _POSIX_SOURCE consistently (todo: revisit the ifndef WIN32 protection) */
  coutf("#ifndef WIN32");
  coutf("#  ifndef OPENACC");
  coutf("#    define _GNU_SOURCE");
  coutf("#  endif");
  coutf("#  define _POSIX_C_SOURCE 200809L");
  coutf("#endif");

  /* In case of cl.exe on Windows, supppress warnings about #pragma acc */
  cout("/* In case of cl.exe on Windows, supppress warnings about #pragma acc */");
  coutf("#ifdef _MSC_EXTENSIONS");
  coutf("#pragma warning(disable: 4068)");
  coutf("#endif");
  cout("");

  coutf("#define MCCODE_STRING \"%s\"", MCCODE_STRING);
  coutf("#define FLAVOR        \"%s\"", FLAVOR);
  coutf("#define FLAVOR_UPPER  \"%s\"", FLAVOR_UPPER);
  cout("");
  /* handles Windows '\' chararcters for embedding sys_dir into source code */
  if (MC_PATHSEP_C != '\\') strcpy(pathsep, MC_PATHSEP_S);
  else strcpy(pathsep, "\\\\");

  sysdir_orig = get_sys_dir();
  sysdir_new  = (char *)mem(2*strlen(sysdir_orig));
  for (i=0; i < strlen(sysdir_orig); i++)
  {
    if (sysdir_orig[i] == '\\')
    { sysdir_new[j] = '\\'; j++; sysdir_new[j] = '\\'; }
    else sysdir_new[j] = sysdir_orig[i];
    j++;
  }
  sysdir_new[j] = '\0';
  if(instr->use_default_main)
    cout("#define MC_USE_DEFAULT_MAIN");
  if(instr->enable_trace)
    cout("#define MC_TRACE_ENABLED");
  if(instr->portable)
    cout("#define MC_PORTABLE");

  /* Basic includes */
  cout("");
  cout("#include <string.h>");
  cout("#include <inttypes.h>");
  cout("");

  /* McCode-specific typedefs */
  cout("typedef double MCNUM;");
  cout("typedef struct {MCNUM x, y, z;} Coords;");
  cout("typedef MCNUM Rotation[3][3];");
  cout("#define MCCODE_BASE_TYPES");
  cout("");
  cout("/* available random number generators */");
  cout("#define _RNG_ALG_MT         1");
  cout("#define _RNG_ALG_KISS       2");
  cout("/* selection of random number generator */");
  cout("#ifndef RNG_ALG");
  cout("#  define RNG_ALG  _RNG_ALG_KISS");
  cout("#endif");
  cout("#if RNG_ALG == _RNG_ALG_MT // MT ");
  cout("#define randstate_t uint32_t");
  cout("#elif RNG_ALG == _RNG_ALG_KISS  // KISS");
  cout("#define randstate_t uint64_t");
  cout("#endif");
  cout("");

  /* the max number of user variables*/
  cout("#ifndef MC_NUSERVAR");
  cout("#define MC_NUSERVAR 10");
  cout("#endif");
  cout("");
  List_handle liter,liter2;
  struct comp_inst *comp;        /* Component instance. */

  /* Output a particle logic JUMP struct */
  cout("/* Particle JUMP control logic */");
  cout("struct particle_logic_struct {");
  cout("int dummy;");
  liter = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter)) != NULL) {
    if (list_len(comp->jump) > 0) { // JUMP ITERATE counters
      struct jump_struct *this_jump;
      List_handle liter2;
      liter2 = list_iterate(comp->jump);
      while((this_jump = (jump_struct*) list_next(liter2))) {
	/* create counter for JUMP iteration */
	if (this_jump->iterate)
	  coutf("  long Jump_%s_%s; /* the JUMP connection <from>_<to> */", comp->name, this_jump->target);
      }
      list_iterate_end(liter2);
    }
  }
  cout("};");
  list_iterate_end(liter);
  cout("");
  
  /* generate particle struct */
  cout("struct _struct_particle {");
  cout("  double x,y,z; /* position [m] */");
#if MCCODE_PROJECT == 1   /* neutron */
  cout("  double vx,vy,vz; /* velocity [m/s] */");
  cout("  double sx,sy,sz; /* spin [0-1] */");
  cout("  int mcgravitation; /* gravity-state */");
  cout("  void *mcMagnet;    /* precession-state */");
  cout("  int allow_backprop; /* allow backprop */");
#elif MCCODE_PROJECT == 2 /* xray */
  cout("  double kx,ky,kz; /* wave-vector */");
  cout("  double phi, Ex,Ey,Ez; /* phase and electrical field */");
#endif
  cout("  /* Generic Temporaries: */");
  cout("  /* May be used internally by components e.g. for special */");
  cout("  /* return-values from functions used in trace, thusreturned via */");
  cout("  /* particle struct. (Example: Wolter Conics from McStas, silicon slabs.) */");
  cout("  double _mctmp_a; /* temp a */");
  cout("  double _mctmp_b; /* temp b */");
  cout("  double _mctmp_c; /* temp c */");
  //cout("  randstate_t randstate[RANDSTATE_LEN]");
  cout("  randstate_t randstate[7];"); // for the KISS generator
  cout("  double t, p;     /* time, event weight */");
  cout("  long long _uid;  /* Unique event ID */");
  cout("  long _index;     /* component index where to send this event */");
  /* these are needed for SCATTERED, ABSORB and RESTORE macros */
  cout("  long _absorbed;  /* flag set to TRUE when this event is to be removed/ignored */");
  cout("  long _scattered; /* flag set to TRUE when this event has interacted with the last component instance */");
  cout("  long _restore;   /* set to true if neutron event must be restored */");
  cout("  long flag_nocoordschange;   /* set to true if particle is jumping */");
  /* Include the struct defined earlier holding information on JUMP logic*/
  cout("  struct particle_logic_struct _logic;");
  /* Append variables from instr USERVARS block to particle struct (user vars,
  *  always double). Also store these strings in in the appropriate instrument
  *  list for later def/undef as state variables (see cogen_raytrace). */

  instr->user_vars = list_create();
  instr->user_vars_types = list_create();
  int uvlist = get_codeblock_vars(instr->vars, instr->user_vars, instr->user_vars_types, (char*) "USERVARS", (char*) "EXTEND");
  // Look in comp definitions
  List_handle liter3;
  liter3 = list_iterate(instr->complist);
  while((comp = (comp_inst*) list_next(liter3)) != NULL) {
    List cvars;
    List ctypes;
    cvars = list_create();
    ctypes = list_create();
    if (get_codeblock_vars(comp->def->uservar_code, cvars, ctypes, (char*) "USERVARS", (char*) "EXTEND")) {
      List_handle cliter;
      List_handle cliter2;
      cliter = list_iterate(cvars);
      cliter2 = list_iterate(ctypes);
      char *cvar;
      char *ctpe;
      while(cvar = (char*) list_next(cliter)) {
        ctpe = (char*) list_next(cliter2);
        char *Numberedvar = (char*) malloc(256*sizeof(char));
	/* We need to attach comp index to cvar */
	sprintf(Numberedvar,"%s_%d",cvar,comp->index);
	list_add(instr->user_vars, Numberedvar);
	list_add(instr->user_vars_types, ctpe);
	printf("\n--> Added COMPONENT %s USERVAR %s with type %s\n",comp->name,Numberedvar,ctpe);
    }
      list_iterate_end(cliter);
      list_iterate_end(cliter2);
    }
  }
  list_iterate_end(liter3);
  if (list_len(instr->user_vars) > 0) {
    cout("  // user variables and comp-injections:");
    List_handle liter;
    List_handle liter2;
    liter = list_iterate(instr->user_vars);
    liter2 = list_iterate(instr->user_vars_types);
    char *var;
    char *tpe;
    while((var = (char*) list_next(liter))) {
      tpe = (char*) list_next(liter2);
      coutf("  %s %s;", tpe, var);
    }
    list_iterate_end(liter);
    list_iterate_end(liter2);
  }
  cout("};");
  cout("typedef struct _struct_particle _class_particle;");
  cout("");
  cout("_class_particle _particle_global_randnbuse_var;");
  cout("_class_particle* _particle = &_particle_global_randnbuse_var;");
  cout("");

  /* Below lines relating to mcgenstate / setstate are in principle McStas-centric, we ought to generate this function based on "project" */
  cout("#pragma acc routine");
  cout("_class_particle mcgenstate(void);");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("#pragma acc routine");
  cout("_class_particle mcsetstate(double x, double y, double z, double vx, double vy, double vz,");
  cout("			   double t, double sx, double sy, double sz, double p, int mcgravitation, void *mcMagnet, int mcallowbackprop);");
  cout("#pragma acc routine");
  cout("_class_particle mcgetstate(_class_particle mcneutron, double *x, double *y, double *z,");
  cout("                           double *vx, double *vy, double *vz, double *t,");
  cout("                           double *sx, double *sy, double *sz, double *p);");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("#pragma acc routine");
  cout("_class_particle mcsetstate(double x, double y, double z, double kx, double ky, double kz,");
  cout("			   double phi, double t, double Ex, double Ey, double Ez, double p, int mcgravitation, void *mcMagnet, int mcallowbackprop);");
  cout("#pragma acc routine");
  cout("_class_particle mcgetstate(_class_particle mcphoton, double *x, double *y, double *z, double *kx, double *ky, double *kz,");
  cout("			   double *phi, double *t, double *Ex, double *Ey, double *Ez, double *p);");
#endif
  cout("");
  cout("extern int mcgravitation;      /* flag to enable gravitation */");
  cout("#pragma acc declare create ( mcgravitation )");
  cout("int mcallowbackprop;        ");
  cout("#pragma acc declare create ( mcallowbackprop )");

  cout("");
  cout("_class_particle mcgenstate(void) {");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("  _class_particle particle = mcsetstate(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, mcgravitation, NULL, mcallowbackprop);");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("  _class_particle particle = mcsetstate(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, mcgravitation, NULL, mcallowbackprop);");
#endif
  cout("  return(particle);");
  cout("}");

  /*generate uservar return functions*/
  cout("/*Generated user variable handlers:*/");
  cout("");

  liter = list_iterate(instr->user_vars);
  cout("#pragma acc routine");
  cout("double particle_getvar(_class_particle *p, char *name, int *suc);");
  cout("");
  cout("#ifdef OPENACC");
  cout("#pragma acc routine");
  cout("int str_comp(char *str1, char *str2);");
  cout("#endif");
  cout("");
  cout("double particle_getvar(_class_particle *p, char *name, int *suc){");
  cout("#ifndef OPENACC");
  cout("#define str_comp strcmp");
  cout("#endif");
  cout("  int s=1;");
  cout("  double rval=0;");
  char *var, *tpe;
  cout("  if(!str_comp(\"x\",name)){rval=p->x;s=0;}");
  cout("  if(!str_comp(\"y\",name)){rval=p->y;s=0;}");
  cout("  if(!str_comp(\"z\",name)){rval=p->z;s=0;}");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("  if(!str_comp(\"vx\",name)){rval=p->vx;s=0;}");
  cout("  if(!str_comp(\"vy\",name)){rval=p->vy;s=0;}");
  cout("  if(!str_comp(\"vz\",name)){rval=p->vz;s=0;}");
  cout("  if(!str_comp(\"sx\",name)){rval=p->sx;s=0;}");
  cout("  if(!str_comp(\"sy\",name)){rval=p->sy;s=0;}");
  cout("  if(!str_comp(\"sz\",name)){rval=p->sz;s=0;}");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("  if(!str_comp(\"phi\",name)){rval=p->phi;s=0;}");
  cout("  if(!str_comp(\"kx\",name)){rval=p->kx;s=0;}");
  cout("  if(!str_comp(\"ky\",name)){rval=p->ky;s=0;}");
  cout("  if(!str_comp(\"kz\",name)){rval=p->kz;s=0;}");
  cout("  if(!str_comp(\"Ex\",name)){rval=p->Ex;s=0;}");
  cout("  if(!str_comp(\"Ey\",name)){rval=p->Ey;s=0;}");
  cout("  if(!str_comp(\"Ez\",name)){rval=p->Ez;s=0;}");
#endif
  cout("  if(!str_comp(\"t\",name)){rval=p->t;s=0;}");
  cout("  if(!str_comp(\"p\",name)){rval=p->p;s=0;}");
  cout("  if(!str_comp(\"_mctmp_a\",name)){rval=p->_mctmp_a;s=0;}");
  cout("  if(!str_comp(\"_mctmp_b\",name)){rval=p->_mctmp_b;s=0;}");
  cout("  if(!str_comp(\"_mctmp_c\",name)){rval=p->_mctmp_c;s=0;}");
  while((var = (char*) list_next(liter))) {
    coutf("  if(!str_comp(\"%s\",name)){rval=*( (double *)(&(p->%s)) );s=0;}",var,var);
  }
  list_iterate_end(liter);
  cout("  if (suc!=0x0) {*suc=s;}");
  cout("  return rval;");
  cout("}");
  cout("");

  liter = list_iterate(instr->user_vars);
  cout("#pragma acc routine");
  cout("void* particle_getvar_void(_class_particle *p, char *name, int *suc);");
  cout("");
  cout("#ifdef OPENACC");
  cout("#pragma acc routine");
  cout("int str_comp(char *str1, char *str2);");
  cout("#endif");
  cout("");
  cout("void* particle_getvar_void(_class_particle *p, char *name, int *suc){");
  cout("#ifndef OPENACC");
  cout("#define str_comp strcmp");
  cout("#endif");
  cout("  int s=1;");
  cout("  void* rval=0;");
  cout("  if(!str_comp(\"x\",name)) {rval=(void*)&(p->x); s=0;}");
  cout("  if(!str_comp(\"y\",name)) {rval=(void*)&(p->y); s=0;}");
  cout("  if(!str_comp(\"z\",name)) {rval=(void*)&(p->z); s=0;}");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("  if(!str_comp(\"vx\",name)){rval=(void*)&(p->vx);s=0;}");
  cout("  if(!str_comp(\"vy\",name)){rval=(void*)&(p->vy);s=0;}");
  cout("  if(!str_comp(\"vz\",name)){rval=(void*)&(p->vz);s=0;}");
  cout("  if(!str_comp(\"sx\",name)){rval=(void*)&(p->sx);s=0;}");
  cout("  if(!str_comp(\"sy\",name)){rval=(void*)&(p->sy);s=0;}");
  cout("  if(!str_comp(\"sz\",name)){rval=(void*)&(p->sz);s=0;}");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("  if(!str_comp(\"kx\",name)){rval=(void*)&(p->kx);s=0;}");
  cout("  if(!str_comp(\"ky\",name)){rval=(void*)&(p->ky);s=0;}");
  cout("  if(!str_comp(\"kz\",name)){rval=(void*)&(p->kz);s=0;}");
  cout("  if(!str_comp(\"Ex\",name)){rval=(void*)&(p->Ex);s=0;}");
  cout("  if(!str_comp(\"Ey\",name)){rval=(void*)&(p->Ey);s=0;}");
  cout("  if(!str_comp(\"Ez\",name)){rval=(void*)&(p->Ez);s=0;}");
  cout("  if(!str_comp(\"phi\",name)){rval=(void*)&(p->phi);s=0;}");
#endif
  cout("  if(!str_comp(\"t\",name)) {rval=(void*)&(p->t); s=0;}");
  cout("  if(!str_comp(\"p\",name)) {rval=(void*)&(p->p); s=0;}");
//  char *var, *tpe;
  while((var = (char*) list_next(liter))) {
    coutf("  if(!str_comp(\"%s\",name)){rval=(void*)&(p->%s);s=0;}",var,var);
  }
  list_iterate_end(liter);
  cout("  if (suc!=0x0) {*suc=s;}");
  cout("  return rval;");
  cout("}");
  cout("");
  
  liter = list_iterate(instr->user_vars);
  liter2 = list_iterate(instr->user_vars_types);
  cout("#pragma acc routine");
  cout("int particle_setvar_void(_class_particle *, char *, void*);");
  cout("");
  cout("int particle_setvar_void(_class_particle *p, char *name, void* value){");
  cout("#ifndef OPENACC");
  cout("#define str_comp strcmp");
  cout("#endif");
  cout("  int rval=1;");
  cout("  if(!str_comp(\"x\",name)) {memcpy(&(p->x),  value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"y\",name)) {memcpy(&(p->y),  value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"z\",name)) {memcpy(&(p->z),  value, sizeof(double)); rval=0;}");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("  if(!str_comp(\"vx\",name)){memcpy(&(p->vx), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"vy\",name)){memcpy(&(p->vy), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"vz\",name)){memcpy(&(p->vz), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"sx\",name)){memcpy(&(p->sx), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"sy\",name)){memcpy(&(p->sy), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"sz\",name)){memcpy(&(p->sz), value, sizeof(double)); rval=0;}");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("  if(!str_comp(\"kx\",name)){memcpy(&(p->kx), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"ky\",name)){memcpy(&(p->ky), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"kz\",name)){memcpy(&(p->kz), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"Ex\",name)){memcpy(&(p->Ex), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"Ey\",name)){memcpy(&(p->Ey), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"Ez\",name)){memcpy(&(p->Ez), value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"phi\",name)){memcpy(&(p->phi), value, sizeof(double)); rval=0;}");
#endif
  cout("  if(!str_comp(\"p\",name)) {memcpy(&(p->p),  value, sizeof(double)); rval=0;}");
  cout("  if(!str_comp(\"t\",name)) {memcpy(&(p->t),  value, sizeof(double)); rval=0;}");
  char *invar;
  while((invar = (char*) list_next(liter))) {
    tpe = (char*) list_next(liter2);
    if (!(strstr(tpe, "[") || strstr(tpe, "]") || strstr(tpe, "*"))){
      // not an array -- we should be able to use memcopy freely
      coutf("  if(!str_comp(\"%s\",name)){memcpy(&(p->%s), value, sizeof(%s)); rval=0;}", invar, invar, tpe);
    }
  }
  list_iterate_end(liter);
  list_iterate_end(liter2);
  cout("  return rval;");
  cout("}");
  cout("");

  liter = list_iterate(instr->user_vars);
  liter2 = list_iterate(instr->user_vars_types);
  cout("#pragma acc routine");
  cout("int particle_setvar_void_array(_class_particle *, char *, void*, int);");
  cout("");
  cout("int particle_setvar_void_array(_class_particle *p, char *name, void* value, int elements){");
  cout("#ifndef OPENACC");
  cout("#define str_comp strcmp");
  cout("#endif");
  cout("  int rval=1;");
 // char *invar;
  while((invar = (char*) list_next(liter))) {
    tpe = (char*) list_next(liter2);
    if ((strstr(tpe, "[") || strstr(tpe, "]") || strstr(tpe, "*"))){
      // an array -- we need to know how many elements we're copying
      coutf("  if(!str_comp(\"%s\",name)){memcpy(&(p->%s), value, elements * sizeof(%s)); rval=0;}", invar, invar, tpe);
    }
  }
  list_iterate_end(liter);
  list_iterate_end(liter2);
  cout("  return rval;");
  cout("}");
  cout("");
  

  /* Function to handle a particle restore of physical particle params */
  cout("#pragma acc routine");
  cout("void particle_restore(_class_particle *p, _class_particle *p0);");
  cout("");
  cout("void particle_restore(_class_particle *p, _class_particle *p0) {");
  cout("  p->x  = p0->x;  p->y  = p0->y;  p->z  = p0->z;");
#if MCCODE_PROJECT == 1     /* neutron */
  cout("  p->vx = p0->vx; p->vy = p0->vy; p->vz = p0->vz;");
  cout("  p->sx = p0->sx; p->sy = p0->sy; p->sz = p0->sz;");
  cout("  p->t = p0->t;  p->p  = p0->p;");
#elif MCCODE_PROJECT == 2   /* xray */
  cout("  p->kx = p0->kx; p->ky = p0->ky; p->kz = p0->kz;");
  cout("  p->Ex = p0->Ex; p->Ey = p0->Ey; p->Ez = p0->Ez;");
  cout("  p->t = p0->t;   p->p  = p0->p;  p->phi  = p0->phi;");
#endif
  cout("  p->_absorbed=0; p->_restore=0;");
  cout("}");
  cout("");

  liter = list_iterate(instr->user_vars);
  cout("#pragma acc routine");
  cout("double particle_getuservar_byid(_class_particle *p, int id, int *suc){");
  cout("  int s=1;");
  cout("  double rval=0;");
  cout("  switch(id){");
  int jvar=0;
  while((var = (char*) list_next(liter))) {
    coutf("  case %d: { rval=*( (double *)(&(p->%s)) );s=0;break;}",jvar++,var);
  }
  cout("  }");
  cout("  if (suc!=0x0) {*suc=s;}");
  cout("  return rval;");
  cout("}");
  cout("");

  liter = list_iterate(instr->user_vars);
  liter2 = list_iterate(instr->user_vars_types);
  cout("#pragma acc routine");
  cout("void particle_uservar_init(_class_particle *p){");
  while((var = (char*) list_next(liter))) {
    tpe = (char*) list_next(liter2);
    if (strstr(tpe, "double") || strstr(tpe, "MCNUM") || strstr(tpe, "int")){
      if (!strstr(tpe, "[") && !strstr(tpe, "]") && !strstr(tpe, "*")) {
	coutf("  p->%s=0;",var);
      } else {
	printf("\nWARNING:\n   --> USERVAR %s is of type %s (array/pointer?)\n", var,tpe);
	printf("   --> and may need specific per-particle\n");
	printf("   --> initialisation through an EXTEND block!\n");
      }
    } else {
      printf("\nWARNING:\n   --> USERVAR %s is of type %s and may need specific\n", var,tpe);
      printf("   --> per-particle initialisation through an\n");
      printf("   --> EXTEND block!\n");
    }
  }
  cout("}");
  cout("");

  /* embed runtime files */
  if(instr->include_runtime)
  {
    cout("#define MC_EMBEDDED_RUNTIME"); /* Some stuff will be static. */
    embed_file((char*) "mccode-r.h");
#if MCCODE_PROJECT == 1     /* neutron */
    embed_file((char*) "mcstas-r.h");
#elif MCCODE_PROJECT == 2   /* xray */
    embed_file("mcxtrace-r.h");
#endif
    /* NeXus support, only active with -DUSE_NEXUS */
    if (verbose) fprintf(stderr, "Compile            '%s -DUSE_NEXUS -lNeXus' to enable NeXus support\n", output_name);
    embed_file((char*) "mccode-r.c");
#if MCCODE_PROJECT == 1     /* neutron */
    embed_file((char*) "mcstas-r.c");
#elif MCCODE_PROJECT == 2   /* xray */
    embed_file("mcxtrace-r.c");
#endif
  }
  else
  {
    coutf("#include \"%s%sshare%smccode-r.h\"",  sysdir_new, pathsep, pathsep);
    fprintf(stderr,"Dependency: %s.o\n", "mccode-r");
#if MCCODE_PROJECT == 1     /* neutron */
    coutf("#include \"%s%sshare%smcstas-r.h\"",  sysdir_new, pathsep, pathsep);
    fprintf(stderr,"Dependency: %s.o\n", "mcstas-r");
#elif MCCODE_PROJECT == 2   /* xray */
    coutf("#include \"%s%sshare%smcxtrace-r.h\"",  sysdir_new, pathsep, pathsep);
    fprintf(stderr,"Dependency: %s.o\n", "mcxtrace-r");
#endif

    fprintf(stderr,"Dependency: %s.o\n", "mcstas-r");
    fprintf(stderr,"Dependency: '-DUSE_NEXUS -lNeXus' to enable NeXus support\n");
    fprintf(stderr,"To build instrument '%s', compile and link with these libraries (in %s%sshare)\n",
      instrument_definition->quoted_source, sysdir_new, pathsep);
  }
  cout("");
  cout("/* *****************************************************************************");
  coutf("* Start of instrument '%s' generated code", instr->name);
  cout("***************************************************************************** */");
  cout("");
  coutf("#ifdef MC_TRACE_ENABLED");
  coutf("int traceenabled = 1;");
  coutf("#else");
  coutf("int traceenabled = 0;");
  coutf("#endif");

  coutf("#define " MCCODE_LIBENV " \"%s%s\"", sysdir_new,pathsep);

  coutf("int   defaultmain         = %d;", instr->use_default_main);
  coutf("char  instrument_name[]   = \"%s\";", instr->name);
  coutf("char  instrument_source[] = \"%s\";", instr->quoted_source);
  coutf("char *instrument_exe      = NULL; /* will be set to argv[0] in main */");

  index=0;
  /* embed instrument file if requested with --source option */
  if (embed_instrument_file) {

    FILE *fid=fopen(instr->source, "rb");
    if (fid) {
      char *content=NULL;
      char *content_quoted=NULL;
      fseek(fid, 0, SEEK_END);
      index = ftell(fid);
      fseek(fid, 0, SEEK_SET);
      content = (char*) malloc(index + 1);
      /* read full file content */
      fread(content, index, 1, fid);
      fclose(fid);
      content[index] = '\0';
      content_quoted = str_quote(content);
      coutf("char  instrument_code[]   = \"%s\";\n", content_quoted);
      str_free(content_quoted);
      str_free(content);
    }
  }
  /* if option is not set, or source file can not be accessed */
  if (!index)
    coutf("char  instrument_code[]   = "
    "\"Instrument %s source code %s is not embedded in this executable.\\n"
    "  Use --source option when running " MCCODE_NAME ".\\n\";", instr->name, instr->quoted_source);

  cout("");
  if(instr->use_default_main)
    cout("int main(int argc, char *argv[]){return mccode_main(argc, argv);}");

} /* cogen_header */


/*******************************************************************************
* var_is_in_codeblock: Checks if variabe of name var and type tpe is in code block
*   code. Filters out comment sections.
*
* code:     code block containing var, or not
* varname:  variable declaration id
*
* returns: char 0 if not, 1 otherwise
*******************************************************************************/
char varname_is_in_codeblock(struct code_block* code, char* varname) {
  char flag_is_in_codeblock = 0;

  if(list_len(code->lines) > 0) {
    List_handle liter = list_iterate(code->lines);
    char *line;                /* Single code line. */
    char *comment_start= NULL; /* this is the C style comment start */
    char *comment_end  = NULL; /* this is the C style comment end */
    char *comment_toend= NULL; /* this is the C++ style comment start (to end of line) */

    // iterate declare code
    while((line = (char*) list_next(liter)))
    {
      char *subline = line;
      char *p       = NULL;

      /* search for comments */
      if (comment_start)       /* continuation from a previous line */
        comment_start = line;
      else if (!comment_start) /* start of a new comment ? */
        comment_start = strstr(line, "/*");
      comment_end   = strstr(line, "*/");
      if (comment_end && comment_end+2 < line+strlen(line))
        comment_end += 2;
      comment_toend = strstr(line, "//");

      if (comment_start && comment_end) { /* a full C-style comment on a line (or continuation to end) */
        for (p=comment_start; p<comment_end; p++) *p=' ';
        comment_start = comment_end = NULL; /* reset locations for next comment */
      }
      if (comment_start && !comment_end) { /* the start of a multiline C-style comment (or continuation) */
        for (p=comment_start; p<line+strlen(line)-1; p++) *p=' ';
      }
      if (comment_toend) {
        for (p=comment_toend; p<line+strlen(line)-1; p++) *p=' ';
      }

      while ((p=strstr(subline, varname))) {
        /* the parameter name appears in code block */
        int char_before=0;
        int char_after=0;
        if (p > line)
          char_before=*(p-1); /* char before the match */
        if (p+strlen(varname) <= line+strlen(line))
          char_after=*(p+strlen(varname)); /* char after the match */
        /* check if appears as a single word */
        if ( (!char_before || (char_before && strchr(" ,\t*",  char_before))) &&
             (!char_after  || (char_after  && strchr(" ,\t;[=", char_after ))) )
          flag_is_in_codeblock++;
        else subline = p+strlen(varname);
        if (flag_is_in_codeblock) break;
        if (p+strlen(varname) >= line+strlen(line)) break;
      } /* while in declare code */
      if (flag_is_in_codeblock) break;

    } /* while line */
    list_iterate_end(liter);
  }

  return flag_is_in_codeblock;
} // varname_is_in_codeblock

/*******************************************************************************
* get_codeblock_vars_allcustom: See get_codeblock_vars.
*   Fills out a single list of comp_iformal (not instr_iformal) and applies the
*   found types as the custom value, and that instr_formal_types is also
*   "custom".
*
* custom_vars: a list which gains comp_iformal entries
*******************************************************************************/
int get_codeblock_vars_allcustom(struct code_block *code, List custom_vars,
  char* block_name, char* movetoblock_name) {

  List vars;
  List types;
  vars = list_create();
  types = list_create();
  int retval;
  retval = get_codeblock_vars(code, vars, types, block_name, movetoblock_name);

  List_handle liter;
  List_handle liter2;
  liter = list_iterate(vars);
  liter2 = list_iterate(types);
  char *var;
  char *tpe;
  while((var = (char*) list_next(liter))) {
    tpe = (char*) list_next(liter2);

    struct comp_iformal* cvar;
    cvar = (comp_iformal*) malloc(sizeof(struct comp_iformal));
    cvar->type = instr_type_custom;
    cvar->type_custom = tpe;
    cvar->id = var;
    cvar->isoptional = 0;
    list_add(custom_vars, cvar);
  }
  list_iterate_end(liter);
  list_iterate_end(liter2);

  // NOTE: free lists vars and types with an empty "freer" to preserve element strings

  return retval;
}

/*******************************************************************************
* get_codeblock_vars: Extracts variable declaration statements from a code block
*   and adds their varnames and types to lists.
*
* code: code block containing variable declaration statements
* vars: variable name strings are added to this list
* types: the string(s) preceding the variable name in the user decl. are added
*
* returns: the number of vars added
*******************************************************************************/
int get_codeblock_vars(struct code_block *code, List vars, List types,
  char* block_name, char* movetoblock_name) {

  if(list_len(code->lines) <= 0)
    return(0);

  List_handle myiter;
  myiter = list_iterate(code->lines);

  char *l;
  int idx = -1;
  int pos = -1;
  int len = -1;
  int ans = 0;

  while((l = (char*) list_next(myiter))) {
    do {
      // line must match this format
      pos = re_match("\\w[\\s\\w\\*]+\\s+\\**\\w+\\[?\\w*\\]?\\[?\\w*\\]?;", l); // match general var decl pattern

      if (pos <= -1) {
        // skip
      }
      else {
        char* tpe;
        char* vn;

        // extract the type
        len = re_match("\\w+\\[?\\w*\\]?\\[?\\w*\\]?;", l+pos); // end of type string
        tpe = (char*) malloc((len + 1) * sizeof(char)); // new location
        *(tpe+len) = '\0'; // null terminate
        if (len > -1) {
          strncpy(tpe, l+pos, len);
        }

        // extract the varname
        pos = re_match("\\w+\\[?\\w*\\]?\\[?\\w*\\]?;", l); // match start of varname
        if (pos > -1) {
          len = re_match(";", l+pos); // match end of varname

          if (len > -1) {
            vn = (char*) malloc((len + 1) * sizeof(char)); // new location
            *(vn+len) = '\0'; // null terminate

            strncpy(vn, l+pos, len);
            l = l + pos + len + 1; // inc line to pos after scolon
            ans++;
          }
        }

        // check that symbol was not found inside a comment block
        if (varname_is_in_codeblock(code, vn)) {
          list_add(types, tpe);
          list_add(vars, vn);
        }
      }
    } while(idx > -1);
  }

  // print a warning if code block contains '=' char
  int warnings = 0;
  if(list_len(code->lines) > 0) {
    List_handle liter;
    char *line;
    liter = list_iterate(code->lines);
    while((line = (char*) list_next(liter)))
      if (strchr(line, '=')) warnings++;
    list_iterate_end(liter);
  }
  if (warnings)
    fprintf(stderr,"Warning: %s block contains %i assignments (= sign).\n"
                   "         Move them into an %s section. May fail at compile.\n"
                   , block_name, warnings, movetoblock_name);

  return(ans);
} // get_codeblock_vars

/*******************************************************************************
* detect_skipable_transforms: Finds components where coordinate transform can be skipped
*   Checks for trace / extend and if origin or target of a jump.
*******************************************************************************/
void detect_skipable_transforms(struct instr_def *instr) {
    //
    // analyze component sequence to find coordinate transformations that can be skipped
    //
    List_handle liter;
    struct comp_inst *comp = NULL;
    struct comp_inst *target_comp = NULL;
    
    // Assume all can be skipped
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {
        comp->skip_transform = 1;
    }
    list_iterate_end(liter);
    
    // Detect those components that can not
    liter = list_iterate(instr->complist);
    while((comp = (comp_inst*) list_next(liter)) != NULL) {

        if ((comp->def->trace_code && list_len(comp->def->trace_code->lines) > 0) || list_len(comp->extend->lines) > 0) {
            // If component has trace or extend, do not skip it
            comp->skip_transform = 0;
        }
        
        if(list_len(comp->jump) > 0) {
            // If this component jumps elsewhere, it can not be skipped
            comp->skip_transform = 0;
            
            // Its target can not be skipped either
            struct jump_struct *this_jump;
            List_handle literJ = list_iterate(comp->jump);
            while (this_jump = (jump_struct*) list_next(literJ)) {
                
                // Find target (not initialized yet)
                List_handle liter3 = list_iterate(instr->complist);
                struct comp_inst *target=NULL;
                while((target = (comp_inst*) list_next(liter3)) != NULL) {
                  if (!strcmp(target->name, this_jump->target))
                    this_jump->target_index = target->index;
                }
                list_iterate_end(liter3);
                if (!this_jump->target_index) /* JUMP e.g. PREVIOUS/NEXT is relative -> absolute */
                  this_jump->target_index += comp->index;

                // component list is 1 indexed so subtract one from target_index
                target_comp = (comp_inst*) list_access(instr->complist, this_jump->target_index - 1);
                target_comp->skip_transform = 0;
            }
            list_iterate_end(literJ);
        }
    }
    list_iterate_end(liter);
}
    
/*******************************************************************************
* cogen: the code generator
*   Generate the output file (in C).
*******************************************************************************/
void
cogen(char *output_name, struct instr_def *instr)
{
  int warnings = 0;

  /* INITIALISE output file. */
  if(!output_name || !output_name[0] || !strcmp(output_name, "-"))
  {
    output_handle = fdopen(1, "w");
    quoted_output_file_name = str_dup((char*) "<stdout>");
  }
  else
  {
    output_handle = fopen(output_name, "w");
    quoted_output_file_name = str_quote(output_name);
  }

  num_next_output_line = 1;
  if(output_handle == NULL)
    fatal_error("Error opening output file '%s'\n", output_name);

  /* and we now call the writers */
  cogen_header(instr, output_name);
  warnings += cogen_decls(instr);
  detect_skipable_transforms(instr);

  warnings += cogen_section(instr, (char*) "INITIALISE", (char*) "init", instr->inits);

  // TRACE section requires a bit more flexibility
  def_trace_section(instr);
  warnings += cogen_trace_functions(instr);
  def_uservars(instr);
  warnings += cogen_raytrace(instr);
  warnings += cogen_rt_funnel(instr);
  undef_uservars(instr);
  undef_trace_section(instr);

  warnings += cogen_section(instr, (char*) "SAVE", (char*) "save", instr->saves);
  warnings += cogen_section(instr, (char*) "FINALLY", (char*) "finally", instr->finals);
  warnings += cogen_section(instr, (char*) "DISPLAY", (char*) "display", NULL);

  // API macro support functions
  cogen_getvarpars_fct(instr);
  cogen_getparticlevar_fct(instr);


  cogen_getcompindex_fct(instr);

  embed_file((char*) "metadata-r.c"); // functions used to query and display instrument/component-defined metadata strings
  embed_file((char*) "mccode_main.c");

  if (verbose && warnings)
    fprintf(stderr,"Warning: The build of the instrument '%s' has %i warnings/errors.\n",
        	instr->name, warnings);
  coutf("/* end of generated C code %s */", output_name);

  fclose(output_handle);
} /* cogen */

#endif
