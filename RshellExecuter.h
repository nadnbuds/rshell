#ifndef RSHELLEXECUTER_H
#define RSHELLEXECUTER_H
#include <vector>

using namespace std;

class RshellExecuter{
	public:
		RshellExecuter();
		
		bool RunCommand(vector<string> Command);
};

#endif
