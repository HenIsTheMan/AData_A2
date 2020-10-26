#include "Quad.h"
#include <iostream>

Quad::Quad():
	parent(nullptr),
	origin({0, 0}),
	width(0),
	height(0),

	UL(nullptr),
	UR(nullptr),
	DL(nullptr),
	DR(nullptr),
	GOList(new std::vector<GO*>()),
	count(0)
{
}

Quad::~Quad(){
	if(GOList){
		for(GO*& go: *GOList){
			delete go;
			go = nullptr;
		}
		delete GOList;
	}
}

void Quad::AddGO(const int& ID, const int& x, const int& y){
	GO* go = new GO(); //Alloc mem on the heap for GO
	go->SetID(ID);
	go->SetPosX(x);
	go->SetPosY(y);
	GOList->emplace_back(go); //Add GO to GOList after setting its member vars
	++count; //Increment count by 1
}

void Quad::Destroy(){
	if(UL){ //If UL exists...
		UL->Destroy();
		UL = nullptr; //Make dangling ptr a null ptr
	}
	if(UR){ //If UR exists...
		UR->Destroy();
		UR = nullptr; //Make dangling ptr a null ptr
	}
	if(DL){ //If DL exists...
		DL->Destroy();
		DL = nullptr; //Make dangling ptr a null ptr
	}
	if(DR){ //If DR exists...
		DR->Destroy();
		DR = nullptr; //Make dangling ptr a null ptr
	}
	delete this;
}

void Quad::Partition(){
	if(count > 3){ //If no. of GOs in GOList of this Quad instance > 3...
		///Set up UL
		UL = new Quad();
		UL->SetParent(this);
		UL->SetOrigin(this->origin);
		UL->SetWidth(width & 1 ? (width - 1) / 2 : width / 2);
		UL->SetHeight(height & 1 ? (height - 1) / 2 : height / 2);

		///Set up UR
		UR = new Quad();
		UR->SetParent(this);
		UR->SetWidth(width & 1 ? (width - 1) / 2 + 1 : width / 2);
		UR->SetHeight(UL->GetHeight());
		UR->SetOrigin({UL->GetOrigin().x + UL->GetWidth(), UL->GetOrigin().y});

		///Set up DL
		DL = new Quad();
		DL->SetParent(this);
		DL->SetWidth(UL->GetWidth());
		DL->SetHeight(height & 1 ? (height - 1) / 2 + 1 : height / 2);
		DL->SetOrigin({UL->GetOrigin().x, UL->GetOrigin().y + UL->GetHeight()});

		///Set up DR
		DR = new Quad();
		DR->SetParent(this);
		DR->SetOrigin({UR->GetOrigin().x, DL->GetOrigin().y});
		DR->SetWidth(UR->GetWidth());
		DR->SetHeight(DL->GetHeight());

		for(const GO* const& go: *GOList){ //Add each GO to the correct child based on each GO's location
			if(go->GetPosX() >= UR->GetOrigin().x){
				if(go->GetPosY() >= DR->GetOrigin().y){
					DR->AddGO(go->GetID(), go->GetPosX(), go->GetPosY());
				} else{
					UR->AddGO(go->GetID(), go->GetPosX(), go->GetPosY());
				}
			} else{
				if(go->GetPosY() >= DL->GetOrigin().y){
					DL->AddGO(go->GetID(), go->GetPosX(), go->GetPosY());
				} else{
					UL->AddGO(go->GetID(), go->GetPosX(), go->GetPosY());
				}
			}
		}

		///Use recursion to continue forming the quadtree
		UL->Partition();
		UR->Partition();
		DL->Partition();
		DR->Partition();
	}
}

void Quad::Print(const int& lvl, const QuadType& type) const{
	for(int i = 0; i < lvl; ++i){
		std::cout << '\t'; //Print horiz tab char
	}
	std::cout << lvl << " - ";
	switch(type){ //Print the type of quad this Quad instance is
		case QuadType::UL:
			(void)printf("Up Left");
			break;
		case QuadType::UR:
			(void)printf("Up Right");
			break;
		case QuadType::DL:
			(void)printf("Down Left");
			break;
		case QuadType::DR:
			(void)printf("Down Right");
			break;
		case QuadType::Root:
			(void)printf("Root");
			break;
	}
	std::cout << " (" << count << ")\n"; //Print the no. of GOs in GOList of this Quad instance
	if(UL){ //If UL exists...
		UL->Print(lvl + 1, QuadType::UL);
	}
	if(UR){ //If UR exists...
		UR->Print(lvl + 1, QuadType::UR);
	}
	if(DL){ //If DL exists...
		DL->Print(lvl + 1, QuadType::DL);
	}
	if(DR){ //If DR exists...
		DR->Print(lvl + 1, QuadType::DR);
	}
}

void Quad::PrintNearbyGOs(const int& ID) const{
	const size_t size = GOList->size(); //Get size of GOList
	if(size == 1){ //If GOList only has 1 GO...
		return (void)printf("No GOs nearby GO with ID \'%d\'!\n", ID);
	}
	(void)printf("Nearby GOs (by IDs): ");
	for(size_t i = 0; i < size; ++i){ //Print all GOs in this Quad instance except for GO with the matching ID
		if((*GOList)[i]->GetID() != ID){
			std::cout << (*GOList)[i]->GetID() << ", ";
		}
	}
	std::cout << "\b\b \n"; //Remove last comma and add a line break
}

const Quad* const Quad::SearchForGO(const int& ID) const{ //Search children 1st
	if(UL){ //If UL exists...
		const Quad* const& quad = UL->SearchForGO(ID);
		if(quad){ //If GO was found in a quad...
			return quad;
		}
	}
	if(UR){ //If UR exists...
		const Quad* const& quad = UR->SearchForGO(ID);
		if(quad){ //If GO was found in a quad...
			return quad;
		}
	}
	if(DL){ //If DL exists...
		const Quad* const& quad = DL->SearchForGO(ID);
		if(quad){ //If GO was found in a quad...
			return quad;
		}
	}
	if(DR){ //If DR exists...
		const Quad* const& quad = DR->SearchForGO(ID);
		if(quad){ //If GO was found in a quad...
			return quad;
		}
	}
	if(GOList){
		for(const GO* const& go: *GOList){
			if(go->GetID() == ID){ //If both IDs match...
				return this; //Return mem address of GO that was found
			}
		}
	}
	return nullptr;
}

const Pos& Quad::GetOrigin() const{
	return origin;
}

const int& Quad::GetWidth() const{
	return width;
}

const int& Quad::GetHeight() const{
	return height;
}

void Quad::SetParent(Quad* const& parent){
	this->parent = parent;
}

void Quad::SetOrigin(const Pos& origin){
	this->origin = origin;
}

void Quad::SetWidth(const int& width){
	this->width = width;
}

void Quad::SetHeight(const int& height){
	this->height = height;
}