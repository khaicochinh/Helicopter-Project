
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_ 

#include "common_function.h"
#include "BaseObject.h"

// dinh nghia size
#define WIDTH_MAIN_OBJECT 100
#define HEIGHT_MAIN_OBJECT 100

// class ke thua Base Object
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events);
	void HandleMove();

private:
	int x_val_;
	int y_val_;

};


#endif // MAIN_OBJECT_H_