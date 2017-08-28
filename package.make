# This is a make stuff that this package adds to the quickbuild.make file.

# Edit config.make to change build instance specific make variables.


CONFIG_VARS := DEBUG_SYMBOL_PREFIX MACRO_API_PREFIX

# default value that may be overridden config.make
# DEBUG_SYMBOL_PREFIX is a prefix added to symbol names
# the code in debug.c is compiled with.
DEBUG_SYMBOL_PREFIX ?= sdk

# empty string by default
MACRO_API_PREFIX ?= SDK_

