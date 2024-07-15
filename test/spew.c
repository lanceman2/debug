#define _GNU_SOURCE
#include <link.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>

#include "../debug.h"

void catcher(int sig) {

    fprintf(stderr, "catch signal %d\n", sig);
    while(1)
        sleep(1);
}

int main(void) {

    signal(SIGSEGV, catcher);

    const size_t LEN = 512;
    char name[LEN];
    memset(name, 0, LEN);

    // Get program name (cmdline):
    {
        FILE *f = fopen("/proc/self/cmdline", "r");
        ASSERT(f, "fopen(\"/proc/self/cmdline\", \"r\") failed");
        ASSERT(fread(name, 1, LEN-1,f) >= 1); 
        ASSERT(feof(f));
        fclose(f);
    }

    fprintf(stderr, "Running: \"%s\" [compiled_spew_level=%d]\n",
            name, getCompiledSpewLevel());

    DSPEW("This was compiled with SPEW_LEVEL_DEBUG on [%d]",
            getCompiledSpewLevel());
    INFO("This was compiled with SPEW_LEVEL_INFO on [%d]",
            getCompiledSpewLevel());
    NOTICE("This was compiled with SPEW_LEVEL_NOTICE on [%d]",
            getCompiledSpewLevel());
    WARN("This was compiled with SPEW_LEVEL_WARN on [%d]",
            getCompiledSpewLevel());
    ERROR("This was compiled with SPEW_LEVEL_ERROR on [%d]",
            getCompiledSpewLevel());

    return 0;
}

