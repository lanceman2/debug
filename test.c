#include "debug.h"

int main(void)
{
    SPEW();
    ERROR("Hi error %d", 345);
    WARN();
    NOTICE();
    INFO();
    DSPEW();
    DSPEW();

    ASSERT(1);
    VASSERT(0, "test %d\n", 55);

    return 0;
}
