#include<stdio.h>
#include<stdlib.h>
#include<SDL3/SDL.h>
#include<assert.h>

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


size_t snake_size(struct SnakeElement **ppsnake){
    assert(ppsnake != NULL);
    assert(*ppsnake != NULL);
    size_t list_size = 1;
    struct SnakeElement *current = *ppsnake;
    
    while (current->pnext != NULL){
        assert(current->x >= 0 && current->x < COLUMNS && current->y >= 0 && current->y < ROWS);
        current = current->pnext;
        list_size++;
    }
    return list_size;
}

//  funciton to draw snake
void draw_snake(SDL_Surface *psurface,struct SnakeElement **ppsnake){
    assert(psurface != NULL);
    assert(ppsnake != NULL);
    assert(*ppsnake != NULL);
    assert(snake_size(ppsnake)==3);
    struct SnakeElement *psnake = *ppsnake;
    int debug_snake_size = 0;
    while(psnake!=NULL){
        
        SNAKE(psnake->x, psnake->y);
        psnake = psnake->pnext;
        debug_snake_size++;
    }
    assert(snake_size(ppsnake) == debug_snake_size);
}


void move_snake(struct SnakeElement **ppsnake,  struct Direction *pdirection){
    //  remove last element
    assert(ppsnake != NULL);
    assert(*ppsnake != NULL);
   

    if(pdirection->dx == 0 && pdirection->dy == 0)
    {
        return;
    }
    size_t size = snake_size(ppsnake);

    if(size==1){

        (*ppsnake)->x += pdirection->dx;
        (*ppsnake)->y += pdirection->dy;
    }
    else{
        //  Append snake element at end of linked list
        struct SnakeElement *pcurrent = *ppsnake;
        int previous_x = pcurrent->x;
        int previous_y = pcurrent->y;

        pcurrent->x += pdirection->dx;
        pcurrent->y += pdirection->dy;
        
        while(pcurrent->pnext!=NULL){

            pcurrent = pcurrent->pnext;

            int tmp_x = pcurrent->x;
            int tmp_y = pcurrent->y;

            pcurrent->x = previous_x;
            pcurrent->y = previous_y;

            previous_x = tmp_x;
            previous_y = tmp_y;
        }
    }
    printf("Snake size =%zu\n", size);
}

//  funciton to get new coords of apple once eaten by snake
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


// ***** funtion to add length to snake once it eats an apple
void lengthen_snake(struct SnakeElement *psnake, struct Direction *pdirection){
    struct SnakeElement new_head = {psnake->x + pdirection->dx,psnake->y + pdirection->dy,psnake}; //technically new snake

    

}


int main(){
    printf("Hello Snake\n");

    SDL_Init(SDL_INIT_VIDEO); // initialization for graphic lib
    SDL_Window* window= SDL_CreateWindow("Classic Snake", WIDTH, HEIGHT,0); // creating an window which opens in center of screen

    SDL_Surface *psurface = SDL_GetWindowSurface(window); //drawing on window

    SDL_Event event;
    
    struct SnakeElement snake = {5,5,NULL};
    struct SnakeElement snakeTail = {5, 6, NULL};
    struct SnakeElement snakeTail2 = {5, 7, NULL};
    snake.pnext = &snakeTail;
    snakeTail.pnext = &snakeTail2;
    struct SnakeElement *psnake = &snake; //pointer to snake
    struct SnakeElement **ppsnake = &psnake; //pointer to snake
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



        // if(direction.dx==0 && direction.dy==0){
        //     direction.dx = 1;
        // }

        SDL_FillSurfaceRect(psurface,&override_rect,COLOR_BLACK);

        move_snake(ppsnake,  pdirection);
        

        if(psnake->x==papple->x && psnake->y==papple->y){
            reset_apple(psnake,papple);
            
            lengthen_snake(psnake, pdirection);
            
        }

        APPLE(papple->x, papple->y);
        draw_snake(psurface, ppsnake);
        DRAW_GRID;
        SDL_UpdateWindowSurface(window);
        SDL_Delay(300);
    }

    
}
