#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Expression.h"
using namespace std;
int main() {
	string s;
	Expression * e;
	while(1) {
		cout << "$ ";
		getline(cin, s);
		e = new Expression(s);
		e->runExpression();
	}	
	return 0;
}
