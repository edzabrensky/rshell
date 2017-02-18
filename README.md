# rShell

------------------
<h1>About this project
------------------
This is a command shell written in c++. It can execute commands located in /bin/. The user must have /bin/ in their directory to properly execute commands. The exit function for this is "exit". By using rShell, you can have access to Unix commands in a C++ environment.

-----------------
<h2> Installation
-----------------
1. Clone the repo
2. Compile with <code>make</code> inside the <code>src</code> directory
3. Use as a command shell, examples given in the section below

--------------
<h2>Uses of rShell
--------------
Rshell behaves exactly like a command shell. 

Example:
ls | echo | mkdir | touch | exit

<p><code>ls</code> - list contents of directory
<p><code>echo</code> - display a line of text
<p><code>mkdir</code> - create an empty folder in the current directory
<p><code>touch</code> - create a file in the current directory
<p><code>exit</code> - exit the command shell

<p>**General single command uses**</p>
    ls #list contents of current directory
    echo hello #display "hello" to the console
    touch newfile #create a new file named "newfile" in the directory
    exit #exit the command shell; this can be used anytime

<p>**Use of connectors for multi-commands**</p>
rShell allows the use of connectors, namely: <code>&&, ||, ;</code>
<p>where:
<p>a command followed by <code>&&</code> only executes if the first command succeeds
<p>a command followed by <code>||</code> only executes if the first command fails
<p>a command followed by <code>;</code> always executes
    ls -a; echo hello; mkdir test || echo world; ls && touch newfile || exit
    
----
<h2>Bugs
----

