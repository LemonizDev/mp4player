#include "SDL.h"

static SDL_AUDIODeviceID audio_device = 0;

int main(int argc, char **argv){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO):

    SDL_AudioSpec wavspec;
    Uint8 *wavbuf = NULL;
    Uint32 wavlen = 0;
    if(SDL_LoadWAV("music.wav", &wavspec,&wavbuf,&wavlen)==NULL){
        fprintf(stderr, "Error, couldnt load WAV file %s\n",SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_AudioSpec desired;
    SDL_zero(desired);
    desired.freq = 4800;
    desired.format = AUDIO_F32;
    desired.channels = 2;
    desired.samples = 4086;
    desired.callback = NULL;

    audio_device = SDL_OpenAudioDevice(NULL,0,&desired,NULL,0);

    SDL_QueueAudio(audio_device,wavbuf,wavlen);
    SDL_FreeWAV(wavbuf);
    
    SDL_PauseAudioDevice(audio_device,0);
    SDL_Delay(5000);
    
    SDL_CloseAudioDevice(audio_device);
    SDL_Quit();
    return 0;
}