
#ifndef THREAT_OBJECT_H_ 
#define THREAT_OBJECT_H_
#include "common_function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector> 

#define WIDTH_THREAT 100
#define HEIGHT_THREAT 40

const int UNDER_LIMIT_THREAT = 200;

class ThreatObject : public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val) {x_val_ = val;}
	void set_y_val(const int& val) {y_val_ = val;}
	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}

	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void InitAmo(AmoObject* p_amo); // tao dan cho threat
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit); // gioi han cua vien dan ban ra
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_; 
};


#endif