COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic

all:
	rm -rf bin
	mkdir -p bin
	$(COMPILE) $(FLAGS) ./src/main.cpp -o ./bin/rshell
	$(COMPILE) $(FLAGS) ./src/RshellReader.cpp -o ./bin/rshell
	$(COMPILE) $(FLAGS) ./src/RshellExecuter.cpp -o ./bin/rshell
	$(COMPILE) $(FLAGS) ./src/RshellManager.cpp -o ./bin/rshell
