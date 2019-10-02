// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)


/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */
void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);

	if (length < 0) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

void runCommands(char *tokens[], char *history[], int counter, _Bool in_background) {
	char *internal[4];
	internal[0] = "exit";
	internal[1] = "pwd";
	internal[2] = "cd";
	internal[3] = "type";
	char cwd[256];
	if (strcmp(tokens[0], "pwd") == 0) {
		write(STDOUT_FILENO, "Current working directory: ", strlen("Current working directory: "));
		write(STDOUT_FILENO, getcwd(cwd, sizeof(cwd)), strlen(getcwd(cwd, sizeof(cwd))));
		write(STDOUT_FILENO, "\n", strlen("\n"));
	} else if (strcmp(tokens[0], "cd") == 0) {
		if (tokens[1] != NULL) {
			if (chdir(tokens[1]) == -1) {
				write(STDOUT_FILENO, "Could not change directory to that path.\n", strlen("Could not change directory to that path.\n"));
			}
		} else {
			write(STDOUT_FILENO, "Please specify path of directory.\n", strlen("Please specify path of directory.\n"));
		}
	} else if (strcmp(tokens[0], "type") == 0) { 
		if (tokens[1] != NULL) {
			bool isInternal = false;
			for (int i=0;i<4;i++) {
				if (strcmp(tokens[1], internal[i]) == 0) {
					isInternal = true;
				}
			}
			write(STDOUT_FILENO, tokens[1], sizeof(tokens[1]));
			if (isInternal) {
				write(STDOUT_FILENO, "is a shell300 builtin\n", sizeof("is a shell300 builtin\n"));
			} else {
				write(STDOUT_FILENO, "is external to shell300\n", sizeof("is external to shell300\n"));
			}
		}				
	} else if (strcmp(tokens[0], "history") == 0) {
		int i = counter-10;
		if (i < 0) {
			i = 0;
		}
		for (;i<counter;i++) {
			char num[3];
			sprintf(num, "%d", i);
			write(STDOUT_FILENO, num, strlen(num));;
			write(STDOUT_FILENO, "        ", strlen("        "));
			write(STDOUT_FILENO, history[i], strlen(history[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}
	} else if (*tokens[0] == '!') {
		if (strcmp(tokens[0], "!!") == 0) {
			write(STDOUT_FILENO, "Performing most recent command\n", strlen("Performing most recent command\n"));
		} else {
			write(STDOUT_FILENO, "Performing command \n", strlen("Performing command \n"));
		}
	} else {
		int pid = fork();
		if (pid < 0) {
			write(STDOUT_FILENO, "Fork failed.", strlen("Fork failed."));
		} else if (pid == 0) {
			write(STDOUT_FILENO, "This is child process. Invoking commands.\n", strlen("This is child process. Invoking commands.\n"));
			if (execvp(tokens[0], tokens) == -1) {
				write(STDOUT_FILENO, "Error: Unable to execute command.\n", strlen("Error: Unable to execute command.\n"));
			}
		} else if (in_background == false) {
			write(STDOUT_FILENO, "This is parent process. Waiting for child.\n", strlen("This is parent process. Waiting for child.\n"));
			while (waitpid(-1, NULL, WNOHANG) > 0)
				;
			write(STDOUT_FILENO, "Done waiting, continuing.\n", strlen("Done waiting, continuing.\n"));
		} else {
			write(STDOUT_FILENO, "This is parent process. Continuing to run.\n", strlen("This is parent process. Continuing to run.\n"));
		}
	}
}

/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
	char *history[256];
	int counter = 0;
	while (true) {

		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		char cwd[256];
		write(STDOUT_FILENO, getcwd(cwd, sizeof(cwd)), strlen(getcwd(cwd, sizeof(cwd))));
		write(STDOUT_FILENO, "$ ", strlen("$ "));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		// DEBUG: Dump out arguments:
		char *recent = malloc(sizeof(char)*256);
		for (int i = 0; tokens[i] != NULL; i++) {
			write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
			write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
			if (i == 0) {				
				strcpy(recent, tokens[i]);
			} else {
				strcat(recent, " ");
				strcat(recent, tokens[i]);		
			}
		}
		if (in_background) {
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
		}

		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */
		if (tokens[0] != NULL) {
			if (*tokens[0] != '!') {						
				history[counter] = recent;
				counter++;	
			}			
			if (strcmp(tokens[0], "exit") == 0) {
				write(STDOUT_FILENO, "Exiting...\n", strlen("Exiting...\n"));
				return 0;
			} else {
				runCommands(tokens, history, counter, in_background);
			}
		}		
	}
	return 0;
}