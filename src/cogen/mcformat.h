#ifndef __MC_FORMAT_H__
#define __MC_FORMAT_H__


/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Instrument: mcformat, McStas format converter
*
* %Identification
* Written by: <a href="mailto:farhi@ill.fr">Emmanuel Farhi</a>
* Date: 1st Feb 2001.
* Origin: <a href="http://www.ill.fr">ILL (France)</a>
* Release: @MCCODE_STRING@
* Version: $Revision$
*
* A McCode format converter to merge/convert data files.
*
* %Description
*
* A McCode format converter to merge/convert data files.
* Parameters are the files/directories to process, and option flags.
* May be used to:
* 1- continue an interupted simulation, and then add (--merge option) the similar
*    data files.
* 2- convert original simple text format into NeXus format (--format=NeXus)
* 3- catenate list files
* 4- reconstruct parameter scan sumulations (--scan)
*
* %Parameters
* INPUT PARAMETERS:
* files [string]:  list of files/directories to convert, separated by spaces
*
* %Link
*
* %End
*******************************************************************************/

#ifndef MCFORMAT
//#define MCFORMAT  "$Revision$" /* avoid memory.c to define Pool functions */
#define MCFORMAT  "0.1.0" /* avoid memory.c to define Pool functions */
#endif

#ifdef USE_MPI
#undef USE_MPI
#endif

/* Instead of including mccode.h file, which would then require to link most
   of the functions of the mcstas executable, we just put there some parts of
   the mccode.h file.
   Build: cc -o mcformat mcformat.c -lm
*/

#define fatal_error printf  /* remove debug.c dependency */
#define debug(msg)

#define MCCODE_H                  /* avoids memory.c to import mccode.h */
typedef struct Pool_header *Pool; /* allows memory to be included */



// TODO: include these runtime files


#include "../lib/share/mccode-r.h" // with decl of MC_PATHSEP
#include "../lib/share/mccode-r.c"

// end of parts copied from mccode.h
#include "../lib/share/read_table-lib.h" // independent library
#include "../lib/share/read_table-lib.c"



#include <dirent.h>
#include <errno.h>

/* Functions defined in memory.c */

void *mem(size_t);    /* Allocate memory. */
void  memfree(void *);    /* Free memory. */
char *str_dup(char *);    /* Allocate new copy of string. */
char *str_dup_n(char *string, int n); /* Copies only first N chars. */
char *str_cat(char *first, ...);/* Concatenate strings to allocated string. */
char *str_quote(char *string);  /* Quote string for inclusion in C code */
void  str_free(char *);   /* Free memory for string. */

/* default global variables required by mccode-r (usually generated in cogen) */
int  defaultmain         = 1;
int  traceenabled        = 0;
char instrument_name[CHAR_BUF_LENGTH];
char instrument_source[CHAR_BUF_LENGTH];
char *instrument_exe = NULL;
int  numipar             = 0;
struct mcinputtable_struct mcinputtable[CHAR_BUF_LENGTH];
mcstatic FILE *siminfo_file        = NULL;

/* default global variables for mcformat converter */
int  files_to_convert_NB    = 0;          /* nb of files to convert */
int  files_to_convert_Array[CHAR_BUF_LENGTH];  /* index of argv[] for these files */
char mcforcemode =0;
char mcverbose   =0;
char mcmergemode =0;
char mcscanmode  =0;
char mcmergesamedir=0;
int  mcdircount  =0; /* number of directories scanned */
int  mcnbconvert =0; /* index of current file */
FILE **mcsimfiles;
char **dirnames;
char **mcinstrnames;
char **mcsources;
char *mcoutputdir=NULL;
int  ipar_var    =0;  /* column index of scan variable (used in mcformat_scan_compare) */

struct fileparts_struct {
  char *FullName;
  char *Path;
  char *Name;
  char *Extension;
};

/* list of functions ******************************************************** */
/*
  char                     *str_dup_numeric(char *orig)
  char                     *str_dup_name(char *orig, int length)
  char                     *str_dup_label(char *orig)
  char                     *str_last_word(char *orig)
  struct                    fileparts_struct fileparts_init(void)
  struct                    fileparts_struct fileparts(char *name)
  void                      fileparts_free(struct fileparts_struct parts)
  struct McStas_file_format mcformat_init_mcstas_struct(void)
  void                      mcformat_print_mcstas_struct(struct McStas_file_format McStasStruct)
  struct McStas_file_format mcformat_free_mcstas_struct(struct McStas_file_format McStasStruct)
  struct McStas_file_format mcformat_read_mcstas(char *filename)
  int                       mcformat_dirwalk(char *dir, int (*fcn)(char *))
  static void               mcformat_usedir(char *dir)
  int                       mcformat_output(struct McStas_file_format McStasStruct)
  int                       mcformat_convert(char *name)
  int                       mcformat_count(char *name)
  int                       mcformat_merge_compare(int nb)
  void                      mcformat_scan_compare(int nb)
  int                       mcformat_merge_output(int nb)
  void                      mcformat_usage(char *pgmname)
  void                      mcformat_parseoptions(int argc, char *argv[])
  int                       main(int argc, char *argv[])
*/

/*******************************************************************************
* str_dup_numeric: makes a clean copy of a string and allocate as numeric
*******************************************************************************/
char *str_dup_numeric(char *orig)
{
  long i;
  char *valid;

  if (!orig || !strlen(orig)) return(NULL);

  for (i=0; i < strlen(orig); i++)
  {
    if ( (orig[i] > 122)
      || (orig[i] < 32)
      || (strchr("!\"#$%&'()*,:;<=>?@[\\]^`/ ", orig[i]) != NULL) )
    {
      orig[i] = ' ';
    }
  }
  orig[i] = '\0';
  /* now skip spaces */
  for (i=0; i < strlen(orig); i++) {
    if (*orig == ' ') orig++;
    else break;
  }

  valid=str_dup(orig);

  return(valid);
} /* str_dup_numeric */

/*******************************************************************************
* str_dup_name: makes a clean copy of a string and allocate as name
*******************************************************************************/
char *str_dup_name(char *orig, int length)
{
  char *valid;

  if (!orig || !strlen(orig)) return(NULL);

  valid=str_dup_n(orig, length > 0 ? length : strlen(orig));
  strcpy_valid(valid, orig);

  return(valid);
} /* str_dup_name */

/*******************************************************************************
* str_dup_label: makes a clean copy of a string and allocate as label/title
*******************************************************************************/
char *str_dup_label(char *orig)
{
  long i;
  char *valid;
  int  length=0;

  if (!orig || !strlen(orig)) return(NULL);

  for (i=0; i < strlen(orig); i++)
  {
    if ( (orig[i] > 122)
      || (orig[i] < 32)
      || (strchr("\"'=:;", orig[i]) != NULL) )
    {
      orig[i] = ' ';
    }
  }
  orig[i] = '\0';
  /* now skip spaces at begining */
  for (i=0; i < strlen(orig); i++) {
    if (*orig == ' ') orig++;
    else break;
  }
  length = strlen(orig);
  /* skip trailing blanks */
  for (i=strlen(orig)-1; i > 0; i--) {
    if (orig[i] == ' ') length--;
    else break;
  }

  valid=str_dup_n(orig, length);

  return(valid);
} /* str_dup_label */

/*******************************************************************************
* str_last_word: points to last word of string
*******************************************************************************/
char *str_last_word(char *orig)
{
  char *pos_end  =NULL;
  char *pos_begin=NULL;
  char separators[]= MC_PATHSEP_S " !\"#$%&'()*,:;<=>?@[\\]^`/.";

  /* first skip trailing separators */
  pos_end = orig+strlen(orig);
  while (pos_end > orig) {
    if (strchr(separators, *pos_end)) pos_end--; /* pass separators at the end */
    else break;
  }
  pos_begin = pos_end-1;
  /* search for non separators (pass word) */
  while (pos_begin >= orig) {
    if (!strchr(separators, *pos_begin)) pos_begin--; /* pass non separators */
    else break;
  }
  pos_begin++;

  if (pos_begin < orig) pos_begin=orig;

  return(pos_begin);
} /* str_last_word */


/*******************************************************************************
* fileparts_init: Initialize a zero fileparts structure
*******************************************************************************/
struct fileparts_struct fileparts_init(void)
{
  struct fileparts_struct parts;

  parts.FullName  = NULL;
  parts.Path      = NULL;
  parts.Name      = NULL;
  parts.Extension = NULL;

  return(parts);
} /* fileparts_init */

/*******************************************************************************
* fileparts: Split a fully qualified file name/path into pieces
* Returns a zero structure if called with NULL argument.
* Returns: fields are non NULL if they exist
*    Path is NULL if no Path
*    Name is NULL if just a Path
*    Extension is "" if just a dot
*******************************************************************************/
struct fileparts_struct fileparts(char *name)
{
  struct fileparts_struct parts;

  parts = fileparts_init();

  if (name) {
    char *dot_pos    = NULL;
    char *path_pos   = NULL;
    char *end_pos    = NULL;
    char *name_pos   = NULL;
    long  dot_length = 0;
    long  path_length= 0;
    long  name_length= 0;

    parts.FullName  = str_dup(name);
    /* extract path+filename+extension from full filename */

    if (strlen(name) == 0) return(parts);

    end_pos = name+strlen(name);  /* end of file name */

    /* extract path: searches for last file separator */
    path_pos= strrchr(name, MC_PATHSEP_C);  /* last PATHSEP */

    if (!path_pos) {
      path_pos   =name;
      path_length=0;
      name_pos   =name;
      parts.Path = str_dup("");
    } else {
      name_pos    = path_pos+1;
      path_length = name_pos - name;  /* from start to path+sep */
      if (path_length) {
        parts.Path = str_cat(name, MC_PATHSEP_S, NULL);
        strncpy(parts.Path, name, path_length);
        parts.Path[path_length]='\0';
      } else parts.Path = str_dup("");
    }

    /* extract ext: now looks for the 'dot' */
    dot_pos = strrchr(name_pos, '.');           /* last dot */
    if (dot_pos > name_pos) {
      dot_length = end_pos - dot_pos;
      if (dot_length > 0) {
        parts.Extension = str_dup(name);
        strncpy(parts.Extension, dot_pos+1, dot_length);  /* skip the dot */
        parts.Extension[dot_length]='\0';
      }
    } else dot_pos = end_pos;

    /* extract Name (without extension) */
    name_length = dot_pos - name_pos; /* from path to dot */
    if (name_length) {
      parts.Name = str_dup(name);
      strncpy(parts.Name, name_pos, name_length);
      parts.Name[name_length]='\0';
    }
  } /* if (name) */
  return (parts);
} /* fileparts */

