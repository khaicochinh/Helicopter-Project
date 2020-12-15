
#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	
}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject:: set_clip()
{
	// frame 1
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = EXP_WIDTH;
	clip_[0].h = EXP_HEIGHT;

	// frame 2
	clip_[1].x = EXP_WIDTH;
	clip_[1].y = 0;
	clip_[1].w = EXP_WIDTH;
	clip_[1].h = EXP_HEIGHT;

	// frame 3
	clip_[2].x = EXP_WIDTH*2;
	clip_[2].y = 0;
	clip_[2].w = EXP_WIDTH;
	clip_[2].h = EXP_HEIGHT;

	// frame 4
	clip_[3].x = EXP_WIDTH*3;
	clip_[3].y = 0;
	clip_[3].w = EXP_WIDTH;
	clip_[3].h = EXP_HEIGHT;

	//// frame 5
	//clip_[4].x = EXP_WIDTH*4;
	//clip_[4].y = 0;
	//clip_[4].w = EXP_WIDTH;
	//clip_[4].h = EXP_HEIGHT;

	//// frame 6
	//clip_[5].x = EXP_WIDTH*5;
	//clip_[5].y = 0;
	//clip_[5].w = EXP_WIDTH;
	//clip_[5].h = EXP_HEIGHT;
}

void ExplosionObject:: ShowEx(SDL_Surface* des)
{
	if(frame_ >= 4)
	{
		frame_ = 0;
	}

	SDLCommonFunc:: AppluSurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}
