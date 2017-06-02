#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>

#include "frames.h"

int main(int argc, char** argv) {
    char** frames;
    int* delays;
    int nbFrames = load_frames(&frames, &delays);
    int i;
    struct timeval stop, start;

    initscr();

    for (i = 0; i < nbFrames; i++) {
        gettimeofday(&start, NULL);
        mvprintw(0,0,"%s\n", frames[i]);
        refresh();
        gettimeofday(&stop, NULL);
        usleep(delays[i] - (stop.tv_usec - start.tv_usec));
    }

    for (int i = 0; i < nbFrames; i++) {
        free(frames[i]);
    }
    free(frames);
    free(delays);
    endwin();
    return 0;
}
