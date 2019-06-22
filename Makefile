###########################################################
#
# Name: Alex Gonzalez, Pierre Kahart
# User: cssc0816
# Class: CS 570, Summer 2019
# Assignment 2, PAM
# Filename: Makefile
#
###########################################################
EXEC = pam
FILES = A2.c
CC = gcc
LFLAGS = -g -lreadline
CFLAGS = -g -c -lreadline -I.
OBJECTS = $(FILES:.c=.o)
$(EXEC):$(OBJECTS)
        $(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
        rm -f *.o
.c.o:
        $(CC) $(CFLAGS) $<
clean:
        rm -f *.o $(EXEC)
#######################[ EOF: Makefile ]###################
