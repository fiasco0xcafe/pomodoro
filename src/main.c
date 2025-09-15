#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "miniaudio.h"
#define MINIAUDIO_IMPLEMENTATION


void alarm_audio (void){
    
}

void print_help (void){
    puts("Usage: pomodoro [MINUTES...]");
}

void print_version (void){
    puts("pomodoro version 0.1.0");
}

int main (int argc, char **argv){
    char *endptr;
    int seconds = 0;
    time_t now = time(NULL);
    long int conversion;

    if (argc < 2){
        fprintf(stderr, "missing argument (pomodoro --help) for help\n");
        return 1;
    }
    else if (strcmp(argv[1], "--help") == 0){
        print_help();
    }
    else if (strcmp(argv[1], "--version") == 0){
        print_version();
    }
    else {
        conversion = strtol(argv[1], &endptr, 10);
            if (endptr == argv[1]){
                puts("Enter the timer length in minutes.");
            }

            else if (*endptr != '\0'){
                printf("Invalid character: %c\n", *endptr);
            }
            else {
                seconds = conversion * 60;
                sleep(seconds);
                time_t timer_secs = time(NULL);
                printf("Total for debugging = %ld\n", timer_secs);
            }
    }
    return 0;
}
