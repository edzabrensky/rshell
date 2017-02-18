#!/bin/sh
./bin/rshell <<'EOF'
echo hello
mkdir test1
ls -a
rm -r test1
ls -a
echo this
mkdir test2 test3
ls
rm -r test2
rm -r test3
ls
touch singlecommandfile.cpp
ls
rm singlecommandfile.cpp
ls
ls -a -l
commandThatShouldntWork
echo hello xD 123
;
&&
||
exit
EOF
