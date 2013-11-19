/*
 * myshell.h
 *
 *  Created on: Jun 19, 2013
 *      Author: carlos
 */

#ifndef MYSHELL_H_
#define MYSHELL_H_

typedef short int bool;


void makeArray(char *argsIn[], char listIn[], char cmdIn[], int listPos);
int getCmdLength(char listIn[]);
bool checkAndSymbol(char listIn[], int lastChar);
bool checkExit(char listIn[]);
short int getCommandLength(char listIn[]);

#endif /* MYSHELL_H_ */
