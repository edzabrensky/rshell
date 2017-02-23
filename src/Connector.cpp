#include "Connector.h"
Connector::Connector() {
	
}
bool Connector::isNone() {
	return false;
}
bool Connector::isAND() {
	return false;
}
bool Connector::isOR() {
	return false;
}
int Connector::runCommand(CommandComponent *cmd) {
	if(cmd->getCommand().compare("exit") == 0) {
		exit(0);
		exit(0);
	}
	
	else if (cmd->getCommand().compare("test") == 0 || cmd->getCommand().compare("[") == 0)
	{
	struct stat buf;
	for (unsigned i = 0; i < cmd->parameters.size(); ++i)
	  {
		if (cmd->parameters.at(i) == "-e")
		{
			if (buf.st_mode & S_ISDIR) // returns 1 if success, -1 if error / failure
			{			   //double check flag that determines if it exists
				cout < "(True)" << endl;
				this->success = true;
			}
			else
			{
				cout << "(False)" << endl;
				this->success = false;
			}
		}
		
		if (cmd->parameters.at(i) == "-f")
		{
			if (buf.st_mode & S_ISREG)
			{
				cout << "(True)" << endl;
				this->success = true;
			}
			else
			{
				cout << "(False)" << endl;
				this->success = false;
			}
		}
		
		if (cmd->parameters.at(i) == "-d")
		{
			if (buf.st_mode & S_ISDIR)
			{
				cout << "(True)" << endl;
				this->success = true;
			}
			else
			{
				cout << "(False)" << endl;
				this->success = false;
			}
		}
		
	  }
			
	}
	
	else {
	char * args[500] = {NULL};
	args[0] = (char*)cmd->getCommand().c_str();
	for(unsigned i = 0; i < cmd->parameters.size(); ++i) {
		args[i +1] = (char*)cmd->parameters.at(i).c_str();
	}
	//syscall on cmd; fork, execvp, waitpid
	pid_t pid = fork();
	if(pid == -1) {
		perror("fork error");
		exit(1);
	}	
	else if (pid == 0) //child
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
	
	else if (pid > 0) //parent
	{
		int status;
		do {
		pid_t endID = (waitpid(pid, &status, WNOHANG|WUNTRACED));
		if(wait(&status) == -1) {
			perror("wait");
		}
		if(endID == -1) {
			perror("waitpid error");
			//exit(EXIT_FAILURE);
		}
			if(WIFEXITED(status)) {
				if(status == 0) {
					success = true;
				}
				else {
					success = false;
				}
			}
			else if(WIFSIGNALED(status)) {
				success = false;
			}
			else if(WIFSTOPPED(status)) {
				success = false;
			}
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));	
	}
	}			
	return 1;
}

