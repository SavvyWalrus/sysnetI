/**
 *  param.hpp
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#ifndef _PARAM_CPP
#define _PARAM_CPP

#include <cstddef>
#include <cstring>
#include <iostream>

#include "param.hpp"

using  namespace std;


Param::Param() 
{
	inputRedirect = outputRedirect = NULL;
	background = 0;
	argumentCount = 0;
}

Param::~Param() {
	// Iterates through the argumentVector and deletes each allocated argument
    for (int i = 0; i < argumentCount; ++i) {
        delete[] argumentVector[i];
    }

	delete[] inputRedirect;
	delete[] outputRedirect;
}

void Param::addArgument (char* newArgument)
{
    // Early exit if no argument or too many arguments
	if (newArgument == NULL || argumentCount >= MAXARGS) return;

    // Allocates memory for the new argument
    argumentVector[argumentCount] = new char[strlen(newArgument) + 1];

    // Copies the argument into argumentVector
	strcpy(argumentVector[argumentCount], newArgument);

	++argumentCount; // Increments number of stored arguments
}

char** Param::getArguments()
{
	return argumentVector;
}

void Param::clearArguments()
{
    // Iterates through the argumentVector and deletes each allocated argument
    for (int i = 0; i < argumentCount; ++i) {
        delete[] argumentVector[i];
        argumentVector[i] = nullptr;
    }

    argumentCount = 0; // Reset the argument count
    setBackground(0); // Resets the background variable
    setInputRedirect(NULL); // Resets the input redirect
    setOutputRedirect(NULL); // Resets the output redirect
}

void Param::setInputRedirect(char *newInputRedirect)
{
	if (inputRedirect != NULL) {
		delete[] inputRedirect;
	}

	inputRedirect = newInputRedirect;
}

void Param::setOutputRedirect(char *newOutputRedirect)
{
	if (outputRedirect != NULL) {
		delete[] outputRedirect;
	}

	outputRedirect = newOutputRedirect;
}
		
void Param::setBackground(int newBackground)
{
	background = newBackground;
}

char* Param::getInputRedirect()
{
	return inputRedirect;
}
		
		
char* Param::getOutputRedirect()
{
	return outputRedirect;
}
		
int Param::getBackground()
{
	return background;
}


void Param::printParams() {
	cout << "InputRedirect: [" 
	     << ((inputRedirect != NULL) ? inputRedirect : "NULL");
	cout << "]" 
	     << endl 
		 <<	"OutputRedirect: [" 
		 << ((outputRedirect != NULL) ? outputRedirect : "NULL");
	cout << "]" 
	     << endl 
		 << "Background: [" 
		 << background 
		 << "]" 
		 << endl 
		 << "ArgumentCount: [" 
		 << argumentCount 
		 << "]" 
		 << endl;
	for (int i = 0; i < argumentCount; i++)
		cout << "ArgumentVector[" 
			 << i 
			 << "]: [" 
			 << argumentVector[i] 
			 << "]" 
			 << endl;
}

#endif
