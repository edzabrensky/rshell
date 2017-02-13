#include "Connector.h"
Connector::Connector() {
	
}
bool Connector::isNone() {
	return false;
}
int Connector::runCommand(CommandComponent *cmd) {
	char * args[500] = {NULL};
	args[0] = (char*)cmd->getCommand().c_str();
	for(unsigned i = 0; i < cmd->parameters.size(); ++i) {
		args[i +1] = (char*)cmd->parameters.at(i).c_str();
	}
	//syscall on cmd; fork, execvp, waitpid
	pid_t pid = fork();
		
	if (pid == 0) //child
	{
		if ( execvp(args[0], args) == -1 ) //ADD PARAMETERS FOR EXECVP
		{
			this->success = false;
			perror ("exec");
		}
	}
	
	if (pid > 0) //parent
	{
		if (wait(0) == -1)
		{
			perror ("wait");
		}
		else {
			success = true;
		}
			
	}			
	return 1;
}

