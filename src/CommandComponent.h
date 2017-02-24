#ifndef __COMMANDCOMPONENT_H__
#define __COMMANDCOMPONENT_H__

#include "Connector.h"
#include <vector>
#include <string>
using namespace std;
class Connector;
class CommandComponent {
	protected:
	Connector * p;
	string command;
	public:
	vector<string> parameters;
	CommandComponent();
	CommandComponent(string command, Connector *p);
	virtual Connector * getConnector();
	string getCommand();	
	void setConnector(Connector *);
};

#endif
