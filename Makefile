PREFIX := /usr/local

CPPFLAGS := -I./include
CPPFLAGS += $(shell pkg-config --cflags-only-I MagickWand)

CFLAGS := -std=c99 -Wall -Wextra -fPIC -pedantic

ifeq ($(CC),gcc)
    CFLAGS += -ggdb3
endif
ifeq ($(CC),clang)
    CFLAGS += -Qunused-arguments -ggdb -Weverything
endif

CFLAGS += $(shell pkg-config --cflags-only-other MagickWand)

LIBRARIES := $(shell pkg-config --libs MagickWand)

AR=ar
ARFLAGS=rvs

SOURCE := $(wildcard src/*.c)

all: libfab.a libfab.so

libfab.so: fab.o buffer.o
	$(CC) -shared -o libfab.so fab.o buffer.o $(LIBRARIES)

libfab.a: fab.o buffer.o
	$(AR) $(ARFLAGS) libfab.a fab.o buffer.o

buffer.o: src/buffer.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) src/buffer.c

fab.o: src/fab.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) src/fab.c

test: libfab.a libfab.so
	$(CC) $(CFLAGS) $(CPPFLAGS) -o libfab-tests test/fab_tests.c -lfab -lcunit
	./libfab-tests

.PHONY: install
install:
	install -m 0755 libfab.a $(PREFIX)/lib
	install -m 0755 libfab.so $(PREFIX)/lib
	install -m 0755 include/fab.h $(PREFIX)/include

.PHONY: clean
clean:
	rm -f *.a *.o *.so
