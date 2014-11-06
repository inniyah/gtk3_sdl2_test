INCLUDES=-I@top_srcdir@/include @SGC_CFLAGS@

EXTRA_DIST = scriptix-conf.in

bindir=${exec_prefix}/bin
bin_PROGRAMS=scriptix
bin_SCRIPTS=scriptix-conf

scriptix_SOURCES=scriptix.cc
scriptix_LDADD=../lib/libscriptix.la ../lib/libsxparse.la
scriptix_LDFLAGS=@SGC_LIBS@
