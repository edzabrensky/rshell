#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include "CommandComposite.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
using namespace std;

class Expression : public CommandComposite {
	public:
	Expression(const string &e);
	void runExpression();
	

};



#endif