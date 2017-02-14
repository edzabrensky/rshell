#include "AND.h"

bool AND::isNone()
{
 return false; 
}

int AND::runCommand(CommandComponent * cmd)
{
  Connector::runCommand(cmd);
  if (success)
  {
    return 1;
  }
  if (!success)
  {
    return 2;
  }
  return 2;
}