/*******************************************************************************
* fileparts_free: Free a fileparts_struct fields
*******************************************************************************/
void fileparts_free(struct fileparts_struct parts)
{
  str_free(parts.FullName);
  str_free(parts.Path);
  str_free(parts.Name);
  str_free(parts.Extension);
} /* fileparts_free */

struct McStas_file_format {
  char    *Source;
  char    *Creator;
  char    *Editor;
  char    *InstrName;
  char    *filename;
  char    *Format;
  char    *Date;
  char    *EndDate;
  double   Ncount;
  char    *component;
  char    *type;
  char    *title;
  char    *xlabel;
  char    *ylabel;
  char    *zlabel;
  char    *xvar;
  char    *yvar;
  char    *zvar;
  char    *xylimits;
  char    *position;
  char    *gravitation;
  char    *outputname;
  char    *Ncount_str;

  t_Table *Data;

  long     m, n, p;
  double   x1, x2, y1, y2, z1, z2;
  char    *ratio;
  double   RunNum;
  double  *p0, *p1, *p2;
  double   Nsum, Psum, P2sum;
  Coords   POSITION;

  int      mcnumipar;
  struct   mcinputtable_struct *mcinputtable;
  char    *dirname;
  double   Scan_ipar_value;
  int      Scan_ipar_index;
  double   Scan_mon_distance;
  int      Scan_mon_index;
}; /* McStas_file_format */

struct McStas_file_format *Files_to_Merge=NULL;
int                       *Scans_to_merge=NULL;

/*******************************************************************************
* mcformat_init_mcstas_struct: Init an empty McStas data structure
*******************************************************************************/
struct McStas_file_format mcformat_init_mcstas_struct(void)
{
  struct McStas_file_format McStasStruct;

  McStasStruct.Format     = NULL;
  McStasStruct.Creator    = NULL;
  McStasStruct.Editor     = NULL;
  McStasStruct.Date       = NULL;
  McStasStruct.EndDate    = NULL;
  McStasStruct.Ncount     = 0;
  McStasStruct.type       = NULL;
  McStasStruct.Source     = NULL;
  McStasStruct.InstrName  = NULL;
  McStasStruct.component  = NULL;
  McStasStruct.title      = NULL;
  McStasStruct.ratio      = NULL;
  McStasStruct.filename   = NULL;
  McStasStruct.xvar       = NULL;
  McStasStruct.yvar       = NULL;
  McStasStruct.xlabel     = NULL;
  McStasStruct.ylabel     = NULL;
  McStasStruct.zvar       = NULL;
  McStasStruct.zlabel     = NULL;
  McStasStruct.xylimits   = NULL;
  McStasStruct.position   = NULL;
  McStasStruct.outputname = NULL;
  McStasStruct.Ncount_str = NULL;

  McStasStruct.Data       = NULL;
  McStasStruct.p0         = NULL;
  McStasStruct.p1         = NULL;
  McStasStruct.p2         = NULL;
  McStasStruct.Nsum       = 0;
  McStasStruct.Psum       = 0;
  McStasStruct.P2sum      = 0;
  McStasStruct.POSITION.x=McStasStruct.POSITION.y=McStasStruct.POSITION.z=0;

  McStasStruct.RunNum     = 0;
  McStasStruct.m          = 0;
  McStasStruct.n          = 0;
  McStasStruct.p          = 0;
  McStasStruct.x1         = 0;
  McStasStruct.x2         = 0;
  McStasStruct.y1         = 0;
  McStasStruct.y2         = 0;
  McStasStruct.z1         = 0;
  McStasStruct.z2         = 0;

  McStasStruct.gravitation= NULL;

  McStasStruct.mcnumipar          =0;
  McStasStruct.mcinputtable       =NULL;
  McStasStruct.dirname          =NULL;

  McStasStruct.Scan_ipar_value  =0;
  McStasStruct.Scan_ipar_index  =0;
  McStasStruct.Scan_mon_distance=0;
  McStasStruct.Scan_mon_index   =0;

  return(McStasStruct);
} /* mcformat_init_mcstas_struct */


void mcformat_print_mcstas_struct(struct McStas_file_format McStasStruct)
{
  printf("Structure from file %s\n", McStasStruct.filename);
  printf("  Format     = %s\n", McStasStruct.Format     );
  printf("  Creator    = %s\n", McStasStruct.Creator    );
  printf("  Editor     = %s\n", McStasStruct.Editor     );
  printf("  Date       = %s\n", McStasStruct.Date       );
  printf("  EndDate    = %s\n", McStasStruct.EndDate    );
  printf("  type       = %s\n", McStasStruct.type       );
  printf("  Source     = %s\n", McStasStruct.Source     );
  printf("  InstrName  = %s\n", McStasStruct.InstrName  );
  printf("  component  = %s\n", McStasStruct.component  );
  printf("  title      = %s\n", McStasStruct.title      );
  printf("  ratio      = %s\n", McStasStruct.ratio      );
  printf("  xvar       = %s\n", McStasStruct.xvar       );
  printf("  yvar       = %s\n", McStasStruct.yvar       );
  printf("  xlabel     = %s\n", McStasStruct.xlabel     );
  printf("  ylabel     = %s\n", McStasStruct.ylabel     );
  printf("  zvar       = %s\n", McStasStruct.zvar       );
  printf("  zlabel     = %s\n", McStasStruct.zlabel     );
  printf("  xylimits   = %s\n", McStasStruct.xylimits   );
  printf("  position   = %s\n", McStasStruct.position   );
  printf("  outputname = %s\n", McStasStruct.outputname );
  printf("  Ncount_str = %s\n", McStasStruct.Ncount_str );
  printf("  dirname  = %s\n", McStasStruct.dirname );

  printf("  gravitation= %s\n", McStasStruct.gravitation );
  printf("  Ncount     = %g\n", McStasStruct.Ncount);
  printf("  RunNum     = %g\n", McStasStruct.RunNum);

  printf("  x1         = %g\n", McStasStruct.x1);
  printf("  x2         = %g\n", McStasStruct.x2);
  printf("  y1         = %g\n", McStasStruct.y1);
  printf("  y2         = %g\n", McStasStruct.y2);
  printf("  z1         = %g\n", McStasStruct.z1);
  printf("  z2         = %g\n", McStasStruct.z2);

  printf("  Data       = %s\n", McStasStruct.Data ? "OK" : "NULL");

  printf("  m          = %ld\n", McStasStruct.m);
  printf("  n          = %ld\n", McStasStruct.n);
  printf("  p          = %ld\n", McStasStruct.p);

  printf("  p0         = %s\n", McStasStruct.p0 ? "OK": "NULL");
  printf("  p1         = %s\n", McStasStruct.p1 ? "OK": "NULL");
  printf("  p2         = %s\n", McStasStruct.p2 ? "OK": "NULL");
  printf("  POSITION   = %g %g %g\n", McStasStruct.POSITION.x, McStasStruct.POSITION.y, McStasStruct.POSITION.z);
  printf("  numipar  = %d\n", McStasStruct.mcnumipar);
  printf("  inputtable = %s\n", McStasStruct.mcinputtable ? "OK": "NULL");
}


/*******************************************************************************
* mcformat_free_mcstas_struct: Free a McStas data structure
*******************************************************************************/
struct McStas_file_format mcformat_free_mcstas_struct(struct McStas_file_format McStasStruct)
{
  memfree(McStasStruct.Format   );
  memfree(McStasStruct.Date     );
  memfree(McStasStruct.EndDate  );
  memfree(McStasStruct.Creator  );
  memfree(McStasStruct.Editor   );
  memfree(McStasStruct.type     );
  memfree(McStasStruct.Source   );
  memfree(McStasStruct.InstrName);
  memfree(McStasStruct.component);
  memfree(McStasStruct.gravitation);
  memfree(McStasStruct.title    );
  memfree(McStasStruct.ratio    );
  memfree(McStasStruct.filename );
  memfree(McStasStruct.xvar     );
  memfree(McStasStruct.yvar     );
  memfree(McStasStruct.xlabel   );
  memfree(McStasStruct.ylabel   );
  memfree(McStasStruct.zvar     );
  memfree(McStasStruct.zlabel   );
  memfree(McStasStruct.xylimits );
  memfree(McStasStruct.position );
  memfree(McStasStruct.outputname );
  memfree(McStasStruct.Ncount_str );

  if (McStasStruct.Data) Table_Free_Array(McStasStruct.Data);
  if (McStasStruct.p0) memfree(McStasStruct.p0 );
  if (McStasStruct.p1) memfree(McStasStruct.p1 );
  if (McStasStruct.p2) memfree(McStasStruct.p2 );

  memfree(McStasStruct.dirname          );

  /* free mcinputtable */
  int i;
  for (i=0; i<McStasStruct.mcnumipar; i++) {
    memfree(McStasStruct.mcinputtable[i].name);
    memfree(McStasStruct.mcinputtable[i].val);
  }
  memfree(McStasStruct.mcinputtable       );

  return(McStasStruct);
} /* mcformat_free_mcstas_struct */

/*******************************************************************************
* mcformat_read_mcstas:  Reads filename and checks for McStas format
*                        extracts header and data and return structure
*                        structure.p1 is NULL in case of failure
*******************************************************************************/
struct McStas_file_format mcformat_read_mcstas(char *filename)
{
  struct McStas_file_format McStasStruct;
  int    m=1,n=1,p=1, i,j;
  long   array_length=0;
  char   flag_abort=0;
  char   flag_pgplot1d=0;

  /* init default empty return value */
  McStasStruct = mcformat_init_mcstas_struct();

  /* opens the file as a t_Table */
  t_Table *rTable=NULL;

  /* gets header and block 1 */
  rTable = Table_Read_Array(filename, &array_length); /* reads all data */
  if (!rTable) { if (mcverbose) fprintf(stderr, "mcformat: file %s not found\n", filename);
    return(McStasStruct);
  }

  /* returns if this is not a McStas format file, or invalid */
  if (!rTable[0].data || (array_length != 1 && array_length != 3))   {
    if (mcverbose) fprintf(stderr, "mcformat: file %s is invalid (%ld blocks)\n",
      filename, array_length);
    flag_abort=1;
  } else if (!rTable[0].header) {
    if (mcverbose) fprintf(stderr, "mcformat: Can not read header from file %s\n"
      "          Data is [%ld x %ld]\n", filename, rTable[0].rows, rTable[0].columns);
    flag_abort=1;
  }

