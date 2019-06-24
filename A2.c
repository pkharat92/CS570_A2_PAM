#include "a2.h"

int main(int argc, char* argv[]) {
	char inputStr[MAX_SIZE], *parsedArgs[MAX_LIST];
	char* parsedArgsPiped[MAX_LIST];
	int execFlag = 0;
	
	while(1) {
		printf("cssc0844%% ");
		if(getInput(inputStr)) continue;
		
		// Exec flag returns 1 if normal command,
		// returns 2 if piped command
		execFlag = processStr(inputStr, parsedArgs, 
			parsedArgsPiped);
			
		// Execute normal command
		if(execFlag == 1)
			execArgs(parsedArgs);
		
		// Execute piped command
		if(execFlag == 2)
			execArgsPiped(parsedArgsPiped);
	} // End while
	return 0;
} // End main

/**
  * Prompts for and gets user input
  */
int getInput(char* str) {
	char* buf;
	
	buf = readline(NULL);
	if(strlen(buf) != 0) {
		add_history(buf);
		strcpy(str, buf);
		return 0;
	}
	else return 1;
} // End getInput()

/**
  * Processes user input
  */
int processStr(char* str, char** parsed, char** parsedPiped) {
	char* str_piped[MAX_LIST];
	int piped = 0;
	
	piped = parsePipe(str, str_piped);
	 
	if(piped) parseSpaceArry(str_piped, parsedPiped);
	else parseSpace(str, parsed);

	// Checks if user invoked "exit" command
	char* strLow = strlwr(parsed[0]);
	if(strcmp(strLow, exitCmd) == 0) {
		printf("\nGoodbye\n"); 
		exit(0);
	}
	else return 1 + piped;
} // End processStr()

/**
  * Parses piped command
  */
int parsePipe(char* str, char** str_piped) {
	int i;
	for(i = 0; i < MAX_LIST; i++) {
		str_piped[i] = strsep(&str, "|");
		if(str_piped[i] == NULL) break;
	} // End for
	
	if(str_piped[1] == NULL) return 0;
	else return 1;
} // End parsePipe()
 
/**
  * Parses normal command;
  * takes single string as input
  */	
void parseSpace(char* str, char** parsed) {
	int i;
	for(i = 0; i < MAX_LIST; i++) {
		parsed[i] = strsep(&str, " ");
		
		if(parsed[i] == NULL) break;
		if(strlen(parsed[i]) == 0) i--;
	} // End for
} // End parseSpace()

/**
  * Parses normal command;
  * takes string array as input
  */	
void parseSpaceArry(char** str_piped, char** parsed) {
	int i;
	for(i = 0; i < MAX_LIST; i++) {
		parsed[i] = strsep(&str_piped[i], " ");
		
		if(parsed[i] == NULL) break;
		if(strlen(parsed[i]) == 0) i--;
	} // End for
} // End parseSpace()
/**
  * Executes normal system commands
  */
void execArgs(char** parsed) {
	// Create child process
	pid_t pid = fork();
	
	if(pid == -1) {
		printf("\nUnable to fork\n");
		return;
	} 
	else if (pid == 0) {
		if(execvp(parsed[0], parsed) < 0) 
			printf("\nUnable to execute command\n");
		exit(0);
	}
	else {
		// Wait for child process to end
		wait(NULL);
		return;
	}
} // End execArgs()

/**
  * Executes piped system commands
  */
void execArgsPiped(char** parsedPiped) {
	int i;
	pid_t pid;
	int in, fd[2];
	
	// First process gets input from original fd
	in = 0;
	
	// We loop through all but the last process
	for(i = 0; i < n - 1; i++) {
		pipe(fd);
		
		// fd[1] is write end of pipe, 
		// carry "in" from previous iteration
		spawn_proc(in, fd[1], i, parsedPiped);
		
		// Close write end of pipe, child will
		// write to next pipe
		close(fd[1]);
		
		// Keep read end of pipe, child will 
		// read from here
		in = fd[0];
	} // End for
	
	// Last process, set stdin to read end of
	// previous pipe and output to original fd
	if(in != 0) dup2(in, 0);
	
	if(pid == -1) {
		printf("\nUnable to fork\n");
		return;
	}
	else if(pid == 0) {	
		// Run the last process
		if(execvp(parsedPiped[i], parsedPiped) < 0) {
			printf("\nUnable to execute command\n");
			exit(0);
		}
	}
	else {
		wait(NULL);	
		return;
	}
} // End void execArgsPiped()

/**
  * Helper function for execArgsPiped()
  */
void spawn_proc(int in, int out, int i, char** parsedPiped) {
	pid_t pid; 
	
	pid = fork();
	
	if(pid == -1) {
		printf("\nUnable to create pipe\n");
		return;
	}
	
	if(pid == 0) {
		if(in != 0) {
			dup2(in, 0);
			close(in);
		}
		
		if(out != 1) {
			dup2(out, 1);
			close(out);
		}
		
		if(execvp(parsedPiped[i], parsedPiped) < 0) {
				printf("\nUnable to execute piped command\n");
				exit(0);
		}
	}
	else {
		wait(NULL);
		return;
	}
} // End spawn_proc()

/**
  * Converts string to lowercase
  */
char *strlwr(char *str) {
	unsigned char *p = (unsigned char *)str;
	
	while(*p) {
		*p = tolower((unsigned char) *p);
		 p++;
	} // End while
	
	return str;
} // End char *strlwr()
