// This program actually still works without including stdio.h but it should be
// here for consistency.

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#include "tests.h"

#define START_TEST(t) \
    diag(#t);         \
    test_##t();

// size of that file
int filesize = 11228;

void test_fgets2()
{
    FILE *pFile;
    char *mystring;
    char buffer[5];

    pFile = fopen("/tmp/mylog.txt", "w");
    fputs("asdfgh\nijk\n", pFile);
    fclose(pFile);

    pFile = fopen("/tmp/mylog.txt", "r");
    is_not_null(pFile);

    mystring = fgets(buffer, 5, pFile);
    is_not_null(mystring);
    is_streq(buffer, "asdf");
    is_streq(mystring, "asdf");
    is_true(buffer == mystring);
    is_eq(strlen(buffer), 4);
    mystring = fgets(buffer, 5, pFile);
    is_streq(buffer, "gh\n");
    is_streq(mystring, "gh\n");
    is_eq(strlen(buffer), 3);
    mystring = fgets(buffer, 5, pFile);
    is_streq(buffer, "ijk\n");
    is_streq(mystring, "ijk\n");
    is_eq(strlen(buffer), 4);
    is_eq(buffer[4], 0);
    is_false(feof(pFile));
    is_false(ferror(pFile));
    mystring = fgets(buffer, 5, pFile);
    is_streq(buffer, "ijk\n");
    is_true(NULL == mystring);
    is_true(feof(pFile));
    is_false(ferror(pFile));

    fclose(pFile);
}

int main()
{
    plan(19);

    START_TEST(fgets2)

    done_testing();
}
