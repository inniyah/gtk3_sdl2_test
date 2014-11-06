INCLUDES=-I@top_srcdir@/include @GC_CFLAGS@

EXTRA_DIST = scriptix-conf.in

bindir=${exec_prefix}/bin
bin_SCRIPTS=scriptix-conf

noinst_PROGRAMS=scriptix

scriptix_SOURCES=scriptix.cc
scriptix_LDADD= ../lib/libsxparse.la ../lib/libscriptix.la -lgc
