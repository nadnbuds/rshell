#ifndef RSHELLEXECUTER_H
#define RSHELLEXECUTER_H
#include <vector>
#include <string>

using namespace std;

class RshellExecuter{
	public:
		RshellExecuter();
		
		char** Convert(vector<string> Command);
		string Pipe(vector<string> Command);
		bool FileInput(vector<string> Command, string filename);
		bool Execute(vector<string> Command);
};

#endif
