#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include "RshellReader.h"

using namespace std;
RshellReader::RshellReader() {
	gethostname(hostname, 40);
	getlogin_r(username, 40);
}

void RshellReader::ReadLine(){
	cout << username << "@" << hostname << "$ ";
	Commands.clear();
	getline(cin, Input);
	SpliceLine();
}

void RshellReader::SpliceLine(){
	for(unsigned x = 0; x < Input.length(); x++){
		 if(Input.at(x) == semiCheck){
			string temp = Input.substr(0,x);
			if(x + 2 < Input.length()){
				Input = Input.substr(x+2);
			}
			else{
				Input = "";
			}
			x = 0;
			Commands.push_back(temp);
			Commands.push_back(";");	
		} if(Input.at(x) == spaceCheck){
			string temp = Input.substr(0, x);
			//Add a bound measure incase this goes over line.length() - 1
			if(x + 1 < Input.length()){
				Input = Input.substr(x+1);
			}
			else{
				Input = "";
			}
			x = 0;
			Commands.push_back(temp);
		}if(Input.at(x) == hashCheck){
			Input = "";
			return;
		}
	}
	//if(Input.at(0) != hashCheck) {
		Commands.push_back(Input);
	//}
}
