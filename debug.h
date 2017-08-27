// The files debug.hpp and debug.cpp should be kept independent of all
// other source file, so they can be used in other software packages.

// We can extend the functionally of these CPP MACRO functions as needs
// arise.  Some of the MACROs may start out as very simple wrappers.
// We'll keep these interfaces and can effectively change the code that
// uses them without editing the code that uses them by changing
// debug.cpp and this file.  We can add environment variable interfaces
// without changing these interfaces and so on.  For example in bash
// shell:
//
//   SDF_SPEW_LEVEL=debug SDF_ASSERTIONS_SLEEP=true ./foobar
//
// But there's no pressing need until we need it.  We can start with
// WARN() being the same as NOTICE(), and whatever.  We can add tty escape
// color codes and the different spew levels later.  Additions like that
// will not effect the coding interfaces that we define here:

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

extern void _spew(const char *pre, const char *file,
        int line, const char *func, const char *fmt, ...)
         // check printf format errors at compile time:
        __attribute__ ((format (printf, 5, 6)));

extern void _assertAction(void);
extern void _catchSigFault(void);


// ##__VA_ARGS__ comma not eaten with -std=c++0x
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=44317
//
// There is a GCC bug where GCC wrongly warns about ##__VA_ARGS__, so using
// #pragma GCC system_header suppresses these warnings.  Should this GCC
// bug get fixed, it'd be good to remove this next code line.
// See also: https://gcc.gnu.org/onlinedocs/cpp/System-Headers.html
#pragma GCC system_header


#  define _SPEW(pre, fmt, ... )\
     _spew(pre, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#  define ERROR(fmt, ...)\
     _spew("ERROR: ", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#  define ASSERT(val) \
    do {\
        if(!((bool) val)) {\
                _SPEW("ERROR: ", "ASSERTION(%s) failed\n", #val);\
                _assertAction();\
        }\
    }\
    while(0)
            
#  define VASSERT(val, fmt, ...) \
    do {\
        if(!((bool) val)) {\
            _SPEW("ERROR: ", "ASSERTION(%s) failed: " #fmt, #val, ##__VA_ARGS__);\
            _assertAction();\
        }\
    }\
    while(0)


#  define FAIL(fmt, ...) \
    do {\
        _SPEW("ERROR:", fmt, ##__VA_ARGS__);\
        _assertAction();\
    } while(0)



#ifdef DEBUG


#  define SPEW(fmt, ...) _SPEW("SPEW: ", fmt, ##__VA_ARGS__)

#  define WARN(fmt, ...) _SPEW("WARN: ", fmt, ##__VA_ARGS__)

#  define NOTICE(fmt, ...) _SPEW("NOTICE: ", fmt, ##__VA_ARGS__)
#  define DSPEW(fmt, ...)  _SPEW("DEBUG: ", fmt, ##__VA_ARGS__)

#  define DASSERT(x)  ASSERT(val)
#  define DVASSERT(x, fmt, ...) VASSERT(val, fmt, ##__VA_ARGS__)


#else


#  define SPEW(fmt, ...)      /* empty marco */

#  define WARN(fmt, ...)      /* empty marco */
#  define NOTICE(fmt, ...)    /* empty marco */
#  define DSPEW(fmt, ...)     /* empty marco */

#  define DASSERT(fmt, ...)   /* empty marco */
#  define DVASSERT(x, fmt, ...) /* empty marco */


#endif // #ifdef DEBUG

#ifdef __cplusplus
}
#endif

