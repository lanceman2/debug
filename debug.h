#ifndef __debug_h__
#define __debug_h__

/*
///////////////////////////////////////////////////////////////////////////
   USER DEFINABLE SELECTOR MACROS make the follow macros come to life
   in the file that includes this debug.h:
 
   DEBUG             -->  DASSERT()
   DEBUG             -->  DZMEM()

   SPEW_LEVEL_DEBUG  -->  DSPEW() INFO() NOTICE() WARN() ERROR()
   SPEW_LEVEL_INFO   -->  INFO() NOTICE() WARN() ERROR()
   SPEW_LEVEL_NOTICE -->  NOTICE() WARN() ERROR()
   SPEW_LEVEL_WARN   -->  WARN() ERROR()
   SPEW_LEVEL_ERROR  -->  ERROR()

   always on is      --> ASSERT() CHECK() RET_ERROR()

   If a macro function is not live it becomes a empty macro with no C code.


///////////////////////////////////////////////////////////////////////////

   Setting SPEW_LEVEL_NONE with still have ASSERT() spewing and ERROR()
   will not spew.
*/


/** \defgroup debug_functions debug developer CPP macro functions

This file provides some CPP (C pre processor) macro debug functions.

ASSERT(), CHECK(), and RET_ERROR() are always defined.

At run-time activity of the macro functions DSPEW(), INFO(), NOTICE(),
WARN(), and ERROR() is determined by the current spew level.

This file is really not much code but is a powerful development tool like
assert(3).  See 'man 3 assert'.  This just adds spewing of line number,
name of function, and other handy information to the basic idea of libc's
assert(3).  For DEBUG mode builds: sprinkle DASSERT() into all your
functions, and zero all memory allocations before you free them.

Most developers have their own form of this crap and we understand it is
best to just use your own macro-ised form of fprintf(strerr, ...) that let
you watch your code run.

@{
 */
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#ifndef EXPORT
#  define EXPORT extern
#endif


