#include "None.h"

bool None::isNone()
{
 return true;
}

int None::runCommand(string cmd)
{
 Connector::runCommand(cmd);
  return 1;
}
