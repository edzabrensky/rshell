#!/bin/sh
#tests commands with ;, &&, or
ls -a; echo hello && mkdir test || echo world; git status && echo hello || echo world || ls -l || touch multicommandtest && ls; echo a ||echo b||echo c|| echo hello&&ls -l;
