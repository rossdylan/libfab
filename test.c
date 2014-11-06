#include <stdio.h>
#include <stdlib.h>
#include <fab.h>


int main(int argc, char** argv) {
    printf("BOLDING-ing it up: '%s'\n", apply_color(BOLD, "Hello There"));
    printf("ITALIC-ing it up: '%s'\n", apply_color(ITALIC, "Hello There"));
    printf("UNDER-ing it up: '%s'\n", apply_color(UNDER, "Hello There"));
    printf("UNDER2-ing it up: '%s'\n", apply_color(UNDER2, "Hello There"));
    printf("STRIKE-ing it up: '%s'\n", apply_color(STRIKE, "Hello There"));
    printf("BLINK-ing it up: '%s'\n", apply_color(BLINK, "Hello There"));
    printf("FLIP-ing it up: '%s'\n", apply_color(FLIP, "Hello There"));

    printf("------------------\n");
    printf("BLACK-ing it up: '%s'\n", apply_color(BLACK, "Hello There"));
    printf("RED-ing it up: '%s'\n", apply_color(RED, "Hello There"));
    printf("GREEN-ing it up: '%s'\n", apply_color(GREEN, "Hello There"));
    printf("YELLOW-ing it up: '%s'\n", apply_color(YELLOW, "Hello There"));
    printf("BLUE-ing it up: '%s'\n", apply_color(BLUE, "Hello There"));
    printf("MAGENTA-ing it up: '%s'\n", apply_color(MAGENTA, "Hello There"));
    printf("CYAN-ing it up: '%s'\n", apply_color(CYAN, "Hello There"));
    printf("WHITE-ing it up: '%s'\n", apply_color(WHITE, "Hello There"));

    printf("------------------\n");
    printf("HIGHLIGHT-BLACK-ing it up: '%s'\n", apply_color(HBLACK, "Hello There"));
    printf("HIGHLIGHT-RED-ing it up: '%s'\n", apply_color(HRED, "Hello There"));
    printf("HIGHLIGHT-GREEN-ing it up: '%s'\n", apply_color(HGREEN, "Hello There"));
    printf("HIGHLIGHT-YELLOW-ing it up: '%s'\n", apply_color(HYELLOW, "Hello There"));
    printf("HIGHLIGHT-BLUE-ing it up: '%s'\n", apply_color(HBLUE, "Hello There"));
    printf("HIGHLIGHT-MAGENTA-ing it up: '%s'\n", apply_color(HMAGENTA, "Hello There"));
    printf("HIGHLIGHT-CYAN-ing it up: '%s'\n", apply_color(HCYAN, "Hello There"));
    printf("HIGHLIGHT-WHITE-ing it up: '%s'\n", apply_color(HWHITE, "Hello There"));

    printf("------------------\n");
    printf("BACKGROUND-BLACK-ing it up: '%s'\n", apply_color(BGBLACK, "Hello There"));
    printf("BACKGROUND-RED-ing it up: '%s'\n", apply_color(BGRED, "Hello There"));
    printf("BACKGROUND-GREEN-ing it up: '%s'\n", apply_color(BGGREEN, "Hello There"));
    printf("BACKGROUND-YELLOW-ing it up: '%s'\n", apply_color(BGYELLOW, "Hello There"));
    printf("BACKGROUND-BLUE-ing it up: '%s'\n", apply_color(BGBLUE, "Hello There"));
    printf("BACKGROUND-MAGENTA-ing it up: '%s'\n", apply_color(BGMAGENTA, "Hello There"));
    printf("BACKGROUND-CYAN-ing it up: '%s'\n", apply_color(BGCYAN, "Hello There"));
    printf("BACKGROUND-WHITE-ing it up: '%s'\n", apply_color(BGWHITE, "Hello There"));

    printf("------------------\n");
    rgb_t c = {120, 0, 100};
    printf("256FG-ing it up: '%s'\n", foreground_256(c, "Hello There"));
    printf("256BG-ing it up: '%s'\n", background_256(c, "Hello There"));
    printf("256HI-ing it up: '%s'\n", highlight_256(c, "Hello There"));

    xcolor_image_t *image = image_to_xterm("/home/rossdylan/Downloads/10469154_10204348274165961_3225173628639169213_o.jpg");
    reduce_image(image);
}
