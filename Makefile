CC=g++
# DEBUG=-g
CFLAGS=-Wall -pedantic -ansi $(DEBUG)
LDFLAGS=
SOURCES=imep.cc
OBJECTS=$(SOURCES:.cc=.o)
.PHONY : clean test_hash

archive: libimep.a

all: $(SOURCES) $(EXECUTABLE)

.cc.o:
	$(CC) -fpic -c $(CFLAGS) $<

libimep.a: $(OBJECTS)
	$(CC) -shared -o libimep.so *.o

clean:
	rm -f *.o $(EXECUTABLE) *.a

test: libimep.a

rebuild: clean all
