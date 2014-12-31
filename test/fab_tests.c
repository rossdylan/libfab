#include <string.h>
#include <stdlib.h>
#include "fab_tests.h"
#include "buffer.h"

#define malloc_or_fail(_ptr_, _size_) if((_ptr_ = malloc(_size_)) == NULL) { CU_FAIL_FATAL("malloc failed"); return;}

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

void test_black(void) {
    test_generic(BLACK, "\x1b[30mHello There\x1b[39m");
}

void test_red(void) {
    test_generic(RED, "\x1b[31mHello There\x1b[39m");
}

void test_green(void) {
    test_generic(GREEN, "\x1b[32mHello There\x1b[39m");
}

void test_yellow(void) {
    test_generic(YELLOW, "\x1b[33mHello There\x1b[39m");
}

void test_blue(void) {
    test_generic(BLUE, "\x1b[34mHello There\x1b[39m");
}

void test_magenta(void) {
    test_generic(MAGENTA, "\x1b[35mHello There\x1b[39m");
}

void test_cyan(void) {
    test_generic(CYAN, "\x1b[36mHello There\x1b[39m");
}

void test_white(void) {
    test_generic(WHITE, "\x1b[37mHello There\x1b[39m");
}


void test_hblack(void) {
    test_generic(HBLACK, "\x1b[1;30;7mHello There\x1b[22;27;39m");
}

void test_hred(void) {
    test_generic(HRED, "\x1b[1;31;7mHello There\x1b[22;27;39m");
}

void test_hgreen(void) {
    test_generic(HGREEN, "\x1b[1;32;7mHello There\x1b[22;27;39m");
}

void test_hyellow(void) {
    test_generic(HYELLOW, "\x1b[1;33;7mHello There\x1b[22;27;39m");
}

void test_hblue(void) {
    test_generic(HBLUE, "\x1b[1;34;7mHello There\x1b[22;27;39m");
}

void test_hmagenta(void) {
    test_generic(HMAGENTA, "\x1b[1;35;7mHello There\x1b[22;27;39m");
}

void test_hcyan(void) {
    test_generic(HCYAN, "\x1b[1;36;7mHello There\x1b[22;27;39m");
}

void test_hwhite(void) {
    test_generic(HWHITE, "\x1b[1;37;7mHello There\x1b[22;27;39m");
}

void test_bgblack(void) {
    test_generic(BGBLACK, "\x1b[40mHello There\x1b[49m");
}

void test_bgred(void) {
    test_generic(BGRED, "\x1b[41mHello There\x1b[49m");
}

void test_bggreen(void) {
    test_generic(BGGREEN, "\x1b[42mHello There\x1b[49m");
}

void test_bgyellow(void) {
    test_generic(BGYELLOW, "\x1b[43mHello There\x1b[49m");
}

void test_bgblue(void) {
    test_generic(BGBLUE, "\x1b[44mHello There\x1b[49m");
}

void test_bgmagenta(void) {
    test_generic(BGMAGENTA, "\x1b[45mHello There\x1b[49m");
}

void test_bgcyan(void) {
    test_generic(BGCYAN, "\x1b[46mHello There\x1b[49m");
}

void test_bgwhite(void) {
    test_generic(BGWHITE, "\x1b[47mHello There\x1b[49m");
}

int init_buffer_tests(void) {
    return 0;
}
int clean_buffer_tests(void) {
    return 0;
}

// Test the buffer implementation when it doesn't need to expand
// currently that means a string < 32 bytes
void test_append_buffer(void) {
    const char *test_string = "Hello";
    fab_buffer_t *buffer = NULL;
    malloc_or_fail(buffer, sizeof(fab_buffer_t))
    init_buffer(buffer);
    append_buffer(buffer, test_string);
    // Assert that the string has been append
    CU_ASSERT(buffer->data_size == strlen(test_string));
    // Assert that we have not expanded the buffer
    // ignore the silly magic # 32, its defined as the starting buffer size
    CU_ASSERT(buffer->buffer_size == 32);
    // Assert that whats in the buffer is the same as what we added
    CU_ASSERT(memcmp(buffer->buffer,
                test_string, strlen(test_string) * sizeof(char)) == 0);
    free_buffer(buffer);
}

void test_append_buffer_expand(void) {
    const char *test_string = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    fab_buffer_t *buffer = NULL;
    malloc_or_fail(buffer, sizeof(fab_buffer_t))
    init_buffer(buffer);
    append_buffer(buffer, test_string);
    // We copied the right amount of data
    CU_ASSERT(buffer->data_size == strlen(test_string));
    // We have expanded the buffer once
    CU_ASSERT(buffer->buffer_size == 64);
    // The data in the buffer is correct
    CU_ASSERT(memcmp(buffer->buffer,
                test_string, strlen(test_string) * sizeof(char)) == 0);
    free_buffer(buffer);
}

void test_truncate_buffer(void) {
    const char *test_string = "Hello";
    fab_buffer_t *buffer = NULL;
    malloc_or_fail(buffer, sizeof(fab_buffer_t));
    init_buffer(buffer);
    append_buffer(buffer, test_string);
    truncate_buffer(buffer);
    // String sizes match
    CU_ASSERT(buffer->data_size == strlen(test_string));
    // Verify that the internal array is now a null-terminated string of the
    // correct length
    CU_ASSERT(strlen(buffer->buffer) == strlen(test_string));
    CU_ASSERT(strcmp(buffer->buffer, test_string) == 0);
    free_buffer(buffer);
}
int main() {
    CU_pSuite format_suite = NULL;
    CU_pSuite buffer_suite = NULL;

    if(CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    format_suite = CU_add_suite("Text Formating", init_text_tests, clean_text_tests);
    if(format_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(size_t i=0; i<NUM_FORMAT_TESTS; i++) {
        if((CU_add_test(format_suite, FORMAT_TESTS[i].name, FORMAT_TESTS[i].func) == NULL)) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    buffer_suite = CU_add_suite("Buffer", init_buffer_tests, clean_buffer_tests);
    if(buffer_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    for(size_t i=0; i<NUM_BUFFER_TESTS; i++) {
        if((CU_add_test(buffer_suite, BUFFER_TESTS[i].name, BUFFER_TESTS[i].func) == NULL)) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int errCode = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return errCode;
}
