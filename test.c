#include "debug.h"

int main(void)
{
    SPEW("\n");
    DSPEW("\n");
    WARN("\n");

    ASSERT(1);
    VASSERT(0, "test %d\n", 55);

    return 0;
}
