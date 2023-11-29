#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>


void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.

// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* texture)
{
	// Creates a variable to get the events.
	SDL_Event event;
	while (1)
	{
		draw(renderer, texture);
		// Waits for an event.
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			// If the "quit" button is pushed, ends the event loop.
			case SDL_QUIT:
			return;

			// If the window is resized, updates and redraws the diagonals.
			case SDL_WINDOWEVENT_RESIZED:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				draw(renderer, texture);
			}
			break;
		}
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


/* function that will determine the color of the pixel at position (x,y) */

inline Uint32 ReadPixel(SDL_Surface* surface, int x, int y)
{
	int bpp = surface -> format -> BytesPerPixel;

	Uint8 *p = (Uint8 *)surface -> pixels + y*surface -> pitch + x*bpp;

	switch (bpp)
	{
		case 1:
			return *p;
		case 2:
			return *(Uint16 *)p;
		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				return p[0]<<16 | p[1]<<8 | p[2];
			}
			else return p[0] | p[1]<<8 | p[2]<<16;
		case 4:
			return *(Uint32 *)p;
		default:
			return 0;
	}
}

/* function that write a pixel at position (x,y) */


inline void WritePixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
	int bpp=surface -> format -> BytesPerPixel;

	Uint8 *p = (Uint8 *)surface -> pixels + y*surface -> pitch + x*bpp;

	switch (bpp)
	{
		case 1:
			*p=pixel;
			break;
		case 2:
			*(Uint16 *)p = pixel;
			break;
		case 3:
			if (SDL_BYTEORDER==SDL_BIG_ENDIAN)
			{
				p[0]=(pixel>>16) & 0xff;
				p[1]=(pixel>>8) & 0xff;
				p[2]= pixel & 0xff;
			}
			else
			{
				p[0]=pixel & 0xff;
				p[1]=(pixel>>8) & 0xff;
				p[2]=(pixel>>16) & 0xff;
			}
			break;
		case 4:
			*(Uint32 *)p=pixel;
			break;
	}
}

/* function that will make a central rotation with an angle in parameter */

SDL_Surface* ImageRotation(SDL_Surface* surface, float angle)
{
	if ((int)angle%360 == 0) return surface;

	SDL_Surface* rotated;
	Uint32 color;
	int mx, my, mxrot, myrot;
	int bx, by;
	float rad;
	float tcos;
	float tsin;
	double wrot;
	double hrot;

	rad= -angle * M_PI / 180.0; // value of the angle in radian

	tcos=cos(rad);
	tsin=sin(rad);

	// length of the output image (witdh and height)
	wrot=ceil(surface->w*fabs(tcos)+surface->h*fabs(tsin));
	hrot=ceil(surface->w*fabs(tsin)+surface->h*fabs(tcos));

	// create the ouput surface in memory
	rotated=SDL_CreateRGBSurface(SDL_SWSURFACE, wrot, hrot,
	surface->format->BitsPerPixel,
	surface->format->Rmask,
	surface->format->Gmask,
	surface->format->Bmask,
	surface->format->Amask);

	if (rotated==NULL) return NULL;

	mxrot=rotated->w/2;
	myrot=rotated->h/2;
	mx=surface->w/2;
	my=surface->h/2;

	for (int j=0; j<rotated->h;j++)
	{
		for (int i=0;i<rotated->w; i++)
		{
			// determination of the new coordinates
			bx=(ceil(tcos*(i-mxrot)+tsin*(j-myrot)+mx));
			by=(ceil(-tsin*(i-mxrot)+tcos*(j-myrot)+my));
			if (bx>=0 && bx<surface->w && by>=0 && by<surface->h)
			{
				// keep the color of the pixel
				color=ReadPixel(surface, bx, by);
				// to put the pixel at the right place
				WritePixel(rotated, i, j, color);
			}
		}
	}
	return rotated;
}

int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 3)
        errx(EXIT_FAILURE, "Warning : missing arguments");

    // Initializes the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a window.
    SDL_Window* window = SDL_CreateWindow("rotation", 0, 0, 640, 400,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer
    (window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Create a surface from the colored image
    SDL_Surface* surface = load_image(argv[1]);

    SDL_Surface* rotated = ImageRotation(surface, atof(argv[2]));

    //Create a texture from the colored surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, rotated);
    if (texture==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());

    //Resize the window according to the size of the image
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_SetWindowSize(window, w, h);

    // Dispatches the events.
    event_loop(renderer, texture);

    // Destroys the objects.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}