#ifdef __cplusplus
extern "C" {
#endif


#define SPEW_FILE stderr


#ifdef DEBUG
#  define DZMEM(x,size)  memset((x), 0, (size))
// Another way to test for bad/freed memory access:
//#  define DZMEM(x,size)  memset((x), 0xFFFFFFFF, (size))
#else
#  define DZMEM(x,size)  /* empty macro */
#endif

#ifdef __GNUC__
// We would like to be able to just call DSPEW() with no arguments
// which can make a zero length printf format.
#  pragma GCC diagnostic ignored "-Wformat-zero-length"
#endif


#ifndef DOXYGEN_RUNNING

EXPORT
void (*assertAction)(FILE *stream, const char *file,
        int lineNum, const char *func);

EXPORT
void spew(uint32_t level, FILE *stream, int errn, const char *pre,
        const char *file, int line, const char *func,
        const char *fmt, ...)
#ifdef __GNUC__
        // check printf format errors at compile time:
        __attribute__ ( ( format (printf, 8, 9 ) ) )
#endif
        ;

EXPORT
void _assert(FILE *stream, const char *file,
        int lineNum, const char *func);


EXPORT
int getCompiledSpewLevel(void);


EXPORT
int getSpewLevel(void);

EXPORT
void setSpewLevel(int level);


#endif // #ifndef DOXYGEN_RUNNING

// This CPP macro function CHECK() is just so we can call most pthread_*()
// (pthread_mutex_init() for example) and maybe other functions that
// return 0 on success and an int error number on failure, and asserts on
// failure printing errno (from ASSERT()) and the return value.  This is
// not so bad given this does not obscure what is being run.  Like for
// example:
//
//   CHECK(pthread_mutex_lock(&s->mutex));
//
// You can totally tell what that is doing.  One line of code instead of
// three.  Note (x) can only appear once in the macro expression,
// otherwise (x) could get executed more than once if it was listed more
// than once.
//
// CHECK() is not a debugging thing; it's inserting the (x) code every
// time.  And the same goes for ASSERT(); ASSERT() is not a debugging
// thing either, it is the coder being to lazy to recover from a large
// number of failure code paths.  If malloc(10) fails we call ASSERT.
// If pthread_mutex_lock() fails we call ASSERT. ...
//
#define CHECK(x) \
    do { \
        int ret = (x); \
        ASSERT(ret == 0, #x "=%d FAILED", ret); \
    } while(0)


// This seems to be an often repeated pattern.  They also seem to have
// crap like this in GTK+, not that that's necessarily a good thing.
//
// This acts like an ASSERT() in that the val arg needs to be true.
//
// If val is not true return ret, else do not return.
//
#define RET_ERROR(val, ret, ...) \
    do {\
        if(!((bool) (val))) {\
            ERROR("" __VA_ARGS__);\
            return ret;\
        }\
    }\
    while(0)



#  define _SPEW(level, stream, errn, pre, fmt, ... )\
     spew(level, stream, errn, pre, __BASE_FILE__, __LINE__,\
        __func__, fmt, ##__VA_ARGS__)


// It's nice to see that it is ASSERT() or DASSERT() as it is in the code;
// hence we pass fname as ASSERT or DASSERT.
#  define DO_ASSERT(fname, val, ...) \
    do {\
        if(!((bool) (val))) {\
            _SPEW(1, SPEW_FILE, errno, #fname"("#val") failed:", "" __VA_ARGS__);\
            _assert(SPEW_FILE, __BASE_FILE__, __LINE__, __func__);\
        }\
    }\
    while(0)


#  define ASSERT(val, ...)   DO_ASSERT(ASSERT, val, ##__VA_ARGS__)


///////////////////////////////////////////////////////////////////////////
// We let the highest verbosity macro flag win.
//

#ifndef DOXYGEN_RUNNING

#ifdef SPEW_LEVEL_DEBUG // The highest verbosity
#  ifndef SPEW_LEVEL_INFO
#    define SPEW_LEVEL_INFO
#  endif
#endif
#ifdef SPEW_LEVEL_INFO
#  ifndef SPEW_LEVEL_NOTICE
#    define SPEW_LEVEL_NOTICE
#  endif
#endif
#ifdef SPEW_LEVEL_NOTICE
#  ifndef SPEW_LEVEL_WARN
#    define SPEW_LEVEL_WARN
#  endif
#endif
#ifdef SPEW_LEVEL_WARN
#  ifndef SPEW_LEVEL_ERROR
#    define SPEW_LEVEL_ERROR
#  endif
#endif

#ifdef SPEW_LEVEL_ERROR
#  ifdef SPEW_LEVEL_NONE
#    undef SPEW_LEVEL_NONE
#  endif
#else
#  ifndef SPEW_LEVEL_NONE
#    define SPEW_LEVEL_NONE // The default.
#  endif
#endif

#endif //#ifndef DOXYGEN_RUNNING



#ifdef DEBUG
#  define DASSERT(val, ...)  DO_ASSERT(DASSERT, val, ##__VA_ARGS__)
#else
#  define DASSERT(val, ...)  /*empty macro*/
#endif

#ifdef SPEW_LEVEL_NONE
#define ERROR(...) _SPEW(0, 0/*no spew stream*/, errno, "ERROR:", "" __VA_ARGS__)
#else
#define ERROR(...) _SPEW(1, SPEW_FILE, errno, "ERROR:", "" __VA_ARGS__)
#endif

#ifdef SPEW_LEVEL_WARN
#  define WARN(...) _SPEW(2, SPEW_FILE, errno, "WARN:", "" __VA_ARGS__)
#else
#  define WARN(...) /*empty macro*/
#endif 

#ifdef SPEW_LEVEL_NOTICE
#  define NOTICE(...) _SPEW(3, SPEW_FILE, errno, "NOTICE:", "" __VA_ARGS__)
#else
#  define NOTICE(...) /*empty macro*/
#endif

#ifdef SPEW_LEVEL_INFO
#  define INFO(...)   _SPEW(4, SPEW_FILE, 0, "INFO:", "" __VA_ARGS__)
#else
#  define INFO(...) /*empty macro*/
#endif

#ifdef SPEW_LEVEL_DEBUG
#  define DSPEW(...)  _SPEW(5, SPEW_FILE, 0, "DEBUG:", "" __VA_ARGS__)
#else
#  define DSPEW(...) /*empty macro*/
#endif

/** @} */

#ifdef __cplusplus
}
#endif



#endif // #ifndef __debug_h__
