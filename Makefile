ifndef CC
	CC=clang
endif

AR=ar
RANLIB=ranlib

all: clean
	$(CC) -c map.c node.c iter.c -std=c11 -g -Wall -pedantic -fPIC
	$(AR) -rc libtreemap.a map.o node.o iter.o
	$(RANLIB) libtreemap.a
	$(CC) -o ex ex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 	
	$(CC) -o bigex bigex.c -L. -std=c11 -ltreemap -g -Wall -pedantic	
	$(CC) -o strex strex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 
	$(CC) -o ovex ovex.c -L. -std=c11 -ltreemap -g -Wall -pedantic 
	$(CC) -o libtreemap.so node.o map.o iter.o -shared 
	rm *.o

clean:
	rm -f libtreemap.{so,a}
	rm -f *.{o,gch}
	rm -f ex strex bigex ovex

