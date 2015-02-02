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
	$(AR) rc libtreemap.a map.o node.o iter.o
	$(RANLIB) libtreemap.a
	$(CC) -o ex ex.o -L. -std=c99 -ltreemap -g 
	$(CC) -o bigex bigex.o -L. -std=c99 -ltreemap -g
	$(CC) -o strex strex.o -L. -std=c99 -ltreemap -g
	$(CC) -o ovex ovex.o -L. -std=c99 -ltreemap -g
	rm $(OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=c99 -g -Wall -pedantic $(FLAGS)

clean:
	rm -f libtreemap.a
	rm -f $(OBJS)
	rm -f ex strex bigex ovex

