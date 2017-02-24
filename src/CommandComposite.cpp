#include "CommandComposite.h"


CommandComposite::CommandComposite() {
}
Connector* CommandComposite::getConnector() {
	return p;
}
void CommandComposite::add(CommandComponent *cmdC) {
	v.push_back(cmdC);
}
void CommandComposite::remove(int pos) {
	v.erase(v.begin() + pos - 1);
}


