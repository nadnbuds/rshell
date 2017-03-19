#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "RshellExecuter.h"
using namespace std;

RshellExecuter::RshellExecuter() {}

int in = 0;

char** RshellExecuter::Convert(vector<string> Command) {
	char ** p;
	//Convert Command into a char** args
	p = new char*[Command.size() + 1];
	p[Command.size()] = NULL;

	for (unsigned x = 0; x < Command.size(); x++) {
		p[x] = const_cast<char*>(Command.at(x).c_str());
	}
	return p;
}

void RshellExecuter::WriteStdin(string input) {
	//pid_t pid;
	//int status;
	in = open(input.c_str(), O_RDONLY);
}

string RshellExecuter::Pipe(vector<string> Command) {
	pid_t pid;
	int status;
	char Buffer[80];
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
		dup2(MyPipe[1], STDOUT_FILENO);
		dup2(in, 0);
		if (execvp(args[0], &args[0]) < 0) {
			close(STDIN_FILENO);
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
			in = MyPipe[0];
			return Buffer;
		}
	}
}

void RshellExecuter::FileOutput(string filename) {
	//pid_t pid;
	//int status;
	in = open(filename.c_str(), O_RDONLY);
}

bool RshellExecuter::FileInput(vector<string> Command, string filename, bool append) {
	pid_t pid;
	int status;
	int out;
	if (append) {
		out = open(filename.c_str(), O_RDWR | O_CREAT | O_APPEND, 0600);
	}
	else {
		out = open(filename.c_str(), O_RDWR | O_CREAT, 0600);
	}
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

bool RshellExecuter::Execute(vector<string> command) {
	pid_t pid;
	int status;
	char** args = Convert(command);
	//Running the Command
	pid = fork();
	if (pid == -1) {
		perror("Fork");
		exit(1);
	}
	else if (pid == 0) {
		//close(1);
		dup2(in, 0);
		if (execvp(args[0], &args[0]) < 0) {
			close(STDIN_FILENO);
			exit(1);
		}
		else {
			exit(0);
		}
	}
	else {
		while (waitpid(-1, &status, 0) != pid) {}
		in = 0;
		if (WEXITSTATUS(status) == 1)
			return false;
		else {
			return true;
		}
	}
}
