#include "Expression.h"


Expression::Expression(const string &e) {
	string s = e;
	if(s.find("#") != string::npos)  {
		s = e.substr(0, e.find("#"));
		cout << "XASDASD" << endl;
	}
	char * str = new char[s.size() +1];
	strcpy(str, s.c_str());
        char * pch;
        pch = strtok (str,";");
	string k;
        while (pch != NULL)
        {
                k = pch;
                cout << k << endl;
                
                pch = strtok (NULL, ";");
        }
	delete[] str;
	
}

void Expression::runExpression() {


}

