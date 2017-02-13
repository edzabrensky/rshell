#include "AND.h"

int AND::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  if (Connector::success)
  {
    return 1;
  }
  if (!Connector::success)
  {
    return 2;
  }
  return 2;
}
