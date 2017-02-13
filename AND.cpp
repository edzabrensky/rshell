#include "AND.h"

int AND::runCommand(string cmd)
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
