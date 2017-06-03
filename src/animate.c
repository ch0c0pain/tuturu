#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <pthread.h>

#include "frames.h"
#include "sound.h"

void *sound_thread(void* data) {
    play_tuturu();
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    char** frames;
    int* delays;
    int nbFrames = load_frames(&frames, &delays);
    int i;
    struct timeval stop, start;
    pthread_t sndThread;

    pthread_create(&sndThread, NULL, sound_thread, NULL);

    initscr();

    for (i = 0; i < nbFrames; i++) {
        gettimeofday(&start, NULL);
        mvprintw(0,0,"%s\n", frames[i]);
        refresh();
        gettimeofday(&stop, NULL);
        usleep(delays[i] - (stop.tv_usec - start.tv_usec));
    }

    for (i = 0; i < nbFrames; i++) {
        free(frames[i]);
    }
    free(frames);
    free(delays);
    endwin();

    pthread_exit(NULL);
    return 0;
}