  if (array_length == 3)
      for (i=1; i<=2; i++)
      if (rTable[0].rows != rTable[i].rows || rTable[0].columns != rTable[i].columns) {
        if (mcverbose) fprintf(stderr, "mcformat: file %s Data dimensions are not consistent\n"
          "          Data[%i] is [%ld x %ld]\n",
          filename, i, rTable[i].rows, rTable[i].columns);
          flag_abort=1;
      }
  if (flag_abort) {
    Table_Free_Array(rTable);
    return(McStasStruct);
  }

  /* analyze content of file : use read-table:Table_ParseHeader ********** */
  char **parsing;
  parsing = Table_ParseHeader(rTable[0].header,
      "Format", /* original Format */
      "Editor",
      "Creator",
      "Date",
      "EndDate",
      "File",   /* original filename */
      "Source","mcinstrument-source",
      "instrument",
      "Ncount",
      "Gravitation",
      "type",
      "component","parent",
      "position",
      "title",
      "ratio",
      "xlabel",
      "ylabel",
      "zlabel",
      "xvar",
      "yvar",
      "zvar",
      "xlimits", "xylimits",
      NULL);

    if (parsing) {
      if (parsing[0])   McStasStruct.Format     = str_dup_label(parsing[0]);
      if (parsing[1])   McStasStruct.Editor     = str_dup_label(parsing[1]);
      if (parsing[2])   McStasStruct.Creator    = str_dup_label(parsing[2]);
      if (parsing[3])   McStasStruct.Date       = str_dup_numeric(parsing[3]);  /* mcstartdate */
      if (parsing[4])   McStasStruct.EndDate    = str_dup_numeric(parsing[4]);  /* DATL */
/*   if (parsing[5])   McStasStruct.filename   = str_dup(parsing[5]); */
      if (parsing[6])   McStasStruct.Source     = str_dup_label(parsing[6]);  /* instrument_source */
      if (parsing[7] && !McStasStruct.Source)
                        McStasStruct.Source     = str_dup_label(parsing[7]);
      if (parsing[8])   McStasStruct.InstrName  = str_dup_label(parsing[8]);  /* instrument_name */
      if (parsing[9])   McStasStruct.Ncount_str = str_dup_numeric(parsing[9]);
      if (parsing[10])  McStasStruct.gravitation= str_dup_numeric(parsing[10]);/* mcgravitation */
      if (parsing[11])  McStasStruct.type       = str_dup_label(parsing[11]); /* array_Xd */
      if (parsing[12])  McStasStruct.component  = str_dup_label(parsing[12]); /* NAME_CURRENT_COMP */
      if (parsing[13] && !McStasStruct.component)
                        McStasStruct.component  = str_dup_label(parsing[13]);
      if (parsing[14])  McStasStruct.position   = str_dup_numeric(parsing[14]); /* string(POS_A_CURRENT_COMP) */
      if (parsing[15])  McStasStruct.title      = str_dup_label(parsing[15]);
      if (parsing[16])  McStasStruct.ratio      = str_dup_numeric(parsing[16]); /* -> RunNum */
      if (parsing[17])  McStasStruct.xlabel     = str_dup_label(parsing[17]);
      if (parsing[18])  McStasStruct.ylabel     = str_dup_label(parsing[18]);
      if (parsing[19])  McStasStruct.zlabel     = str_dup_label(parsing[19]);
      if (parsing[20])  McStasStruct.xvar       = str_dup_label(parsing[20]);
      if (parsing[21])  McStasStruct.yvar       = str_dup_label(parsing[21]);
      if (parsing[22])  McStasStruct.zvar       = str_dup_label(parsing[22]);
      if (parsing[23])  McStasStruct.xylimits   = str_dup_numeric(parsing[23]); /* x/y min/max */
      if (parsing[24] && !McStasStruct.xylimits)
                        McStasStruct.xylimits   = str_dup_numeric(parsing[24]);
      for (i=0; i<=24; i++) {
        if (parsing[i]) free(parsing[i]);
      }
      free(parsing);
    }

/* will be determined over original values when writting  new data file:
        filename
        format
        statistics
        signal
        values
     */
  if (!McStasStruct.InstrName && !McStasStruct.Source)
    McStasStruct.Source = str_dup("McStas_Instrument");
  else if (!McStasStruct.InstrName && McStasStruct.Source) {
    char *ext=NULL; /* if not found, use instr file name without extension */
    ext = strstr(McStasStruct.Source, ".ins");
    if (!ext) ext = strstr(McStasStruct.Source, " ins");
    if (ext) McStasStruct.InstrName = str_dup_n(McStasStruct.Source, (ext-McStasStruct.Source));
    else McStasStruct.InstrName = str_dup(McStasStruct.Source);
  } else if (McStasStruct.InstrName && !McStasStruct.Source) {
    char *ext=NULL; /* if not found, use instr name without extension */
    ext = strstr(McStasStruct.InstrName, ".ins");
    if (!ext) ext = strstr(McStasStruct.InstrName, " ins");
    if (ext) McStasStruct.Source = str_dup_n(McStasStruct.InstrName, (ext-McStasStruct.InstrName));
    else McStasStruct.Source = str_dup(McStasStruct.InstrName);
  }

  if (McStasStruct.Ncount_str) McStasStruct.Ncount=atof(McStasStruct.Ncount_str);

  /* header analysis: general keywords */
  if (McStasStruct.ratio) {  /* extracts RunNum and Ncount values separated by '/' */
    double runnum=0, ncount=0;
    int   i;
    i = sscanf(McStasStruct.ratio, "%lg %lg", &runnum, &ncount);
    if (i) McStasStruct.RunNum = runnum;
    if (i>1) {
      if (!McStasStruct.Ncount && ncount) McStasStruct.Ncount = ncount;
      else if (ncount && McStasStruct.Ncount != ncount)
        fprintf(stderr, "Warning: %s: conflicting Ncount %f value with 'ratio' one %f\n",
          filename, McStasStruct.Ncount, ncount);
    } else if (!McStasStruct.Ncount) /* no Ncount and ratio is a single value: Ncount == runnum */
      McStasStruct.Ncount = McStasStruct.RunNum;
  }
  if (!McStasStruct.Ncount) {
    McStasStruct.Ncount = 1e6;
    fprintf(stderr, "Warning: %s: can not extract Ncount. using default (%g)\n",
      filename, McStasStruct.Ncount);
  }
  if (!McStasStruct.RunNum) McStasStruct.RunNum = McStasStruct.Ncount;
  if (McStasStruct.RunNum < McStasStruct.Ncount*0.99)
    fprintf(stderr, "Warning: %s: Temporary results with ratio %g/%g. Simulation results are not completed.\n",
      filename, McStasStruct.RunNum, McStasStruct.Ncount);

  /* analyse type, and check that Data dims are m,n,p */
  if (McStasStruct.type) {
    if (!strcmp(McStasStruct.type, "array_0d")) m=n=p=1;
    else if (sscanf(McStasStruct.type, "array_1d(%d)",&m) == 1) n=p=1;
    else if (sscanf(McStasStruct.type, "array_2d(%d, %d)",&n,&m) == 2) p=1;
    else if (sscanf(McStasStruct.type, "array_3d(%d, %d, %d)",&n,&m,&p) == 3) { /* void */ }
    else if (sscanf(McStasStruct.type, "multiarray_1d(%d)", &m)) {
      if (!mcscanmode) fprintf(stderr, "Warning: %s: use --scan flag for multiarray/scans (skipped)\n", filename);
      return(McStasStruct);
    }
  } else {
    fprintf(stderr, "Warning: %s: invalid data type '%s' (not 1d/2d/3d/multiarray)\n", filename, McStasStruct.type);
    return(McStasStruct);
  }

/* Scans: just test existence. If yes, then will skip the SIM file */
  /*
  "# Numpoints: "
  "# xvars: "
  "# yvars: "
*/
  /* check if data block is transposed */
  if (m != rTable[0].rows    && n != rTable[0].columns
   && m == rTable[0].columns && n == rTable[0].rows) {
    if (mcverbose) fprintf(stderr, "Warning: %s: Data block is transposed. Fixing.\n", filename);
    int tmp=m;
    m=n; n=tmp;
  }
  if (m != rTable[0].rows) {
    fprintf(stderr, "Warning: %s: conflicting Data row numbers\n"
                    "         expected=%d found=%ld. Fixing. Check first line of Data block.\n", filename, m, rTable[0].rows);
    m = rTable[0].rows;
  }
  if (McStasStruct.Format && (strstr(McStasStruct.Format, "binary") || strstr(McStasStruct.Format, "float") || strstr(McStasStruct.Format, "double")))
    fprintf(stderr, "WARNING: %s: Format of data file indicates binary blocks."
                    "         Not supported. Might crash.\n", filename);
  if (McStasStruct.Format && McStasStruct.type
    && strstr(McStasStruct.Format, "PGPLOT") && array_length == 1
    && strstr(McStasStruct.type, "array_1d") && rTable[0].columns == 4) flag_pgplot1d=1;
  if (flag_pgplot1d) n = 4;
  if (n != rTable[0].columns) {
    fprintf(stderr, "Warning: %s: conflicting Data column numbers\n"
                    "         expected=%d found=%ld. Fixing. Check first line of Data block.\n", filename, n, rTable[0].columns);
    n = rTable[0].columns;
  }
  if (flag_pgplot1d) n = 1;
  McStasStruct.m = rTable[0].rows; /* dimensions from the Table */
  McStasStruct.n = flag_pgplot1d ? 1 : rTable[0].columns;
  McStasStruct.p = p; /* extracted from type */

  m = McStasStruct.m;
  n = McStasStruct.n;


  /* extract limits values */
  McStasStruct.x1=1; McStasStruct.x2=McStasStruct.m;
  McStasStruct.y1=1; McStasStruct.y2=McStasStruct.n;
  McStasStruct.z1=1; McStasStruct.z2=McStasStruct.p;
  if (McStasStruct.xylimits) {
    i = sscanf(McStasStruct.xylimits, "%lg %lg %lg %lg %lg %lg",
      &(McStasStruct.x1), &(McStasStruct.x2),
      &(McStasStruct.y1), &(McStasStruct.y2),
      &(McStasStruct.z1), &(McStasStruct.z2));
    if (i != 2 && i != 4 && i != 6)
      fprintf(stderr, "Warning: %s: invalid xylimits '%s'. extracted %i values\n",
        filename, McStasStruct.xylimits, i);
  }

  /* special case of 2D binary files: axes must be exchanged */
  if (strstr(mcformat, "binary") || strstr(mcformat, "float") || strstr(mcformat, "double"))
  if (p == 1 && m>1 && n>1) {
    double tmp; char* c;
    tmp=McStasStruct.x1; McStasStruct.x1=McStasStruct.y1; McStasStruct.y1=tmp;
    tmp=McStasStruct.x2; McStasStruct.x2=McStasStruct.y2; McStasStruct.y2=tmp;
    c=McStasStruct.xlabel; McStasStruct.xlabel=McStasStruct.ylabel; McStasStruct.ylabel=c;
    c=McStasStruct.xvar;   McStasStruct.xvar=McStasStruct.yvar;     McStasStruct.yvar=c;
  }

