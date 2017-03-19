#ifndef RSHELLEXECUTER_H
#define RSHELLEXECUTER_H
#include <vector>
#include <string>

using namespace std;

class RshellExecuter {
public:
	RshellExecuter();

	char** Convert(vector<string> Command);
	void WriteStdin(string input);
	string Pipe(vector<string> Command);
	bool FileInput(vector<string> Command, string filename, bool append);
	void FileOutput(string filename);
	bool Execute(vector<string> Command);

private:
	int in, MyPipe[2];
};

#endif
