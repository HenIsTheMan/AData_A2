#include <iostream>
#include <fstream>
#include <string>
#include "GOManager.h"

void LoadData(const GOManager& manager, const char* const& fPath){
	std::string line;
	std::ifstream stream(fPath);
	size_t commaPos;

	if(!stream.is_open()){ //If file cannot be opened...
		return (void)printf("Failed to open and read \"%s\"\n", fPath);
	}
	if(stream.peek() == std::ifstream::traits_type::eof()){ //If file is empty...
		return (void)printf("\"%s\" is empty!\n", fPath);
	}
	while(getline(stream, line)){ //Read every line in file
		commaPos = line.find(',');
		const int ID = stoi(line.substr(0, commaPos)); //Get ID from file
		line.erase(0, commaPos + 1 + int(line.at(commaPos + 1) == ' ')); //int(line.at(commaPos + 1) == ' ') is for if there is a space behind a comma

		commaPos = line.find(',');
		const int xCoord = stoi(line.substr(0, commaPos)); //Get xCoord from file
		const int yCoord = stoi(line.substr(commaPos + 1 + int(line.at(commaPos + 1) == ' '))); //Get yCoord from file //int(line.at(commaPos + 1) == ' ') is for if there is a space behind a comma

		manager.AddGO(ID, xCoord, yCoord); //Send signal to add GO to GOList in root quad of GOManager instance
	}
	stream.close();
	manager.Partition(); //Send signal to form the quadtree
}

short RetrieveUserInput(){ //Retrieve user input
	short choice;
	while(true){
		(void)puts("(1) Print Tree");
		(void)puts("(2) Print surrounding GOs");
		(void)printf("Enter choice: ");
		std::cin >> choice;
		try{ //Exception handling to ensure choice is either 1 or 2
			if(choice != 1 && choice != 2){
				throw("Invlid input!\n");
			} else{
				std::cout << std::endl;
				return choice;
			}
		} catch(const char* const& text){
			(void)puts(text);
			system("pause");
		}
		system("cls"); //Clear console screen
	}
}

int main(){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //To check for mem leaks
	system("Color 0A"); //Change console text colour

	GOManager manager; //Create GOManager instance
	LoadData(manager, "Data.txt"); //Load data into GOManager instance
	if(RetrieveUserInput() == 1){ //If user inputs 1...
		manager.PrintTree(); //Print the quadtree
	} else{ //Else...
		int ID; 
		std::cout << "Enter GO's ID: ";
		std::cin >> ID;
		manager.PrintNearbyGOs(ID); //Print GOs nearby GO with a certain ID
	}
}