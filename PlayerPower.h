/*
* Ngay 29/12/2020
* Bou Bou
* Luot choi cho nhan vat
*/
#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H
#include "BaseObject.h"
#include <vector>

class PlayerPower : public BaseObject{
public:
	PlayerPower() ;
	~PlayerPower() ;
	void SetNumber(const int& num) { number_ = num ;} 
	void AddPos(const int& xpos) ;
	void Render(SDL_Surface* des) ;
	void Init() ;
	void Decrease() ;
	//void Crease() ;
private:
	int number_ ;
	std::vector <int> pos_list_ ;
	
} ;

#endif