# CS570_A2_PAM
In this program, we are implementing a program actuator and microshell.

Author: Alex Gonzalez, Pierrer Kahart
User: cssc0816
Class: CS 570, Summer 2019
Assignment 2, PAM
Filename: README.txt

*********************************************************************************************

File manifest:

A2.c >>> Source code for main
A2.h >>> Header file
Makefile >>> Tool for compiling program

After compiling using Makefile:
pam >>> Executable file

*********************************************************************************************

Compile instructions:
Inside ~/a2 folder, type 'make' command and Makefile will compile the code automatically.

*********************************************************************************************

Operating instructions:
This programs simulates a microshell to run executable files.

After compiling code with 'make' command an executable file named "pam" will be created.

Type 'pam' and the program will run printing out "cssc0844% ".

Here the user can enter a filename of an executbale file to run. If this filename is not a
fully qualified path name the program will search for it. 

If the entered file is not executable the program will print out "Unable to execute command"
and rerturn to first state to wait for new user input.

If the file entered is an executable file a new process will be created to run the file.

Files can be run with up to one argument by entering it after the filename.

More than one executable file can be run with different processes by building pipes between
them with the character "|" as delimeter for different filenames.

In order to exit the program the user may enter "exit" and it will exit gracefully.

*********************************************************************************************


