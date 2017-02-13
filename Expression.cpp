#include "Expression.h"
//assumes the first string is the command even if it is a connector
//e.g. if the user types "&& ls -a" it will assume && is a command and the arguments are ls and -a
Expression::Expression(const string &e) {
	string s = e;
	if(s.find("#") != string::npos)  {
		s = e.substr(0, e.find("#"));
		//cout << s << endl;
	}
	char * str = new char[s.size() +1];
	strcpy(str, s.c_str());
        char * pch;
        pch = strtok (str," \n");
	string k;
	int i = 0;
        while (pch != NULL)
        {
                k = pch;
                cout << k << endl;
		if(i == 0) {
			v.push_back(new CommandComponent(k, new None()));
			++i;
		}
		else {
			if(strcmp("&&",pch) == 0) {
				v.at(i - 1)->setConnector(new AND());
			}
			else if(strcmp(";", pch) == 0) {
				v.at(i - 1)->setConnector(new Semicolon());
			}		
			else if(strcmp("||", pch) == 0) {
				v.at(i - 1)->setConnector(new OR());
			}
			else {
				if(v.at(i - 1)->getConnector()->isNone()) {
					v.at(i - 1)->parameters.push_back(k);	
				}
				else {
					v.push_back(new CommandComponent(k, new None()));
				}
			}
		}	
                pch = strtok (NULL, " \n");
        }
	delete[] str;
	
	


	/*string p = e;
	string token;
	while(p.size() > 0) {
		if(p.find("&&") == string::npos && p.find("||") == string::npos && p.find(";") == string::npos) {
			//v.push_back(new CommandComponent(p, new None());	
			//s = "";
		}
		else if(p.find("&&") < p.find("||") && p.find("||") <= p.find(";")) {
			//token = p.substr(0, p.find("&&");
			//v.push_back(new CommandComponent(token, new AND());
			//p = p.substr(p.find("&&" + 2, p.size() - 1 - p.find("&&") + 1);
		}

	}*/		
}

void Expression::runExpression() {
	int i = 0;
	while(i < static_cast<int>(v.size())) {
		i += v.at(i)->getConnector()->runCommand(v.at(i));
	}
}

