#include "Semicolon.h"

bool isNone()
{
 return false; 
}

int Semicolon::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  return 1;
}
