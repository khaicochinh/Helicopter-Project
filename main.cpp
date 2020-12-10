 /**
  * Programming C ++ games using SDL
  *
  * This is a Helicopter game programming project
  * Author: Nguyen Van Ninh
  * Start day: 31.10.2020
  * Date of update: 09.12.2020
  */

#include "common_function.h"
#include "MainObject.h"
#include "ThreatObject.h"

using namespace std;

// constructor function
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
	bool is_run_screen = true;
	int bg_x = 0;
	bool is_quit = false;

	if(Init() == false)
	{
		return 0;
	}

	// load background
	g_bkground = SDLCommonFunc:: LoadImage("bg7200_3.png");
	if(g_bkground == NULL)
	{
		return 0;
	}
	
	// create object of type MainObject
	MainObject human_object; 
	human_object.SetRect(100, 200);
	bool ret = human_object.LoadImg("heli1.png");
	if(!ret)
	{
		return 0;
	}
	
	// create threat object
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for(int t = 0; t < NUM_THREATS; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if(p_threat) // luon kiem tra p_threat xem co khac NULL khong
		{
			ret = p_threat->LoadImg("ufo-threat.png");
			if(ret == false)
			{
				return 0;
			}
			 
			int rand_y = rand()%400;
			if(rand_y > SCREEN_HEIGHT - 200)
			{
				rand_y = SCREEN_HEIGHT*0.3;
			}

			p_threat->SetRect(SCREEN_WITH + t*300, rand_y);
			p_threat->set_x_val(3);

			AmoObject* p_amo = new AmoObject(); // tao mot doi tuong dan threat
			p_threat->InitAmo(p_amo); // nap dan vao threat
		}
	}

	// handle events
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

		// apply background
		// move background : way 1
		/*bg_x -= 2;
		SDLCommonFunc:: ApplySurface(g_bkground, g_screen, bg_x, 0);
		SDLCommonFunc:: ApplySurface(g_bkground, g_screen, bg_x + SCREEN_WITH, 0);
		if(bg_x <= -SCREEN_WITH)
		{
			bg_x = 0;
		}*/

		// move background : way 2
		if(is_run_screen == true)
		{
			bg_x -= 1;
			if(bg_x <= -(WIDTH_BACKGROUND - SCREEN_WITH))
			{
				is_run_screen = false;
			}
			else
			{
				SDLCommonFunc:: ApplySurface(g_bkground, g_screen, bg_x, 0); 
			}
		}
		else
		{
			SDLCommonFunc:: ApplySurface(g_bkground, g_screen, bg_x, 0); 
		}

		// implement main object
		human_object.Show(g_screen); // update lai vi tri cua doi tuong
		human_object.HandleMove();
		human_object.MakeAmo(g_screen);


		// implement threat object
		for(int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if(p_threat)
			{
				p_threat->Show(g_screen);
				p_threat->HandleMove(SCREEN_WITH, SCREEN_HEIGHT);
				p_threat->MakeAmo(g_screen, SCREEN_WITH, SCREEN_HEIGHT);
			}
		}

		// update screen
		if(SDL_Flip(g_screen) == -1)
			return 0;
	}
	 
	delete [] p_threats; 
	SDLCommonFunc:: CleanUp();
	 SDL_Quit();

	return 1;
}
	 