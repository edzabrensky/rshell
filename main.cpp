#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Expression.h"
using namespace std;
int main() {
	string s;
	Expression * e;
	char hostname[1024];
	int result = gethostname(hostname, 1024);
	char username[1024];
	result = getlogin_r(username, 1024);
	while(1) {
		printf("%s@%s", username, hostname);
		cout << "$ ";
		getline(cin, s);
		e = new Expression(s);
		e->runExpression();
	}
	
	/*char * args[3];
	string ls = "ls";
	args[0] = (char*) ls.c_str();
	args[1] = (char*) ls.c_str();
	args[2] = NULL;
	
	if(execvp(args[0],args) == -1)
	{
		perror("exec");

	}
	*/
	return 0;
}








