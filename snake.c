#include<stdio.h>
#include<SDL3/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define CELL_SIZE 15  // simple size of single cell of grid, a squared cell
#define ROWS HEIGHT/CELL_SIZE   // getting number of rows for grid
#define COLUMNS WIDTH/CELL_SIZE // getting number of cols for grid
#define GRID_COLOR 0x1f1f1f1f // grid color
#define LINE_WIDTH 2
//  funciton for the drawing grid
int draw_grid(SDL_Surface *surface){
    //  making horizontal line for the gird 
    SDL_Rect line = {0, 0, WIDTH, LINE_WIDTH};
    for (line.y = 0; line.y < HEIGHT;line.y+=CELL_SIZE){ // line is moved down at every step by cell size 
        //  each iteration draw one horizontal line
        SDL_FillSurfaceRect(surface, &line, GRID_COLOR);
    }

    //  making vertical line for the grid
    line.y = 0; // reset y so vertical line start from very top
    line.h = HEIGHT; // gives height of window to line 
    line.w = LINE_WIDTH; // thickenss of line

    for (line.x = 0; line.x < WIDTH;line.x+=CELL_SIZE)
    {
        SDL_FillSurfaceRect(surface, &line, GRID_COLOR);
    }
}

int main(){
    printf("Hello Snake\n");

    SDL_Init(SDL_INIT_VIDEO); // initialization for graphic lib
    SDL_Window* window= SDL_CreateWindow("Classic Snake", WIDTH, HEIGHT,0); // creating an window which opens in center of screen

    SDL_Surface *surface = SDL_GetWindowSurface(window); //drawing on window
    SDL_Rect rect = {200, 200, 200, 200};
    // SDL_FillRect(surface, &rect, 0xffffffff); // this was used in sdl2 now it has become FillSurfaceRect in sdl3
    SDL_FillSurfaceRect(surface, &rect, 0xffffffff);

    draw_grid(surface);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
}
