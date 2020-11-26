
#include "common_function.h"
using namespace std;

// load image function
SDL_Surface* SDLCommonFunc:: LoadImage(string file_path)
{
	SDL_Surface* load_image = NULL;
    SDL_Surface* optimize_image = NULL;
    load_image = IMG_Load(file_path.c_str());
    if (load_image != NULL)
    {
		optimize_image= SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		// transparent background - lam mat mau background
		if (optimize_image != NULL) 
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}

	return optimize_image;
}

// load image to screen
void SDLCommonFunc:: ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
}

// giai phong bo nho
void SDLCommonFunc:: CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}