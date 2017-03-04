#tests for the test command

#tests on something that already exists, should return True, True, False for both cases
test -e src/AND.cpp && echo "path exists" 
test -f src/AND.cpp && echo "it exists and it's a regular file"
test -d src/AND.cpp && echo "it exists and it's a directory"

[ -e src/AND.cpp ] && echo "path exists"
[ -f src/AND.cpp ] && echo "it exists and it's a regular file"
[ -d src/AND.cpp ] && echo "it exists and it's a directory"

#tests on something that is created in current directory, should return True, False, True for both cases
mkdir emptydir
test -e emptydir && echo "path exists"
test -f emptydir && echo "it exists and it's a regular file"
test -d emptydir && echo "it exists and it's a directory"

[ -e emptydir ] && echo "path exists"
[ -f emptydir ] && echo "it exists and it's a regular file"
[ -d emptydir ] && echo "it exists and it's a directory"

#tests on something that does not exist, should all return False
rm -r emptydir
test -e emptydir && echo "path exists"
test -f emptydir && echo "it exists and it's a regular file"
test -d emptydir && echo "it exists and it's a directory"

[ -e emptydir ] && echo "path exists"
[ -f emptydir ] && echo "it exists and it's a regular file"
[ -d emptydir ] && echo "it exists and it's a directory"

#tests on invalid files / nonexistent files in other directories, should all return False
test -e src/ASDzxcvvq.cpp && echo "path exists"
test -f src/ASDzxcvvq.cpp && echo "it exists and it's a regular file"
test -d src/ASDzxcvvq.cpp && echo "it exists and it's a directory"
