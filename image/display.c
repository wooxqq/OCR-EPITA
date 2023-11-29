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
// texture: Texture to display.
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
			case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				draw(renderer, texture);
			}
			break;
		}
	}
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
    SDL_Window* window = SDL_CreateWindow("display", 0, 0, 640, 400,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Creates a texture that contains the image
    SDL_Texture* texture = IMG_LoadTexture(renderer, argv[1]);
    if (texture == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Gets the width and the height of the texture.
    int w, h;
    if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    // Resizes the window
    SDL_SetWindowSize(window, w, h);

    // Dispatches the events.
    event_loop(renderer, texture);

    // Destroys the objects.
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
