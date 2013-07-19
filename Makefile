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
	ar -rcs libimep.a imep.o

clean:
	rm -rf *.o $(EXECUTABLE) *.a autom4te.cache/ config.*

test: libimep.a

rebuild: clean all
