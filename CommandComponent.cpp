#include "CommandComponent.h"

CommandComponent::CommandComponent() : p(0) {}

CommandComponent::CommandComponent(string command, Connector * p) : p(p), command(command) {}


Connector * CommandComponent::getConnector() {
	return p;

}

string CommandComponent::getCommand() {
	return command;

}

void CommandComponent::setConnector(Connector * x) {
	p = x;
}



