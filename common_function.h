// dinh nghia cac ham thuong dung trong project

#ifndef COMMON_FUNCTION_H_  // dinh nghia mot ham (learn about header guard)
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;
// dinh dang cac thong so co dinh cho man hinh
const int WIDTH_BACKGROUND = 7200;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WITH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 5; // so luong cac threat

// global variables (g_)
static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface *g_img_menu = NULL;
static SDL_Surface *g_game_over = NULL;

static SDL_Event g_even;

static Mix_Chunk* g_sound_bg;
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[3];

// xu ly tranh trung lap ham 
namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void AppluSurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y); // apply surface for explosion
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);

	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif