C = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	rm -rf ./bin
	mkdir -p ./bin
	g++ -Wall -Werror -ansi -pedantic ./src/main.cpp ./src/RshellReader.cpp ./src/RshellExecuter.cpp ./src/RshellManager.cpp -o ./bin/rshell


main:
	$(C) $(FLAGS) ./src/main.cpp -o ./bin/main
	
RshellReader:
	$(C) $(FLAGS) ./src/RshellReader.cpp -o ./bin/RshellReader
	
RshellExecuter:
	$(C) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/RshellExecuter
	
RshellManager:
	$(C) $(FLAGS) ./src/RshellManager.cpp -o ./bin/RshellManager
