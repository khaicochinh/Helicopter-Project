// dinh nghia cac ham thuong dung trong project

#ifndef COMMON_FUNCTION_H_  // dinh nghia mot ham (learn about header guard)
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
// dinh dang cac thong so co dinh cho man hinh
const int WIDTH_BACKGROUND = 4800;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WITH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3; // so luong cac threat

// global variables (g_)
static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Event g_even;

// xu ly tranh trung lap ham 
namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
}

#endif