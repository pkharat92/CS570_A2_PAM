#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_SIZE 1000 // max number of letters supported
#define MAX_LIST 100 // max number of commands supported
#define MAX_PIPE 99 // max number of pipes

char exitCmd[] = "exit";
int n; // actual numnber of piped commands

//Function prototypes
int getInput(char* str);
int processStr(char* str, char** parsed, char** parsedPiped);
int parsePipe(char* str, char** str_piped);
void parseSpace(char* str, char** parsed);
void parseSpaceArry(char** str_parsed, char** parsed);
void execArgs(char** parsed);
void execArgsPiped(char** parsedPiped);
void spawn_proc(int in, int out, int i, char** parsedPiped);
char *strlwr(char *str);
