#include <iostream>
#include <string>
#include <vector>
#include "RshellReader.h"

using namespace std;
void RshellReader::ReadLine(){
	cout << "Rshell$ ";
	Commands.clear();
	getline(cin, Input);
	SpliceLine();
}

void RshellReader::SpliceLine(){
	for(unsigned x = 0; x < Input.length(); x++){
		if(Input.at(x) == spaceCheck){
			string temp = Input.substr(0, x);
			//Add a bound measure incase this goes over line.length() - 1
			Input = Input.substr(x+1);
			x = 0;
			Commands.push_back(temp);
		}
		if(Input.at(x) == semiCheck){
			string temp = Input.substr(0,x);
			Input = Input.substr(x+1);
			x = 0;
			Commands.push_back(temp);
			Commands.push_back(";");
		}
		if(Input.at(x) == hashCheck){
			return;
		}
	}
	Commands.push_back(Input);
}
