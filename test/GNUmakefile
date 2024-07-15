# This is a GNU make make file.

CPPFLAGS := -Werror -Wall


assert_SOURCES := assert.c ../debug.c
assert_CPPFLAGS := -DSPEW_LEVEL_DEBUG

dassert_SOURCES := $(assert_SOURCES)
dassert_CPPFLAGS := -DSPEW_LEVEL_DEBUG -DDEBUG

dspew_SOURCES := spew.c ../debug.c
dspew_CPPFLAGS := -DSPEW_LEVEL_DEBUG

info_SOURCES := spew.c ../debug.c
info_CPPFLAGS := -DSPEW_LEVEL_INFO

notice_SOURCES := spew.c ../debug.c
notice_CPPFLAGS := -DSPEW_LEVEL_NOTICE

warn_SOURCES := spew.c ../debug.c
warn_CPPFLAGS := -DSPEW_LEVEL_WARN

error_SOURCES := spew.c ../debug.c
error_CPPFLAGS := -DSPEW_LEVEL_ERROR

none_SOURCES := spew.c ../debug.c
none_CPPFLAGS := -DSPEW_LEVEL_NONE

setSpewLevel_SOURCES := setSpewLevel.c ../debug.c
setSpewLevel_CPPFLAGS := -DSPEW_LEVEL_DEBUG

assertAction_SOURCES := assertAction.c ../debug.c
assertAction_CPPFLAGS := -DSPEW_LEVEL_DEBUG









include ../quickbuild.make

