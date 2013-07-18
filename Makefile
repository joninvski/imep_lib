CC=g++
# DEBUG=-g
CFLAGS=-Wall -pedantic -ansi $(DEBUG)
LDFLAGS=
SOURCES=imep.cc
OBJECTS=$(SOURCES:.cc=.o)
.PHONY : clean test_hash

archive: libimep.a

all: $(SOURCES) $(EXECUTABLE)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

libimep.a: $(OBJECTS)
	ar -rcs libimep.a imep.o

clean:
	rm -f *.o $(EXECUTABLE) *.a

rebuild: clean all
