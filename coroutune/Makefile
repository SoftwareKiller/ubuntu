COMM_MAKE = 1
COMM_ECHO = 1
version=0.5
v=debug
include co.mk

########## options ##########
CFLAGS += -g -fno-strict-aliasing -O0 -Wall -export-dynamic \
	-Wall -pipe  -D_GNU_SOURCE -D_REENTRANT -fPIC -Wno-deprecated -m64

UNAME := $(shell uname -s)

ifeq ($(UNAME), FreeBSD)
LINKS += -g -L./lib -lcolib -lpthread
else
LINKS += -g -L./lib -lcolib -lpthread -ldl
endif

COLIB_OBJS=co_epoll.o co_routine.o co_hook_sys_call.o coctx_swap.o coctx.o
#co_swapcontext.o

PROGS = colib echosvr main

all:$(PROGS)

colib:libcolib.a libcolib.so

libcolib.a: $(COLIB_OBJS)
	$(ARSTATICLIB) 
libcolib.so: $(COLIB_OBJS)
	$(BUILDSHARELIB) 

echosvr:echosvr.o
	$(BUILDEXE)

main:main.o
	$(BUILDEXE)

dist: clean libco-$(version).src.tar.gz

libco-$(version).src.tar.gz:
	@find . -type f | grep -v CVS | grep -v .svn | sed s:^./:libco-$(version)/: > MANIFEST
	@(cd ..; ln -s libco_pub libco-$(version))
	(cd ..; tar cvf - `cat libco_pub/MANIFEST` | gzip > libco_pub/libco-$(version).src.tar.gz)
	@(cd ..; rm libco-$(version))

clean:
	$(CLEAN) *.o $(PROGS)
	rm -fr MANIFEST lib solib libco-$(version).src.tar.gz libco-$(version)
