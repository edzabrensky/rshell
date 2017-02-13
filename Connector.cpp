#include "Connector.h"

Connector::Connector() {
	
}

int Connector::runCommand(string cmd) {
	//syscall on cmd; fork, execvp, waitpid
	if (worked)
	{
		this->success = true;
	}
	if (!worked)
	{
		this->success = false;
	}
	return 1;
}

