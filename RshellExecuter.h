#ifndef RSHELLEXECUTER_H
#define RSHELLEXECUTER_H
#include <vector>
#include <string>

using namespace std;

class RshellExecuter{
	public:
		RshellExecuter();
		
		bool RunCommand(vector<string> Command);
};

#endif
