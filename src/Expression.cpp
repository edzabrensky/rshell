#include "Expression.h"
//assumes the first string is the command even if it is a connector
//e.g. if the user types "&& ls -a" it will assume && is a command and the arguments are ls and -a
Expression::Expression(const string &e) {
	this->setConnector(new None());

	vExpression = new vector<pair<int,int> >;
	string s = e;
	if(s.find("#") != string::npos)  {
		s = e.substr(0, e.find("#"));
		//cout << s << endl;
	}
	if(e.find('(') == string::npos && e.find(')') == string::npos) {
		parse(s);
	}
	else if(!balancedParenthesis(s)) {
		//cout << s << endl;
		cout << "Parenthesis not balanced." << endl;
	}
	else {//balanced parenthsis
		this->setConnector(new None());
		createTree(s); 	
		//cout << s << endl;
		//cout << vOfOrderedCommands.size() << endl;
		/*for(unsigned i = 0; i <vOfOrderedCommands.size(); ++i) {
			//for(unsigned j = 0; j < (vOfOrderedCommands.at(i)->v).size(); ++j) {
				//cout << (vOfOrderedCommands.at(i)->v).at(0)->getCommand() << endl;
			//}
			cout << vOfOrderedCommands.at(i)->getConnector() << endl;
			if(vOfOrderedCommands.at(i)->getConnector() == 0) {
				vOfOrderedCommands.erase(vOfOrderedCommands.begin() + i);
				i =0;
			}
		}*/
	
	}		
}
int Expression::findLastConnector(const string &s) {//if x = 0 then it is None if x = 1 then its &, if 2 then or, if 3 then semicolon
	int recent = 0;
	/*char* str = new char[s.size() +1];
	strcpy(str,s.c_str());
	char * pch = strtok(str, " ");
	string *k;
	while(pch != NULL) {
		k = new string(pch);
		if((*k).find("&&") == string::npos && (*k).find("||") == string::npos && (*k).find(";")  == string::npos) {
			recent = 0;
		}
		else if((*k).find("&&"))		
		pch = strtok(NULL, " ");
	}*/
	return recent;
}

