
all.o: main.cpp RshellExecuter.cpp RshellExecuter.h RshellReader.cpp RshellReader.h RshellManager.cpp RshellManager.h
	g++ -Wall -Werror -ansi -pedantic
rshell.o: main.cpp RshellExecuter.cpp RshellExecuter.h RshellReader.cpp RshellReader.h RshellManager.cpp RshellManager.h
	g++ -Wall -Werror -ansi -pedantic
