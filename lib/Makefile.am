EXTRA_DIST=grammar.hh grammar.cc lexer.cc grammar.yy lexer.ll

INCLUDES=-I@top_srcdir@/include @GC_CFLAGS@

libdir=${exec_prefix}/lib
lib_LTLIBRARIES=libscriptix-@INTERFACE_VERSION@.la libsxparse-@INTERFACE_VERSION@.la

libscriptix_@INTERFACE_VERSION@_la_SOURCES=\
	array.cc \
	assoc.cc \
	error.cc \
	eval.cc \
	function.cc \
	global.cc \
	iter.cc \
	list.cc \
	name.cc \
	number.cc \
	schedule.cc \
	stdlib.cc \
	string.cc \
	struct.cc \
	system.cc \
	thread.cc \
	type.cc \
	value.cc
libscriptix_@INTERFACE_VERSION@_la_LDFLAGS=-version-info @SO_VERSION@
libsxparse_@INTERFACE_VERSION@_la_SOURCES=\
	grammar.cc \
	lexer.cc \
	parser.cc \
	compiler.cc \
	transform.cc 
libsxparse_@INTERFACE_VERSION@_la_LDFLAGS=-version-info @SO_VERSION@


grammar.cc grammar.hh: grammar.yy
	@PATH_BISON@ -y -d -o grammar.cc grammar.yy
	-[ -f grammar.cc.h ] && mv -f grammar.cc.h grammar.hh

lexer.cc: lexer.ll grammar.hh
	@PATH_FLEX@ -olexer.cc lexer.ll
