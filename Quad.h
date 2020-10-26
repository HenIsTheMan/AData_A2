#pragma once
#include <vector>
#include "GO.h"

class Quad final{
public:
	enum struct QuadType{
		UL = 0,
		UR,
		DL,
		DR,
		Root,
		Amt
	};

	Quad(); //Default ctor
	~Quad(); //Default dtor

	void AddGO(const int& ID, const int& x, const int& y); //Add a GO to GOList
	void Destroy(); //Helper func for destroying the quadtree
	void Partition(); //Helper func for forming the quadtree
	void Print(const int& lvl, const QuadType& type) const; //Helper func for printing the quadtree
	void PrintNearbyGOs(const int& ID) const; //Print GOs nearby GO with a certain ID
	const Quad* const SearchForGO(const int& ID) const; //Search for GO with a certain ID

	///Getters
	const Pos& GetOrigin() const;
	const int& GetWidth() const;
	const int& GetHeight() const;

	///Setters
	void SetParent(Quad* const& parent);
	void SetOrigin(const Pos& origin);
	void SetWidth(const int& width);
	void SetHeight(const int& height);
private:
	Quad* parent;
	Pos origin; //Origin of quad
	int width; //Width of quad
	int height; //Height of quad

	Quad* UL; //Up/Top Left
	Quad* UR; //Up/Top Right
	Quad* DL; //Down/Bottom Left
	Quad* DR; //Down/Bottom Right
	std::vector<GO*>* GOList;
	int count;
};