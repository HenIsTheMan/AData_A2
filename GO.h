#pragma once

struct Pos final{
	int x;
	int y;
};

class GO final{
public:
	GO(); //Default ctor
	~GO() = default; //Default dtor

	///Getters
	const int& GetPosX() const;
	const int& GetPosY() const;
	const int& GetID() const;

	///Setters
	void SetPosX(const int& x);
	void SetPosY(const int& y);
	void SetID(const int& ID);
private:
	Pos pos;
	int ID;
};