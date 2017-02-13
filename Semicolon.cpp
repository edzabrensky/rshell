#include "Semicolon.h"

bool Semicolon::isNone()
{
 return false; 
}

int Semicolon::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  return 1;
}
