#ifndef RSHELLREADER_H
#define RSHELLREADER_H
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class RshellReader{
     
    private:
        string Input;
        static const char spaceCheck = ' ';
        static const char semiCheck = ';';
        static const char hashCheck = '#';

    public:
    	vector<string> Commands;
	char hostname[40];
	char username[40];
	RshellReader();
    	void ReadLine();  
    	void SpliceLine();
    
    
};

#endif
