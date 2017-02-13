#include "Connector.h"
Connector::Connector() {
	
}
bool Connector::isNone() {
	return false;
}
int Connector::runCommand(CommandComponent *cmd) {
	//syscall on cmd; fork, execvp, waitpid
	pid_t pid = fork();
	
	if (pid == -1) //error
	{
		perror ("fork");
		this->success = false;
	}
		
	if (pid == 0) //child
	{
		this->success = true;
		if ( execvp(REPLACE WITH PARAMETERS) == -1 ) //ADD PARAMETERS FOR EXECVP
		{
			perror ("exec");
		}
	}
	
	if (pid > 0) //parent
	{
		if (wait(0) == -1)
		{
			perror ("wait");
		}
			
	}
			
	return 1;
}

