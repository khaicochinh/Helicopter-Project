

#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WITH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT ;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
	if(p_amo_list_.size() > 0) // kiem tra va giai phong bo nho
	{
		for(int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if(p_amo != NULL)
			{
				delete p_amo; // luu y: khi dung con tro co new la phai co delete
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	if(p_amo)
	{
		bool ret = p_amo->LoadImg("bullet_threat.png");
		if(ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			p_amo->set_x_val(9);
			p_amo_list_.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for(int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			if(p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft();
			}
			else // neu dan da di qua man hinh thi set lai vi tri ban dau cho dan
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x - 50, rect_.y + rect_.h*1.2);
			}
		}
	}
}

void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x -= x_val_; // khoang cach di chuyen cua threat
	if(rect_.x < 0) // neu di qua man hinh thi set lai ban dau
	{
		rect_.x = SCREEN_WITH;
		int rand_y = rand()%400;
		if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT*0.3;
		}

		rect_.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
}

void ThreatObject:: Reset(const int& xborder)
{
	// reset lai vi tri cua ca doi tuong sau khi va cham
	rect_.x = xborder;
	int rand_y = rand()%400;
	if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT*0.3;
	}

	rect_.y = rand_y;

	for(int i = 0; i < p_amo_list_.size(); i ++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			ResetAmo(p_amo);
		}
	}
}

void ThreatObject:: ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x - 50, rect_.y + rect_.h*1.2);
}