#ifndef __FAB_TESTS_H
#define __FAB_TESTS_H
#include <CUnit/Basic.h>
#include "fab.h"

typedef struct {
    const char *name;
    CU_TestFunc func;
} TestDef;

int init_text_tests(void);
int clean_text_tests(void);
void test_generic(Color c, const char *str);
void test_bold(void);
void test_italic(void);
void test_underline(void);
void test_underline2(void);
void test_strike(void);
void test_blink(void);
void test_flip(void);
void test_black(void);
void test_red(void);
void test_green(void);
void test_yellow(void);
void test_blue(void);
void test_magenta(void);
void test_cyan(void);
void test_white(void);

static TestDef TESTS[] = {
    {"Test Bold", test_bold},
    {"Test Italic", test_italic},
    {"Test Underline", test_underline},
    {"Test Underline 2", test_underline2},
    {"Test Strike", test_strike},
    {"Test Blink", test_blink},
    {"Test Flip", test_flip},
    {"Test Black", test_black},
    {"Test Red", test_red},
    {"Test Green", test_green},
    {"Test Yellow", test_yellow},
    {"Test Blue", test_blue},
    {"Test Magenta", test_magenta},
    {"Test Cyan", test_cyan},
    {"Test White", test_white}
};

static size_t NUMTESTS = 15;
#endif
