#define W 480
#define H 480
#define N 9
#define MAX_LINE_LENGTH 1000
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT (WINDOW_WIDTH)


#include <err.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>


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

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture,NULL,NULL);
    SDL_RenderPresent(renderer);
}


SDL_Surface* load_image(const char* path)
{
    SDL_Surface* s = IMG_Load(path);
    SDL_Surface* rs =  SDL_ConvertSurfaceFormat(s,SDL_PIXELFORMAT_RGB888,0);
    SDL_FreeSurface(s);
    return rs;
}


void event_loop()
{
    SDL_Event event;
    while(1)
    {
	SDL_WaitEvent(&event);
	switch(event.type)
	{
	   case SDL_QUIT:
		return;
	}
    }

}

int main(int argc, char **argv)
{
    if (argc!=2)
    {
         errx(EXIT_FAILURE, "Warning : missing arguments");
    }
    int grid[N][N];
    FILE *ptr =  fopen(argv[1],"r");
    txt_to_grid(ptr,grid);
 /*   for (int i =0;i<N;i++)
    {
	    for (int j = 0;j<N;j++)
	    {
		    printf("%d",grid[i][j]);
	    }
	    printf("\n");
    }*/

    SDL_Event event;
    SDL_Rect rect1,rect2,rect3,rect4,rect5,rect6,rect7,rect8,rect9;
    SDL_Renderer *renderer;
    SDL_Texture *texture1,*texture2,*texture3,*texture4,*texture5,*texture6,*texture7,*texture8,*texture9;

    SDL_Window *window;
    //SDL_Surface *surface;
    int quit=0;
    int count=0;
    char *font_path= "font.ttf"; 
    char *image = "empty_grid.jpg";
    //char *str =(char *) malloc 
    char *str = malloc(sizeof(char) * 28);
    //char temp;

    /* Inint TTF. */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    

    TTF_Init();
    TTF_Font *font = TTF_OpenFont(font_path, 42);
   
    if (font == NULL) {
        errx(EXIT_FAILURE, "error: font not found\n");
    }
  
	    
    /*temp = grid[0][0];
    strcat(str,temp);
    printf(str);*/
    texture1 = IMG_LoadTexture(renderer,image);
    //texture2 = IMG_LoadTexture(renderer,image);
 
    draw(renderer,texture1);
    draw(renderer,texture2);
    draw(renderer,texture3); 
    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' ';	
    }
    printf("\n");
    str[27] = 0;
    count++;
    //printf("%s",str);
    get_text_and_rect(renderer, 25, 12, str, font, &texture1, &rect1);
    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' '; 	
    }
    count++;
    get_text_and_rect(renderer, 30, 64, str, font, &texture2, &rect2);

    
    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' '; 	
    }
    count++;
    get_text_and_rect(renderer, 30, 116, str, font, &texture3, &rect3);

     for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' '; 	
    }
    count++;
    get_text_and_rect(renderer, 30, 168, str, font, &texture4, &rect4);


     for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';	
    	str[3*i+2] = ' '; 
    }
    count++;
    get_text_and_rect(renderer, 30, 220, str, font, &texture5, &rect5);

    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';	
    	str[3*i+2] = ' '; 
    }
    count++;
    get_text_and_rect(renderer, 30, 272, str, font, &texture6, &rect6);

    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' '; 	
    }
    count++;
    get_text_and_rect(renderer, 30, 324, str, font, &texture7, &rect7);

    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';	
	str[3*i+2] = ' '; 
    }
    count++;
    get_text_and_rect(renderer, 30, 376, str, font, &texture8, &rect8);

    for (int i=0;i<9;i++)
    {
	str[3*i] = grid[count][i]+48;
	str[(3*i)+1] = ' ';
	str[3*i+2] = ' '; 	
    }
    get_text_and_rect(renderer, 30, 428, str, font, &texture9, &rect9);

    while (!quit) 
    {	
       	SDL_WaitEvent(&event);

            if (event.type == SDL_QUIT) {
                quit = 1;
            }
	    if(event.type==SDL_WINDOWEVENT)
	    {
			if(event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
		   draw(renderer,texture1);
		}
	    }
        
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
          //SDL_RenderClear(renderer);

        /* Use TTF textures. */
        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);
	SDL_RenderCopy(renderer, texture3, NULL, &rect3);
	SDL_RenderCopy(renderer, texture4, NULL, &rect4);
	SDL_RenderCopy(renderer, texture5, NULL, &rect5);
	SDL_RenderCopy(renderer, texture6, NULL, &rect6);
	SDL_RenderCopy(renderer, texture7, NULL, &rect7);
	SDL_RenderCopy(renderer, texture8, NULL, &rect8);
	SDL_RenderCopy(renderer, texture9, NULL, &rect9);




        SDL_RenderPresent(renderer);
    }

    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    SDL_DestroyTexture(texture5);
    SDL_DestroyTexture(texture6);
    SDL_DestroyTexture(texture7);
    SDL_DestroyTexture(texture8);
    SDL_DestroyTexture(texture9);

    //SDL_DestroyTexture(texture);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;

}
