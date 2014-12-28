PREFIX ?= /usr/local

CFLAGS += -std=c99 -Wall -Wextra -fPIC -pedantic
CFLAGS += $(shell pkg-config --cflags-only-other MagickWand)
CPPFLAGS += -I./include
CPPFLAGS += $(shell pkg-config --cflags-only-I MagickWand)

ifeq ($(CC),gcc)
    CFLAGS += -ggdb3
endif
ifeq ($(CC),clang)
    CFLAGS += -Qunused-arguments -ggdb -Weverything
endif

LDLIBS += $(shell pkg-config --libs MagickWand)
VPATH = src
OBJS := fab.o buffer.o

ARFLAGS=rvs

.PHONY: all
all: libfab.a libfab.so

$(OBJS): %.o: src/%.c

libfab.so: $(OBJS)
	$(CC) -shared -o $@ $^ $(LDLIBS)

libfab.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.PHONY: test
test: all
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
