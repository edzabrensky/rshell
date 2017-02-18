# rShell

------------------
<h1>About this project
------------------
This is a command shell written in c++. It can execute commands located in /bin/. The user must have /bin/ in their directory to properly execute commands. The exit function for this is "exit". By using rShell, you can have access to Unix commands in a C++ environment.

-----------------
<h2> Installation
-----------------
1. <code>git clone https://github.com/<b>yourusername</b>/rshell.git</code>
2. <code>cd rshell</code>
3. <code>git checkout hw2</code>
4. <code>make</code>
5. <code>bin/rshell</code>

--------------
<h2>Uses of rShell
--------------
rShell behaves exactly like a [command shell](http://pubs.opengroup.org/onlinepubs/007904875/utilities/xcu_chap02.html). 

Example:
[ls](https://en.wikipedia.org/wiki/Ls) | [echo](https://en.wikipedia.org/wiki/Echo_(command)) | [mkdir](https://en.wikipedia.org/wiki/Mkdir) | [touch](https://en.wikipedia.org/wiki/Touch_(Unix)) | [exit](http://tldp.org/LDP/abs/html/exit-status.html)

<p><code>ls</code> - list contents of directory
<p><code>echo</code> - display a line of text
<p><code>mkdir</code> - create an empty folder in the current directory
<p><code>touch</code> - create a file in the current directory
<p><code>exit</code> - exit the command shell

<p><b>General single command uses</b></p>
    ls #list contents of current directory
    echo hello #display "hello" to the console
    touch newfile #create a new file named "newfile" in the directory
    exit #exit the command shell; this can be used anytime

<p><b>Use of connectors for multi-commands</b></p>
rShell allows the use of connectors, namely: <code>&&, ||, ;</code>
<p>where:
<p>a command followed by <code>&&</code> only executes if the first command succeeds
<p>a command followed by <code>||</code> only executes if the first command fails
<p>a command followed by <code>;</code> always executes </p>
<code>ls -a; echo hello; mkdir test || echo world; ls && touch newfile || exit</code>
    
----
<h2>Bugs
----
* After running tests, there are occasions where <code>exit</code> has to be typed twice to successfully end the program
