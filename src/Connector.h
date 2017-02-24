#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "CommandComponent.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>
#include <cstring>
using namespace std;

class CommandComponent;
class Connector {
	public:
	Connector();
	bool success;
	virtual int runCommand(CommandComponent *);
	virtual bool isNone();
	virtual bool isAND();
	virtual bool isOR();
};

#endif
