#!/bin/sh
#tests commands with comments
#
#exit
#echo hello world; ls -a && cd || 123 && exit
./bin/rshell << 'EOF'
ls -a #echo comment###ls -l
echo hello #ls -l #ls -a #ls #ls######echo world
echo world #mkdir test #exit
ls -l #echo test #mkdir folder
mkdir testdir #exit #echo 123
ls #exit #echo exit #123123
rm -r testdir #echo removed test directory
ls #-l
ls -a && lol; echo xD #&& hello
echo this is a series of words that print that should cut off here #and not continue to print to the console #ls #exit
#echo this should not print
#echo this should also not print
echo creating an empty text file named emptytext #touch emptytextShouldNotBeMade
touch emptytext #echo world && echo hello || mkdir empty || ls -l && echo done || exit;
ls #-a
rm emptytext #rm emptytext1
exit
EOF
