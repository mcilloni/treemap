ifndef CC
	CC=clang
endif

ifndef AR
	AR=ar 
endif

ifndef RANLIB
	RANLIB=ranlib
endif

ARCH = $(shell uname -m)
UNAME = $(shell uname)

FLAGS =

ifeq ($(ARCH),x86_64)
ifeq (,$(findstring CYGWIN,$(UNAME)))
	FLAGS += -fPIC
endif
endif

.PHONY: all,clean

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(OBJS)
	$(CC) -c map.c node.c iter.c -std=c11 -g -Wall -pedantic -fPIC
	$(AR) rc libtreemap.a map.o node.o iter.o
	$(RANLIB) libtreemap.a
	$(CC) -o ex ex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 	
	$(CC) -o bigex bigex.c -L. -std=c11 -ltreemap -g -Wall -pedantic	
	$(CC) -o strex strex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 
	$(CC) -o ovex ovex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 
	rm *.o

%.o: %.c
	$(CC) -c $< -o $@ -std=c11 -g -Wall -pedantic $(FLAGS)

clean:
	rm -f libtreemap.a
	rm -f $(OBJS)
	rm -f ex strex bigex ovex

