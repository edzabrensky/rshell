#!/bin/sh
#tests exit and commands with exit
ls -a; echo hello
echo world; invalidbashcommand && exit #shouldn't exit since invalidbashcommand isn't a valid command
echo 123 #exit
touch testfile; stillshouldntexit && exit #shouldn't exit since stillshouldntexit isn't a valid command
ls;
rm testfile;
ls;
echo 456; echo dontexit || exit #shouldn't exit as echo dontexit should work
ls -l; echo should exit && exit #should exit here as echo is a valid command
echo hello #this part should not output
echo 1 #none of these
echo 2 #should print
echo 3 #to console
