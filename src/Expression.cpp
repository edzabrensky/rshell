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
	char * str = new char[s.size() + 1];
        strcpy(str, s.c_str());
	char * pch = new char;
        pch = strtok (str," \n");
        string* k;
	string p = s;
	char * hcc = new char;
	//str[s.size()] = NULL;
	while (pch != NULL)
        {
                k = new string(pch);
		//cout << *k << (*k).size() << endl;
                //if(v.size() == 0) {
                //                        v.push_back(new CommandComponent(k, new None()));
                //}
	 	//else {
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
					//hcc = strtok( NULL, " \n");
                                	parse((*k).substr(0, (*k).find(";")));
					v.back()->setConnector(new Semicolon());
					if((*k).find(";") + 1 < (*k).size() - 1) {//if ; isnt the last part of the string
                                		parse((*k).substr((*k).find(";") + 1, (*k).size() - 1 - (*k).find(";")));       
                                	}
					//pch = hcc;
					pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");
				}
                                
                        }
                        else if((*k).find("||") != string::npos) {
				if(v.size() == 0 && (*k).find("||") == 0) {
					v.push_back(new CommandComponent(*k, new None()));
					pch = strtok(NULL, " \n");
				}
				else {
					//pch = strtok(NULL, " \n");
                                	parse((*k).substr(0, (*k).find("||")));
                                	v.back()->setConnector(new OR());
                                	if((*k).find("||") + 2 < (*k).size() - 1) {//if ; isnt the last part of the string
                                        	parse((*k).substr((*k).find("||") + 2, (*k).size() - 2 - ((*k).find("||"))));
                                       		// cout <<k.substr(k.find("||") + 2, k.size() - 1 - k.find("||") + 2) << endl;
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
					
					//pch = strtok((char*)p.substr(s.find((*k)) + (*k).size() + 1, p.size() - (*k).size()).c_str(), " \n");
					//strcpy(hcc, pch);
                                	//parse((*k).substr(0, (*k).find("&&")));
                                	//pch = strtok(NULL, " \n");
                                	parse((*k).substr(0, (*k).find("&&")));
                               		v.back()->setConnector(new AND());
                                	if((*k).find("&&") + 2 < (*k).size() - 1) {//if ; isnt the last part of the string
                                        	parse((*k).substr((*k).find("&&") + 2, (*k).size() - 2 - ((*k).find("&&"))));
                                		//parse(pch[k.find("&&") +2]);
                                		//cout << "XDDD" << endl;
					}
					pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");

					//pch = hcc;
					//pch =strtok(NULL, " \n");
				}

                        }

			else {
				//pch = strtok(NULL, " \n");
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
				//pch = strtok((char*)p.substr(s.find((*k)) + (*k).size(), p.size() - (*k).size()).c_str(), " \n");
				
				pch = strtok(NULL, " \n");
                        }
                //}
                //pch = strtok (NULL, " \n");
	
	}
	//delete[] str;
}

void Expression::runExpression() {
	int i = 0;
	while(i < static_cast<int>(v.size())) {
		//cout << v.size() << endl;
		//cout << v.at(i)->getCommand() << endl;
		i += v.at(i)->getConnector()->runCommand(v.at(i));
		//cout << i << endl;
	}
}









