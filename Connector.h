#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

using namespace std;
class Connector {
	public:
	Connector();
	bool success;
	virtual int runCommand(string cmd);
	virtual bool isNone();
};

#endif
