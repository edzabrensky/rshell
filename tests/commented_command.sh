#!/bin/sh
#tests commands with comments
#
#exit
#echo hello world; ls -a && cd || 123 && exit
./bin/rshell < "tests/commented_command.txt"
