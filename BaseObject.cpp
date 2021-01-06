// cac lop co so dai dien cho cac doi tuong co ban - lop cha
#include "BaseObject.h"

// constructor
BaseObject:: BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}

// destructor
BaseObject:: ~BaseObject()
{
	if(p_object_ != NULL )
	{ 
		SDL_FreeSurface(p_object_); 
	}
}

// loadimange function
bool BaseObject:: LoadImg(const char* file_name)
{
	p_object_ = SDLCommonFunc:: LoadImage(file_name); // load image object
	if(p_object_ == NULL)
		return false;
	return true;
}

// show img
void BaseObject:: Show(SDL_Surface* des)
{
	 if(p_object_ != NULL)
	 {
		 rect_ = SDLCommonFunc:: ApplySurface(p_object_, des, rect_.x, rect_.y); // vi tri cua object
	 }
}