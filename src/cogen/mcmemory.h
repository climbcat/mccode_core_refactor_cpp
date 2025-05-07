#ifndef __MC_MEMORY_H__
#define __MC_MEMORY_H__


/*******************************************************************************
*
* McStas, neutron ray-tracing package
*         Copyright (C) 1997-2009, All rights reserved
*         Risoe National Laboratory, Roskilde, Denmark
*         Institut Laue Langevin, Grenoble, France
*
* Kernel: memory.c
*
* %Identification
* Written by: K.N.
* Date: Jul  1, 1997
* Origin: Risoe
* Release: McStas CVS_090504
* Version: $Revision$
*
* Memory management functions.
*
*       $Id$
*
*******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>



/* Abstract data type for lists. */
typedef struct List_header *List;
typedef struct List_position *List_handle;

List list_create(void);             /* Create list. */
void list_add(List, void *);        /* Add element at end. */
void* list_access(List, int);       /* Get element in list. */
void list_free(List, void (*)(void *)); /* Deallocate a list. */
int list_len(List l);               /* Get list length. */
List_handle list_iterate(List);     /* Prepare to traverse list. */
List_handle list_iterate_back(List);     /* Prepare to traverse list. */
void *list_next(List_handle);       /* Get next element in list. */
void *list_previous(List_handle);       /* Get previous element in list. */
void list_iterate_end(List_handle); /* End list traversal. */
int list_undef(List l);
List list_cat(List l1, List l2);
List list_copy(List, void * (*)(void *));





/*******************************************************************************
* Functions defined in memory.c
*******************************************************************************/

typedef struct Pool_header *Pool;

void *mem(size_t);        /* Allocate memory. */
void memfree(void *);     /* Free memory. */
char *str_dup(char *);    /* Allocate new copy of string. */
char *str_dup_n(char *string, int n); /* Copies only first N chars. */
char *str_cat(char *first, ...);/* Concatenate strings to allocated string. */
char *str_quote(char *string);  /* Quote string for inclusion in C code */
void str_free(char *);    /* Free memory for string. */

Pool pool_create(void);   /* Create pool. */
void pool_free(Pool p);   /* Free pool and associated memory. */
void *pool_mem(Pool p, size_t size); /* Allocate memory in pool. */


/* Allocate memory to a pointer. If p is a pointer to type t, palloc(p) will
   make p point to dynamically allocated memory for one element of type
   t. Used to dynamicaaly allocate structures, eg.
   `struct S *p; palloc(p);'. */

// TODO: fix every instance of memory allocation macro usage
//#define palloc(p) ((p) = mem( sizeof(*(p))) )
#define palloc(p) (mem( sizeof(*(p)) ))


/* Allocate an array to a pointer. If p is a pointer to type t, nalloc(p, n)
   will make p point to a dynamically allocated array with n elements of type
   t. */

// TODO: fix every instance of memory allocation macro usage
//#define nalloc(p, n) ((p) = mem( (n)*sizeof(*(p))) )
#define nalloc(p, n) (mem( (n)*sizeof(*(p)) ))


// TODO: deal with these
#define fatal_error printf
#define debug printf




/*******************************************************************************
* Allocate memory. This function never returns NULL; instead, the
* program is aborted if insufficient memory is available.
*******************************************************************************/
void *
mem(size_t size)
{
    void *p = calloc(1, size);    /* Allocate and clear memory. */
    if(p == NULL) fatal_error("memory exhausted during allocation of size %ld.", (long)size);
    return p;
}

/*******************************************************************************
* Free memory allocated with mem().
*******************************************************************************/
void memfree(void *p)
{
  if(p == NULL)
    debug(("memfree(): freeing NULL memory.\n"));
  else
    free(p);
}

/*******************************************************************************
* Allocate a new copy of a string.
*******************************************************************************/
char *
str_dup(char *string)
{
  if (string == NULL) {
    return NULL;
  }

  char *s;

  s = (char*) mem(strlen(string) + 1);
  strcpy(s, string);
  return s;
}


/*******************************************************************************
* Allocate a new copy of initial N chars in a string.
*******************************************************************************/
char *
str_dup_n(char *string, int n)
{
  char *s;

  s = (char*) mem(n + 1);
  strncpy(s, string, n);
  s[n] = '\0';
  return s;
}


/*******************************************************************************
* Allocate a new string to hold the concatenation of given strings. Arguments
* are the strings to concatenate, terminated by NULL.
*******************************************************************************/
char *
str_cat(char *first, ...)
{
  char *s;
  va_list ap;
  int size;
  char *arg;

  size = 1;                     /* Count final '\0'. */
  va_start(ap, first);
  for(arg = first; arg != NULL; arg = va_arg(ap, char *))
    size += strlen(arg);        /* Calculate string size. */
  va_end(ap);
  s = (char*) mem(size);
  size = 0;
  va_start(ap, first);
  for(arg = first; arg != NULL; arg = va_arg(ap, char *))
  {
    strcpy(&(s[size]), arg);
    size += strlen(arg);
  }
  va_end(ap);
  return s;
}

/*******************************************************************************
* Allocate a new string holding the result of quoting the input string. The
* result is suitable for inclusion in C source code.
*******************************************************************************/
char *
str_quote(char *string)
{
  char *badchars = (char*) "\\\"\r\n\t";
  char *quotechars = (char*) "\\\"rnt";
  char *q=NULL, *res=NULL, *ptr;
  int len, pass;
  int c;
  char snew[5];

  /* Loop over the string twice, first counting chars and afterwards copying
     them into an allocated buffer. */
  for(pass = 0; pass < 2; pass++)
  {
    char *p = string;

    if(pass == 0)
      len = 0;                  /* Prepare to compute length */
    else
      q = res = (char*) mem(len + 1);   /* Allocate buffer */
    /* Notice the cast to unsigned char; without it, the isprint(c) below will
       fail for characters with negative plain char values. */
    while((c = (unsigned char)(*p++)))
    {
      ptr = strchr(badchars, c);
      if(ptr != NULL)
        sprintf(snew, "\\%c", quotechars[ptr - badchars]);
      else if(isprint(c))
        sprintf(snew, "%c", c);
      else
        sprintf(snew, "\\%03o", c);
      if(pass == 0)
        len += strlen(snew);     /* Count in length */
      else
        for(ptr = snew; (*q = *ptr) != 0; ptr++)
          q++;                  /* Copy over chars */
    }
  }
  return res;
}


/*******************************************************************************
* Free memory for a string.
*******************************************************************************/
void
str_free(char *string)
{
  memfree(string);
}


// TODO: ???
//#ifndef MCFORMAT

struct Pool_header
  {
    List list;
  };

/*******************************************************************************
* Create a pool in which to allocate memory that may be easily freed all at a
* time by freeing the pool.
*******************************************************************************/
Pool
pool_create(void)
{
  Pool p;

  p = (Pool) palloc(p);
  p->list = list_create();
  return p;
}

/*******************************************************************************
* Deallocate a pool as well as all memory allocated within it.
*******************************************************************************/
void
pool_free(Pool p)
{
  List_handle liter;
  void *mem;

  liter = list_iterate(p->list);
  while((mem = list_next(liter)))
  {
    memfree(mem);
  }
  list_iterate_end(liter);

  memfree(p);
  // pools *are* lists, which have automatically-allocated memory (which we should free)
  // the method above only frees part of the memory
  list_free(p->list, memfree);
}


/*******************************************************************************
* Allocate memory in a pool.
*******************************************************************************/
void *
pool_mem(Pool p, size_t size)
{
  void *m = mem(size);
  list_add(p->list, m);
  return m;
}


#endif
