#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

typedef unsigned char pcre_uint8;
typedef unsigned int pcre_uint32;
typedef struct pcre_extra {
  unsigned long int flags;        /* Bits for which fields are set */
  void *study_data;               /* Opaque data from pcre_study() */
  unsigned long int match_limit;  /* Maximum number of calls to match() */
  void *callout_data;             /* Data passed back in callouts */
  const unsigned char *tables;    /* Pointer to character tables */
  unsigned long int match_limit_recursion; /* Max recursive calls to match() */
  unsigned char **mark;           /* For passing back a mark pointer */
  void *executable_jit;           /* Contains a pointer to a compiled jit code */
} pcre_extra;
typedef struct pcre_study_data {
  pcre_uint32 size;               /* Total that was malloced */
  pcre_uint32 flags;              /* Private flags */
  pcre_uint8 start_bits[32];      /* Starting char bits */
  pcre_uint32 minlength;          /* Minimum subject length */
} pcre_study_data;

void test_mark()
{
    pcre_extra *extra = NULL;
    pcre_study_data *study;
    pcre_uint8 *markptr;
    void * allocated = malloc(sizeof(pcre_extra) + sizeof(pcre_study_data));
    extra = (pcre_extra *)allocated;
    study = (pcre_study_data *)((char *)extra + sizeof(pcre_extra));
    memset(study->start_bits, 0, 32 * sizeof(pcre_uint8));
    extra->study_data = study;
    study->size = sizeof(pcre_study_data);
    extra->mark = &markptr;
    is_eq(study->size, 44);
    is_eq(sizeof(pcre_extra), 64);
    for (int i=0; i<32; i++)
        is_eq(study->start_bits[i], 0);
}

int main()
{
    plan(34);

    test_mark();

    done_testing();
}
