CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell compileTest1 compileTest2 compileTest3 compileTest4
	$(CC) $(CLAGS) src/AND.cpp src/OR.cpp src/None.cpp src/Semicolon.cpp src/main.cpp src/Expression.cpp src/CommandComposite.cpp src/CommandComponent.cpp src/Connector.cpp -o bin/rshell
rshell : makedir

makedir : 
	mkdir bin

compileTest1 :
	chmod 711 tests/test_test.sh

compileTest2 :
	chmod 711 tests/precedence_test.sh

compileTest3 :
	chmod 711 tests/commented_command.sh

compileTest4 : 
	chmod 711 tests/exit.sh
