#ifndef __COMMANDCOMPONENT_H__
#define __COMMANDCOMPONENT_H__

#include "Connector.h"
#include <vector>

class CommandComponent {
	protected:
	Connector * p;
	string command;
	vector<string> parameters;
	public:
	CommandComponent();
	CommandComponent(string command, Connector *p);
	Connector * getConnector();
	string getCommand();	

};

#endif
