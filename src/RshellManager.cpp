#include<iostream>
#include<vector>
#include<map>
#include <stdio.h>
#include "RshellReader.h"
#include "RshellExecuter.h"
#include "RshellManager.h"

using namespace std;

RshellManager::RshellManager(){
	Exit = false;
	RunShell();	
}

void RshellManager::RunShell(){
	while(!Exit){
		Reader.ReadLine();
		Interpret(Reader.Commands);
		mode = ";";
	}
}

bool RshellManager::Interpret(vector<string> Commands){
	//Command "Que"
	vector<vector<string> > Que;
	currentCommand.clear();

	//Adding all commands to the Que
	while(Commands.size() > 0){
		//Checks for indicators of a new commands
		if (CheckNew(Commands.at(0))) {
			if (currentCommand.size() > 0) {
				Que.push_back(currentCommand);
			}
			currentCommand.clear();

			//Special () case
			if (Commands.at(0) == "(") {
				int pcount = 1;
				currentCommand.push_back(Commands.at(0));
				pop_front(Commands);
				while (pcount > 0 && Commands.size() > 0) {
					if (Commands.at(0) == "(") {
						pcount++;
					}
					if (Commands.at(0) == ")") {
						pcount--;
					}
					currentCommand.push_back(Commands.at(0));
					pop_front(Commands);
				}
			}

			//All other cases
			else {
				currentCommand.push_back(Commands.at(0));
				pop_front(Commands);
			}

			//PushBack Special case
			Que.push_back(currentCommand);
			currentCommand.clear();
		}

		//Append to current command
		else if (Commands.size() > 0) {
			currentCommand.push_back(Commands.at(0));
			pop_front(Commands);
		}
	}
	//Add Final command
	if (currentCommand.size() > 0) {
		Que.push_back(currentCommand);
		currentCommand.clear();
	}
	//Parse and return
	Parse(Que);
	return lastCmdWorked;
}

void RshellManager::Parse(vector<vector<string> > Que) {
	unsigned index;
	/* Test to check the commands being input
	cout << Que.size() << endl;
	for (unsigned x = 0; x < Que.size(); x++) {
		for (unsigned y = 0; y < Que.at(x).size(); y++) {
			cout << Que.at(x).at(y) << ", ";
		}
		cout << endl;
	} */
	
	for (index = 0; index < Que.size(); index++) {
		//cout << index << endl;
		//Check if special command
		//Currently messy and all in this function b/c I have to alter index, looking for a work around
		if(Que.at(index).at(0) == "exit"){
			Exit = true;
		}
		else if(Que.at(index).at(0) == "test" || Que.at(index).at(0) == "[") {
			//Implement test function here
		}
		else if (Que.at(index).at(0) == "&&") {
			if (!lastCmdWorked) {
				index++;
				if (index >= Que.size()) {
					break;
				}
			}
		}
		else if (Que.at(index).at(0) == "||") {
			if (lastCmdWorked) {
				index++;
				if (index >= Que.size()) {
					break;
				}
			}
		}
		else if (Que.at(index).at(0) == "(") {
			pop_front(Que.at(index));
			Que.at(index).pop_back();
			lastCmdWorked = Interpret(Que.at(index));
		}
		else {
			lastCmdWorked = Executer.RunCommand(Que.at(index));
		}
	}
}

bool RshellManager::DetermineRun(){
	if(mode == "&&"){
		return lastCmdWorked;
	}
	else if(mode == "||"){
		return !lastCmdWorked;
	}
	else{
		return true;
	}
}

bool RshellManager::CheckNew(string Command) {
	if (Command == ";") {
		return true;
	}
	else if (Command == "(") {
		return true;
	}
	else if (Command == ")") {
		return true;
	}
	else if (Command == "&&") {
		return true;
	}
	else if (Command == "||") {
		return true;
	}
	else {
		return false;
	}
}



template<typename T>
void RshellManager::pop_front(vector<T>& vec)
{
	if(!vec.empty())
		for(unsigned x = 0; x < vec.size()-1; x++){
			vec.at(x) = vec.at(x+1);
		}
		vec.pop_back();
}

