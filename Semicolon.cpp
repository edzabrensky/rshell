#include "Semicolon.h"

int Semicolon::runCommand(string cmd)
{
  Connector::runCommand(cmd);
  return 1;
}
