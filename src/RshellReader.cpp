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
	unsigned x = 0;
	while(x < Input.length()){
		//Splices ; from the line
		 if(Input.at(x) == semiCheck){
			string temp = Input.substr(0,x);
			if (temp.size() > 0) {
				Commands.push_back(temp);
			}
			Commands.push_back(";");
			if(x + 1 < Input.length()){
				Input = Input.substr(x+1);
			}
			else{
				Input = "&symbols&";
				break;
			}
			x = 0;
		}
		 //Splices all Spaces
		 else if (Input.at(x) == spaceCheck) {
			 string temp = Input.substr(0, x);
			 //Add a bound measure incase this goes over line.length() - 1
			 if (x + 1 < Input.length()) {
				 Input = Input.substr(x + 1);
			 }
			 else {
				 Input = "&symbols&";
			 }
			 x = 0;
			 if (temp.size() > 0) {
				 Commands.push_back(temp);
			 }
		 }
		//Splices ( from the line
		else if (Input.at(x) == ParCheck1) {
			 string temp = Input.substr(0, x);
			 if (temp.size() > 0) {
				 Commands.push_back(temp);
			 }
			 Commands.push_back("(");
			 if (x + 1 < Input.length()) {
				 Input = Input.substr(x + 1);
			 }
			 else {
				 Input = "&symbols&";
				 break;
			 }
			 x = 0;
		 }
		//Splices ) from the line
		else if (Input.at(x) == ParCheck2) {
			string temp = Input.substr(0, x);
			if (temp.size() > 0) {
				Commands.push_back(temp);
			}
			Commands.push_back(")");
			if (x + 1 < Input.length()) {
				Input = Input.substr(x + 1);
			}
			else {
				Input = "&symbols&";
				break;
			}
			x = 0;
		}
		//Comments
		else if(Input.at(x) == hashCheck){
			Input = "";
			return;
		}
		else {
			x++;
		}
	}
	//Final pushback
	if (Input != "&symbols&") {
		Commands.push_back(Input);
	}
}