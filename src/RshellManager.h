#ifndef RSHELLMANAGER_H
#define RSHELLMANAGER_H
#include <vector>
#include <string>
#include "RshellReader.h"
#include "RshellExecuter.h"

using namespace std;

class RshellManager {

	public:
		RshellManager();
		void RunShell();		

	private:
		bool Exit;
		bool lastCmdWorked;
		string mode;
		RshellReader Reader;
		RshellExecuter Executer;
		vector<string> currentCommand;
		
		bool Interpret(vector<string> Commands);
		bool DetermineRun();
		bool extraCommands();
		void setExit();
		template <typename T> void pop_front(vector<T>& vec);

};

#endif
