#include "Semicolon.h"

bool Semicolon::isNone()
{
 return false; 
}
bool Semicolon::isOR() {
 return false;
}
bool Semicolon::isAND() {
 return false;
}
int Semicolon::runCommand(CommandComponent * cmd)
{
  Connector::runCommand(cmd);
  return 1;
}
