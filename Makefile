PREFIX := /usr/local
CFLAGS := -I./include
CFLAGS += -std=c99 -Wall -Wextra -fPIC -pedantic
CFLAGS += $(shell pkg-config --cflags MagickWand)
LIBRARIES := $(shell pkg-config --libs MagickWand)
ifeq ($(CC),gcc)
    CFLAGS += -ggdb3
endif
ifeq ($(CC),clang)
    CFLAGS += -ggdb -Weverything
endif

AR=ar
ARFLAGS=rvs

SOURCE := $(wildcard src/*.c)

all: libfab.a libfab.so

.PHONY: shared
libfab.so: fab.o
	$(CC) -shared -o libfab.so fab.o $(LIBRARIES)
libfab.a: fab.o
	$(AR) $(ARFLAGS) libfab.a fab.o
fab.o: src/fab.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $(SOURCE)

.PHONY: install
install:
	cp libfab.so $(PREFIX)/lib/
	chown root $(PREFIX)/lib/libfab.so
	chmod 0755 $(PREFIX)/lib/libfab.so
	cp include/fab.h $(PREFIX)/include/
	chown root $(PREFIX)/include/fab.h
	chmod 0755 $(PREFIX)/include/fab.h

.PHONY: clean
clean:
	rm -f *.a *.o *.so
