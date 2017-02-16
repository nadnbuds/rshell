#include<iostream>
#include<vector>
#include<map>

class RshellExecuter{
    enum BashCommands{
        nodef,
        close,
    };
    
    public:
        RshellExecuter(){
            mapStringToBash["Exit"] = close;
        }
        
        //
        bool RunCommand(vector<string> Command){
            switch(mapStringToBash[Command.at(0)]){
                    case close:
                        
                        break;
                    default:
                        break;
                }
                return false;
        }
    private:
        map<string, BashCommands> mapStringToBash;
};