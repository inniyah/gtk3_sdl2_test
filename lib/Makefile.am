EXTRA_DIST=grammar.hh grammar.cc lexer.cc grammar.yy lexer.ll

CXXFLAGS := @CXXFLAGS@ @SGC_CFLAGS@

libdir=${exec_prefix}/lib
lib_LTLIBRARIES=libscriptix.la libsxparse.la

libscriptix_la_SOURCES=\
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
libscriptix_la_LDFLAGS=-version-info @LIBSOVER@
libsxparse_la_SOURCES=\
	grammar.cc \
	lexer.cc \
	parser.cc \
	compiler.cc \
	transform.cc 
libsxparse_la_LDFLAGS=-version-info @LIBSOVER@


grammar.cc grammar.hh: grammar.yy
	@PATH_BISON@ -y -d -o grammar.cc grammar.yy

lexer.cc: lexer.ll grammar.hh
	@PATH_FLEX@ -olexer.cc lexer.ll
