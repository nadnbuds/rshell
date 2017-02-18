CC= g++
CFLAGS = -Wall -Werror -ansi -pedantic
all:
	mkdir -p ./bin
	$(CC) $(CFLAGS) RshellExecuter.cpp RshellReader.cpp RshellManager.cpp main.cpp
