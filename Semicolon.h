#ifndef SEMICOLON_H
#define SEMICOLON_H
#include <string>
#include "Connector.h"

using namespace std;

class Semicolon : public Connector {
  public:
  int runCommand(string cmd);
  bool isNone();
};

#endif
