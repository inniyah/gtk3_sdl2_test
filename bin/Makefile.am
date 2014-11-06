INCLUDES=-I@top_srcdir@/include @GC_CFLAGS@

noinst_PROGRAMS=scriptix

scriptix_SOURCES=scriptix.cc
scriptix_LDADD= ../lib/libsxparse-@INTERFACE_VERSION@.la ../lib/libscriptix-@INTERFACE_VERSION@.la -lgc
