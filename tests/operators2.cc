#include <stdio.h>
#include "tests.h"

typedef unsigned int pcre_uint32;
typedef unsigned char pcre_uchar;
#define PCRE_PUCHAR const pcre_uchar *

#define PREP_A 0x0002
#define PREP_B 0x0010

int main()
{
	plan(4);

    diag("Increment with assign");
    {
        pcre_uchar str[] = "abcdef";
        pcre_uchar *p = str;
        pcre_uint32 pp;
        pcre_uint32 pp2 = *p;
        PCRE_PUCHAR p2 = p;
        pp = *p++ = 'z';
        pp2 = *p;
        is_eq(*p2, 'z');
        is_eq(pp, 'z');
        is_eq(pp2, 'b');
    }

    diag("Test complement");
    {
        unsigned long int flags = 32;
        flags &= ~(PREP_A|PREP_B);
        is_eq(flags, 32);
    }

	done_testing();
}
