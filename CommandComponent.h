#include "Connector.h"

class CommandComponent {
	protected:
	Connector * p;
	string command;
	public:
	CommandComponent();
	CommandComponent(string command, Connector *p);
	

};
