PROGRAM=test

all: $(PROGRAM) libraries

SRCS = MainGtk3App.cpp Sdl2App.cpp Threads.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

PKG_CONFIG=gtk+-3.0 sdl2 gtkglext-3.0 gdkglext-3.0
PKG_CONFIG_CFLAGS=`pkg-config --cflags $(PKG_CONFIG)`
PKG_CONFIG_LIBS=`pkg-config --libs $(PKG_CONFIG)`

CFLAGS= -O2 -g -Wall
INCS=-I. -Islmath/include
LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined
LIBS=$(PKG_CONFIG_LIBS) -lgc -lpthread -lm -Lslmath -lslmath

$(PROGRAM): $(OBJS) libraries
	g++ $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

libraries: slmath/libslmath.a slmath/libscriptix.a

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS) $(INCS) $(PKG_CONFIG_CFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS) $(INCS) $(PKG_CONFIG_CFLAGS)

.depend depend dep:
	g++ $(CFLAGS) -MM $(SRCS) $(INCS) $(PKG_CONFIG_CFLAGS) > .depend
	$(MAKE) -C slmath .depend

ifeq (.depend,$(wildcard .depend))
include .depend
endif

slmath/libslmath.a:
	$(MAKE) -C slmath libslmath.a

slmath/libscriptix.a:
	$(MAKE) -C scriptix libscriptix.a

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
	rm -f *.o *.a *~

clean-all: clean
	$(MAKE) -C slmath clean
	$(MAKE) -C scriptix clean

.PHONY: all depend dep clean clean-all install
