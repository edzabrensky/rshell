#!/bin/sh
#tests commands with ;, &&, or
ls; mkdir emptydir || echo world
ls; rm -r emptydir && ls
echo world || emptydir && git status
echo 1; echo 2; echo 3; echo 4; echo 5 && echo 6 || echo 7 || echo 8; echo 9 && echo 10 && echo 11
ls -a; echo hello && mkdir test || echo world; git status && echo hello || echo world || ls -l || touch multicommandtest && ls; echo a ||echo b||echo c|| echo hello&&ls -l;
ls; rm -r test && rm multicommandtest
echo test || echo world
echo world || echo test
echo test && echo world
echo world && echo test
