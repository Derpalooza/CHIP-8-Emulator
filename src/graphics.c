#include <SDL2/SDL.h>

#include "graphics.h"

#define CHIP8_DISPLAY_WIDTH		640
#define CHIP8_DISPLAY_HEIGHT	320

// Window and screen surfaces
static SDL_Window *s_window = NULL;
static SDL_Surface *s_screen_surface = NULL;

// Monochrome pixel surfaces
static SDL_Surface *s_white_pixel = NULL;
static SDL_Surface *s_black_pixel = NULL;

void graphics_init() {
	// Initialize SDL and create the window surface
	if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}

	s_window = SDL_CreateWindow("CHIP-8 Emulator",
															SDL_WINDOWPOS_UNDEFINED,
															SDL_WINDOWPOS_UNDEFINED,
															CHIP8_DISPLAY_WIDTH,
															CHIP8_DISPLAY_HEIGHT,
															SDL_WINDOW_SHOWN);

	if(s_window == NULL) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	// Initialize window to black screen
	s_screen_surface = SDL_GetWindowSurface(s_window);
	SDL_FillRect(s_screen_surface, NULL, SDL_MapRGB(s_screen_surface->format, 0, 0, 0));		
	SDL_UpdateWindowSurface(s_window);

	// Optimize pixel surfaces for repeated blitting
	SDL_Surface* surface = SDL_GetWindowSurface(s_window);

	// Initialize white pixel
	SDL_FillRect(surface, NULL, SDL_MapRGB(s_screen_surface->format, 255, 255, 255));
	s_white_pixel = SDL_ConvertSurface(surface, s_screen_surface->format, 0);

	// Initialize black pixel
	SDL_FillRect(surface, NULL, SDL_MapRGB(s_screen_surface->format, 0, 0, 0));
	s_black_pixel = SDL_ConvertSurface(surface, s_screen_surface->format, 0);	

	// Free space used by old surface
	SDL_FreeSurface(surface);
}

void graphics_blit(bool value, uint8_t x, uint8_t y) {
	SDL_Rect stretchRect = { .x = 10*x, .y = 10*y, .w = 10, .h = 10 };
	SDL_Surface* pixel = value ? s_white_pixel : s_black_pixel;
	SDL_BlitScaled(pixel, NULL, s_screen_surface, &stretchRect );
}

void graphics_update() {
	SDL_UpdateWindowSurface(s_window);
}

void graphics_close() {
	SDL_FreeSurface(s_white_pixel);
	SDL_FreeSurface(s_black_pixel);

	SDL_DestroyWindow(s_window);

	SDL_Quit();
}

