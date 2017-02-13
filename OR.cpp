#include "OR.h"

bool isNone()
{
 return false; 
}

int OR::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  if (success)
  {
    return 2;
  }
  if (!success)
  {
    return 1;
  }
  return 1;
}
