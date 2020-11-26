#include "common_function.h"
#include "MainObject.h"

using namespace std;

// ham khoi tao
bool Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}

	g_screen = SDL_SetVideoMode(SCREEN_WITH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(g_screen == NULL)
		return false;

	return true;
}

// main function
int main(int arc, char*argv[]) 
{
	bool is_quit = false;

	if(Init() == false)
	{
		return 0;
	}

	// load background
	g_bkground = SDLCommonFunc:: LoadImage("bkground2.png");
	if(g_bkground == NULL)
	{
		return 0;
	}
	
	MainObject human_object; // khoi tao mot doi tuong kieu MainObject
	human_object.SetRect(100, 200);
	bool ret = human_object.LoadImg("heli1.png");
	if(!ret)
	{
		return 0;
	}
	
	// xu ly cac su kien
	while(!is_quit)
	{
		while (SDL_PollEvent(&g_even)) 
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even);
		}

		SDLCommonFunc:: ApplySurface(g_bkground, g_screen, 0, 0);
		human_object.Show(g_screen); // update lai vi tri cua doi tuong
		human_object.HandleMove();
		if(SDL_Flip(g_screen) == -1)
			return 0;
	 }

	 SDLCommonFunc:: CleanUp();
	 SDL_Quit();

	 return 1;
}
	 