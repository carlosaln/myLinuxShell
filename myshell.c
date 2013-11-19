#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "myshell.h"

#define true 1
#define false 0


int main() {

	bool exitShell = false;
	static int MAX_ARGS = 10;
	static int MAX_SIZE = 256;

	while (exitShell == false) {
		printf("myshell> ");

		// Process input into a working form

		char listIn[MAX_SIZE];
		fgets(listIn,MAX_SIZE, stdin);
		int cmdListLength = getCommandLength(listIn);
		char *args[MAX_ARGS];
		memset(args, 0, sizeof args);

		//Check amount of arguments
		if (cmdListLength > 10) {
			printf("Maximum argument limit reached. Please use %d or less arguments.\n", MAX_ARGS);
			continue;
		}


		// Find out the length of the command
		bool found = false;
		int i = 0;
		while (found == false)
		{
			if ((strncmp(&listIn[i], " ", 1)) == 0
					|| (strncmp(&listIn[i], "\n", 1)) == 0)
				found = true;

			else
				i++;
		}

		// Insert command into its own string
		int cmdSize = i;
		char cmd[cmdSize];
			int j;
			for (j = 0; j < cmdSize; j++)
			{
				cmd[j] = listIn[j];
			}


		//Check for exit command
		if ((strncmp(&listIn, "exit\n", 5)) == 0) {
			exit(1);
		}

		/* creates an array of pointers to character arrays
		 * that can be used by to execv. */
		makeArray(args, listIn, cmd, i);


	    //check for & at end of string
	    bool andSymbol = checkAndSymbol(listIn, (strlen(listIn) - 2));

		/****** FINISH SETUP, START EXECUTION *****/

		//Create child process
		pid_t pID;
		pID = fork();
		int status;
		int execStatus;

		if (andSymbol == 1) {//parent does NOT wait
			args[getCommandLength(listIn)-1] = NULL;
			//Stuff for the child process
			if (pID == 0) {
				execStatus = execvp(args[0], args);
				if (execStatus < 0) {
					printf("Error: invalid command.\n");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}
			//Stuff in case of failure creating process
			else if (pID < 0) {
				perror("Executing application failed!\n");
				exit(1);
			}

		}

		else { //do stuff for DO wait

			if (pID == 0) {
				/*******PLACE NEW PROGRAM EXECUTION EXECVP HERE******/
				execStatus = execvp(args[0], args);
				if (execStatus < 0) {
					printf("Error: invalid command.\n");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}
			//Stuff in case of failure creating process
			else if (pID < 0) {
				perror("Executing application failed!\n");
				exit(1);
			}
			else {
				while(wait(&status) != pID);
				if(WIFSIGNALED(status))
					printf("\nParent process did wait, child didn't work\n");
			}
		}



	}
	return 0;

}

short int getCommandLength(char listIn[]) {
	int i = 0;
	//Argument count should be <= 0, so we use short.
	short int count = 0;
	bool endReached = false;

	while (endReached == false) {
		if (listIn[i] == ' ') {
			count++;
		}
		else if (listIn[i] == '\n') {
			count++;
			endReached = true;
		}
		i++;
	}
	return count;
}

void makeArray(char *argsIn[], char listIn[], char cmdIn[], int listPos) {

	int argsPos = 0;
	argsIn[argsPos] = cmdIn;
	argsIn[argsPos][listPos] = '\0';
	argsPos++;
	argsIn[argsPos] = malloc(20);


	// If there are no arguments present, set the second pointer to NULL
	if ((strncmp(&listIn[listPos], "\n", 1)) == 0)
	{
		argsIn[argsPos] = NULL;
	}

	// If there are arguments, parse through them and add them to argsIn
	else if ((strncmp(&listIn[listPos], " ", 1)) == 0)
	{
		int k = 0; //string index counter
		listPos = listPos + 1; //start on the first argument from listIn
		bool end = false;
		while (end == false)
		{
			if ((strncmp(&listIn[listPos], "\n", 1)) == 0)
			{
				argsIn[argsPos][k] = '\0';
				end = true;
			}

			// End the string with a null pointer, increment the array
			// counter, and allocate memory for the next argument.
			else if ((strncmp(&listIn[listPos], " ", 1)) == 0)
			{

				while ((strncmp(&listIn[listPos], " ", 1)) == 0) {
					listPos++;
				}
			}

			else
			{
				argsIn[argsPos][k] = listIn[listPos];
				listPos++;
				k++;

				if((strncmp(&listIn[listPos], " ", 1)) == 0) {
					argsIn[argsPos][k] = '\0';
					argsPos++;
					k = 0;
					argsIn[argsPos] = malloc(20);
				}
				else if ((strncmp(&listIn[listPos], "\n", 1)) == 0) {
					argsIn[argsPos][k] = '\0';
				}

//				if ((strncmp(&listIn[listPos], " ", 1)) == 0
//						|| (strncmp(&listIn[listPos], "\n", 1)) == 0) {
//					argsIn[argsPos][k] = '\0';
//					argsPos++;
//					k = 0;
//					argsIn[argsPos] = malloc(20);
//				}

			}
		}
	}
}

//Gets the command length
int getCmdLength(char listIn[])
{
    bool found = false;
    int i = 0;
    while (found == false)
    {
        if ((strncmp(&listIn[i], " ", 1)) == 0
            || (strncmp(&listIn[i], "\n", 1)) == 0)
            found = true;

        else
            i++;
    }
    printf("# of commands: %d", i);
    return i;
}





//Allison's Additions
//Checks for And Symbol
bool checkAndSymbol(char listIn[], int lastChar)
{
    if(listIn[lastChar] == '&')
        return true;
    else
        return false;
}

//Checks for Exit
bool checkExit(char listIn[])
{
    if ((strncmp(listIn, "exit\n", 5)) == 0) {
        return true;
    }
    else
        return false;
}
