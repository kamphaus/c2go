// Array examples

#include "tests.h"
#include <stdlib.h>

#define START_TEST(t) \
    diag(#t);         \
    test_##t();

typedef unsigned char pcre_uint8;
typedef unsigned char pcre_uchar;
typedef unsigned short pcre_uint16;

#define PRIV(name) _pcre_##name
extern const pcre_uint8     PRIV(OP_lengths)[];
#define IMM2_SIZE 2
#define LINK_SIZE 2

#define PT_ANY        0    /* Any property - matches all chars */
#define PT_SC         4    /* Script (e.g. Han) */

#define STR_A                       "\101"
#define STR_a                       "\141"
#define STR_b                       "\142"
#define STR_c                       "\143"
#define STR_e                       "\145"
#define STR_i                       "\151"
#define STR_m                       "\155"
#define STR_n                       "\156"
#define STR_r                       "\162"
#define STR_y                       "\171"

#define STRING_Any0 STR_A STR_n STR_y "\0"
#define STRING_Arabic0 STR_A STR_r STR_a STR_b STR_i STR_c "\0"
#define STRING_Armenian0 STR_A STR_r STR_m STR_e STR_n STR_i STR_a STR_n "\0"

const char PRIV(utt_names)[] =
  STRING_Any0
  STRING_Arabic0
  STRING_Armenian0;

enum {
  ucp_Arabic,
  ucp_Armenian,
};

typedef struct {
  pcre_uint16 name_offset;
  pcre_uint16 type;
  pcre_uint16 value;
} ucp_type_table;

const ucp_type_table PRIV(utt)[] = {
  {   0, PT_ANY, 0 },
  {   4, PT_SC, ucp_Arabic },
  {  11, PT_SC, ucp_Armenian }
};

#define STRCMP_UC_C8(str1, str2) \
  strcmp((char *)(str1), (str2))

int comp (char* name, int i) {
    return STRCMP_UC_C8(name, PRIV(utt_names) + PRIV(utt)[i].name_offset);
}

void test_arr_type_lookup() {
    is_true(comp("Any", 0) == 0);
    is_true(comp("Any", 1) != 0);
    is_true(comp("Arabic", 1) == 0);
    is_true(comp("Arabic", 2) != 0);
    is_true(comp("Armenian", 2) == 0);
    is_true(comp("Armenian", 1) != 0);
}

int main()
{
    plan(6);

    START_TEST(arr_type_lookup);

    done_testing();
}
