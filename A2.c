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
			execArgsPiped(parsedArgs, parsedArgsPiped);
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
	char* str_piped[2];
	int piped = 0;
	
	piped = parsePipe(str, str_piped);
	
	// Piped command is parsed
	if(piped) {
		parseSpace(str_piped[0], parsed);
		parseSpace(str_piped[1], parsedPiped);
	}
	// Normal command is parsed
	else parseSpace(str, parsed);
	
	// Checks if user invoked "exit" command
	char* strLow = strlwr(parsed[0]);
	if(strcmp(strLow, exitCmd) == 0) {
		printf("\nGoodbye\n"); 
		kill(0, SIGTERM);
		exit(0);
	}
	else return 1 + piped;
} // End processStr()

/**
  * Parses piped command
  */
int parsePipe(char* str, char** str_piped) {
	// Tokenizes piped command, 
	// using "|" as delimiter
	int i;
	for(i = 0; i < MAX_PIPE; i++) {
		str_piped[i] = strsep(&str, "|");
		if(str_piped[i] == NULL) break;
	} // End for
	
	if(str_piped[1] == NULL) return 0;
	return 1;
} // End parsePipe()
 
/**
  * Parses normal command
  */	
void parseSpace(char* str, char** parsed) {
	// Tokenizes either normal
	// or piped commands, using
	// whitespace as delimiter
	int i;
	for(i = 0; i < MAX_LIST; i++) {
		parsed[i] = strsep(&str, " ");
		 
		// If end of array is reached
		if(parsed[i] == NULL) break;
		 
		// If token is '\0', ignore it
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
		printf("\nUnable to fork child process\n");
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
void execArgsPiped(char** parsed, char** parsedPiped) {
	int pipefd[2];
	pid_t p1, p2;
	
	if(pipe(pipefd) < 0) {
		printf("\nUnable to create pipe\n");
		return;
	}
	
	p1 = fork();
	
	// Child 1 is running
	if(p1 < 0) {
		close(pipefd[0]); // Close (unused) read end of pipe
		dup2(pipefd[1], STDOUT_FILENO); // Maps input end of pipe to stdout
		close(pipefd[1]);
		
		if(execvp(parsed[0], parsed) < 0) {
			printf("\nUnable to execute command 1\n");
			exit(0);
		}
	}
	// Parent is running
	else {
		p2 = fork();
		
		// Child 2 is running
		if(p2 == 0) {
			close(pipefd[1]); // Close (unused) write end of pipe
			dup2(pipefd[0], STDIN_FILENO); 
			close(pipefd[0]); 
			if(execvp(parsedPiped[0], parsedPiped) < 0) {
				printf("\nUnable to execute command 2\n");
				exit(0);
			}
		}
		// Parent is running, wait for child processes to end
		else {
			wait(NULL);
			wait(NULL);
		}
	}
} // End void execArgsPiped()

char *strlwr(char *str) {
	unsigned char *p = (unsigned char *)str;
	
	while(*p) {
		*p = tolower((unsigned char) *p);
		 p++;
	} // End while
	
	return str;
} // End char *strlwr()