  McStasStruct.filename   = str_dup(filename);
  if (!McStasStruct.component) McStasStruct.component=str_dup(filename);
  struct fileparts_struct file_parts=fileparts(filename);
  char *tmp=str_cat(file_parts.Name, ".", file_parts.Extension, NULL);
  McStasStruct.outputname = str_dup_name(tmp, 0);
  memfree(tmp);
  fileparts_free(file_parts);
  McStasStruct.dirname  = str_dup(dirname);
  if (McStasStruct.position) sscanf(McStasStruct.position, "%lg %lg %lg",
    &McStasStruct.POSITION.x,&McStasStruct.POSITION.y,&McStasStruct.POSITION.z);

  /* header analysis: get instrument parameters and fills numipar and inputtable */
  char *s = rTable[0].header;
  char *tok=s;
  char *equal_sign=NULL;
  char *name_start=NULL;
  numipar = 0;
  while (tok) { /* extract parameter=value as clean names */
    tok = strstr(s, "Parameters");
    if (!tok) tok = strstr(s, "parameters");
    if (!tok) tok = strstr(s, "Param");
    if (!tok) tok = strstr(s, "param");
    if (!tok) break;
    parsing = Table_ParseHeader(tok, "Parameters", NULL); /* get line */
    if (!parsing[0]) parsing = Table_ParseHeader(tok, "parameters", NULL); /* get line */
    if (!parsing[0]) parsing = Table_ParseHeader(tok, "Param", NULL); /* get line */
    if (!parsing[0]) parsing = Table_ParseHeader(tok, "param", NULL); /* get line */
    name_start = (parsing[0] ? str_dup(parsing[0]) : NULL);
    memfree(parsing[0]); free(parsing);
    if (!name_start) break;
    equal_sign = strchr(name_start+1, '=');
    if (equal_sign > name_start && strlen(name_start)) {
      char *name_to_equal=str_dup_n(name_start, equal_sign-name_start);
      char *name=str_last_word(name_to_equal);
      char *value      = str_dup(equal_sign+1);
      if (name && value && strlen(name) && strlen(value)) {
        char *name_label = str_dup_label(name);
        /*printf("name_to_equal='%s' name='%s' value='%s'\n", name_to_equal, name, value); */
        mcinputtable[numipar].name = name_label;
        mcinputtable[numipar].type = instr_type_string;
        mcinputtable[numipar].val  = value;
        mcinputtable[numipar].par  = NULL;
        numipar++;
      }
      memfree(name_to_equal);
    }
    memfree(name_start);
    s = tok+strlen("Param");
  } /* end while tok */

  /* now transfer mcinputtable into McStasStruct */
  McStasStruct.mcnumipar = numipar;
  McStasStruct.mcinputtable = (struct mcinputtable_struct *)mem(numipar*sizeof(struct mcinputtable_struct));
  for (i=0; i<numipar; i++) {
    McStasStruct.mcinputtable[i] = mcinputtable[i];
  }

  McStasStruct.Data = rTable;

  /* transfer Data into p0, p1, p2 */
  McStasStruct.p1   = (double*)mem(McStasStruct.m*McStasStruct.n*McStasStruct.p*sizeof(double));
  if ((array_length == 3 || flag_pgplot1d) && !strstr(McStasStruct.Format, " list ")) {
    McStasStruct.p0 = (double*)mem(McStasStruct.m*McStasStruct.n*McStasStruct.p*sizeof(double));
    McStasStruct.p2 = (double*)mem(McStasStruct.m*McStasStruct.n*McStasStruct.p*sizeof(double));
  }

  if (flag_pgplot1d)
  { /* this is a 1D PGPLOT data file.
       columns [ xvar, p, err, N ] */
    memfree(McStasStruct.yvar); McStasStruct.yvar=str_dup("I");
    for (i=0; i<m; i++) {
      McStasStruct.p1[i] = Table_Index(McStasStruct.Data[0], i, 1);
      McStasStruct.p2[i] = Table_Index(McStasStruct.Data[0], i, 2);
      McStasStruct.p0[i] = Table_Index(McStasStruct.Data[0], i, 3);
    }
  } else if (array_length == 1 || strstr(McStasStruct.Format, " list ")) {
    /* lists are stored as is */
    for (i=0; i<m; i++)
      for (j=0; j <n*p; j++) {
        int tmp=i*n*p+j;
        McStasStruct.p1[tmp] =
          Table_Index(McStasStruct.Data[0], i, j);
    }
  } else if (array_length == 3) { /* order in files is [p, err, N] */
    for (i=0; i<m; i++)
      for (j=0; j <n*p; j++) {
        int tmp=i*n*p+j;
        McStasStruct.p1[tmp] = Table_Index(McStasStruct.Data[0], i, j);
        McStasStruct.p2[tmp] = Table_Index(McStasStruct.Data[1], i, j);
        McStasStruct.p0[tmp] = Table_Index(McStasStruct.Data[2], i, j);
      }
  } else
    fprintf(stderr, "Warning: %s: can not store data blocks (total %ld).\n",
                    filename, array_length);

  /* compute back the original sigma->p2 array (see mcestimate_error) */
  if (McStasStruct.p0 && McStasStruct.p1 && McStasStruct.p2) {
    double *p0 = McStasStruct.p0;
    double *p1 = McStasStruct.p1;
    double *p2 = McStasStruct.p2;
    for (i=0; i < m*n*p; i++) {
      if (p2[i] > 0) p2[i] = (p0[i] > 1 ? ((p0[i]-1)*p2[i]*p2[i] + p1[i]*p1[i]/p0[i])/p0[i]
                         : p1[i]);
    }
  }
  McStasStruct.m *= -1; /* always transposed in files w/r to memory */

  /* free McStasStruct.Data for better memory management */
  Table_Free_Array(McStasStruct.Data); McStasStruct.Data=NULL;

  return(McStasStruct);
} /* end mcformat_read_mcstas */

/*******************************************************************************
* mcformat_dirwalk:  apply fcn to all files in dir (see K & R 'C language')
*                    returns number of processed files
*******************************************************************************/
int mcformat_dirwalk(char *dir, int (*fcn)(char *))
{
  char name[CHAR_BUF_LENGTH];
  int  ret=0;
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "mcformat: can't open %s\n", dir);
    return 0;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;    /* skip self and parent */
    if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
      fprintf(stderr, "mcformat: name %s%c%s too long\n",
        dir, MC_PATHSEP_C, dp->d_name);
    else {
      sprintf(name, "%s%c%s", dir, MC_PATHSEP_C, dp->d_name);
      ret += (*fcn)(name);
    }
  }
  closedir(dfd);
  return(ret);
} /* end mcformat_dirwalk */

/*******************************************************************************
* mcformat_usedir: set directory to use. Same as mcuse_dir with force option.
*******************************************************************************/
static void mcformat_usedir(char *dir)
{
#ifdef MC_PORTABLE
  fprintf(stderr, "Error: "
          "Directory output cannot be used with portable simulation (mcformat_usedir)\n");
  return;
#else  /* !MC_PORTABLE */
#ifndef WIN32
  if(!mcdisable_output_files && mkdir(dir, 0777))
#else
  if(!mcdisable_output_files && mkdir(dir))
#endif
  {
    int errno_mkdir = errno;
    if (errno_mkdir == ENOENT) {
      if (mcverbose) fprintf(stderr, "mkdir: ENOENT A directory component in pathname '%s' does not exist or is a dangling symbolic link.\n", dir);
      /* we build the required elements in the path */
      struct fileparts_struct dir_parts = fileparts(dir);
      if (strlen(dir_parts.Path)) {
        char *path_pos= strrchr(dir_parts.Path, MC_PATHSEP_C);  /* last PATHSEP */
        if (path_pos == dir_parts.Path+strlen(dir_parts.Path)-1) dir_parts.Path[strlen(dir_parts.Path)-1] = '\0';
        if (mcverbose) fprintf(stderr, "mcformat: Warning: building output directory '%s' from '%s'.\n", dir_parts.Path, dir);
        mcformat_usedir(dir_parts.Path);
        fileparts_free(dir_parts);
        mcformat_usedir(dir);
      }
    } else if (errno_mkdir == EEXIST) {
      fprintf(stderr, "mkdir: EEXIST pathname %s already exists (not necessarily as a directory).\n", dir);
      if (!mcforcemode && mcscanmode != 2) {
        fprintf(stderr, "Error: unable to create directory '%s' (mcformat_usedir)\n", dir);
        fprintf(stderr, "(Maybe the directory already exists? Use --force, --scan-only or --test before -d %s to override)\n", dir);
        exit(1);
      }
      fprintf(stderr, "mcformat: Warning: re-using output directory '%s'.\n", dir);
    } else {
      switch (errno_mkdir) {
#ifdef EACCES
      case EACCES:
        fprintf(stderr, "mkdir: EACCES The parent directory does not allow write permission\n"
        "       or one of the directories in pathname did not allow search permission.\n"); break;
#endif
#ifdef EFAULT
      case EFAULT:
        fprintf(stderr, "mkdir: EFAULT pathname points outside your accessible address space.\n"); break;
#endif
#ifdef ELOOP
      case ELOOP:
        fprintf(stderr, "mkdir: ELOOP Too many symbolic links were encountered in resolving pathname.\n"); break;
#endif
#ifdef ENAMETOOLONG
      case ENAMETOOLONG:
        fprintf(stderr, "mkdir: ENAMETOOLONG pathname was too long.\n"); break;
#endif
#ifdef ENOMEM
      case ENOMEM:
        fprintf(stderr, "mkdir: ENOMEM Insufficient kernel memory was available.\n"); break;
#endif
#ifdef ENOSPC
      case ENOSPC:
        fprintf(stderr, "mkdir: ENOSPC The device containing pathname has no room for the new directory.\n"); break;
#endif
#ifdef ENOTDIR
      case ENOTDIR:
        fprintf(stderr, "mkdir: ENOTDIR A component used as a directory in pathname is not, in fact, a directory.\n"); break;
#endif
#ifdef EPERM
      case EPERM:
        fprintf(stderr, "mkdir: EPERM The filesystem containing pathname does not support the creation of directories.\n"); break;
#endif
#ifdef EROFS
      case EROFS:
        fprintf(stderr, "mkdir: EROFS pathname refers to a file on a read-only filesystem.\n"); break;
#endif
      default:
        fprintf(stderr, "mkdir: ERROR %i using mkdir.\n", errno_mkdir); break;
      }
      fprintf(stderr, "mcformat: Fatal error accessing %s. Aborting.\n", dir);
      exit(-1);
    }
  }
  if (mcverbose) printf("mcformat: Creating directory %s.\n", dir);
  dirname = dir;

#endif /* !MC_PORTABLE */
} /* mcformat_usedir */

