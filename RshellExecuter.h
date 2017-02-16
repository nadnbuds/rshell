#include<iostream>
#include<vector>
#include<map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class RshellExecuter{
    
    public:
        RshellExecuter(){}
        
        bool RunCommand(vector<string> Command){
            pid_t pid;
            int status;
            pid = fork();
            if(pid == -1){
                perror("Fork");
                exit(1);
                return false;
            }
            else if(pid == 0){
                if(execvp(Command.at(0).c_str(), Command) < 0){
                    exit(1);
                    return false;
                }                
            }
            else{
                while(wait(&status) != pid)
                {
                    
                }
                return true;
                
            }
        }
    private:
};