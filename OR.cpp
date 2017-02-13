#include "OR.h"

int OR::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  if (Connector::success)
  {
    return 2;
  }
  if (!Connector::success)
  {
    return 1;
  }
  return 1;
}
