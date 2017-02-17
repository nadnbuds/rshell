#include<iostream>
#include<vector>
#include<map>
#include "RshellReader.h"
#include "RshellExecuter.h"
#include "RshellManager.h"

using namespace std;

RshellManager::RshellManager(){
	RunShell();	
}

void RshellManager::RunShell(){
	while(!stop){
		Reader.ReadLine();
		Interpret(Reader.Commands);
	}
}

void RshellManager::Interpret(vector<string> Commands){
	currentCommand.clear();
	while(Commands.size() > 0){
		if(Commands.at(0) == ";" || Commands.at(0) == "&&" || Commands.at(0) == "||"){
			mode = Commands.at(0);
			if(DetermineRun())
				lastCmdWorked = Executer.RunCommand(currentCommand);
			pop_front(Commands);
			currentCommand.clear();
		}
		currentCommand.push_back(Commands.at(0));
		pop_front(Commands);
	}
	if(DetermineRun())
		lastCmdWorked = Executer.RunCommand(currentCommand);
}

bool RshellManager::DetermineRun(){
	if(currentCommand.size() == 1){
		stop = (currentCommand.at(0) == "Exit");
	}
	else if(mode == "&&"){
		return lastCmdWorked;
	}
	else if(mode == "||"){
		return !lastCmdWorked;
	}
	else{
		return true;
	}
}

void RshellManager::setStop(){
	stop = true;
}

	template<typename T>
void RshellManager::pop_front(vector<T>& vec)
{
	if(!vec.empty())
		vec.erase(vec.begin());
}

