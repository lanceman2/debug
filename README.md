# DEBUG

My personal DEBUG code.  It's that fprintf() to stderr wrapper code that
everyone who has ever wrote a C (or maybe C++) library API (application
programming interface) writes.  In my case I just have a spew functions and
a few assert functions.  They are butt ugly CPP (C preprocessor macro)
functions.  I find in general it's good to avoid CPP code, but debugging
without a hand full of simple spew and assert CPP macros is hard.  These
are along the line of extending the standard C library functions perror(3)
and assert(3) in a way that I'm accustom to, and not much more.

My plain is to make this a common/minimal dependency for my other C/C++
software projects.

In general I hate and avoid using a lot of CPP macro code, but I find
these functions are essential.  These few CPP macro functions help me
scope my code (at least at run-time) where as most other CPP macro
functions make scoping code a nightmare.  I detest the GTK+ GObject CPP
macros; I just can't follow (scope) them, where as the GTK+ spew functions
are fine.


