#include "CommandComponent.h"

CommandComponent::CommandComponent() : p(0) {}

CommandComponent::CommandComponent(string command, Connector * p) : p(p), command(command) {}
