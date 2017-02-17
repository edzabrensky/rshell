#include "Connector.h"
Connector::Connector() {
	
}
bool Connector::isNone() {
	return false;
}
int Connector::runCommand(CommandComponent *cmd) {
	if(cmd->getCommand().compare("exit") == 0) {
		exit(0);
		exit(0);
	}
	else {
	char * args[500] = {NULL};
	args[0] = (char*)cmd->getCommand().c_str();
	for(unsigned i = 0; i < cmd->parameters.size(); ++i) {
		args[i +1] = (char*)cmd->parameters.at(i).c_str();
	}
	//syscall on cmd; fork, execvp, waitpid
	pid_t pid = fork();
		
	if (pid == 0) //child
	{
		if ( execvp(args[0], args) == -1 ) 
		{
			this->success = false;
			perror ("exec");
			exit(1);
		}
		else {
			exit(0);
		}
	}
	
	if (pid > 0) //parent
	{
		int status;
		if (wait(0) == -1)
		{
			perror ("wait");
		}
		else {
			pid_t result = waitpid(0, &status, WNOHANG); //need to do if status == 1 then success = false if status == 0 then return 1
			if(result == -1) {
				success = false;
			}
			else {
				success = true;
			}
		}
			
	}
	}			
	return 1;
}

