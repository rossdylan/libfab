#include <string.h>
#include <stdlib.h>
#include "fab_tests.h"


int init_text_tests(void) {
    return 0;
}

int clean_text_tests(void) {
    return 0;
}

void test_generic(Color c, const char *str) {
    char *formatted = apply_color(c, "Hello There");
    int compare = strncmp(formatted, str, strlen(formatted));
    free(formatted);
    CU_ASSERT(compare == 0)
}

void test_bold(void) {
    test_generic(BOLD, "\x1b[1mHello There\x1b[22m");
}

void test_italic(void) {
    test_generic(ITALIC, "\x1b[3mHello There\x1b[23m");
}

void test_underline(void) {
    test_generic(UNDER, "\x1b[4mHello There\x1b[24m");
}

void test_underline2(void) {
    test_generic(UNDER2, "\x1b[21mHello There\x1b[24m");
}

void test_strike(void) {
    test_generic(STRIKE, "\x1b[9mHello There\x1b[29m");
}

void test_blink(void) {
    test_generic(BLINK, "\x1b[5mHello There\x1b[25m");
}

void test_flip(void) {
    test_generic(FLIP, "\x1b[7mHello There\x1b[27m");
}

void test_green(void) {
    test_generic(GREEN, "\x1b[32mHello There\x1b[39m");
}


int main() {
    CU_pSuite psuite = NULL;
    if(CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    psuite = CU_add_suite("Text Formating", init_text_tests, clean_text_tests);
    if(psuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(size_t i=0; i<NUMTESTS; i++) {
        if((CU_add_test(psuite, TESTS[i].name, TESTS[i].func) == NULL)) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
