
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
			y_val_ -= HEIGHT_MAIN_OBJECT/15; // do cao giam xuong 
			break;
		case SDLK_DOWN: 
			y_val_ += HEIGHT_MAIN_OBJECT/15;
			break;
		case SDLK_RIGHT: 
			x_val_ += WIDTH_MAIN_OBJECT/15;
			break;
		case SDLK_LEFT: 
			x_val_ -= WIDTH_MAIN_OBJECT/15;
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
			y_val_ += HEIGHT_MAIN_OBJECT/15; // do cao giam xuong 
			break;
		case SDLK_DOWN: 
			y_val_ -= HEIGHT_MAIN_OBJECT/15;
			break;
		case SDLK_RIGHT: 
			x_val_ -= WIDTH_MAIN_OBJECT/15;
			break;
		case SDLK_LEFT: 
			x_val_ += WIDTH_MAIN_OBJECT/15;
			break;
		default:
			break;
		}
	}
	else if(events.type ==	SDL_MOUSEBUTTONDOWN) // xu ly su kien chuot
	{
		AmoObject* p_amo = new AmoObject();
		if(events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("rocket.png");
			p_amo->set_type(AmoObject::LASER);
		}
		else if(events.button.button == SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("laser2.png");
			p_amo->set_type(AmoObject::SPHERE);
		}

		p_amo->SetRect(this->rect_.x + this->rect_.w - 20, this->rect_.y + this->rect_.h - 40 );
		p_amo->set_is_move(true);
		p_amo->set_x_val(20);
		p_amo_list_.push_back(p_amo);
	}
	else if(events.type == SDL_MOUSEBUTTONUP)
	{

	}
	else
	{
		;//
	}
}

void MainObject:: MakeAmo(SDL_Surface* des)
{
	for(int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo != NULL)
		{
			if(p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMove(SCREEN_WITH, SCREEN_HEIGHT);
			}
			else 
			{
				if(p_amo != NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin() + i); // xoa mot phan tu qua gioi han 
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
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
