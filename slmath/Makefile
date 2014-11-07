LIBNAME=slmath
LIBRARY=lib$(LIBNAME)

all: static
static: $(LIBRARY).a
dynamic: $(LIBRARY).so

MAJOR=0
MINOR=0

SOURCES = $(shell find src -name "*.cpp")
INCLUDE_DIR = include

SHARED_OBJS = $(SOURCES:.cpp=.shared.o)
STATIC_OBJS = $(SOURCES:.cpp=.static.o)

CFLAGS=-O2 -g -Wall 
STATIC_CFLAGS= -O2 -g -Wall $(CFLAGS) -I$(INCLUDE_DIR) 
SHARED_CFLAGS= $(STATIC_CFLAGS) -fPIC
LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined
LIBS=

$(LIBRARY).so.$(MAJOR).$(MINOR): $(SHARED_OBJS)
	g++ $(LDFLAGS) -shared \
		-Wl,-soname,$(LIBRARY).so.$(MAJOR) \
		-o $(LIBRARY).so.$(MAJOR).$(MINOR) \
		$+ -o $@ $(LIBS)

$(LIBRARY).so: $(LIBRARY).so.$(MAJOR).$(MINOR)
	rm -f $@.$(MAJOR)
	ln -s $@.$(MAJOR).$(MINOR) $@.$(MAJOR)
	rm -f $@
	ln -s $@.$(MAJOR) $@

$(LIBRARY).a: $(STATIC_OBJS)
	ar cru $@ $+

%.shared.o: %.cpp
	g++ -o $@ -c $+ $(SHARED_CFLAGS)

%.shared.o: %.c
	gcc -o $@ -c $+ $(SHARED_CFLAGS)

%.so : %.o
	g++ $(LDFLAGS) -shared $^ -o $@

%.static.o: %.cpp
	g++ -o $@ -c $+ $(STATIC_CFLAGS)

%.static.o: %.c
	gcc -o $@ -c $+ $(STATIC_CFLAGS)

.depend depend dep:
	g++ $(CFLAGS) -MM $(SOURCES) $(INCS) $(PKG_CONFIG_CFLAGS) > .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

clean:
	rm -f $(SHARED_OBJS)
	rm -f $(STATIC_OBJS)
	rm -f $(FIXED_OBJS)
	rm -f $(STATIC_FIXED_OBJS)
	rm -f *.so *.so* *.a *~

.PHONY: all static dynamic depend dep clean install
