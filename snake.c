#include<stdio.h>
#include<SDL3/SDL.h>

#define WIDTH 900
#define HEIGHT 600
int main(){
    printf("Hello Snake\n");

    SDL_Init(SDL_INIT_VIDEO); // initialization for graphic lib
    SDL_Window* window= SDL_CreateWindow("Classic Snake", WIDTH, HEIGHT,0); // creating an window which opens in center of screen
    SDL_Delay(5000);
}
