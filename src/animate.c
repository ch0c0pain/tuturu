#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>
#include <unistd.h>

#include "frames.h"

int main(int argc, char** argv) {
    char buf[1024];
    char *str;
    char** frames;
    int* delays;
    int nbFrames = load_frames(&frames, &delays);
    int i;

    tgetent(buf, getenv("TERM"));
    str = tgetstr("cl", NULL);

    for (i = 0; i < nbFrames; i++) {
        fputs(str, stdout);
        printf("%s\n", frames[i]);
        usleep(delays[i]);
    }

    for (int i = 0; i < nbFrames; i++) {
        free(frames[i]);
    }
    free(frames);
    free(delays);
    return 0;
}
