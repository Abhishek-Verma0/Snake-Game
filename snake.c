#include<stdio.h>
#include<SDL3/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define CELL_SIZE 30  // simple size of single cell of grid, a squared cell
#define ROWS HEIGHT/CELL_SIZE   // getting number of rows for grid
#define COLUMNS WIDTH/CELL_SIZE // getting number of cols for grid
#define COLOR_GRID 0x1f1f1f1f // grid color
#define COLOR_WHITE 0xffffffff // Snake color
#define COLOR_APPLE 0xFFFF0000 // fruit color
#define LINE_WIDTH 2

#define SNAKE(x,y) fill_cell(surface,x,y,COLOR_WHITE)  // for snake
#define DRAW_GRID draw_grid(surface) // for the grid

#define APPLE(x,y) fill_cell(surface,x,y,COLOR_APPLE)
//  funciton for the drawing grid
int draw_grid(SDL_Surface *surface){
    //  making horizontal line for the gird 
    SDL_Rect line = {0, 0, WIDTH, LINE_WIDTH};
    for (line.y = 0; line.y < HEIGHT;line.y+=CELL_SIZE){ // line is moved down at every step by cell size 
        //  each iteration draw one horizontal line
        SDL_FillSurfaceRect(surface, &line, COLOR_GRID);
    }

    //  making vertical line for the grid
    line.y = 0; // reset y so vertical line start from very top
    line.h = HEIGHT; // gives height of window to line 
    line.w = LINE_WIDTH; // thickenss of line

    for (line.x = 0; line.x < WIDTH;line.x+=CELL_SIZE)
    {
        SDL_FillSurfaceRect(surface, &line, COLOR_GRID);
    }
}


//  for snake 
void fill_cell(SDL_Surface* surface, int x,int y,Uint32 color){
    SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillSurfaceRect(surface, &rect, color);
}

int main(){
    printf("Hello Snake\n");

    SDL_Init(SDL_INIT_VIDEO); // initialization for graphic lib
    SDL_Window* window= SDL_CreateWindow("Classic Snake", WIDTH, HEIGHT,0); // creating an window which opens in center of screen

    SDL_Surface *surface = SDL_GetWindowSurface(window); //drawing on window

    SDL_Event event;
    //  writing game loop
    int game = 1;
    int snake_x = 5;
    int snake_y = 5;
    int apple_x = 10;
    int apple_y = 14;
    while(game){

        while(SDL_PollEvent(&event)){
            if(event.type== SDL_EVENT_QUIT){
                game = 0;
            }
            if(event.type==SDL_EVENT_KEY_DOWN){
                if(event.key.key==SDLK_RIGHT){
                    snake_x++;
                }
                if(event.key.key==SDLK_LEFT){
                    snake_x--;
                }
                if(event.key.key==SDLK_UP){
                    snake_y--;
                }
                if(event.key.key==SDLK_DOWN){
                    snake_y++;
                }
            }
        }
        
        
       
        SNAKE( snake_x, snake_y);
        APPLE(apple_x, apple_y);
        DRAW_GRID;
        SDL_UpdateWindowSurface(window);
        SDL_Delay(20);
    }

}
