#tests exit and commands with exit
ls -a; echo hello
echo world; invalidbashcommand && exit
echo 123 #exit
touch testfile; stillshouldntexit && exit
ls -l; echo should exit || exit
