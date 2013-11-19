MyShell
=======

Project 1 Group Members:
------------------------
* Roger Harris - rwh0003
* Allison Holt - amh0029
* Carlos Lemus - cal0018
    
Lab Machine(s) used:
--------------------
tux194 in Davis Hall Linux Lab, Auburn University
    
How to Compile
--------------
Type in the command "make" to compile the shell.  To execute the program type "./myshell".  Note, the quotation marks are not put into the command prompt.

Description / Explanation of Project Source Code
------------------------------------------------
Our assignment was to make a robust shell.  The user executes our shell to make system commands.  We use the execvp to implement the commands the user specifies.  We allow a maximum of ten commands to be entered into the shell and executed.  If the user enters more than 10 commands, the system will display an error and has the user enter another command.  To exit the shell, type "exit" into the shell.
