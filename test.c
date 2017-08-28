#include "debug.h"

int main(void)
{
    SDK_SPEW();
    SDK_ERROR("Hi error %d", 345);
    SDK_WARN();
    SDK_NOTICE();
    SDK_INFO();
    SDK_DSPEW();
    SDK_DSPEW();

    SDK_ASSERT(1, "");
    SDK_ASSERT(2, "test %d\n", 55);

    SDK_FAIL("");

    return 0;
}
