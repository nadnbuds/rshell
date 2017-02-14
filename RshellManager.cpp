#include<iostream>
#include<vector>
#include<map>
#include "RshellReader.h"

using namespace std;

class RshellManager{
    
    enum BashCommands{
        nodef,
        close,
    };
    
    public:
        RshellManager(){
            mapStringToBash["Exit"] = close;
            StartShell();
        }
    
    private:
        map<string, BashCommands> mapStringToBash;
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
                switch(mapStringToBash[Commands.at(0)]){
                    case close:
                        stop = true;
                        break;
                    default:
                        break;
                }
            }
        }
};

int main(){
    
}