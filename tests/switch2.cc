// This file tests the various forms of switch statement.
//
// We must be extra sensitive to the fact that switch fallthrough is handled
// differently in C and Go. Break statements are removed and fallthrough
// statements are added when necessary.
//
// It is worth mentioning that a SwitchStmt has a CompoundStmt item that
// contains all of the cases. However, if the individual case are not enclosed
// in a scope each of the case statements and their childen are part of the same
// CompoundStmt. For example, the first switch statement below contains a
// CompoundStmt with 12 children.

#include <stdio.h>
#include <stdbool.h>
#include "tests.h"

void goto_label(bool use_goto)
{
    for (;;) {
        switch (0)
        {
        case 3:
            continue;
        case 0:
            if (use_goto) {
                for (;;)
                    break;
                goto LABEL;
                fail("code should not reach here");
            } else if (false) {
                goto LABELX;
                goto LABELY;
                fail("code should not reach here");
            }
            /* other comment */
            // some comment
            /* fallthrough */
        LABELY:
        case 4:
        LABEL:
            printf("x");
        case 1:
            pass(__func__);
            break;
        case 2:
            ;
        LABELX:
        default:
            fail("code should not reach here");
            break;
        }
        break;
    }
}

void scoped_goto_label(bool use_goto)
{
    for (;;) {
        switch (0)
        {
        case 3:
            {
                continue;
            }
        case 0:
            {
                if (use_goto) {
                    for (;;) {
                        break;
                    }
                    goto LABEL;
                    fail("code should not reach here");
                } else if (false) {
                    goto LABELX;
                    goto LABELY;
                    fail("code should not reach here");
                }
                /* other comment */
                // some comment
                /* fallthrough */
            }
        LABELY: {}
        case 4: {}
        LABEL:
            {
                printf("x");
            }
        case 1:
            {
                pass(__func__);
                break;
            }
        case 2:
            {
                int x = 0;
                printf("%d", x);
                break;
            }
        LABELX: {}
        default:
            {
                fail("code should not reach here");
                break;
            }
        }
        break;
    }
}

int main()
{
    plan(4);

    goto_label(false);
    goto_label(true);

    // For each of the tests above there will be identical cases that use scopes
    // for the case statements.
    scoped_goto_label(false);
    scoped_goto_label(true);

    done_testing();
}