/*******************************************************************************
* mcformat_output: write monitor file and optionally free memory
*******************************************************************************/
int mcformat_output(struct McStas_file_format McStasStruct)
{
  char *currentdir= dirname; /* save current dir */
  int i;


  if (mcdisable_output_files) return(1);
  if (!McStasStruct.p1) return(0); /* empty data */
  /* determine in which directory we are and set SIM file */

  if (!mcdircount) {
    if (!strlen(instrument_name)) strcpy(instrument_name, McStasStruct.InstrName);
    if (!strlen(instrument_source)) strcpy(instrument_source, McStasStruct.Source);
    if (!siminfo_file) siminfo_init(NULL); /* open SIM file once */
  } else {
    if (!mcmergemode) i=mcdircount-1;
    else {
      for (i=0; i<mcdircount; i++)
        if (!strcmp(dirnames[i], McStasStruct.dirname)) break;
    }
    if (i >= mcdircount) {
        fprintf(stderr, "ERROR: unable to find directory '%s' in scanned list\n", McStasStruct.dirname);
        return(0);
    }
    if (!mcsimfiles[i]) {
      dirname      = McStasStruct.dirname;
      mcinstrnames[i]= str_dup(McStasStruct.InstrName);
      mcsources[i]   = str_dup(McStasStruct.Source);
      strncpy(instrument_name,     str_last_word(mcinstrnames[i]), CHAR_BUF_LENGTH);
      strncpy(instrument_source  , str_dup(mcsources[i]), CHAR_BUF_LENGTH);
      siminfo_init(NULL); /* open new SIM file in this dir for the first time */
      mcsimfiles[i]  = siminfo_file;
    } else siminfo_file = mcsimfiles[i];
    dirname = dirnames[i];
  }

/* transfer to global variables used in output functions */
  if (!McStasStruct.Date) mcstartdate = 0;
  else {
    mcstartdate         = atol(McStasStruct.Date);
    if (!mcstartdate) sscanf(McStasStruct.Date, "Simulation started %ld", &mcstartdate);
  }
  mcgravitation       = (McStasStruct.gravitation && strstr(McStasStruct.gravitation, "yes") ? 1 : 0);
  mcrun_num = McStasStruct.RunNum;
  mcncount  = McStasStruct.Ncount;
  strncpy(instrument_source, str_dup(McStasStruct.Source), CHAR_BUF_LENGTH);
  strncpy(instrument_name  , str_last_word(McStasStruct.InstrName), CHAR_BUF_LENGTH);
  /* transfer numipar */
  numipar = McStasStruct.mcnumipar;
  for (i=0; i<numipar; i++) {
    mcinputtable[i] = McStasStruct.mcinputtable[i];
  }
  dirname = McStasStruct.dirname;

  /* write data file from McStasStruct */
  if (mcverbose) printf("mcformat: Writing %s from %s\n", McStasStruct.outputname, McStasStruct.filename);

  if (strstr(McStasStruct.Format, "PGPLOT") && strstr(McStasStruct.type, "array_1d") && !mcdisable_output_files) {
    mcdetector_out_1D(McStasStruct.title, McStasStruct.xlabel, McStasStruct.ylabel,
                  McStasStruct.xvar, McStasStruct.x1, McStasStruct.x2, McStasStruct.m,
                  McStasStruct.p0, McStasStruct.p1, McStasStruct.p2, McStasStruct.outputname,
                  McStasStruct.component, McStasStruct.POSITION);
  } else if (!mcdisable_output_files)
  mcdetector_out_2D(McStasStruct.title,
    McStasStruct.xlabel, McStasStruct.ylabel,
    McStasStruct.x1, McStasStruct.x2, McStasStruct.y1, McStasStruct.y2,
    McStasStruct.m, McStasStruct.n,
    McStasStruct.p0,
    McStasStruct.p1,
    McStasStruct.p2,
    McStasStruct.outputname,
    McStasStruct.component,
    McStasStruct.POSITION);

  dirname = currentdir;
  return(1);
} /* end mcformat_output */

/*******************************************************************************
* mcformat_convert: recursive wrapper to the conversion routine (see K & R)
*                   returns number of processed files
*******************************************************************************/
int mcformat_convert(char *name)
{
  struct stat               stbuf;
  struct McStas_file_format McStasFile;
  int    ret=0;

  if (!name || !strlen(name)) return(0);

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "mcformat: can't access file %s\n", name);
    return 0;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) { /* dir: recursive call */
    char *upper_dir= dirname;
    char *name_win=name;
#ifdef WIN32
    if (isalpha(name[0]) && name[1] == ':') name_win += 2;  // skip Windows disk label before cat
#endif
    char *lower_dir= mcoutputdir ? str_cat(mcoutputdir, MC_PATHSEP_S, name_win, NULL)
                               : str_dup(name);
    /* entering new directory */
    if (!mcdisable_output_files) mcformat_usedir(lower_dir);
    else dirname = lower_dir;
    dirnames[mcdircount] = lower_dir;
    mcsimfiles[mcdircount] = NULL;
    mcinstrnames[mcdircount]=NULL;
    mcsources[mcdircount]   =NULL;
    mcdircount++; /* number of directories scanned */
    ret += mcformat_dirwalk(name, mcformat_convert);
    if (mcverbose) printf("mcformat: coming back to upper directory %s\n", upper_dir);
    dirname = upper_dir;
  } else {
    /* process the current file */
    if (mcverbose) printf("mcformat: reading %s (%ld bytes)\n", name, (long int)stbuf.st_size);
    McStasFile = mcformat_read_mcstas(name);

    if (!McStasFile.p1) {
      if (mcverbose) fprintf(stderr, "mcformat: warning: skipping %s (invalid format).\n", name);
      return 0;
    }

    if (!mcmergemode && !mcscanmode) { /* direct conversion */

      /* now calls the output routines: sim and data files (0d, 1d, 2d) and free */
      if (mcverbose) mcformat_print_mcstas_struct(McStasFile); fflush(stdout);
      if (mcformat_output(McStasFile))
        if (mcverbose) {
          printf("mcformat: converting %s (%ld bytes) ", name, (long int)stbuf.st_size);
          printf("into %s%s ", dirname ? dirname : ".", dirname ? MC_PATHSEP_S : "");
          if (mcdisable_output_files) printf(" (--test mode)\n"); else printf("\n");
        }

      mcformat_free_mcstas_struct(McStasFile);

    } else { /* store: merging of all files from either a scan or similar files */
      Files_to_Merge[mcnbconvert] = McStasFile; /* copy */
      mcnbconvert++; /* global index */
    }

    ret++; /* number of valid data files loaded from DIR */
  } /* end else single file */
  return (ret);
} /* end mcformat_convert */

/*******************************************************************************
* mcformat_count: count the number of files to store for merge mode
*******************************************************************************/
int mcformat_count(char *name)
{
  struct stat               stbuf;
  int    ret=0;

  if (!name || !strlen(name)) return(0);

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "mcformat: can't access file %s\n", name);
    return 0;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR) { /* recursive call */
    mcdircount++; /* number of directories scanned */
    ret += mcformat_dirwalk(name, mcformat_count);
  } else {
    ret++;
  }
  return (ret);
} /* end mcformat_count */

