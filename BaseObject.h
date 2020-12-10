
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_ // dinh nghia mot ham
#include "common_function.h"

class BaseObject
{
public:
	BaseObject(); // ham constructor mac dinh
	~BaseObject(); // ham huy - destroy
	void Show(SDL_Surface* des);
	bool LoadImg(const char* file_name);
	void SetRect(const int& x, const int& y)
	{
		rect_.x = x; 
		rect_.y = y;
	} // tham chieu dang hang
	SDL_Rect GetRect() const {return rect_;}
	SDL_Surface* GetObject() {return p_object_;}

protected: // bien thanh vien
	SDL_Rect rect_; // shift (-) dai dien cho bien thanh vien
	SDL_Surface* p_object_;
}; // chu y cuoi class phai co dau (;)

#endif