#include<stdio.h>
#include<stdlib.h>
#include<SDL3/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define CELL_SIZE 30  // simple size of single cell of grid, a squared cell
#define ROWS HEIGHT/CELL_SIZE   // getting number of rows for grid
#define COLUMNS WIDTH/CELL_SIZE // getting number of cols for grid
#define COLOR_GRID 0x1f1f1f1f // grid color
#define COLOR_WHITE 0xffffffff // Snake color
#define COLOR_APPLE 0xFFFF0000 // fruit color
#define COLOR_BLACK 0x00000000 //black color
#define LINE_WIDTH 2

#define SNAKE(x,y) fill_cell(psurface,x,y,COLOR_WHITE)  // for snake
#define DRAW_GRID draw_grid(psurface) // for the grid

#define APPLE(x,y) fill_cell(psurface,x,y,COLOR_APPLE)



//  creating data structure to store the snake coord and whole snake body coords like linked list
struct SnakeElement
{
    int x, y;

    //  can be null in case of last element
    struct SnakeElement *pnext;
};

struct Direction
{ // only one value should be !=0 at one time so one dirxn movement can be done
    int dx,dy;
};

struct Apple{
    int x, y;
};

//  funciton for the drawing grid
int draw_grid(SDL_Surface *psurface){
    //  making horizontal line for the gird 
    SDL_Rect line = {0, 0, WIDTH, LINE_WIDTH};
    for (line.y = 0; line.y < HEIGHT;line.y+=CELL_SIZE){ // line is moved down at every step by cell size 
        //  each iteration draw one horizontal line
        SDL_FillSurfaceRect(psurface, &line, COLOR_GRID);
    }

    //  making vertical line for the grid
    line.y = 0; // reset y so vertical line start from very top
    line.h = HEIGHT; // gives height of window to line 
    line.w = LINE_WIDTH; // thickenss of line

    for (line.x = 0; line.x < WIDTH;line.x+=CELL_SIZE)
    {
        SDL_FillSurfaceRect(psurface, &line, COLOR_GRID);
    }
}


//  for snake 
void fill_cell(SDL_Surface* psurface, int x,int y,Uint32 color){
    SDL_Rect rect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillSurfaceRect(psurface, &rect, color);
}

//  funciton to draw snake
void draw_snake(SDL_Surface *psurface,struct SnakeElement *psnake){
    if(psnake!=NULL){

        SNAKE(psnake->x, psnake->y);
        draw_snake(psurface, psnake->pnext);
    }

}

struct SnakeElement move_snake(struct SnakeElement *psnake,  struct Direction *pdirection){

    if(psnake->pnext==NULL){
      return  (struct SnakeElement){psnake->x + pdirection->dx,psnake->y + pdirection->dy,NULL};
        
    }
    //  remove last element
    struct SnakeElement *plast=psnake;
    size_t num_elements = 0;
    while (plast->pnext!=NULL)
    {
        plast=plast->pnext;
        num_elements++;
    }
    if(num_elements>1){
        struct SnakeElement *pBeforeLast=psnake;

        while (pBeforeLast->pnext!=plast){
            pBeforeLast = pBeforeLast->pnext;
            pBeforeLast->pnext = NULL;
        }
    }
    //create new head
    struct SnakeElement new_head = {psnake->x + pdirection->dx,psnake->y + pdirection->dy,psnake};

    return new_head;
}

//  function to get new coords of apple once eaten by snake
void reset_apple(struct SnakeElement *psnake ,struct Apple *papple){
    papple->x = COLUMNS * ((double)rand() / RAND_MAX);
    papple->y = ROWS * ((double)rand() / RAND_MAX);
    //  if apple coords lies on snake body coords find new one
    struct SnakeElement *pcurrent = psnake; 
//  checking if new coord of apple lies on snake body or not recursively
    do {
        
        if(pcurrent->x==papple->x && pcurrent->y==papple->y){
            reset_apple(psnake, papple);
            break;
        }
        pcurrent = pcurrent->pnext;

    } while (pcurrent != NULL);
}


// ***** function to add length to snake once it eats an apple
struct SnakeElement lengthen_snake(struct SnakeElement *psnake, struct Direction *pdirection){
    struct SnakeElement new_head = {psnake->x + pdirection->dx,psnake->y + pdirection->dy,psnake}; //technically new snake

    return new_head;
}


int main(){
   

    SDL_Init(SDL_INIT_VIDEO); // initialization for graphic lib
    SDL_Window* window= SDL_CreateWindow("Classic Snake", WIDTH, HEIGHT,0); // creating an window which opens in center of screen

    SDL_Surface *psurface = SDL_GetWindowSurface(window); //drawing on window

    SDL_Event event;

    struct SnakeElement snake = {5,5,NULL};
    struct SnakeElement *psnake = &snake; //pointer to snake
    struct Direction direction = {0, 0};
    struct Direction *pdirection = &direction; //pointer to directon
    struct Apple apple;
    struct Apple *papple = &apple;
    reset_apple(psnake, papple); // make sure coord do not collide


    SDL_Rect override_rect = {0, 0, WIDTH, HEIGHT}; // it is for like if snake moves from one block to next then previous should get back to normal grid 

    //  writing game loop
    int game = 1;
  
   
    while(game){
       
        while(SDL_PollEvent(&event)){
            if(event.type== SDL_EVENT_QUIT){
                game = 0;
            }
            if(event.type==SDL_EVENT_KEY_DOWN){
                direction = (struct Direction){0, 0};
                if(event.key.key==SDLK_RIGHT){
                    direction.dx = 1;
                     }
                if(event.key.key==SDLK_LEFT){
                    direction.dx = -1;
                    }
                if(event.key.key==SDLK_UP){
                    direction.dy = -1;
                }
                if(event.key.key==SDLK_DOWN){
                    direction.dy = 1;  
                }
            }
        }
        if(direction.dx==0 && direction.dy==0){
            direction.dx = 1;
        }

        SDL_FillSurfaceRect(psurface,&override_rect,COLOR_BLACK);
        
      struct SnakeElement moved_snake= move_snake(psnake, pdirection);
      struct SnakeElement *pmoved_snake = &moved_snake;

      if (psnake->x == papple->x && psnake->y == papple->y)
      {
          reset_apple(psnake, papple);
          moved_snake = lengthen_snake(pmoved_snake, pdirection);
          pmoved_snake = &moved_snake;
      }

        APPLE(papple->x, papple->y);
        draw_snake(psurface, pmoved_snake);
        DRAW_GRID;
        SDL_UpdateWindowSurface(window);
        SDL_Delay(300);
    }

    
}
