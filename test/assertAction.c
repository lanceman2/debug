#include <stdio.h>
#include <stdint.h>

#include "../debug.h"


void myAssert(FILE *stream, const char *file,
        int lineNum, const char *func) {

    fprintf(stream, "%s:%d %s() calling myAssert()\n",
            file, lineNum, func);
}



int main(void) {

    assertAction = myAssert;

    // If CPP (C preprocessor) macro DEBUG is defined this happens, else
    // it does not.
    DASSERT(0);

    // If we get here:
    INFO("Did not call DASSERT(0)");

    // This should happen no matter what.
    ASSERT(0);

    return 0;
}

