#ifndef AND_H
#define AND_H
#include <string>

using namespace std;

class AND : public Connector {
  public:
  int runCommand(string cmd);
};

#endif
