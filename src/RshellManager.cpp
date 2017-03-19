#include<iostream>
#include<vector>
#include<map>
#include <stdio.h>
#include "RshellReader.h"
#include "RshellExecuter.h"
#include "RshellManager.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

RshellManager::RshellManager() {
	Exit = false;
	RunShell();
}

void RshellManager::RunShell() {
	while (!Exit) {
		Reader.ReadLine();
		Interpret(Reader.Commands);
		mode = ";";
	}
}

bool RshellManager::Interpret(vector<string> Commands) {
	//Command "Que"
	vector<vector<string> > Que;
	currentCommand.clear();

	//Adding all commands to the Que
	while (Commands.size() > 0) {
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

//Actually runs the Commands
void RshellManager::Parse(vector<vector<string> > Que) {
	unsigned index;
	/*//Test to check the commands being input
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

		if (Que.at(index).at(0) == "exit") {
			Exit = true;
		}
		else if (Que.at(index).at(0) == "test" || Que.at(index).at(0) == "[") {
			//Implement test function here
			string flag; //stores flag
			string p; //file path
			struct stat buf; //buf from stat.h
			bool e = false; //checks if file exists <- used for -e flag
							//checking flags to run the test correctly, if no flag is provided the we will assume it is -e
			if (Que.at(index).at(0) == "[") {
				Que.at(index).pop_back();
			}
			if (Que.at(index).at(1) == "-e") {
				flag = "-e";
				p = Que.at(index).at(2);
			}
			else if (Que.at(index).at(1) == "-f") {
				flag = "-f";
				p = Que.at(index).at(2);
			}
			else if (Que.at(index).at(1) == "-d") {
				flag = "-d";
				p = Que.at(index).at(2);
			}
			else {
				flag = "-e";
				p = Que.at(index).at(1);
			}
			int stattest = stat(p.c_str(), &buf); //stattest stores the result of stat() 0 = success, -1 = fail/error
												  //checks if the file/directory exists
			if (stattest == 0) {
				e = true;
			}
			else {
				perror("stat");
				cout << "(False)" << endl;
				lastCmdWorked = false;
				break;
			}

			if (flag == "-e") { //this will return true because we checked existence above
				cout << "(True)" << endl;
				lastCmdWorked = e;
			}
			else if (flag == "-f") { //this checks if it is a regular file
				if (S_ISREG(buf.st_mode)) { //S_ISREG() function checks if it is a regular file using st_mode
					cout << "(true)" << endl;
					lastCmdWorked = true;
				}
				else {
					cout << "(false)" << endl;
					lastCmdWorked = false;
				}
			}
			else if (flag == "-d") { //this checks if it is a directory
				if (S_ISDIR(buf.st_mode)) { //S_ISDIR checks for a directory using st_mode
					cout << "(true)" << endl;
					lastCmdWorked = true;
				}
				else {
					cout << "(false)" << endl;
					lastCmdWorked = false;
				}
			}
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
		else if (index < Que.size() - 1) {
			if (Que.at(index + 1).at(0) == "|") {
				string arg = Executer.Pipe(Que.at(index));
				if (index < Que.size() - 2) {
					//Executer.WriteStdin(arg);
				}
				index++;
			}
			else if (Que.at(index + 1).at(0) == "<") {
				//Executer.FileOutput(Que.at(index), Que.at(index + 2).at(0));
			}
			else if (Que.at(index + 1).at(0) == ">") {
				Executer.FileInput(Que.at(index), Que.at(index + 2).at(0), false);
			}
			else if (Que.at(index + 1).at(0) == ">>") {
				Executer.FileInput(Que.at(index), Que.at(index + 2).at(0), true);
			}
		}
		else {
			lastCmdWorked = Executer.Execute(Que.at(index));
		}
	}
}

//Checks if a new Command is being input
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
	else if (Command == "<") {
		return true;
	}
	else if (Command == ">") {
		return true;
	}
	else if (Command == ">>") {
		return true;
	}
	else if (Command == "|") {
		return true;
	}
	else {
		return false;
	}
}



template<typename T>
void RshellManager::pop_front(vector<T>& vec)
{
	if (!vec.empty())
		for (unsigned x = 0; x < vec.size() - 1; x++) {
			vec.at(x) = vec.at(x + 1);
		}
	vec.pop_back();
}

