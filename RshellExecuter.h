#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class RshellExecuter{
    
    public:
        RshellExecuter(){}
        
        bool RunCommand(vector<string> Command){
            pid_t pid;
            int status;
            
            //Convert Command into a char** args
            char* p[Command.size()];
            for(int x = 0; x < Command.size(); x ++){
                p[x] = const_cast<char*>(Command.at(x).c_str());
            }
            char **args = p;
            
            //Running the Command
            pid = fork();
            cout << pid;
            if(pid == -1){
                perror("Fork");
                exit(1);
                return false;
            }
            else if(pid == 0){
                if(execvp(args[0], args) < 0){
                    exit(1);
                    return false;
                }
            }
            else{
               while(wait(&status) != pid){}
                
            }
        }
    private:
};