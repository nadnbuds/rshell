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
	currentCommand.clear();
	while(Commands.size() > 0){
		if(Commands.at(0) == ";" || Commands.at(0) == "&&" || Commands.at(0) == "||" || Commands.at(0) == "("){
			if(DetermineRun()){
				if(extraCommand()){
				}
				else{
					Exit = (currentCommand.at(0) == "exit");
					lastCmdWorked = Executer.RunCommand(currentCommand);
				}
			}
			mode = Commands.at(0);
			pop_front(Commands);
			currentCommand.clear();

		}
		currentCommand.push_back(Commands.at(0));
		pop_front(Commands);
	}
	if(DetermineRun()){
		if(extraCommand()){
		}
		else{
			Exit = (currentCommand.at(0) == "exit");
			lastCmdWorked = Executer.RunCommand(currentCommand);
		}
		return lastCmdWorked;
	}
	return false;
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

bool RshellManager::extraCommand(){
	if(currentCommand.at(0) == "test" || currentCommand.at(0) == "["){
	
	}
	else if(currentCommand.at(0) == "("){
		//Create Vector<string> of the rest of commands with a termination on ")"
		lastCmdWorked = Interperet(commands)
	}	
}

void RshellManager::setExit(){
	Exit = true;
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

