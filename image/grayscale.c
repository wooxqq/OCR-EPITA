#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Updates the display.
//
// renderer: Renderer to draw on.
// texture: Texture that contains the image.
void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, 0, 0);
	SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* grayscale)
{
	// Creates a variable to get the events.
	SDL_Event event;
	SDL_Texture* t = grayscale;
	while (1)
	{
		draw(renderer, t);
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
				draw(renderer, t);
			}
			break;
		}
	}
}

// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
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

// Converts a colored pixel into grayscale.

// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
	Uint8 r, g, b;
	SDL_GetRGB(pixel_color, format, &r, &g, &b);
	Uint8 average = 0.3*r + 0.59*g + 0.11*b;
	r=g=b=average;
	Uint32 color = SDL_MapRGB(format, r, g, b);
	return color;
}

void surface_to_grayscale(SDL_Surface* surface)
{
	Uint32* pixels = surface->pixels;
	int len = surface->w * surface->h;
	SDL_PixelFormat* format = surface->format;
	if (SDL_LockSurface(surface))
	{
		errx(EXIT_FAILURE, "lock surface");
	}
	for (int i=0; i<len; i++)
	{
		pixels[i]=pixel_to_grayscale(pixels[i], format);
	}
	SDL_UnlockSurface(surface);
}

int main(int argc, char** argv)
{
    // Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Warning : missing arguments");

    // Initializes the SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a window.
    SDL_Window* window = SDL_CreateWindow("grayscale", 0, 0, 640, 400,
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

    //Create a texture from the colored surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());

    //Resize the window according to the size of the image
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_SetWindowSize(window, w, h);

    //Convert the surface into grayscale
    surface_to_grayscale(surface);

    //Create a new texture from the grayscale surface
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture==NULL) errx(EXIT_FAILURE, "%s", SDL_GetError());

    //Free the surface
    SDL_FreeSurface(surface);

    // Dispatches the events.
    event_loop(renderer, texture2);

    // Destroys the objects.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

