CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell 
	$(CC) $(CLAGS) src/AND.cpp src/OR.cpp src/None.cpp src/Semicolon.cpp src/main.cpp src/Expression.cpp src/CommandComposite.cpp src/CommandComponent.cpp src/Connector.cpp -o bin/rshell
rshell : makedir

makedir : 
	mkdir bin
