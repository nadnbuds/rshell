#ifndef RSHELLMANAGER_H
#define RSHELLMANAGER_H
#include <vector>
#include <string>

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
		
		void Interpret(vector<string> Commands);
		bool DetermineRun();
		void setExit();
		template <typename T> void pop_front(vector<T>& vec);

};

#endif
