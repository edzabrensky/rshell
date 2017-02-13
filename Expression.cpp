#include "Expression.h"
//assumes the first string is the command even if it is a connector
//e.g. if the user types "&& ls -a" it will assume && is a command and the arguments are ls and -a
Expression::Expression(const string &e) {
	string s = e;
	if(s.find("#") != string::npos)  {
		s = e.substr(0, e.find("#"));
		//cout << s << endl;
	}
	parse(s);

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

void Expression::parse(const string &s) {
	char * str = new char[s.size() +1];
        strcpy(str, s.c_str());
	char * pch;
        pch = strtok (str," \n");
        string k;
	while (pch != NULL)
        {
                k = pch;
                //if(v.size() == 0) {
                //                        v.push_back(new CommandComponent(k, new None()));
                //}
		//else {
               	        if(strcmp("&&",pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new AND());
                        }
                        else if(strcmp(";", pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new Semicolon());
                        }
                        else if(strcmp("||", pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new OR());
                        }
                        else if(k.find(";") != string::npos && v.size() > 0) {
                                parse(k.substr(0, k.find(";")));
				v.back()->setConnector(new Semicolon());
				if(k.find(";") + 1 > k.size() - 1) {//if ; isnt the last part of the string
                                	parse(k.substr(k.find(";") + 1, k.size() - 1 - k.find(";")));       
                                }
                                
                        }
                        else if(k.find("||") != string::npos && v.size() > 0) {
                                parse(k.substr(0, k.find("||")));
                                v.back()->setConnector(new OR());
                                if(k.find("||") + 2 > k.size() - 1) {//if ; isnt the last part of the string
                                        parse(k.substr(k.find("||") + 2, k.size() - 1 - (k.find("||") + 1)));
                                       // cout <<k.substr(k.find("||") + 2, k.size() - 1 - k.find("||") + 2) << endl;
                                }

                        }
			else if(k.find("&&") != string::npos && v.size() > 0) {
                                parse(k.substr(0, k.find("&&")));
                                v.back()->setConnector(new AND());
                                if(k.find("&&") + 2 > k.size() - 1) {//if ; isnt the last part of the string
                                        parse(k.substr(k.find("&&") + 2, k.size() - 1 - (k.find("&&") + 1)));
                                }

                        }

			else {
				if(v.size() == 0) {
					v.push_back(new CommandComponent(k, new None()));
				}
				else {
                                	if(v.back()->getConnector()->isNone()) {
                                        	v.back()->parameters.push_back(k);
                                	}
                                	else {
                                        	v.push_back(new CommandComponent(k, new None()));
                                	}
				}
                        }
                //}
                pch = strtok (NULL, " \n");
	
	}
	delete[] str;
}

void Expression::runExpression() {
	int i = 0;
	while(i < static_cast<int>(v.size())) {
		//cout << v.size() << endl;

		i += v.at(i)->getConnector()->runCommand(v.at(i));
		//cout << i << endl;
	}
}









