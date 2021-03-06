 /**
  * Programming C ++ games using SDL
  *
  * This is a Helicopter game programming project
  * Author: Nguyen Van Ninh
  * Start day: 31.10.2020
  * Date of update: 03.01.2021
  */

#include "common_function.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"


TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;

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

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )
		return false;

	// read file .wav audio
	g_sound_bg = Mix_LoadWAV("avenger_soundtrack.wav");
	g_sound_bullet[0] = Mix_LoadWAV("bullet_main.wav");
	g_sound_bullet[1] = Mix_LoadWAV("bullet_main1.wav");
	g_sound_exp[0] = Mix_LoadWAV("explosion1.wav");
	g_sound_exp[1] = Mix_LoadWAV("explosion.wav");
	// g_sound_exp[2] = Mix_LoadWAV("game_over.wav");

	if(g_sound_bg == NULL || g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL)
	{
		return false;
	}

	if(TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("Amatic-Bold.ttf", 20);
	g_font_menu = TTF_OpenFont("28 Days Later.ttf", 40);
	if(g_font_text == NULL)
	{
		return false;
	}

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
	g_bkground = SDLCommonFunc:: LoadImage("bg7200.png");
	if(g_bkground == NULL)
	{
		return 0;
	}
	Mix_PlayChannel(-1, g_sound_bg, 0);

	// make player power
	PlayerPower player_power ;
	player_power.Init();

	// text object
	TextObject time_game;
	time_game.SetColor(TextObject::BLACK_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::BLACK_TEXT);


	// create object of type MainObject
	MainObject plane_object; 
	plane_object.SetRect(100, 300);
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

	unsigned int die_number = 0 ; // so lan chet cua main
	unsigned int mark_value = 0; // bien quan ly diem

	// show menu
	int ret_menu = SDLCommonFunc :: ShowMenu(g_screen, g_font_menu);
	if(ret_menu == 1)
		is_quit = true;

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
			plane_object.HandleInputAction(g_even, g_sound_bullet);
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

		// show player power
		player_power.Render(g_screen) ;

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

					Mix_PlayChannel(-1, g_sound_exp[1], 0);
					die_number++;
					if(die_number <=2){
						SDL_Delay(1500) ;
						plane_object.SetRect(100, 300) ;
						player_power.Decrease() ;
						player_power.Render(g_screen) ;

						if(SDL_Flip(g_screen) == -1 ){
							delete [] p_threats ;
							SDLCommonFunc::CleanUp() ;
							SDL_Quit() ;
							return 0 ;
						}
					}
					else{
						if(MessageBox(NULL, L"GAME OVER!", L"Notice", MB_OK) == IDOK)
						{
							g_game_over = SDLCommonFunc:: LoadImage("gameover.png");
							if(g_game_over == NULL)
							{
								return 0;
							}

							delete [] p_threats; 
							SDLCommonFunc:: CleanUp();
							SDL_Quit();
							return 1;
						}
					}
				}

				// check collision main & threat bullet
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

							Mix_PlayChannel(-1, g_sound_exp[1], 0);

							die_number++;
							if(die_number <=2){
								SDL_Delay(1500) ;
								plane_object.SetRect(100, 300) ;
								player_power.Decrease() ;
								player_power.Render(g_screen) ;

								if(SDL_Flip(g_screen) == -1 ){
									delete [] p_threats ;
									SDLCommonFunc::CleanUp() ;
									SDL_Quit() ;
									return 0 ;
								}
							}
							else{
								if(MessageBox(NULL, L"GAME OVER!", L"Notice", MB_OK) == IDOK)
								{
									g_game_over = SDLCommonFunc:: LoadImage("gameover.png");
									if(g_game_over == NULL)
									{
										return 0;
									}
									/*delete [] p_threats; 
									SDLCommonFunc:: CleanUp();
									SDL_Quit();*/
									return 1;
								}
							}
						}
					}
				}

				// check collision main bullet & threat 
				std::vector<AmoObject*> amo_list2 = plane_object.GetAmoList();
				for(int am = 0; am < amo_list2.size(); am ++)
				{
					AmoObject* p_amo = amo_list2.at(am); // da co con tro thi luon phai kiem tra xem no co NULL hay khong
					if(p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if(ret_col)
						{
							mark_value++;

							for(int ex = 0; ex < 4; ex ++)
							{
								int x_pos = p_amo->GetRect().x - EXP_WIDTH*0.5;
								int y_pos = p_amo->GetRect().y - EXP_HEIGHT*0.5;

								exp_main.set_frame(ex);
								exp_main.SetRect(x_pos, y_pos);
								exp_main.ShowEx(g_screen);

								// update screen
								if(SDL_Flip(g_screen) == -1)
									return 0;
							}
							p_threat->Reset(SCREEN_WITH + tt*400);
							plane_object.RemoveAmo(am);
							Mix_PlayChannel(-1, g_sound_exp[0], 0); 
						}
					}
				}
			}
		}
		
		// show time to play game
		std::string str_time = "Time: ";
		Uint32 time_value = SDL_GetTicks()/1000;
		std::string str_val = std::to_string(time_value);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.SetRect(1150, 10);
		time_game.CreateGameText(g_font_text, g_screen);

		// show mark value in screen
		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.CreateGameText(g_font_text, g_screen);

		// update screen
		if(SDL_Flip(g_screen) == -1)
			return 0;
	}
	 
	delete [] p_threats; 
	SDLCommonFunc:: CleanUp();
	SDL_Quit();

	return 1;
}
	 