#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "RshellExecuter.h"

using namespace std;

RshellExecuter::RshellExecuter(){}

bool RshellExecuter::RunCommand(vector<string> Command){
	bool value = false;
	char ** p;
	//Convert Command into a char** args
	p = new char*[Command.size() + 1];
	p[Command.size()] = NULL;
		
	for(unsigned x = 0; x < Command.size(); x ++){
		p[x] = const_cast<char*>(Command.at(x).c_str());
	}
	value = Execute(p);
	delete [] p;
	return value;

	
}

bool RshellExecuter::Execute(char** args){
	pid_t pid;
	int status;
	
	//Running the Command
	pid = fork();
	if(pid == -1){
		perror("Fork");
		exit(1);
	}
	else if(pid == 0){
		if(execvp(args[0], &args[0]) < 0){
			exit(1);
		}
		else{
			exit(0);
		}
	}
	else{
		while(waitpid(-1, &status, 0) != pid){}
		if(WEXITSTATUS(status) == 1)
			return false;
		else{
			return true;
		}
	}
}