/*******************************************************************************
* mcformat_merge_compare: merge files and free the redundant items. Find scans.
*******************************************************************************/
int mcformat_merge_compare(int nb)
{
  int i,j,k;

  if (!Files_to_Merge) return(0);
  /* loop on Files_to_Merge */
  for (i=0; i<nb; i++) {
    struct McStas_file_format McStasStruct=Files_to_Merge[i];

    /* skip empty elements */
    if (!McStasStruct.p1) continue;

    /* we multiply the p1 and p2 by the Ncount so that the operations take
       into account the relative Ncount weight of each simulation. We will
       divide by the sum(Ncount) at the end of operation */
    if (!strstr(McStasStruct.Format, " list ")) /* NOT FOR LISTs (content non additive) */
    for (j=0; j<abs(McStasStruct.m*McStasStruct.n*McStasStruct.p); j++) {
      Files_to_Merge[i].p1[j] *= Files_to_Merge[i].Ncount;
      if (Files_to_Merge[i].p2) Files_to_Merge[i].p2[j] *= Files_to_Merge[i].Ncount;
    }

    /* second loop to search for similar items to add to Files_to_Merge[i] */
    for (j=i+1; j<nb; j++) {
      struct McStas_file_format ThisStruct=Files_to_Merge[j];
      if (!ThisStruct.p1) continue;

      /* Parameters check: mcinputtable.name and mcinputtable.val */
      /* flag_equiv_parname must be true  to go on */
      /* flag_equiv_parval  is      false if this is a SCAN item */
      char flag_equiv_parname = (ThisStruct.mcnumipar == McStasStruct.mcnumipar);
      char flag_equiv_parval  = flag_equiv_parname;
      if (flag_equiv_parname) {
        for (k=0; k<McStasStruct.mcnumipar; k++) {
          /* test if parameter names are the same */
          if (strcmp(ThisStruct.mcinputtable[k].name, McStasStruct.mcinputtable[k].name))
            { flag_equiv_parname=0; break; }
          if (strcmp(ThisStruct.mcinputtable[k].val, McStasStruct.mcinputtable[k].val))
            flag_equiv_parval=0;
        }
      }
      if (!flag_equiv_parname) continue;

      /* Data/List: must be of same kind */
      char flag_list = 0;
        if ( strstr(ThisStruct.Format, " list ")      &&  strstr(McStasStruct.Format, " list "))
          flag_list=1; /* two lists */
        else if (!strstr(ThisStruct.Format, " list ") && !strstr(McStasStruct.Format, " list "))
          flag_list=2; /* two monitors */
      if (!flag_list) continue;

      /* Data type check: dimension, limits, xvar, yvar, zvar, xlabel, ylabel, zlabel */
      /* limits may be forced (to avoid rounding errors) */
      /* number of rows may be different for lists */
      char flag_data = (
        (flag_list==1 || ThisStruct.m == McStasStruct.m) &&
        ThisStruct.n == McStasStruct.n &&
        ThisStruct.p == McStasStruct.p &&
        (!ThisStruct.xvar || !McStasStruct.xvar || !strcmp(ThisStruct.xvar, McStasStruct.xvar)) &&
        (!ThisStruct.yvar || !McStasStruct.yvar || !strcmp(ThisStruct.yvar, McStasStruct.yvar)) &&
        (!ThisStruct.zvar || !McStasStruct.zvar || !strcmp(ThisStruct.zvar, McStasStruct.zvar)) &&
        (!ThisStruct.xlabel || !McStasStruct.xlabel || !strcmp(ThisStruct.xlabel, McStasStruct.xlabel)) &&
        (!ThisStruct.ylabel || !McStasStruct.ylabel || !strcmp(ThisStruct.ylabel, McStasStruct.ylabel)) &&
        (!ThisStruct.zlabel || !McStasStruct.zlabel || !strcmp(ThisStruct.zlabel, McStasStruct.zlabel)) );
      if (!flag_data) continue;

      char flag_limits=(mcforcemode || mcscanmode ||
          (ThisStruct.n == 1 && ThisStruct.x1 == McStasStruct.x1) ||
          (ThisStruct.x1 == McStasStruct.x1 && ThisStruct.y1 == McStasStruct.y1)
          );
      if (!flag_limits)  {
        fprintf(stderr, "Warning: Axes limits are not identical for %s and %s. Skipping (use --force to override).\n",
          McStasStruct.filename, ThisStruct.filename);
        continue;
      }

      /* Warning if gravitation not constant (may be forced) */
      char flag_gravitation = mcforcemode || (
           ThisStruct.gravitation && McStasStruct.gravitation
        && !strcmp(ThisStruct.gravitation, McStasStruct.gravitation));
      if (!flag_gravitation && (ThisStruct.gravitation || McStasStruct.gravitation))
        fprintf(stderr, "Warning: Gravitation is not constant for %s and %s.\n",
          McStasStruct.filename, ThisStruct.filename);

      /* Names check: InstrName, Source and component */
      /* directories must be different except if mcmergesamedir */
      char flag_names = (
        (!ThisStruct.InstrName || !McStasStruct.InstrName
            || !strcmp(ThisStruct.InstrName, McStasStruct.InstrName)) &&
        (!ThisStruct.Source || !McStasStruct.Source
            || !strcmp(ThisStruct.Source, McStasStruct.Source)) &&
        (!ThisStruct.component || !McStasStruct.component
            || !strcmp(ThisStruct.component, McStasStruct.component)) &&
        (mcmergesamedir || !ThisStruct.dirname || !McStasStruct.dirname
            || strcmp(ThisStruct.dirname, McStasStruct.dirname)) );
      if (!flag_names) continue;

      /* handle scan index */
      if (!flag_equiv_parval) {
        /* attach index j to scan column origin monitor 'i' */
        if (Scans_to_merge[i] < 0) Scans_to_merge[i] = i;
        if (mcverbose && Scans_to_merge[j] < 0 && Scans_to_merge[i] >= 0) printf("  Gathering Scan step %s/%s (%d) with %s/%s (%d)\n",
          McStasStruct.dirname, McStasStruct.outputname, i,
          ThisStruct.dirname,  ThisStruct.outputname,    j);
        if (Scans_to_merge[j] < 0) Scans_to_merge[j] = i;
        /* next i if this is a scan (no add/cat) */
        continue; /* for j */
      }

      if (!mcmergemode) continue;

      if (mcverbose) fprintf(stderr,"  %s %s/%s (%d) with %s/%s (%d) total %ld elements\n",
        flag_list==2 ? "Adding" : "Appending",
        McStasStruct.dirname, McStasStruct.outputname, i,
        ThisStruct.dirname,  ThisStruct.outputname,    j,
        (long)abs(McStasStruct.m*McStasStruct.n*McStasStruct.p));

      if (flag_list==1) {  /* if list: catenate data j to end of i */
        /* allocate new array of size rows(i+j), same n,p */
        double *p1=mem(abs((ThisStruct.m+McStasStruct.m)*McStasStruct.n*McStasStruct.p)*sizeof(double));
        /* copy data from i */
        int index_i, index_j, index; /* data index is index_i*columns+index_j */
        for (index_i=0; index_i<abs(McStasStruct.m); index_i++)
          for (index_j=0; index_j<abs(McStasStruct.n*McStasStruct.p); index_j++) {
            index=index_i*abs(McStasStruct.n*McStasStruct.p)+index_j;
            p1[index] = McStasStruct.p1[index];
        }
        /* catenate data from j */
        for (index_i=0; index_i<abs(ThisStruct.m); index_i++)
          for (index_j=0; index_j<abs(McStasStruct.n*McStasStruct.p); index_j++) {
            int index_shifted=(index_i+abs(McStasStruct.m))*abs(McStasStruct.n*McStasStruct.p)+index_j;
            index=index_i*abs(McStasStruct.n*McStasStruct.p)+index_j;
            p1[index_shifted] = ThisStruct.p1[index];
        }
        Files_to_Merge[i].m += ThisStruct.m;
        /* free original arrays in i and j */
        memfree(McStasStruct.p1); memfree(ThisStruct.p1);
        Files_to_Merge[j].p1 = NULL;
        /* attach new array to i and leave j in empty state */
        Files_to_Merge[i].p1 = p1;
      } else { /* else add data i+j */
        int index_i;
        /* add data from j to i. p1 and p2 are weighted by their Ncount */
        for (index_i=0; index_i<abs(McStasStruct.m*McStasStruct.n*McStasStruct.p); index_i++) {
          if (McStasStruct.p0) Files_to_Merge[i].p0[index_i] += ThisStruct.p0[index_i];
                               Files_to_Merge[i].p1[index_i] += ThisStruct.Ncount*ThisStruct.p1[index_i];
          if (McStasStruct.p2) Files_to_Merge[i].p2[index_i] += ThisStruct.Ncount*ThisStruct.p2[index_i];

        }
        /* free and leave j in empty state */
        memfree(ThisStruct.p0); memfree(ThisStruct.p1); memfree(ThisStruct.p2);
        Files_to_Merge[j].p0=Files_to_Merge[j].p1=Files_to_Merge[j].p2=NULL;
      }
      Files_to_Merge[i].Ncount += ThisStruct.Ncount;
      Files_to_Merge[i].RunNum += ThisStruct.RunNum;
    } /* end for j */

    /* divide p1 and p2 by total Ncount to account for the weighted sum */
    if (!strstr(McStasStruct.Format, " list ")) /* NOT FOR LISTs (content non additive) */
    for (j=0; j<abs(McStasStruct.m*McStasStruct.n*McStasStruct.p); j++) {
      Files_to_Merge[i].p1[j] /= Files_to_Merge[i].Ncount;
      if (Files_to_Merge[i].p2) Files_to_Merge[i].p2[j] /= Files_to_Merge[i].Ncount;
    }

    /* now count integral values for item Files_to_Merge[i] */
    double Nsum=0, Psum=0, P2sum=0;
    for (j=0; j<abs(Files_to_Merge[i].m*Files_to_Merge[i].n*Files_to_Merge[i].p); j++) {
      double N=1,I=0,E=0;
      if (Files_to_Merge[i].p0) N = Files_to_Merge[i].p0[j];
      if (Files_to_Merge[i].p1) I = Files_to_Merge[i].p1[j];
      if (Files_to_Merge[i].p2) E = Files_to_Merge[i].p2[j];
      Nsum += N;
      Psum += I;
      P2sum += Files_to_Merge[i].p2 ? E : I*I;
    }
    Files_to_Merge[i].Nsum = Nsum;
    Files_to_Merge[i].Psum = Psum;
    Files_to_Merge[i].P2sum= P2sum;
  } /* end for i */
  return(nb);
} /* mcformat_merge_compare */

/* sorting functions for qsort: sort monitor files with distance */
#ifdef HAVE_QSORT
int sort_distances (const void *a, const void *b)
{
  const int *pa = (const int *) a;
  const int *pb = (const int *) b;
  int ia=*pa;
  int ib=*pb;
  double da=Files_to_Merge[ia].POSITION.x*Files_to_Merge[ia].POSITION.x
           +Files_to_Merge[ia].POSITION.y*Files_to_Merge[ia].POSITION.y
           +Files_to_Merge[ia].POSITION.z*Files_to_Merge[ia].POSITION.z;
  double db=Files_to_Merge[ib].POSITION.x*Files_to_Merge[ib].POSITION.x
           +Files_to_Merge[ib].POSITION.y*Files_to_Merge[ib].POSITION.y
           +Files_to_Merge[ib].POSITION.z*Files_to_Merge[ib].POSITION.z;
  if       (da > db) return 1;
  else if (da < db) return -1;
  else /* same distance, sort on names */
  return strcmp(Files_to_Merge[ia].filename, Files_to_Merge[ib].filename);
}

/* sorting functions for qsort: sort monitor column with ipar.val */
int sort_ipar_mon (const void *a, const void *b)
{
  const int *pa = (const int *) a;
  const int *pb = (const int *) b;
  int ia=*pa;
  int ib=*pb;
  double da=Files_to_Merge[ia].mcinputtable[ipar_var].type == instr_type_string ?
    0 : atof(Files_to_Merge[ia].mcinputtable[ipar_var].val);
  double db=Files_to_Merge[ib].mcinputtable[ipar_var].type == instr_type_string ?
    0 : atof(Files_to_Merge[ib].mcinputtable[ipar_var].val);
  if       (da > db) return 1;
  else if (da < db) return -1;
  else {/* same distance, sort on ipar value then filenames */
   int tmp=strcmp(Files_to_Merge[ia].mcinputtable[ipar_var].val,
                  Files_to_Merge[ib].mcinputtable[ipar_var].val);
   if (tmp) return(tmp);
   else return strcmp(Files_to_Merge[ia].filename, Files_to_Merge[ib].filename);
  }
}
#endif

