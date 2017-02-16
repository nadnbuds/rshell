#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RshellReader{
    
    private:
        string Input;
        static const char spaceCheck = ' ';
        static const char semiCheck = ';';
        static const char hashCheck = '#';
    public:

    vector<string> Commands;

    void ReadLine(){
            cout << "Rshell$ ";
            Commands.clear();
            getline(cin, Input);
            SpliceLine();
    }
    
    void SpliceLine(){
        for(unsigned x = 0; x < Input.length(); x++){
            if(Input.at(x) == spaceCheck){
                string temp = Input.substr(0, x-1);
                //Add a bound measure incase this goes over line.length() - 1
                Input = Input.substr(x+1);
                x = 0;
                Commands.push_back(temp);
            }
            if(Input.at(x) == semiCheck){
                string temp = Input.substr(0,x-1);
                Input = Input.substr(x+1);
                x = 0;
                Commands.push_back(temp);
                Commands.push_back(";");
            }
            if(Input.at(x) == hashCheck){
                return;
            }
        }
        Commands.push_back(Input);
    }
    
};
