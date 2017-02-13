#ifndef NONE_H
#define NONE_H
#include <string>

using namespace std;

class None : public Connector{
 public:
  int runCommand(string cmd);
}

#endif
