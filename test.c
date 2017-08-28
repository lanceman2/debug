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

    ASSERT(1, "");
    ASSERT(2, "test %d\n", 55);

    FAIL("");

    return 0;
}
