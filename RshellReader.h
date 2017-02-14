#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RshellReader{
    
    private:
        string line;
        static const char spaceCheck = ' ';
        static const char semiCheck = ';';
        vector<string> Commands;
    public:

    void ReadLine(){
            cout << "Rshell$ ";
            cin >> line;
            SpliceLine(line);
    }
    
    void SpliceLine(string line){
        for(unsigned x = 0; x < line.length(); x++){
            if(line.at(0) == spaceCheck){
                string temp = line.substr(0, x-1);
                //Add a bound measure incase this goes over line.length() - 1
                if(line.at(0 == spaceCheck)){
                    line = line.substr(x+1);
                }
                else{
                    line = line.substr(x);
                }
                x = 0;
                Commands.push_back(temp);
            }
        }
    }
    
    vector<string> GetInputCommands(){
        return Commands;
    }
    
};
