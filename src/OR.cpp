#include "OR.h"

bool OR::isNone()
{
 return false; 
}

int OR::runCommand(CommandComponent * cmd)
{
  Connector::runCommand(cmd);
  if (success)
  {
    return 2;
  }
  return 1;
}
