#ifndef __MCCEXP_H__
#define __MCCEXP_H__



/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright 1997-2002, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Kernel: cexp.c
*
* %Identification
* Written by: K.N.
* Date: Aug  7, 1997
* Origin: Risoe
* Release: McStas 1.6
* Version: $Revision$
*
* Handle expressions used as arguments to components etc.
*
*******************************************************************************/

#include <stdarg.h>
#include <stdio.h>



/*******************************************************************************
* Definitions for cexp.c
*******************************************************************************/

/* Type for expressions. The implementation is private and values of this type
   must only be accessed through the proper function calls. */
typedef struct cexp *CExp;

/* Extern functions defined in cexp.c */
CExp exp_id(char *id);    /* Make normal identifier. */
CExp exp_extern_id(char *id); /* Make extern identifier. */
CExp exp_number(char *n); /* Make expression from number. */
CExp exp_string(char *s); /* Make expression from string. */
CExp exp_ctoken(char *s); /* Make expression from generic C token */
CExp exp_compound(int n, ...);  /* Make compound expression */
void exp_free(CExp e);    /* Free memory for expression */
char *exp_tostring(CExp e); /* Convert expression to string. */
void exp_fprint(FILE *f, CExp e); /* Output an expression to file. */
int exp_isvalue(CExp e);  /* Ask if expression is a value. */
void exp_setlineno(CExp e, int n); /* Set line number of expression */
int exp_getlineno(CExp e);  /* Get line number of expression, or zero */



/* The internal structure implementing a C expression. */
struct cexp
  {
    char *s;		    /* String representation */
    int isvalue;	    /* True if identifier or string/number constant */
    int lineno;		    /* Starting line number, or zero */
  };

/* Create an expression from a string representing a value (either identifier,
   constant number, or constant string). */
static CExp
mkvalueexp(char *s)
{
  CExp e;
  e = (CExp) palloc(e);
  e->s = s;
  e->isvalue = 1;
  e->lineno = 0;		/* Initially no line number set */
  return e;
}

/* Create an expression from a string not representing a value. */
static CExp
mknonvalueexp(char *s)
{
  CExp e;
  e = (CExp) palloc(e);
  e->s = s;
  e->isvalue = 0;
  e->lineno = 0;		/* Initially no line number set */
  return e;
}

/*******************************************************************************
* Handle identifiers used as arguments to components.
* There are two types of identifiers: normal and extern. Normal identifiers
* refer to formal arguments of the instrument, and are always of type
* double. These can be varied eg. to perform a scan. Extern identifiers refer
* to user-supplied C identifiers that is typically put in the declaration and
* initialization sections of the instrument definition.
*
* The final version will distinguish (using a union) between these two types,
* and will maintain a mapping from formal parameters of the instrument to
* generated names in the generated simulation (the extern names must be
* copied unchanged). But in this first version a simpler scheme is used: all
* identifier expressions are simply strings, and all normal identifiers refer
* to instrument parameters.
*******************************************************************************/

CExp
exp_id(char *id)  /* used in e.g. cogen:cogen_comp_init_par AND splits*/
{
  return mkvalueexp(str_cat( (char*) "_instrument_var._parameters.", id, NULL));
}

CExp
exp_extern_id(char *id)
{
  return mkvalueexp(str_dup(id));
}

CExp
exp_number(char *n)
{
  return mkvalueexp(str_dup(n));
}

CExp
exp_string(char *s)
{
  char *quoted, *result;
  quoted = str_quote(s);
  result =  str_cat((char*) "\"", s, (char*) "\"", NULL);
  str_free(quoted);
  return mkvalueexp(result);
}

CExp
exp_ctoken(char *s)
{
  return mknonvalueexp(str_dup(s));
}

CExp
exp_compound(int n, ...)
{
  char *result, *snew;
  CExp e;
  va_list ap;
  char *separator = (char*) "";		/* Token separator, initially empty */

  va_start(ap, n);
  result = str_dup((char*) "");
  while(n-- > 0)
  {
    e = va_arg(ap, CExp);
    snew = str_cat(result, separator, e->s, NULL);
    str_free(result);
    result = snew;
    separator = (char*) " ";		/* Now use space separator for rest. */
  }
  return mknonvalueexp(result);
}

void
exp_free(CExp e)
{
  str_free(e->s);
  memfree(e);
}


char *
exp_tostring(CExp e)
{
  char *s = e->s;
  if(s == NULL)
  {
    assert(1 == 0 && "they said this was bad");
    /*
    s = "";
    debugn((DEBUG_HIGH, "exp_tostring(): NULL cexp received.\n"));
    */
  }
  return str_dup(s);
}

void
exp_fprint(FILE *f, CExp e)
{
  fputs(e->s, f);
}

int
exp_isvalue(CExp e)
{
  return e->isvalue;
}

void
exp_setlineno(CExp e, int n)
{
  e->lineno = n;
}

int
exp_getlineno(CExp e)
{
  return e->lineno;
}


#endif