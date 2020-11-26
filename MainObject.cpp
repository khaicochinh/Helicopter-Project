
#include "MainObject.h"

MainObject:: MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject:: ~MainObject()
{
	;
}

void MainObject:: HandleInputAction(SDL_Event events)
{
	if(events.type == SDL_KEYDOWN) // bat su kien phim nhan xuong
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: 
			y_val_ -= HEIGHT_MAIN_OBJECT/5; // do cao giam xuong 
			break;
		case SDLK_DOWN: 
			y_val_ += HEIGHT_MAIN_OBJECT/5;
			break;
		case SDLK_RIGHT: 
			x_val_ += WIDTH_MAIN_OBJECT/5;
			break;
		case SDLK_LEFT: 
			x_val_ -= WIDTH_MAIN_OBJECT/5;
			break;
		default:
			break;
		}
	}
	else if(events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: 
			y_val_ += HEIGHT_MAIN_OBJECT/5; // do cao giam xuong 
			break;
		case SDLK_DOWN: 
			y_val_ -= HEIGHT_MAIN_OBJECT/5;
			break;
		case SDLK_RIGHT: 
			x_val_ -= WIDTH_MAIN_OBJECT/5;
			break;
		case SDLK_LEFT: 
			x_val_ += WIDTH_MAIN_OBJECT/5;
			break;
		default:
			break;
		}
	}
	else if(events.type ==	SDL_MOUSEBUTTONDOWN) // xu ly su kien chuot
	{
	}
	else if(events.type == SDL_MOUSEBUTTONUP)
	{
	}
	else
	{
		;//
	}
}

void MainObject:: HandleMove()
{
	rect_.x += x_val_;
	// xu ly khi doi tuong tran man hinh
	if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WITH - 50)
	{
		rect_.x -= x_val_;
	}

	// xu ly truong hop may bay cham dat
	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100)
	{
		rect_.y -= y_val_;
	}
}
