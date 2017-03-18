#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "RshellExecuter.h"
using namespace std;

RshellExecuter::RshellExecuter(){}

char** RshellExecuter::Convert(vector<string> Command){
	char ** p;
	//Convert Command into a char** args
	p = new char*[Command.size() + 1];
	p[Command.size()] = NULL;
		
	for(unsigned x = 0; x < Command.size(); x ++){
		p[x] = const_cast<char*>(Command.at(x).c_str());
	}
	return p;
}

string RshellExecuter::Pipe(vector<string> Command) {
	pid_t pid;
	int status;
	int MyPipe[2];
	char Buffer[80];
	int out = open("output.txt", O_RDWR | O_CREAT | O_APPEND, 0600);
	char** args = Convert(Command);

	//Running the Command
	if (pipe(MyPipe) == -1) {
		perror("Pipe");
	}
	pid = fork();
	if (pid == -1) {
		perror("Fork");
		exit(1);
	}
	else if (pid == 0) {
		//close(1);
		close(MyPipe[0]);
		dup2(MyPipe[1], STDOUT_FILENO);
		close(out);
		if (execvp(args[0], &args[0]) < 0) {
			exit(1);
		}
		else {
			exit(0);
		}
	}
	else {
		close(MyPipe[1]);
		while (waitpid(-1, &status, 0) != pid) {}
		if (WEXITSTATUS(status) == 1) {
			return "%Error%";
		}
		else {
			read(MyPipe[0], Buffer, sizeof(Buffer));
			return Buffer;
		}
	}
}

bool RshellExecuter::FileInput(vector<string> Command, string filename) {
	pid_t pid;
	int status;
	int MyPipe[2];
	int out = open(filename.c_str(), O_RDWR | O_CREAT | O_APPEND, 0600);
	char** args = Convert(Command);

	//Running the Command
	if (pipe(MyPipe) == -1) {
		perror("Pipe");
	}
	pid = fork();
	if (pid == -1) {
		perror("Fork");
		exit(1);
	}
	else if (pid == 0) {
		//close(1);
		close(MyPipe[0]);
		dup2(out, STDOUT_FILENO);
		close(out);
		if (execvp(args[0], &args[0]) < 0) {
			exit(1);
		}
		else {
			exit(0);
		}
	}
	else {
		close(MyPipe[1]);
		while (waitpid(-1, &status, 0) != pid) {}
		if (WEXITSTATUS(status) == 1) {
			return false;
		}
		else {
			return true;
		}
	}
}

bool RshellExecuter::Execute(vector<string> command){
	pid_t pid;
	int status;
	char** args = Convert(command);
	//Running the Command
	pid = fork();
	if(pid == -1){
		perror("Fork");
		exit(1);
	}
	else if(pid == 0){
		//close(1);
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
