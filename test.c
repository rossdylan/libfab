#include <stdio.h>
#include <stdlib.h>
#include <fab.h>


int main(int argc, char** argv) {
    printf("BOLDING-ing it up: '%s'\n", apply_format(BOLD, "Hello There"));
    printf("ITALIC-ing it up: '%s'\n", apply_format(ITALIC, "Hello There"));
    printf("UNDER-ing it up: '%s'\n", apply_format(UNDER, "Hello There"));
    printf("UNDER2-ing it up: '%s'\n", apply_format(UNDER2, "Hello There"));
    printf("STRIKE-ing it up: '%s'\n", apply_format(STRIKE, "Hello There"));
    printf("BLINK-ing it up: '%s'\n", apply_format(BLINK, "Hello There"));
    printf("FLIP-ing it up: '%s'\n", apply_format(FLIP, "Hello There"));

    printf("------------------\n");
    printf("BLACK-ing it up: '%s'\n", apply_format(BLACK, "Hello There"));
    printf("RED-ing it up: '%s'\n", apply_format(RED, "Hello There"));
    printf("GREEN-ing it up: '%s'\n", apply_format(GREEN, "Hello There"));
    printf("YELLOW-ing it up: '%s'\n", apply_format(YELLOW, "Hello There"));
    printf("BLUE-ing it up: '%s'\n", apply_format(BLUE, "Hello There"));
    printf("MAGENTA-ing it up: '%s'\n", apply_format(MAGENTA, "Hello There"));
    printf("CYAN-ing it up: '%s'\n", apply_format(CYAN, "Hello There"));
    printf("WHITE-ing it up: '%s'\n", apply_format(WHITE, "Hello There"));

    printf("------------------\n");
    printf("HIGHLIGHT-BLACK-ing it up: '%s'\n", apply_format(HBLACK, "Hello There"));
    printf("HIGHLIGHT-RED-ing it up: '%s'\n", apply_format(HRED, "Hello There"));
    printf("HIGHLIGHT-GREEN-ing it up: '%s'\n", apply_format(HGREEN, "Hello There"));
    printf("HIGHLIGHT-YELLOW-ing it up: '%s'\n", apply_format(HYELLOW, "Hello There"));
    printf("HIGHLIGHT-BLUE-ing it up: '%s'\n", apply_format(HBLUE, "Hello There"));
    printf("HIGHLIGHT-MAGENTA-ing it up: '%s'\n", apply_format(HMAGENTA, "Hello There"));
    printf("HIGHLIGHT-CYAN-ing it up: '%s'\n", apply_format(HCYAN, "Hello There"));
    printf("HIGHLIGHT-WHITE-ing it up: '%s'\n", apply_format(HWHITE, "Hello There"));

    printf("------------------\n");
    printf("BACKGROUND-BLACK-ing it up: '%s'\n", apply_format(BGBLACK, "Hello There"));
    printf("BACKGROUND-RED-ing it up: '%s'\n", apply_format(BGRED, "Hello There"));
    printf("BACKGROUND-GREEN-ing it up: '%s'\n", apply_format(BGGREEN, "Hello There"));
    printf("BACKGROUND-YELLOW-ing it up: '%s'\n", apply_format(BGYELLOW, "Hello There"));
    printf("BACKGROUND-BLUE-ing it up: '%s'\n", apply_format(BGBLUE, "Hello There"));
    printf("BACKGROUND-MAGENTA-ing it up: '%s'\n", apply_format(BGMAGENTA, "Hello There"));
    printf("BACKGROUND-CYAN-ing it up: '%s'\n", apply_format(BGCYAN, "Hello There"));
    printf("BACKGROUND-WHITE-ing it up: '%s'\n", apply_format(BGWHITE, "Hello There"));

    printf("------------------\n");
    rgb_t c = {120, 0, 100};
    printf("256FG-ing it up: '%s'\n", foreground_256(c, "Hello There"));
    printf("256BG-ing it up: '%s'\n", background_256(c, "Hello There"));
    printf("256HI-ing it up: '%s'\n", highlight_256(c, "Hello There"));

    xcolor_image_t *image = image_to_xterm("/home/rossdylan/Downloads/10469154_10204348274165961_3225173628639169213_o.jpg");
    reduce_image(image);
}
