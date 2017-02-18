#ifndef AND_H
#define AND_H
#include <string>
#include "Connector.h"

using namespace std;

class AND : public Connector {
  public:
  int runCommand(CommandComponent * cmd);
  bool isNone();
  bool isAND();
  bool isOR();
};

#endif
