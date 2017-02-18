C = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	mkdir -p ./bin
	$(C) $(FLAGS) ./src/main.cpp -o ./bin/rshell
	$(C) $(FLAGS) ./src/RshellReader.cpp -o ./bin/rshell
	$(C) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/rshell
	$(C) $(FLAGS) ./src/RshellManager.cpp -o ./bin/rshell

main:
	$(C) $(FLAGS) ./src/main.cpp -o ./bin/rshell
	
RshellReader:
	$(C) $(FLAGS) ./src/RshellReader.cpp -o ./bin/rshell
	
RshellExecuter:
	$(C) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/rshell
	
RshellManager:
	$(C) $(FLAGS) ./src/RshellManager.cpp -o ./bin/rshell
