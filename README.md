# rshell

------------------
<h1>About this project
------------------
This is a command shell written in c++. It can execute commands located in /bin/. The user must have /bin/ in their directory to properly execute commands. The exit function for this is "exit".

-----------------
<h2> Installation
-----------------
1. Clone the repo
2. Compile with <code>make</code> inside the <code>src</code> directory
3. Use as a command shell, examples given in the section below

--------------
<h2>Uses of rshell
--------------
Rshell behaves exactly like a command shell. 

Example:
ls | echo | mkdir | touch | exit

<p><code>ls</code> - list contents of directory
<p><code>echo</code> - display a line of text
<p><code>mkdir</code> - create an empty folder in the current directory
<p><code>touch</code> - create a file in the current directory
<p><code>exit</code> - exit the command shell

<p>Some uses: </p>
    ls
    echo hello
    touch newfile
    exit

----
<h2>Bugs
----

