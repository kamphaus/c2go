// This program actually still works without including stdio.h but it should be
// here for consistency.

#include "tests.h"

#define START_TEST(t) \
    diag(#t);         \
    test_##t();

typedef unsigned char x_uint;
typedef unsigned char y_uint;
typedef struct {
    unsigned char a;
    unsigned char b;
} z_struct;

void test_voidcast()
{
    x_uint x = 42;
    void * y = &x;
    y_uint *z = (y_uint*) y;
    is_eq(42, *z);
    x_uint arr1[] = { 1, 2, 3, 4 };
    y = arr1;
    z_struct *arr2 = (z_struct*) y;
    is_eq(1, arr2[0].a);
    is_eq(2, arr2[0].b);
    is_eq(3, arr2[1].a);
    is_eq(4, arr2[1].b);
}

int main()
{
    plan(5);

    START_TEST(voidcast)

    done_testing();
}
