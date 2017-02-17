#include "None.h"

bool None::isNone()
{
 return true;
}

int None::runCommand(CommandComponent * cmd)
{
 Connector::runCommand(cmd);
  return 1;
}
