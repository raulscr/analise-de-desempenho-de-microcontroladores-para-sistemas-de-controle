#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

COMPONENT_SRCDIRS += pid_lib/
COMPONENT_SRCDIRS += pid_lib/qn_lib/

COMPONENT_ADD_INCLUDEDIRS += pid_lib/
COMPONENT_ADD_INCLUDEDIRS += pid_lib/qn_lib/
