#include <stdio.h>
#include <stdlib.h>
#include <fab.h>


int main(int argc, char** argv) {
    char *bold = apply_color(BOLD, "Hello There");
    printf("BOLDING-ing it up: '%s'\n", bold);
    free(bold);

    char *italic = apply_color(ITALIC, "Hello There");
    printf("ITALIC-ing it up: '%s'\n", italic);
    free(italic);

    char *under = apply_color(UNDER, "Hello There");
    printf("UNDER-ing it up: '%s'\n", under);
    free(under);

    char *under2 = apply_color(UNDER2, "Hello There");
    printf("UNDER2-ing it up: '%s'\n", under2);
    free(under2);

    char *strike = apply_color(STRIKE, "Hello There");
    printf("STRIKE-ing it up: '%s'\n", strike);
    free(strike);


    char *blink = apply_color(BLINK, "Hello There");
    printf("BLINK-ing it up: '%s'\n", blink);
    free(blink);

    char *flip = apply_color(FLIP, "Hello There");
    printf("FLIP-ing it up: '%s'\n", flip);
    free(flip);


    printf("------------------\n");
    char *black = apply_color(BLACK, "Hello There");
    printf("BLACK-ing it up: '%s'\n", black);
    free(black);

    char *red = apply_color(RED, "Hello There");
    printf("RED-ing it up: '%s'\n", red);
    free(red);

    char *green = apply_color(GREEN, "Hello There");
    printf("GREEN-ing it up: '%s'\n", green);
    free(green);

    char *yellow = apply_color(YELLOW, "Hello There");
    printf("YELLOW-ing it up: '%s'\n", yellow);
    free(yellow);

    char *blue = apply_color(BLUE, "Hello There");
    printf("BLUE-ing it up: '%s'\n", blue);
    free(blue);

    char *magenta = apply_color(MAGENTA, "Hello There");
    printf("MAGENTA-ing it up: '%s'\n", magenta);
    free(magenta);

    char *cyan = apply_color(CYAN, "Hello There");
    printf("CYAN-ing it up: '%s'\n", cyan);
    free(cyan);

    char *white = apply_color(WHITE, "Hello There");
    printf("WHITE-ing it up: '%s'\n", white);
    free(white);

    printf("------------------\n");

    char *hblack = apply_color(HBLACK, "Hello There");
    printf("HBLACK-ing it up: '%s'\n", hblack);
    free(hblack);

    char *hred = apply_color(HRED, "Hello There");
    printf("HRED-ing it up: '%s'\n", hred);
    free(hred);

    char *hgreen = apply_color(HGREEN, "Hello There");
    printf("HGREEN-ing it up: '%s'\n", hgreen);
    free(hgreen);

    char *hyellow = apply_color(HYELLOW, "Hello There");
    printf("HYELLOW-ing it up: '%s'\n", hyellow);
    free(hyellow);

    char *hblue = apply_color(HBLUE, "Hello There");
    printf("HBLUE-ing it up: '%s'\n", hblue);
    free(hblue);

    char *hmagenta = apply_color(HMAGENTA, "Hello There");
    printf("HMAGENTA-ing it up: '%s'\n", hmagenta);
    free(hmagenta);

    char *hcyan = apply_color(HCYAN, "Hello There");
    printf("HCYAN-ing it up: '%s'\n", hcyan);
    free(hcyan);

    char *hwhite = apply_color(HWHITE, "Hello There");
    printf("HWHITE-ing it up: '%s'\n", hwhite);
    free(hwhite);

    printf("------------------\n");

    char *bgblack = apply_color(BGBLACK, "Hello There");
    printf("BGBLACK-ing it up: '%s'\n", bgblack);
    free(bgblack);

    char *bgred = apply_color(BGRED, "Hello There");
    printf("BGRED-ing it up: '%s'\n", bgred);
    free(bgred);

    char *bggreen = apply_color(BGGREEN, "Hello There");
    printf("BGGREEN-ing it up: '%s'\n", bggreen);
    free(bggreen);

    char *bgyellow = apply_color(BGYELLOW, "Hello There");
    printf("BGYELLOW-ing it up: '%s'\n", bgyellow);
    free(bgyellow);

    char *bgblue = apply_color(BGBLUE, "Hello There");
    printf("BGBLUE-ing it up: '%s'\n", bgblue);
    free(bgblue);

    char *bgmagenta = apply_color(BGMAGENTA, "Hello There");
    printf("BGMAGENTA-ing it up: '%s'\n", bgmagenta);
    free(bgmagenta);

    char *bgcyan = apply_color(BGCYAN, "Hello There");
    printf("BGCYAN-ing it up: '%s'\n", bgcyan);
    free(bgcyan);

    char *bgwhite = apply_color(BGWHITE, "Hello There");
    printf("BGWHITE-ing it up: '%s'\n", bgwhite);
    free(bgwhite);

    printf("------------------\n");
    rgb_t c = {120, 0, 100};
    char *f256 = foreground_256(c, "Hello There");
    char *bg256 = background_256(c, "Hello There");
    char *h256 = highlight_256(c, "Hello There");
    printf("256FG-ing it up: '%s'\n", f256);
    free(f256);
    printf("256BG-ing it up: '%s'\n", bg256);
    free(bg256);
    printf("256HI-ing it up: '%s'\n", h256);
    free(h256);

    if(argc >= 2) {
        xcolor_image_t *image = image_to_xterm(argv[1]);
        char *image_text = image_to_string(image);
        printf("%s", image_text);
        free(image_text);
        xcolor_image_free(image);
    }
}
