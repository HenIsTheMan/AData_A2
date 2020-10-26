#include "GOManager.h"

GOManager::GOManager():
	root(new Quad())
{
	root->SetParent(nullptr);
	root->SetOrigin({0, 0});
	root->SetWidth(200);
	root->SetHeight(200);
}

GOManager::~GOManager(){
	if(root){ //If root exists...
		root->Destroy();
		root = nullptr; //Make dangling ptr a null ptr
	}
}

void GOManager::AddGO(const int& ID, const int& x, const int& y) const{
	root->AddGO(ID, x, y);
}

void GOManager::Partition() const{
	root->Partition();
}

void GOManager::PrintTree() const{
	root->Print(0, Quad::QuadType::Root);
}

void GOManager::PrintNearbyGOs(const int& ID) const{
	const Quad* const& quad = root->SearchForGO(ID); //Get quad which GO with a certain ID is in
	quad ? quad->PrintNearbyGOs(ID) : (void)printf("GO with ID \'%d\' not found!\n", ID);
}