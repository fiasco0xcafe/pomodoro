#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int seconds = 0;
    time_t now = time(NULL);
    long int conversion;

    if (argc < 2){
        fprintf(stderr, "missing argument (pomodoro --help) for help\n");
    }
    else if (strcmp(argv[1], "--help") == 0){
        puts("Usage: pomodoro [MINUTES...]");
    }
    else {
        conversion = strtol(argv[1], NULL, 10);
        seconds = conversion * 60;
        sleep(seconds);
        time_t timer_secs = time(NULL);
        printf("Total for debugging = %ld\n", timer_secs);
    }
    return 0;
}
