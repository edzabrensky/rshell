#include "CommandComposite.h"


CommandComposite::CommandComposite() {
}

void CommandComposite::add(CommandComponent *cmdC) {
	v.push_back(cmdC);
}
void CommandComposite::remove(int pos) {
	v.erase(v.begin() + pos - 1);
}


