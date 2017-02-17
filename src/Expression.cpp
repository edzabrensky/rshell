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
}

void Expression::parse(const string &s) {
	char * str = new char[s.size() + 1];
        strcpy(str, s.c_str());
	char * pch = new char;
        pch = strtok (str," \n");
        string* k;
	string p = s;
	char * hcc = new char;
	while (pch != NULL)
        {
                k = new string(pch);
               	        if(strcmp("&&",pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new AND());
				pch = strtok(NULL, " \n");
                        }
                        else if(strcmp(";", pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new Semicolon());
				pch = strtok(NULL, " \n");
                        }
                        else if(strcmp("||", pch) == 0 && v.size() > 0) {
                                v.back()->setConnector(new OR());
				pch = strtok(NULL, " \n");
                        }
                        else if((*k).find(";") != string::npos) {
				if(v.size() == 0 && (*k).find(";") == 0) {
					v.push_back(new CommandComponent(*k, new None()));	
					pch = strtok(NULL, " \n");
				}
				else { 
                                	parse((*k).substr(0, (*k).find(";")));
					v.back()->setConnector(new Semicolon());
					if((*k).find(";") + 1 < (*k).size() - 1) {//if ; isnt the last part of the string
                                		parse((*k).substr((*k).find(";") + 1, (*k).size() - 1 - (*k).find(";")));       
                                	}
					pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");
				}
                                
                        }
                        else if((*k).find("||") != string::npos) {
				if(v.size() == 0 && (*k).find("||") == 0) {
					v.push_back(new CommandComponent(*k, new None()));
					pch = strtok(NULL, " \n");
				}
				else {
                                	parse((*k).substr(0, (*k).find("||")));
                                	v.back()->setConnector(new OR());
                                	if((*k).find("||") + 2 < (*k).size() - 1) {//if ||  isnt the last part of the string
                                        	parse((*k).substr((*k).find("||") + 2, (*k).size() - 2 - ((*k).find("||"))));
                                	}
					pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");
				}

                        }
			else if((*k).find("&&") != string::npos) {
				if(v.size() == 0 && (*k).find("&&") == 0) {
					v.push_back(new CommandComponent(*k, new None()));
					pch = strtok(NULL, " \n");
				}
				else {
                                	parse((*k).substr(0, (*k).find("&&")));
                               		v.back()->setConnector(new AND());
                                	if((*k).find("&&") + 2 < (*k).size() - 1) {//if && isnt the last part of the string
                                        	parse((*k).substr((*k).find("&&") + 2, (*k).size() - 2 - ((*k).find("&&"))));
					}
					pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");
				}

                        }

			else {
				if(v.size() == 0) {
					v.push_back(new CommandComponent(*k, new None()));
				}
				else {
                                	if(v.back()->getConnector()->isNone()) {
                                        	v.back()->parameters.push_back(*k);
                                	}
                                	else {
                                        	v.push_back(new CommandComponent(*k, new None()));
                                	}
				}
				
				pch = strtok(NULL, " \n");
                        }
	
	}
	//delete[] str;
}

void Expression::runExpression() {
	int i = 0;
	while(i < static_cast<int>(v.size())) {
		i += v.at(i)->getConnector()->runCommand(v.at(i));
	}
	while(v.size() > 0) {
		v.pop_back();
	}
}









