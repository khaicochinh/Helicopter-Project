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
#include "ExplosionObject.h"

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
	MainObject plane_object; 
	plane_object.SetRect(100, 200);
	bool ret = plane_object.LoadImg("heli_main1.png");
	if(!ret)
	{
		return 0;
	}
	

	// init explosion object
	ExplosionObject exp_main;
	ret = exp_main.LoadImg("exp_main.png");
	exp_main.set_clip();
	if(!ret) return 0;



	// create threat object
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for(int t = 0; t < NUM_THREATS; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if(p_threat) // luon kiem tra p_threat xem co khac NULL khong
		{
			ret = p_threat->LoadImg("heli_threat1.png");
			if(ret == false)
			{
				return 0;
			}
			 
			double rand_y = rand()%400;
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
			plane_object.HandleInputAction(g_even);
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
		plane_object.HandleMove();
		plane_object.Show(g_screen); // update lai vi tri cua doi tuong
		plane_object.MakeAmo(g_screen);


		// implement threat object
		for(int tt = 0; tt < NUM_THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if(p_threat)
			{
				p_threat->HandleMove(SCREEN_WITH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WITH, SCREEN_HEIGHT);

				// update screen
				if(SDL_Flip(g_screen) == -1)
					return 0;
				
				// check collision main & threats
				bool is_col =  SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
				if(is_col)
				{
					for(int ex = 0; ex < 4; ex ++)
					{
						int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
						int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

						exp_main.set_frame(ex);
						exp_main.SetRect(x_pos, y_pos);
						exp_main.ShowEx(g_screen);

						SDL_Delay(100);

						// update screen
						if(SDL_Flip(g_screen) == -1)
							return 0;
					}

					if(MessageBox(NULL, L"GAME OVER!", L"Notice", MB_OK) == IDOK)
					{
						delete [] p_threats; 
						SDLCommonFunc:: CleanUp();
						SDL_Quit();
						return 1;
					}
				}

				// check collision main & bullet threat
				std::vector<AmoObject*> amo_list = p_threat->GetAmoList();
				for(int im = 0; im < amo_list.size(); im ++)
				{
					AmoObject* p_amo = amo_list.at(im); 
					if(p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_amo->GetRect());
						if(ret_col)
						{
							for(int ex = 0; ex < 4; ex ++)
							{
								int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH*0.5;
								int y_pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

								exp_main.set_frame(ex);
								exp_main.SetRect(x_pos, y_pos);
								exp_main.ShowEx(g_screen);

								SDL_Delay(100);

								// update screen
								if(SDL_Flip(g_screen) == -1)
									return 0;
							}

							if(MessageBox(NULL, L"GAME OVER!", L"Notice ^^", MB_OK) == IDOK)
							{
								/*delete [] p_threats; 
								SDLCommonFunc:: CleanUp();
								SDL_Quit();*/
								return 1;
							}
						}
					}
				}

				std::vector<AmoObject*> amo_list2 = plane_object.GetAmoList();
				for(int am = 0; am < amo_list2.size(); am ++)
				{
					AmoObject* p_amo = amo_list2.at(am); // da co con tro thi luon phai kiem tra xem no co NULL hay khong
					if(p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if(ret_col)
						{
							for(int ex = 0; ex < 4; ex ++)
							{
								int x_pos = (p_amo->GetRect().x + p_amo->GetRect().w*0.5) - EXP_WIDTH*0.5;
								int y_pos = (p_amo->GetRect().y + p_amo->GetRect().h*0.5) - EXP_HEIGHT*0.5;

								exp_main.set_frame(ex);
								exp_main.SetRect(x_pos, y_pos);
								exp_main.ShowEx(g_screen);

								// update screen
								if(SDL_Flip(g_screen) == -1)
									return 0;
							}
							p_threat->Reset(SCREEN_WITH + tt*300);
							plane_object.RemoveAmo(am);
						}
					}
				}
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
	 