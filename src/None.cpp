#include "None.h"

bool None::isNone()
{
 return true;
}
bool None::isOR() {
 return false;
}
bool None::isAND() {
 return false;
}
int None::runCommand(CommandComponent * cmd)
{
 Connector::runCommand(cmd);
  return 1;
}
