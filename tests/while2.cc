#include <stdio.h>
#include "tests.h"

typedef float **triangle;
#define deadtri(tria)  ((tria)[1] == (triangle) NULL)

int main()
{
    plan(4);

	diag("do while with continue");
	{
	int * ok;
	int value2;
	ok = & value2;
	*ok = 1;
	int iterator = 0;
    do{
        iterator ++;
        *ok = 0;
        if (iterator >10){
            fail("execution should not reach here");
            break;
        }
        continue;
        fail("execution should not reach here");
    }while(*ok);
    is_eq(*ok, 0);
    is_eq(iterator, 1);
    iterator = 0;
    do{
        iterator ++;
        *ok = 0;
        for (int i=0; i<5; i++) {
            iterator ++;
            continue; // this will only continue the inner loop
        }
        if (iterator >10){
            fail("execution should not reach here");
            break;
        }
        continue;
        fail("execution should not reach here");
    }while(*ok);
    is_eq(*ok, 0);
    is_eq(iterator, 6);
	}

    done_testing();
}
