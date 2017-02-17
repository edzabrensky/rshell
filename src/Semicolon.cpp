#include "Semicolon.h"

bool Semicolon::isNone()
{
 return false; 
}

int Semicolon::runCommand(CommandComponent * cmd)
{
  Connector::runCommand(cmd);
  return 1;
}
