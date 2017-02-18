#ifndef NONE_H
#define NONE_H
#include <string>
#include "Connector.h"

using namespace std;

class None : public Connector{
 public:
  int runCommand(CommandComponent * cmd);
  bool isNone();
  bool isAND();
  bool isOR();
};

#endif
