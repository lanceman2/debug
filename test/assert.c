#include <stdio.h>
#include <stdint.h>

#include "../debug.h"


int main(void) {

    // If CPP (C preprocessor) macro DEBUG is defined this happens, else
    // it does not.
    DASSERT(0);

    // If we get here:
    INFO("Did not call DASSERT(0)");

    // This should happen no matter what.
    ASSERT(0);

    return 0;
}

