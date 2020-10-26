#pragma once
#include "Quad.h"

class GOManager final{
public:
	GOManager(); //Default ctor
	~GOManager(); //Default dtor
	void AddGO(const int& ID, const int& x, const int& y) const;
	void Partition() const;
	void PrintTree() const;
	void PrintNearbyGOs(const int& ID) const;
private:
	Quad* root; //Ptr to root quad
};