#ifndef SEMICOLON_H
#define SEMICOLON_H
#include <string>
#include "Connector.h"

using namespace std;

class Semicolon : public Connector {
  public:
  int runCommand(CommandComponent * cmd);
  bool isNone();
  bool isOR();
  bool isAND();
};

#endif
