PREFIX := /usr/local
CFLAGS := -I./include
CFLAGS += -std=c99 -Wall -Wextra -fPIC -pedantic
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
	$(CC) -shared -o libfab.so fab.o
libfab.a: fab.o
	$(AR) $(ARFLAGS) libfab.a fab.o
fab.o: src/fab.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $(SOURCE)

.PHONY: install
install:
	cp libfab.a /usr/local/lib/
	chown root /usr/local/lib/libfab.a
	chmod 0755 /usr/local/lib/libfab.a
	cp include/fab.h /usr/local/include/
	chown root /usr/local/include/fab.h
	chmod 0755 /usr/local/include/fab.h

.PHONY: clean
clean:
	rm -f libfab.a
	rm -f *.o

