#include "A2.h"

using namespace std;

int main() {
	while(true) {
		string str;
		const char *filename;
		
		cout <<	"cssc0884% ";
		cin >> str;
		
		if(tolower(str) == "exit") return 0;
		else filename = str.c_str();
		
		if(is_exec(filename))
			// Create process and
			// run files
			
		// Need if statement to 
		// check if user writes "exit"
	} // End while
} // End main

/** Checks if the file is executable
 */
bool is_exec(const char *filename) {
	struct stat file_status;
	
	// Returns file type and mode,
	// returns -1 if error occurs
	if(stat(file, &file_status) < 0) 
		return false;
	
	// Checks if file has execute permission
	if(file_status.st_mode & IEXEC) != 0)
		return true;
	
	return false;
} // End bool is_exec()
	