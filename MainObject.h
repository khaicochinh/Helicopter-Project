
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_ 

#include "common_function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

// dinh nghia size
#define WIDTH_MAIN_OBJECT 60
#define HEIGHT_MAIN_OBJECT 30

// class ke thua Base Object
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void MakeAmo(SDL_Surface* des); // tao doi tuong bullet
	void MainObject:: RemoveAmo(const int& idx); // remove bullet

private:
	int x_val_;
	int y_val_;

	// su dung vector de khai bao list amo object, khi do amo se la 1 truong thuoc main object
	std::vector<AmoObject*> p_amo_list_; 
};


#endif // MAIN_OBJECT_H_