void Expression::createTree(const string &s) {//TODO: NEED TO CHECK FOR CONNECTOR BEFORE EACH EXPRESSION BEFORE EXECUTING
	string temp;
	for(unsigned i = 0; i < vExpression->size(); ++i) {//there can be a command before and after each vExpression element
		//cout << vExpression->at(i).first << " " << vExpression->at(i).second << endl;
		if(vExpression->at(i).first - 1 > 0 && i == 0) {
			//cout << s.substr(0,vExpression->at(i).first - 1) << "XD" << endl;
			vOfOrderedCommands.push_back(new Expression(s.substr(0,vExpression->at(i).first - 1)));
			if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
				vOfOrderedCommands.pop_back();	
			}
			else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
				vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
			}
			else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                        }
			else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                        }
			else {
				vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
			}

			//check for the last command in the expression just added and see what its connector is then add it to the expression's connector.
		}
		vOfOrderedCommands.push_back(new Expression(s.substr(vExpression->at(i).first + 1, vExpression->at(i).second -1 - vExpression->at(i).first)));
		//vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new None());
		//cout << s.substr(vExpression->at(i).first + 1, vExpression->at(i).second -1 - vExpression->at(i).first) << endl;
		if(i == vExpression->size() -1 && (s.size() - 1 > vExpression->at(i).second)) {//last expression 
			//vOfOrderedCommands.push_back(new Expression(s.substr(vExpression->at(i).second + 1, s.size() - 1 - vExpression->at(i).second - 1)));
			temp = s.substr(vExpression->at(i).second + 1, s.size()-1 - vExpression->at(i).second );
			//cout << temp << endl;
                        if(temp.find("&&") == string::npos && temp.find("||") == string::npos && temp.find(";") == string::npos) {
                                vOfOrderedCommands.push_back(new Expression(temp)); 
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new None());
                                if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() == 0) {//no Connector so there is no connector before it
                                	vOfOrderedCommands.pop_back();
                        	}//need to check if its AND or OR or semicolon
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                        	}
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                        	}
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                        	}
                        	else {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                        	}

                        }
                        else if(temp.find("&&") < temp.find("||") && temp.find("&&") < temp.find(";")) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new AND());
				//temp = temp.substr(temp.find("&&") + 2, temp.size() -1);
                                temp = temp.substr(temp.find("&&") + 2, temp.size() -1 - temp.find("&&") - 1);
				//cout << temp << "123123" << endl;
                                //vOfOrderedCommands.push_back(new Expression(temp));
                                if(temp.size() != 0) {
                                        vOfOrderedCommands.push_back(new Expression(temp));
					if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                		vOfOrderedCommands.pop_back();
                        		}
                        		else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                		vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                        		}
                        		else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                		vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                        		}
                        		else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                		vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                        		}
                        		else {
                                		vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                        		}


                                }
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new AND());

                        }
                        else if(temp.find("||") < temp.find("&&") && temp.find("||") < temp.find(";")) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new OR());
				//temp = temp.substr(temp.find("||") + 2, temp.size() -1);
                                temp = temp.substr(temp.find("||") + 2, temp.size() -1 - temp.find("||") - 1);//FIXME:CHANGED -2 at the end to -1
                                //vOfOrderedCommands.push_back(new Expression(temp));
                                if(temp.size() != 0) {
                                        vOfOrderedCommands.push_back(new Expression(temp));
					if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                                vOfOrderedCommands.pop_back();
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                        }
                                        else {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                        }

                                }
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new OR());

                        }
                        else if(temp.find(";") < temp.find("||") && temp.find(";") < temp.find("&&")) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new Semicolon());
				temp = temp.substr(temp.find(";") + 1, temp.size() -1 - temp.find(";") );
                                //vOfOrderedCommands.push_back(new Expression(temp));
                                if(temp.size() != 0) {
				        if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                                vOfOrderedCommands.pop_back();
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                        }
                                        else {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                        }

                                }
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new Semicolon());

                        }

		}
		else if(i + 1 < vExpression->size()){//not last expression so there could be something after this expression and before the next one
			//cout << "ASDASDASD" << endl;
			temp = s.substr(vExpression->at(i).second + 1, vExpression->at(i+1).first - vExpression->at(i).second - 1);
			if(temp.find("&&") == string::npos && temp.find("||") == string::npos && temp.find(";") == string::npos) {
				vOfOrderedCommands.push_back(new Expression(temp));
				//vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new None());
				if((vOfOrderedCommands.at(v.size()-1)->v).size() == 0) {//no Connector so there is no connector before it
                                	vOfOrderedCommands.pop_back();
                        	}//need to check if its AND or OR or semicolon
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                        	}
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                        	}
                        	else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                        	}
                        	else {
                                	vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                        	}

			}
			else if(temp.find("&&") < temp.find("||") && temp.find("&&") < temp.find(";")) {
				vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new AND());
				temp = temp.substr(temp.find("&&") + 2, temp.size() -1 - temp.find("&&") - 1);
				//vOfOrderedCommands.push_back(new Expression(temp));
				if(temp.size() > 0) {
					//cout << temp << "OMG" << endl;
                                        vOfOrderedCommands.push_back(new Expression(temp));
					int k = vOfOrderedCommands.size()-1;
                                        if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                                vOfOrderedCommands.pop_back();
                                        }
                                        /*else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                        }
                                        else {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                        }*/
					//int k = vOfOrderedCommands.size()-1; 
					else {
						string tempS;
						while((vOfOrderedCommands.at(k)->v).size()  > 0) {
							//cout << (vOfOrderedCommands.at(k)->v).size()  << endl;
							tempS = (vOfOrderedCommands.at(k)->v).at(0)->getCommand();
							for(unsigned p = 0; p < ((vOfOrderedCommands.at(k)->v).at(0)->parameters).size(); ++p) {
								//if(((vOfOrderedCommands.at(k)->v).at(0)->parameters).size() > 0) {
								tempS = tempS + ' ';
								tempS = tempS + ((vOfOrderedCommands.at(k)->v).at(0)->parameters).at(p);
								//} 
							}
							//vOfOrderedCommands.push_back(new Expression((vOfOrderedCommands.at(k)->v).at(0)->getCommand()));
							vOfOrderedCommands.push_back(new Expression(tempS));
							if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isAND()) {
								 vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
							}
							else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isOR()) {
								vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());	
							}
							else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isNone()) {
								vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
							}
							else {
								vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());	
							}
							(vOfOrderedCommands.at(k)->v).erase((vOfOrderedCommands.at(k)->v).begin());
							//vOfOrdered
							//make new expressions starting from the first and get their connectors and assign the connectors to the expression
						}
						vOfOrderedCommands.erase(vOfOrderedCommands.begin() + k);
					}
                                }
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new AND());

			}
			else if(temp.find("||") < temp.find("&&") && temp.find("||") < temp.find(";")) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new OR());
				temp = temp.substr(temp.find("||") + 2, temp.size() -1 - temp.find("||") - 1);
                                //cout << temp.size() << "xD" << endl;
                                //cout << "made it" << endl;
				if(temp.size() > 0) {
					vOfOrderedCommands.push_back(new Expression(temp));
					int k = vOfOrderedCommands.size()-1;
                                        if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                                vOfOrderedCommands.pop_back();
                                        }
                                        /*else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                        }
                                        else {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                        }*/
					else {
					string tempS;
                                                while((vOfOrderedCommands.at(k)->v).size()  > 0) {
                                                        tempS = (vOfOrderedCommands.at(k)->v).at(0)->getCommand();
                                                        for(unsigned i = 0; i < ((vOfOrderedCommands.at(k)->v).at(0)->parameters).size(); ++i) {
                                                                tempS = tempS + ' ';
                                                                tempS = tempS + ((vOfOrderedCommands.at(k)->v).at(0)->parameters).at(i);
                                                        }
                                                        vOfOrderedCommands.push_back(new Expression(tempS));
                                                        if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isAND()) {
                                                                 vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                                        }
                                                        else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isOR()) {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                                        }
                                                        else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isNone()) {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                                        }
                                                        else {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                                        }
                                                        (vOfOrderedCommands.at(k)->v).erase((vOfOrderedCommands.at(k)->v).begin());
						
                                                }
						vOfOrderedCommands.erase(vOfOrderedCommands.begin() + k);
					}
				}
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new OR());

                        }
			else if(temp.find(";") < temp.find("||") && temp.find(";") < temp.find("&&")) {
                                vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new Semicolon());
				temp = temp.substr(temp.find(";") + 1, temp.size() -1 - temp.find(";"));
                                //vOfOrderedCommands.push_back(new Expression(temp));
                                if(temp.size() != 0) {
                                        vOfOrderedCommands.push_back(new Expression(temp));
					int k = vOfOrderedCommands.size()-1;
                                        if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size()  == 0) {
                                                vOfOrderedCommands.pop_back();
                                        }
                                        /*else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isAND()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isOR()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                        }
                                        else if((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).at((vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->v).size() - 1)->getConnector()->isNone()) {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                        }
                                        else {
                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                        }*/
					else {
					string tempS;
                                                while((vOfOrderedCommands.at(k)->v).size() > 0) {
                                                        tempS = (vOfOrderedCommands.at(k)->v).at(0)->getCommand();
                                                        for(unsigned i = 0; i < ((vOfOrderedCommands.at(k)->v).at(0)->parameters).size(); ++i) {
                                                                tempS = tempS + ' ';
                                                                tempS = tempS + ((vOfOrderedCommands.at(k)->v).at(0)->parameters).at(i);
                                                        }
                                                        vOfOrderedCommands.push_back(new Expression(tempS));
                                                        if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isAND()) {
                                                                 vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new AND());
                                                        }
                                                        else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isOR()) {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new OR());
                                                        }
                                                        else if((vOfOrderedCommands.at(k)->v).at(0)->getConnector()->isNone()) {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new None());
                                                        }
                                                        else {
                                                                vOfOrderedCommands.at(vOfOrderedCommands.size() -1)->setConnector(new Semicolon());
                                                        }
                                                        (vOfOrderedCommands.at(k)->v).erase((vOfOrderedCommands.at(k)->v).begin());
                                                }
						vOfOrderedCommands.erase(vOfOrderedCommands.begin() + k);
					}
                                }
                                //vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->setConnector(new Semicolon());

                        }


			//vOfOrderedCommands.push_back(new Expression(s.substr(vExpression->at(i).second + 1, vExpression->at(i+1).first - 1)));
		}
			
	}
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
	if(vOfOrderedCommands.size() == 0) {
		int i = 0;
		while(i < static_cast<int>(v.size())) {
			int x = i;
			i += v.at(i)->getConnector()->runCommand(v.at(i));
			if(!v.at(x)->getConnector()->isOR()) {
				if(v.at(i-1)->getConnector()->isAND() && !v.at(x)->getConnector()->success) {
					int j = i;
					while(j< v.size() && v.at(j)->getConnector()->isAND() || j<v.size() && v.at(j)->getConnector()->isNone() && v.at(j-1)->getConnector()->isAND()) {
						++j;
						if(j < v.size() && !v.at(j)->getConnector()->isNone()) {
							++i;
						}
						else {
							++i;
						}
					}
					if(i < v.size() && v.at(i-1)->getConnector()->isNone() && i < v.size() && v.at(i-1)->getConnector()->isAND()) {
						--i;
					}
					++i;
				}
			}
			else if(i < v.size() && v.at(i)->getConnector()->isOR() && (v.at(x)->getConnector()->success) && v.at(i)->getConnector()->isOR() && !v.at(i)->getConnector()->isAND() || i <v.size() && v.at(x)->getConnector()->isOR() && v.at(i)->getConnector()->isNone() && !v.at(i-1)->getConnector()->isAND() && i-1 != x) {

				int j = i;
				while(j < v.size() && v.at(j)->getConnector()->isOR()) {
					v.at(j)->getConnector()->success = true;
					++j;
					++i;
				}	
				if(i < v.size() && v.at(i)->getConnector()->isNone() && (v.at(i-1)->getConnector()->isAND() || i < v.size() && v.at(i-1)->getConnector()->isOR())) {
					++i;
				}
			}
			/*if( i == v.size() - 1 && v.at(i)->getConnector()->success) {
				this->getConnector()->success = true;
			}*/
		}
	}
	else {//FIXME: Maybe check that each expression does not have None Connector?
		for(unsigned i = 0; i <vOfOrderedCommands.size(); ++i) {
			//cout << vOfOrderedCommands.at(i)->getCommand().size() << endl;
			if(i == 0) {//first command
				vOfOrderedCommands.at(i)->runExpression();
				if((vOfOrderedCommands.at(0)->vOfOrderedCommands).size() > 0 && (vOfOrderedCommands.at(0)->vOfOrderedCommands).at((vOfOrderedCommands.at(0)->vOfOrderedCommands).size() - 1)->getConnector()->success || (vOfOrderedCommands.at(i)->v).size() > 0 && (vOfOrderedCommands.at(i)->v).at((vOfOrderedCommands.at(i)->v).size() -1)->getConnector()->success ) {
                                        //vOfOrderedCommands.at(0)->getConnector()->success = true;
					this->getConnector()->success = true;
					//cout << "XDDDDDD" << endl << endl;
                                }
				/*if(vOfOrderedCommands.at(i)->vOfOrderedCommands.size() >0) {
					vOfOrderedCommands.at(i)->getConnector()->success = vOfOrderedCommands.at(i)->vOfOrderedCommands.at((vOfOrderedCommands.at(i)->vOfOrderedCommands).size() -1 )->getConnector()->success;
				}*/
			

			}
			//else if(vOfOrderedCommands.at(i)->getConnector() == 0) {
				//vOfOrderedCommands.erase(vOfOrderedCommands.begin() + i);
				//--i;
				
			//}
			else { //need to check expression before hand and its connector
				if(vOfOrderedCommands.at(i - 1)->getConnector() != 0 && vOfOrderedCommands.at(i - 1)->getConnector()->isAND()){//if AND expression beforehand
					//cout << "hellpp" << endl;
					if((vOfOrderedCommands.at(i-1)->v).size() > 0 && (vOfOrderedCommands.at(i-1)->v).at((vOfOrderedCommands.at(i-1)->v).size() -1)->getConnector()->success || vOfOrderedCommands.at(i-1)->getConnector()->success) {
						vOfOrderedCommands.at(i)->runExpression();	
						//cout << "FOUND AND" << endl;
						if(vOfOrderedCommands.at(i)->vOfOrderedCommands.size() > 0 && vOfOrderedCommands.at(i)->vOfOrderedCommands.at(vOfOrderedCommands.at(i)->vOfOrderedCommands.size() - 1)->getConnector()->success) {
                                                        vOfOrderedCommands.at(i)->getConnector()->success = true;
                                                }

					}
					else {
						//++i;
						//vOfOrderedCommands.at(i)->runExpression();

						//vOfOrderedCommands.at(i)->getConnector()->success = true;
						//cout << "entered AND branch" << i <<  endl;
					}
				}
				else if(vOfOrderedCommands.at(i - 1)->getConnector() != 0 && vOfOrderedCommands.at(i -1)->getConnector()->isOR()) {
					//cout << "entered branch" << endl;
					if((vOfOrderedCommands.at(i-1)->v).size() > 0 && !((vOfOrderedCommands.at(i-1)->v).at((vOfOrderedCommands.at(i-1)->v).size() -1)->getConnector()->success)) {
                                                vOfOrderedCommands.at(i)->runExpression();
						if(vOfOrderedCommands.at(i)->vOfOrderedCommands.size() > 0 && vOfOrderedCommands.at(i)->vOfOrderedCommands.at(vOfOrderedCommands.at(i)->vOfOrderedCommands.size() - 1)->getConnector()->success) {
							vOfOrderedCommands.at(i)->getConnector()->success = true;
						}	
                                        }
                                        else {
						(vOfOrderedCommands.at(i)->v).at((vOfOrderedCommands.at(i)->v).size() - 1)->getConnector()->success = true;
						vOfOrderedCommands.at(i)->getConnector()->success =true;
                                                //++i;
                                                //vOfOrderedCommands.at(i)->runExpression();
						//cout << i << "ASDASD" << endl;
                                        }
	
				}
				else if(vOfOrderedCommands.at(i - 1)->getConnector() != 0 && vOfOrderedCommands.at(i - 1)->getConnector()->isNone()) {
					vOfOrderedCommands.at(i)->runExpression();
					//vOfOrderedCommands.at(i)->getConnector()->success =false;
					/*if((vOfOrderedCommands.at(i)->v).size() > 0) {
						vOfOrderedCommands.at(i)->getConnector()->success = (vOfOrderedCommands.at(i)->v).at((vOfOrderedCommands.at(i)->v).size() -1)->getConnector()->success; 
					}*/
					//cout << "none" << i << endl;	
					//FIXME: need to do soemthing if they dont have a connector in between expressions.
				}
				else {//isSemicolon
					vOfOrderedCommands.at(i)->runExpression();	
				}
			}
			/*if(vOfOrderedCommands.size() > 0) {
				this->getConnector()->success = vOfOrderedCommands.at(vOfOrderedCommands.size()-1)->getConnector()->success;
			}*/
		}
		/*if(vOfOrderedCommands.size() > 0 && vOfOrderedCommands.at(vOfOrderedCommands.size() - 1)->getConnector()->success) {
			this->getConnector()->success = true;
		}*/
	}
		//if(i == 0) {
		//	i += v.at(i)->getConnector()->runCommand(v.at(i));
		//}
		//else {
			/*if(v.at(i-1)->getConnector()->isAND() && !(v.at(i-1)->getConnector()->success)) {
				++i;
			}
			else if(v.at(i-1)->getConnector()->isOR() && v.at(i-1)->getConnector()->success) {
				++i;
			}
			else {
				i+= v.at(i)->getConnector()->runCommand(v.at(i));
			}*/
			
		//}
		//int x = i;
		//i += v.at(i)->getConnector()->runCommand(v.at(i));
		/*if(i - 1 < v.size()) {
			if(!(v.at(i-1)->getConnector()->success)) {
				if(v.at(i-1)->getConnector()->isOR()) {
					int j = i;
					bool s = true;
					bool x;
					while(s) {
						if(j == 0) {
							s = false;
							i+= v.at(i)->getConnector()->runCommand(v.at(i));
						}
						else if(!(v.at(j-1)->getConnector()->isOR())) {
							if(v.at(j-1)->getConnector()->success) {
								++i;//i += v.at(i)->getConnector()->runCommand(v.at(i));
								s = false;
								;;x = true;
							}
							else {
								i+= v.at(i)
								s = false;
							}		
						}
						else {
							--j;
						}	
					}
				}
				else {
					i+=v.at(i)->getConnector()->runCommand(v.at(i));
				}
			}
			else {
				i+=v.at(i)->getConnector()->runCommand(v.at(i));
			}
		}
		else {
			i+=v.at(i)->getConnector()->runCommand(v.at(i));
		}*/
	//while(v.size() > 0) {
	//	v.pop_back();
	//}
}




bool Expression::balancedParenthesis(const string  &e) {
	stack<int> pStack;
	string copy = e;
	for(unsigned i = 0; i < copy.size(); ++i) {
		if(copy.at(i) == '(') {
                        pStack.push(i);
                }
                else if(copy.at(i) == ')') {
                        if(pStack.empty()) {
                                return false;
                        }
			unsigned j = 0;
			while(  j < vExpression->size()) {
				if(vExpression->at(j).first > pStack.top() && vExpression->at(j).second < i) {
					vExpression->erase(vExpression->begin() +j);
					j = 0;
				}
				else {
					++j;
				}
			}
			vExpression->push_back(make_pair(pStack.top(),i));
                        pStack.pop();
                }
	}
	if(pStack.size() == 0) {
		return true;
	}
	return false;
}




















