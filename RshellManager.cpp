#include<iostream>
#include<vector>
#include "RshellReader.h"

using namespace std;

class RshellManager{
    public:
        RshellManager(){
            StartShell();
        }
    
    private:
        bool stop;
        RshellReader Reader;
        void StartShell(){
            while(!stop){
                Reader.ReadLine();
                Interpret(Reader.GetInputCommands());
            }
        }
        
        void Interpret(vector<string> Commands){
            while(Commands.size() > 0){
                
                //Implement Str2Int or enum
                //http://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4067/Switch-on-Strings-in-C.htm
                switch(Commands){
                    case Commands.at(0).equals("Exit"):
                        stop = true;
                        break;
                    default:
                        break;
                }
            }
        }
};