/*********************************************************************
* mcformat_scan_compare: assemble scanned monitors into multiarray sets
*                        warning: this function is a real headache
*********************************************************************/
void mcformat_scan_compare(int nb)
{
  /* definition of a scan
    Must be 'mergeable' data but with different ipar values
    Each Scans_to_merge[] index set is a column of multiarray_1d (this is a scanned monitor)
    Must analyse scan columns (Scans_to_merge[]) to gather them with
      -common ipar names (set of scanned monitors)
      -same set (monitor number) length and monitor names
      -same ipar values define rows
   */
  int scan_index1=0;
  int i=0,j;

  /* test if there is scan data to be processed */
  for (scan_index1=0; scan_index1<nb; scan_index1++) {
    if (Scans_to_merge[scan_index1] < 0 || Scans_to_merge[scan_index1] < scan_index1) continue;
    else { i=1; break; }
  }

  if (i == 0)
    fprintf(stderr, "Warning: Could not find scanned parameter within 'Param' lines in data file headers.\n"
          "Ignoring [mcformat:mcformat_scan_compare].\n");

  /* loop on Scans_to_merge: index > -1  */
  for (scan_index1=0; scan_index1<nb; scan_index1++) {
    if (Scans_to_merge[scan_index1] < 0 || Scans_to_merge[scan_index1] < scan_index1) continue;
    /* get all sets of given index: Scans_to_merge[j] = index */
    int scan_length1= 1;
    int next_in_scan=-1;
    ipar_var        = 0; /* global variable, as it is used in sorting function 'sort_ipar_mon' */
    int scan_index2;
    /* compute length of monitor column (length of scan): scan_length1 */
    for (scan_index2=scan_index1+1; scan_index2<nb; scan_index2++)
      if (Scans_to_merge[scan_index1] == Scans_to_merge[scan_index2]) {
        scan_length1++;
        if (next_in_scan < 0) next_in_scan = scan_index2;
      }
    if (scan_length1 <= 1) continue; /* not a scan, single data set: go to next data file */

    /* count other monitors in Scans_to_merge with same ipar names and values: mon_count */
    int mon_count=0;
    int Scan_columns[nb];
    for (scan_index2=0; scan_index2<nb; Scan_columns[scan_index2++]=-1);

    for (scan_index2=0; scan_index2<nb; scan_index2++) {
      char flag_matchpar=0;
      if (scan_index1 == scan_index2) {
        mon_count++; Scan_columns[scan_index2] = scan_index1; continue;
      }
      /* must be a scan */
      if (Scans_to_merge[scan_index2] < 0) continue; /* scan_index2 */
      /* must have same numipar */
      if (Files_to_Merge[scan_index1].mcnumipar != Files_to_Merge[scan_index2].mcnumipar) continue; /* scan_index2 */
      /* must have same scan length as first monitor */
      int scan_length2= 0;
      for (j=scan_index2; j<nb; j++)
        if (Scans_to_merge[scan_index2] == Scans_to_merge[j]) {
          scan_length2++;
        }
      if (scan_length1 != scan_length2) continue; /* scan_index2 */
      /* must have same ipar.name and values along column */
      int ipar2;
      for (ipar2=0; ipar2<Files_to_Merge[scan_index2].mcnumipar; ipar2++) {
        char *this_parname = Files_to_Merge[scan_index2].mcinputtable[ipar2].name;
        char *this_parval  = Files_to_Merge[scan_index2].mcinputtable[ipar2].val;
        /* look back into 'scan_index1' series for similar parameters */
        for(j=scan_index1; j<nb; j++) {
          if (Scans_to_merge[j] == Scans_to_merge[scan_index1]) {
            /* in original column, look if we can find ipar */
            int ipar1;
            for (ipar1=0; ipar1<Files_to_Merge[j].mcnumipar; ipar1++) {
              if (strcmp(Files_to_Merge[j].mcinputtable[ipar1].name, this_parname)
               || strcmp(Files_to_Merge[j].mcinputtable[ipar1].val,  this_parval) ) continue; /* ipar1 */
              flag_matchpar=1;
              break;
            } /* for ipar1 */
            if (flag_matchpar) break; /* j: we found matching ipar both in scan_index1 and scan_index2 */
          } /* if */
        } /* for scan_index1b */
        if (!flag_matchpar) break; /* ipar2: ipar of scan_index2 not found in scan_index1 */
      } /* for ipar2 */
      if (!flag_matchpar) continue; /* scan_index2: an ipar of scan_index2 was not found in scan_index1. try other scan_index2 */
      else {
        mon_count++;
        /* attach that file to first monitor of dir/column */
        Scan_columns[scan_index2] = scan_index2;
      }
    } /* for scan_index2 */

    /* get first varying ipar: ipar_var */
    for (j=0; j<Files_to_Merge[scan_index1].mcnumipar; j++) {
      /* compare ipar value of scan_index1 and next_in_scan: stored in j */
      if (strcmp(Files_to_Merge[scan_index1].mcinputtable[j].val, Files_to_Merge[next_in_scan].mcinputtable[j].val)) break;
    }
    /* test if ipar has changed in scan else go to next data file */
    if (j < Files_to_Merge[scan_index1].mcnumipar) ipar_var=j;
    /* now we know how many scanned monitor there are */

    if (mcverbose)
      printf("scan from %s has %d rows (scan steps) of %d columns (monitors) varying %s\n",
        Files_to_Merge[scan_index1].filename, scan_length1, mon_count,
        Files_to_Merge[scan_index1].mcinputtable[ipar_var].name);

    /* single Scan_columns[] is an unsorted row
      and have same ipar name/value in same dir/row */

    /* single Scans_to_merge[i] value is an unsorted column
      and have same name in different directories/columns
      but different ipar values */

    /* allocate array: scan_length1(rows)*(numipar+2*mon_count) */
    t_Table Scan;
    if (!Table_Init(&Scan,
      scan_length1,
      Files_to_Merge[scan_index1].mcnumipar+2*mon_count)) {
      fprintf(stderr, "Warning: %s: Can not allocate Scan %ix(%i+2*%i) multiarray_1d. Skipping.\n",
          Files_to_Merge[scan_index1].filename, scan_length1,
          Files_to_Merge[scan_index1].mcnumipar,
          mon_count);
      continue;
    }
    char *header=(char*)mem(64*CHAR_BUF_LENGTH); strcpy(header, "");
    char *youts =(char*)mem(64*CHAR_BUF_LENGTH); strcpy(youts,  "");
    double ipar_min=FLT_MAX, ipar_max=0;

    /* we first sort Scan_columns(monitors) with distance */
    int Scan_distances[mon_count];  /* this is column index */
    j = 0;

    for (scan_index2=0; scan_index2<nb; scan_index2++)
      if (Scan_columns[scan_index2]>=0) Scan_distances[j++] = Scan_columns[scan_index2];
#ifdef HAVE_QSORT
    qsort(Scan_distances, mon_count, sizeof(int), sort_distances);
#endif
    for (j=0; j<mon_count; j++) { /* loop for each column */
      int Monitor_column[scan_length1];
      int k=0;
      for (i=0; i<scan_length1; Monitor_column[i]=i) { i++; }
      for (scan_index2=0; scan_index2<nb; scan_index2++) {
        /* find Scan_distances[j] in Scans_to_merge */
        if (Scans_to_merge[scan_index2] >= 0 && Scans_to_merge[scan_index2] == Scan_distances[j]) {
          Monitor_column[k++] = scan_index2;
          Scans_to_merge[scan_index2]=-1; /*inactivate that scan element */
        }
      }
      /* sort each monitor column with ipar value */
#ifdef HAVE_QSORT
      qsort(Monitor_column, scan_length1, sizeof(int), sort_ipar_mon);
#endif
      /* extract sorted column and set Scan */
      for (i=0; i<scan_length1; i++) { /* loop on column elements(row) */
        Table_SetElement(&Scan,
          i,
          Files_to_Merge[scan_index1].mcnumipar+2*j,
          Files_to_Merge[Monitor_column[i]].Psum);
        Table_SetElement(&Scan,
          i, Files_to_Merge[scan_index1].mcnumipar+2*j+1,
          mcestimate_error(
            Files_to_Merge[Monitor_column[i]].Ncount,
            Files_to_Merge[Monitor_column[i]].Psum,
            Files_to_Merge[Monitor_column[i]].P2sum));
        if (j==0) { /* first monitor in row also sets ipar */
          for (k=0; k<Files_to_Merge[Monitor_column[i]].mcnumipar; k++) {
            Table_SetElement(&Scan,
              i, k,
              atof(Files_to_Merge[Monitor_column[i]].mcinputtable[k].val));
            /* set name of ipar */
            if (i==0) {
              strcat(header, Files_to_Merge[Monitor_column[i]].mcinputtable[k].name);
              strcat(header, " ");
            }
          }
        } /* if j==0 */
        double this=atof(Files_to_Merge[Monitor_column[i]].mcinputtable[ipar_var].val);
        if (ipar_min > this) ipar_min=this;
        if (ipar_max < this) ipar_max=this;
      } /* for i */
      strcat(header, Files_to_Merge[Scan_distances[j]].outputname); strcat(header, "_I ");
      strcat(header, Files_to_Merge[Scan_distances[j]].outputname); strcat(header, "_ERR ");
      strcat(youts, "("); strcat(youts, Files_to_Merge[Scan_distances[j]].outputname); strcat(youts, "_I,");
      strcat(youts, Files_to_Merge[Scan_distances[j]].outputname); strcat(youts, "_ERR) ");
    } /* for j */
    Scan.header=header;

    Scans_to_merge[scan_index1]=-1; /* inactivate that scan element */

    char *title=str_cat("Scan of ",
      Files_to_Merge[scan_index1].mcinputtable[ipar_var].name, NULL);
    /* output scan multiarray */
    /* for PGPLOT: open mcstas.sim */
    if (strcasestr(mcformat, "McCode")) siminfo_init(NULL); /* open new SIM file in this dir for the first time */
    else siminfo_name=NULL;
    char *datfile=NULL;
    if (!datfile) datfile = str_cat("mcstas.", "dat", NULL);
    strcat(mcformat, " scan ");
    if (mcverbose)
      printf("Writing scan file=%s (%s) into directory %s: %s=%g:%g\n",
        datfile, siminfo_name, dirname,
        Files_to_Merge[scan_index1].mcinputtable[ipar_var].name, ipar_min, ipar_max);
    strcpy(instrument_name,   Files_to_Merge[scan_index1].InstrName);
    strcpy(instrument_source, Files_to_Merge[scan_index1].Source);
    if (!mcdisable_output_files)
    mcdetector_out_2D(title,
      Files_to_Merge[scan_index1].mcinputtable[ipar_var].name,
      Files_to_Merge[scan_index1].ylabel,
      ipar_min, ipar_max, 0, 0,
      -scan_length1, Files_to_Merge[scan_index1].mcnumipar+2*mon_count,
      NULL, Scan.data, NULL, datfile,
      Files_to_Merge[scan_index1].component,
      Files_to_Merge[scan_index1].POSITION);

    /* for PGPLOT: close mcstas.sim */
    if (strstr(mcformat, "McCode")) siminfo_close();
    Table_Free(&Scan);
    memfree(datfile);
    memfree(youts);
    memfree(title);
    /* go to end of scan and continue to search for scans */
  } /* for scan_index1 */
} /*  mcformat_scan_compare */

