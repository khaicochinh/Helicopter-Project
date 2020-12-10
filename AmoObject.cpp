
#include "AmoObject.h"

// contructor function
AmoObject :: AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	amo_type_ = NONE;
}

// destructor function
AmoObject :: ~AmoObject()
{
}

void AmoObject::HandleMove(const int& x_border, const int& y_border) // x_border & y_border la gioi han cua vien dan tren man hinh
{
	if(is_move_ == true)
	{
		rect_.x += x_val_;
		if(rect_.x > x_border)
		{
			is_move_ = false;
		} 
	}
}

void AmoObject::HandleMoveRightToLeft()
{
	rect_.x -= x_val_;
	if(rect_.x < 0)
	{
		is_move_ = false;
	}
}

void AmoObject :: HandleInputAction(SDL_Event events)
{
}

