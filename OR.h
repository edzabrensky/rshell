#ifndef OR_H
#define OR_H
#include <string>
#include "Connector.h"

using namespace std;

class OR : public Connector {
  public:
  int runCommand(string cmd);
};

#endif