/*******************************************************************************
* mcformat_merge_output: output non empty files
*                        special handling for multiarray/scans
*******************************************************************************/
int mcformat_merge_output(int nb)
{
  int i;
  char mcdisable_output_files_sav=mcdisable_output_files;
  if (mcscanmode == 2) mcdisable_output_files=1; /* scan only will skip writing for non scan files */
  /* output files for non empty elements */
  for (i=0; i<nb; i++) {
    if (mcformat_output(Files_to_Merge[i])) {
      if (mcverbose) {
        printf("mcformat: merging/scanning %s ", Files_to_Merge[i].outputname);
        printf("into %s%s ",
          Files_to_Merge[i].dirname ? Files_to_Merge[i].dirname : ".",
          Files_to_Merge[i].dirname ? MC_PATHSEP_S : "");
        if (mcdisable_output_files) printf(" (--test or --scan-only mode)\n"); else printf("\n");
      }
    }
  }
  mcdisable_output_files = mcdisable_output_files_sav;

  if (mcscanmode) {
  /* build and output scans (if any) for non empty elements of same index */
  mcformat_scan_compare(nb);
  /* allocate nb_scan rows of nb_vars+(nb_monitors*3) columns */
  /* fill in scan variables extracted from mcinputtable */
  /* fill in monitor values */
  /* call outout routine for scans (can not be binary format): from mcrun.pl */
  }

  /* free merged/scan elements */
  for (i=0; i<nb; i++) mcformat_free_mcstas_struct(Files_to_Merge[i]);
  return(nb);
}

/*******************************************************************************
* mcformat_usage: print mcformat usage/help
*******************************************************************************/
void mcformat_usage(char *pgmname)
{
  int i;

  fprintf(stderr, "%s version %s format conversion tool (" MCCODE_STRING ")\n", pgmname, MCFORMAT);
  fprintf(stderr, "Usage: %s [options] file1|dir1 file2|dir2 ...\n", pgmname);
  fprintf(stderr,
"Convert/merge files and directories from McStas format to an other specified format\n"
"Options are:\n"
"  -d DIR    --dir=DIR        Put all data files in directory DIR.\n"
"  -f FILE   --file=FILE      Put all data in a single file.\n"
"  --no-output-files          Do not write any data files (test data).\n"
"  -h        --help           Show this help message.\n"
"  -p FORMAT --format=FORMAT  Output data files using format FORMAT\n"
"  -c        --force          Force writting in existing directories\n"
"  -t        --test           Test mode, does not write files\n"
"  -m        --merge          Add/Append equivalent data files and lists\n"
"            --merge-samedir  Merges inside same directories (dangerous)\n"
"  -s        --scan           Gather simulations per scan series\n"
"  -so       --scan-only      Create scan series but does not merge data\n"
"            --verbose        Verbose mode\n"
"\n"
"Examples:\n"
"mcformat -d target_dir original_dir\n"
"  # using default target format %s\n"
"mcformat -d target_dir original_dir --format=target_format\n"
"mcformat -d target_dir original_dir1 original_dir2 --merge\n"
"  # merge simulation data sets (grids)\n"
"mcformat -d target_dir dir1 dir2 ... --scan\n"
"  # merge scan data sets\n\n",
getenv(FLAVOR_UPPER "_FORMAT") ? getenv(FLAVOR_UPPER "_FORMAT") : "MCCODE");

  fprintf(stderr, "Available output formats are (default is %s):\n  ", mcformat);
  fprintf(stderr, "\n  Format modifiers: FORMAT may be followed by 'binary float' or \n");
  fprintf(stderr, "  'binary double' to save data blocks as binary. This removes text headers.\n");
  fprintf(stderr, "  The " FLAVOR_UPPER "_FORMAT environment variable may set the default FORMAT to use.\n");
} /* mcformat_usage */

/*******************************************************************************
* mcformat_parseoptions: parse command line parameters
*******************************************************************************/
void
mcformat_parseoptions(int argc, char *argv[])
{
  int i;
  char cwd[CHAR_BUF_LENGTH];
  dirname = NULL;
  for(i = 1; i < argc; i++)
  {
    if(!strcmp("-d", argv[i]) && (i + 1) < argc)
      mcformat_usedir(argv[++i]);
    else if(!strncmp("-d", argv[i], 2))
      mcformat_usedir(&argv[i][2]);
    else if(!strcmp("--dir", argv[i]) && (i + 1) < argc)
      mcformat_usedir(argv[++i]);
    else if(!strncmp("--dir=", argv[i], 6))
      mcformat_usedir(&argv[i][6]);
    else if(!strcmp("-h", argv[i]) || !strcmp("--help", argv[i]))
    {  mcformat_usage(argv[0]); exit(0); }
    else if(!strcmp("-v", argv[i]) || !strcmp("--version", argv[i]))
    {  fprintf(stderr, "mcformat version %s format conversion tool (" MCCODE_STRING ")\n", MCFORMAT); exit(-1); }
    else if(!strcmp("-c", argv[i]))
      mcforcemode = 1;
    else if(!strcmp("--force", argv[i]))
      mcforcemode = 1;
    else if(!strncmp("--format=", argv[i], 9)) {
      mcformat=&argv[i][9];
    }
    else if(!strcmp("--format", argv[i]) && (i + 1) < argc) {
      mcformat=argv[++i];
    }
    else if(!strcmp("--no-output-files", argv[i]))
      mcdisable_output_files = 1;
    else if(!strcmp("--verbose", argv[i]))
      mcverbose  = 1;
    else if(!strcmp("-t", argv[i]) || !strcmp("--test", argv[i]))
      mcdisable_output_files = 1;
    else if(!strcmp("-m", argv[i]) || !strcmp("--merge", argv[i]))
      mcmergemode= 1;
    else if(!strcmp("-s", argv[i]) || !strcmp("--scan", argv[i]))
      mcscanmode = 1;
    else if(!strcmp("-so", argv[i]) || !strcmp("--scan-only", argv[i]))
      mcscanmode = 2;
    else if(!strcmp("--merge-samedir", argv[i]))
      mcmergesamedir=mcmergemode=1;
    else {
      /* convert argv[i]: store index of argument */
      if (files_to_convert_NB <CHAR_BUF_LENGTH)
        files_to_convert_Array[files_to_convert_NB++] = i;
      else
        fprintf(stderr, "Warning: Exceeding maximum number of files to process (%d).\n"
          "Ignoring %s [mcformat:mcformat_parseoptions].\n",
          CHAR_BUF_LENGTH, argv[i]);
    }
  }

  if (!dirname) {
    getcwd(cwd, CHAR_BUF_LENGTH);
    dirname = str_dup(cwd); /* default is to export to PWD */
  }
} /* mcformat_parseoptions */

/*******************************************************************************
* main: program entry point (start):calls parseoptions, convert and merge
*******************************************************************************/
int main(int argc, char *argv[])
{
  time_t t;
  int j;

#ifdef MAC
  argc = ccommand(&argv);
#endif

  t = (time_t)mcstartdate;
  time(&t);
  mcstartdate = t;
  mcformat=getenv(FLAVOR_UPPER "_FORMAT") ?
           getenv(FLAVOR_UPPER "_FORMAT") : "MCCODE";
  /* default is to output as McCode format */

  /* parse parameters from the command line and get files to convert */
  mcformat_parseoptions(argc, argv);

  if (!files_to_convert_NB) {  mcformat_usage(argv[0]); exit(-1); }

  /* check format */
  if (!mcformat || !strlen(mcformat)
   || !strcasecmp(mcformat, "McStas") || !strcasecmp(mcformat, "McXtrace")
   || !strcasecmp(mcformat, "PGPLOT"))
    mcformat = "MCCODE";

  mcnbconvert = mcdircount = 0;
  mcoutputdir = dirname; /* base output dir */

  /* count the number of files to store */
  for(j = 0; j < files_to_convert_NB; j++) {
    int    i;
    i = files_to_convert_Array[j]; /* does the job for each file/dir */
    mcnbconvert += mcformat_count(argv[i]);
  }
  if (mcdircount) { /* allocate list of directories amd FILE handles */
    dirnames  = (char**)mem(mcdircount*sizeof(char*));
    mcsimfiles  = (FILE**)mem(mcdircount*sizeof(FILE*));
    mcinstrnames= (char**)mem(mcdircount*sizeof(char*));
    mcsources   = (char**)mem(mcdircount*sizeof(char*));
  }
  if (mcmergemode || mcscanmode) {
    printf("mcformat: Will process and merge/scan %d data file%s in %d director%s.\n",
      mcnbconvert, mcnbconvert > 1 ? "s" : "", mcdircount, mcdircount > 1 ? "ies" : "y");
    /* allocate array of Original file structures */
    Files_to_Merge = mem(mcnbconvert*sizeof(struct McStas_file_format));
    Scans_to_merge = mem(mcnbconvert*sizeof(int));
    for (j=0; j<mcnbconvert; j++) {
      Files_to_Merge[j] = mcformat_init_mcstas_struct();
      Scans_to_merge[j] = -1;
    }

  }
  mcnbconvert = mcdircount = 0;

  strcpy(instrument_source, "");
  strcpy(instrument_name  , "");

  /* calls the conversion routine. SIM file opened at first conversion in mcformat_convert */
  for(j = 0; j < files_to_convert_NB; j++) {
    int    i;
    i = files_to_convert_Array[j]; /* does the job for each file/dir */
    mcformat_convert(argv[i]);
  }

  if (mcmergemode || mcscanmode) {
    /* call to merging routine (free some Files_to_Merge elements) */
    mcformat_merge_compare(mcnbconvert);
    /* iterative call to output routine for remaining elements of Files_to_Merge */
    mcformat_merge_output(mcnbconvert);
    if (Files_to_Merge) memfree(Files_to_Merge);
    if (Scans_to_merge) memfree(Scans_to_merge);
  }

  /* clean up: close all SIM files */
  if (!mcdisable_output_files) {
    if (!mcdircount) siminfo_close();
    else {
      for (j=0; j<mcdircount; j++) {
        if (mcsimfiles[j]) {
          dirname = dirnames[j];
          siminfo_file     = mcsimfiles[j];
          strncpy(instrument_source, str_last_word(mcinstrnames[j]), CHAR_BUF_LENGTH);
          strncpy(instrument_name  , str_last_word(mcsources[j]), CHAR_BUF_LENGTH);
          siminfo_close();
          mcsimfiles[j] = NULL;
          memfree(mcinstrnames[j]);
          memfree(mcsources[j]);
          memfree(dirnames[j]);
        }
      }
      memfree(dirnames);
      memfree(mcsimfiles);
      memfree(mcinstrnames);
      memfree(mcsources);
    }
  }

  return mcnbconvert; /* number of converted files */

} /* main */


#endif
