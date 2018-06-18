#include <stdio.h>
#include "tests.h"

enum { ESC_A = 1, ESC_d };
static const short int escapes[] = {
     -ESC_d
};

// main function

int main()
{
	plan(1);

    is_eq(escapes[0], -2);

	done_testing();
}
