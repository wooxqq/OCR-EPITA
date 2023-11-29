#define W 480
#define H 480
#define N 9
#define MAX_LINE_LENGTH 1000
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT (WINDOW_WIDTH)


#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

void txt_to_grid(FILE *ptr,int grid[N][N])
{
    char line[MAX_LINE_LENGTH];
	size_t x=0;
	size_t count=0;
	while(fgets(line,MAX_LINE_LENGTH,ptr))
	{
		if(strlen(line)!=1) //si c'est une vraie ligne
		{
			for (size_t i=0;i<strlen(line);i++)
			{
				if(line[i]!=' ' && i!=11)//si il y'a un chiffre
				{
				   if (line[i]=='.'){grid[x][i-count] =0 ;}
				
				   else
				   {
					   grid[x][i-count] =(int)line[i]-48;
				   }
				}
			        else{count++;}	
			}
			x++;
		}
		count=0;
	}	
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) 
{
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {0, 0, 0, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}
int main(int argc,char* argv[])
{
    if (argc!=2)
    {
         errx(EXIT_FAILURE, "Warning : missing arguments");
    }
    int grid[N][N];
    FILE *ptr =  fopen(argv[1],"r");
    txt_to_grid(ptr,grid);

    SDL_Event event;
    SDL_Rect rect1, rect2;
    SDL_Renderer *renderer;
    SDL_Texture *texture1, *texture2;
    SDL_Window *window;
    char *font_path = "font.ttf";
    int quit;

    /* Inint TTF. */
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 24);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text_and_rect(renderer, 0, 0, "hello", font, &texture1, &rect1);
    get_text_and_rect(renderer, 0, rect1.y + rect1.h, "world", font, &texture2, &rect2);

    quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        /* Use TTF textures. */
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);

        SDL_RenderPresent(renderer);
    }

    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;

}
