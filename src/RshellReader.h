#ifndef RSHELLREADER_H
#define RSHELLREADER_H
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

    	void ReadLine();  
    	void SpliceLine();
    
    
};

#endif
