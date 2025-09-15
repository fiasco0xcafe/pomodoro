#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

void print_help (void){
    puts("Usage: pomodoro [MINUTES...]");
}

void print_version (void){
    puts("pomodoro version 0.1.0");
}

int main (int argc, char **argv){
    ma_result result;
    ma_decoder decoder;
    ma_device_config deviceConfig;
    ma_device device;
    char *endptr;
    int seconds = 0;
    time_t now = time(NULL);
    long int conversion;

    if (argc < 3){
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
        conversion = strtol(argv[2], &endptr, 10);
            if (endptr == argv[2]){
                puts("Enter the timer length in minutes.");
            }

            else if (*endptr != '\0'){
                printf("Invalid character: %c\n", *endptr);
            }
            else {
                seconds = conversion * 60;
                sleep(seconds);
                time_t timer_secs = time(NULL);
                result = ma_decoder_init_file(argv[1], NULL, &decoder);
                if (result != MA_SUCCESS) {
                    printf("Could not load file: %s\n", argv[1]);
                    return 1;
            }
                deviceConfig = ma_device_config_init(ma_device_type_playback);
                deviceConfig.playback.format   = decoder.outputFormat;
                deviceConfig.playback.channels = decoder.outputChannels;
                deviceConfig.sampleRate        = decoder.outputSampleRate;
                deviceConfig.dataCallback      = data_callback;
                deviceConfig.pUserData         = &decoder;
                if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) {
                    printf("Failed to open playback device.\n");
                    ma_decoder_uninit(&decoder);
                    return -3;
            }

                if (ma_device_start(&device) != MA_SUCCESS) {
                    printf("Failed to start playback device.\n");
                    ma_device_uninit(&device);
                    ma_decoder_uninit(&decoder);
                    return -4;
            }

                printf("Press Enter to quit...");
                getchar();

                ma_device_uninit(&device);
                ma_decoder_uninit(&decoder);
            }
    }
    return 0;
}
