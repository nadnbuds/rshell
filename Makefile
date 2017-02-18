C = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin
	g++ -Wall -Werror -ansi -pedantic ./src/main.cpp -o ./bin/rshell
	$(C) $(FLAGS) ./src/RshellReader.cpp -o ./bin/RshellReader
	$(C) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/RshellExecuter
	$(C) $(FLAGS) ./src/RshellManager.cpp -o ./bin/RshellManager

main:
	$(C) $(FLAGS) ./src/main.cpp -o ./bin/main
	
RshellReader:
	$(C) $(FLAGS) ./src/RshellReader.cpp -o ./bin/RshellReader
	
RshellExecuter:
	$(C) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/RshellExecuter
	
RshellManager:
	$(C) $(FLAGS) ./src/RshellManager.cpp -o ./bin/RshellManager
