#ifndef OR_H
#define OR_H
#include <string>
#include "Connector.h"

using namespace std;

class OR : public Connector {
  public:
  int runCommand(CommandComponent * cmd);
  bool isNone();
  bool isOR();
  bool isAND();
};

#endif
