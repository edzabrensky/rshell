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
}//ss
int Connector::runCommand(CommandComponent *cmd) {
	bool p = false;
	for(unsigned i = 0; i < cmd->parameters.size(); ++i) {
		if(cmd->parameters.at(i).compare("<") == 0 ||//detect if a pipe is found
			cmd->parameters.at(i).compare(">") == 0 ||
			cmd->parameters.at(i).compare("|") == 0 ||
			cmd->parameters.at(i).compare(">>") == 0) {
			p = true;
		}
	}
	if(cmd->getCommand().compare("exit") == 0) {
		exit(0);
		exit(0);
	}

	else if(p) {//pipe found
		char ** arr[500] = {NULL};
		//vector<char *> temp;
		bool prev = true;
		int size = 0;
		int tempSize = 0;
		char ** temp = new char*[20];
		temp[0] = (char*)cmd->getCommand().c_str();
		++tempSize;
		for(unsigned i = 0; i < cmd->parameters.size(); ++i) {
		//	cout << cmd->parameters.at(i) << " " << endl;
                	if(cmd->parameters.at(i).compare("<") == 0 ||//detect if a pipe is found
                        	cmd->parameters.at(i).compare(">") == 0 ||
                        	cmd->parameters.at(i).compare("|") == 0 ||
                        	cmd->parameters.at(i).compare(">>") == 0) {
                        	//p = true;
                        	if(tempSize == 1) {
					temp[tempSize] = NULL;
				}
                        	/*if(i == 0) {
					++size;
				}*/
                        	arr[size] = temp;
				/*if(i == 0) {
					++size;
				}*/
				temp = new char*[20]; 
				tempSize = 0;
				/*if(i != 0) {
					++size;
				}*/
				++size;
                	}
			else {
				temp[tempSize] = (char*)cmd->parameters.at(i).c_str();	
				if(i == cmd->parameters.size() - 1) {	
					arr[size] = temp;
					++size;
				}
				++tempSize;
			}
        	}//supposed to fill arr with each command and its parameters. the number of pipes should be size - 1.
		int q[2];
		(arr[size]) = NULL;
		arr[size+1] = NULL;
		pid_t pid;
		int d = 0;
		int fd_in = 0;
		int curr_index = 0;
		//int curr_in;
		//cout << size << endl;
		for(int i = 0; i < cmd->parameters.size(); ++i) {
			if(cmd->parameters.at(i).compare("<") == 0) {
				int pid1 = fork();
				/*d = open(*(arr[curr_index+1]), O_RDONLY);
				dup2(d, STDIN_FILENO);
				in = 0;
				curr_in = dup(0);*/
				if(pid1 < 0) {
					perror("fork");
				}	
				else if(pid1 == 0) {
					d = open(*(arr[curr_index+1]), O_RDONLY);
					dup2(d, STDIN_FILENO);
					close(d);
					execvp((arr[curr_index])[0], arr[curr_index]);
					perror("execvp");
					exit(1);
				}
				else {
					waitpid(pid1, 0, 0);
					++curr_index;
					//++curr_index;
					//dup2(curr_out, 1);
					//free(*arr);
				}	
			}
			else if(cmd->parameters.at(i).compare(">") == 0) {
				int pid1 = fork();
				if(pid1 < 0) {
					perror("fork");
				}
				else if(pid1 == 0) {
					d = creat(*(arr[curr_index+1]), 0644);
					dup2(d, STDOUT_FILENO);
					close(d);
					execvp((arr[curr_index])[0], arr[curr_index]);
					perror("execvp");
					exit(1);
				}
				else {
					waitpid(pid1, 0,0);
					++curr_index;
				}
			}
			else if(cmd->parameters.at(i).compare(">>") == 0) {
				int pid1 = fork();
				if(pid1 < 0) {
					perror("fork");
				}
				else if(pid1 == 0) {
					d = open(*(arr[curr_index+1]),O_WRONLY | O_CREAT |  O_APPEND, S_IRUSR | S_IWUSR);
					dup2(d, STDOUT_FILENO);
					close(d);
					execvp((arr[curr_index])[0], arr[curr_index]);
					perror("execvp");
					exit(1);
				}
				else {
					waitpid(pid1, 0, 0);
					++curr_index;
				}
			}
			else if(cmd->parameters.at(i).compare("|") == 0) {
				//cout << "ADFADF" << endl;
				pipe(q);
				if((pid = fork()) == 0) {
					if(d != 0) {
						dup2(d, 0);
						close(d);
					}
					if(q[1] != 0) {
						dup2(q[1],1);
						close(q[1]);
					}
					execvp((arr[curr_index])[0], arr[curr_index]);
					perror("execvp");
					exit(1);
				}
				else if(pid > 0) {
					//waitpid(pid, 0 ,0);
					close(q[1]);
					d = q[0];
					++curr_index;
					if(curr_index == size - 1 && d != 0) {
						//cout << "ASDASD" ;
						dup2(d,0);
						execvp((arr[curr_index])[0],arr[curr_index]);
						//exit(0);	
						//close(d);
						/*pid_t pid2;
						if((pid2 = fork()) == 0) {
							execvp((arr[curr_index])[0],arr[curr_index]);
							perror("execvp");
							exit(1);
						}
						else if(pid2 >0) {
							waitpid(pid2, 0 ,0);
							cout << "ASDASD";	
						}*/
					}
					//++curr_index;
				}
				/*if(pid < 0) {
					exit(EXIT_FAILURE);
				}
				else if(pid == 0) { 
					dup2(d, 0);
					//close(q[0]);
					//close(d);
					//dup2(q[0], 0);
					//if((arr[curr_index+1]) != NULL) {
					if(curr_index + 1 < size) {
						//dup2(q[1],1);
						//cout << "A" << endl;
						//dup2(q[1], 1);
						//close(q[1]);
						//close(q[1]);
						//dup2(q[1], STDOUT_FILENO);
					}
					//close(d);
					//close(q[0]);
					//close(q[1]);
					//close(d);
					//close(d);
					execvp((arr[curr_index])[0], arr[curr_index]);
					perror("execvp");
					exit(1);
				}
				else {
					//if(curr_index + 1 < size) {
					dup2(q[1],1);
					//}
					//wait(NULL);
					waitpid(pid, 0 , 0);
					close(q[1]);
					close(q[0]);
					d = q[0];
					//d, q[0]);
					curr_index++;
				}*/
			}
			//else if(cmd->parameters.at(i).compare("

		}
		
	}
	else if (cmd->getCommand().compare("test") == 0 && cmd->parameters.size() >= 1) //path at v.at(v.size() - 1)
	{
	struct stat buf;
	stat((cmd->parameters.at(cmd->parameters.size() - 1)).c_str(), &buf);
	for (unsigned i = 0; i < cmd->parameters.size() - 1; ++i && success)
	  {
		if (cmd->parameters.at(i) == "-e")
		{
			if (stat(cmd->parameters.at(cmd->parameters.size() - 1).c_str(), &buf) == 0) //checks if something exists
			{
			//cout << "it's either a folder or file" << endl;
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else if (cmd->parameters.at(i) == "-f")
		{
			if (S_ISREG(buf.st_mode))
			{
				//cout << "it's a file" << endl;
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else if (cmd->parameters.at(i) == "-d")
		{
			if (S_ISDIR(buf.st_mode))
			{
				//cout << "it's a folder" << endl;
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else
		{

		}
		
	  }
		if (this->success)
		{
			cout << "(True)" << endl;
		}
		else
		{
			cout << "(False)" << endl;
		}
	
	}
	
	else if (cmd->getCommand().compare("[") == 0 && cmd->parameters.size() >= 2) //difference being that the path will be at v.at(v.size() - 2) instead of v.at(v.size() - 1)
	{
	struct stat buf;
	stat((cmd->parameters.at(cmd->parameters.size() - 2)).c_str(), &buf);
	for (unsigned i = 0; i < cmd->parameters.size() - 2; ++i && success)
	  {
		if (cmd->parameters.at(i) == "-e")
		{
			if (stat(cmd->parameters.at(cmd->parameters.size() - 2).c_str(), &buf) == 0)
			{
			//cout << "it's a folder or file" << endl;
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else if (cmd->parameters.at(i) == "-f")
		{
			if (S_ISREG(buf.st_mode))
			{
				//cout << "it's a file" << endl;
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else if (cmd->parameters.at(i) == "-d")
		{
			if (S_ISDIR(buf.st_mode))
			{
				//cout << "it's a folder" << endl; 
				this->success = true;
			}
			else
			{
				this->success = false;
				//break;
			}
		}
		
		else
		{

		
		}
		if (this->success)
		{
			cout << "(True)" << endl;
		}
		else
		{
			cout << "(False)" << endl;
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

