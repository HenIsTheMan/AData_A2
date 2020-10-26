#include "GO.h"

GO::GO():
	pos({0, 0}),
	ID(0)
{
}

const int& GO::GetPosX() const{
	return pos.x;
}

const int& GO::GetPosY() const{
	return pos.y;
}

const int& GO::GetID() const{
	return ID;
}
	
void GO::SetPosX(const int& x){
	pos.x = x;
}

void GO::SetPosY(const int& y){
	pos.y = y;
}

void GO::SetID(const int& ID){
	this->ID = ID;
}