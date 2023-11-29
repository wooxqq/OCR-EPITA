#include "images.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#define MAXCHAR 10000

inline Uint32 LookPixel(SDL_Surface* surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	switch(bpp)
	{
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				return p[0] << 16 | p[1] << 8 | p[2];
			}
			else
			{
				return p[0] | p[1] << 8 | p[2] << 16;
			}
		case 4:
			return *(Uint32 *)p;
		default:
			return 0;
	}
}

SDL_Surface* load_image(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if (surface==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_Surface* surface2 = SDL_ConvertSurfaceFormat
        (surface, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(surface);
	if (surface2==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());
	return surface2;
}


Matrix* surfacetomatrix(SDL_Surface* surface)
{
	Matrix* matrice = matrix_create(surface->w,surface->h);
	int white = 0;
	int black =1;
	for (int i=0; i<matrice->rows; i++)
	{
		for (int j=0; i<matrice->cols; j++)
		{
			Uint8 r, g, b;
			SDL_GetRGB(LookPixel(surface,i,j), surface->format, &r, &g, &b);
			matrice->entries[i][j] = (r > 150) ? black : white;
		}
	}
	return matrice;
}


/*char* surfacetofile(SDL_Surface* surface)
{
	char* ans=malloc(sizeof(char *)*28*28*2);
	int white = 0;
	int black = 1;
	for (int i=0; i<surface->w; i++)//28
	{
		for (int j =0; j<surface->h; j++)//28
		{
			Uint8 r, g ,b;
			SDL_GetRGB(LookPixel(surface,i,j), surface->format, &r, &g, &b);
			ans[i+j]= (r > 150) ? black : white;
			ans[i+j+1]=',';
		}
	}
	return ans;
}

Img** csv_to_imgs(char* file_string, int number_of_imgs) {
	FILE *fp;
	Img** imgs = malloc(number_of_imgs * sizeof(Img*));
	char row[MAXCHAR];
	fp = fopen(file_string, "r");

	// Read the first line 
	fgets(row, MAXCHAR, fp);
	int i = 0;
	while (feof(fp) != 1 && i < number_of_imgs) {
		imgs[i] = malloc(sizeof(Img));
		int j = 0;
		fgets(row, MAXCHAR, fp);
		char* token = strtok(row, ",");
		imgs[i]->img_data = matrix_create(28, 28);
		while (token != NULL) {
			if (j == 0) 
			{
				imgs[i]->label = atoi(token);
			} 
			else
			{
				imgs[i]->img_data->entries[(j-1) / 28][(j-1) % 28] = atoi(token) / 256.0;
			}
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
	fclose(fp);
	return imgs;
}

void img_print(Img* img) {
	matrix_print(img->img_data);
	printf("Img Label: %d\n", img->label);
}

void img_free(Img* img) {
	matrix_free(img->img_data);
	free(img);
	img = NULL;
}

void imgs_free(Img** imgs, int n) {
	for (int i = 0; i < n; i++) {
		img_free(imgs[i]);
	}
}
*/

int main(int argc,char** argv)
{
	SDL_Surface* surface=load_image("../../utils/digit-1.png");
	Matrix* m=surfacetomatrix(surface);
	matrix_print(m);
}
