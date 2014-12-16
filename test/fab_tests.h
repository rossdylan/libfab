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

void test_hblack(void);
void test_hred(void);
void test_hgreen(void);
void test_hyellow(void);
void test_hblue(void);
void test_hmagenta(void);
void test_hcyan(void);
void test_hwhite(void);

void test_bgblack(void);
void test_bgred(void);
void test_bggreen(void);
void test_bgyellow(void);
void test_bgblue(void);
void test_bgmagenta(void);
void test_bgcyan(void);
void test_bgwhite(void);

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
    {"Test White", test_white},
    {"Test Highlight Black", test_hblack},
    {"Test Highlight Red", test_hred},
    {"Test Highlight Green", test_hgreen},
    {"Test Highlight Yellow", test_hyellow},
    {"Test Highlight Blue", test_hblue},
    {"Test Highlight Magenta", test_hmagenta},
    {"Test Highlight Cyan", test_hcyan},
    {"Test highlight White", test_hwhite},
    {"Test Background Black", test_bgblack},
    {"Test Background Red", test_bgred},
    {"Test Background Green", test_bggreen},
    {"Test Background Yellow", test_bgyellow},
    {"Test Background Blue", test_bgblue},
    {"Test Background Magenta", test_bgmagenta},
    {"Test Background Cyan", test_bgcyan},
    {"Test Background White", test_bgwhite}
};

static size_t NUMTESTS = 31;
#endif
