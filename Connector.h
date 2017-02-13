#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <string>
#include <unistd.h>
using namespace std;
class Connector {
	public:
	Connector();
	bool success;
	virtual int runCommand(string cmd);	
};

#endif
