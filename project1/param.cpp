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
        argumentVector[i] = nullptr;
    }

	delete inputRedirect;
	delete outputRedirect;
}

void Param::addArgument (char* newArgument)
{
    // Early exit if no argument
	if (newArgument == NULL) return;

    // Allocates memory for the new argument
    argumentVector[argumentCount] = new char[strlen(newArgument)];

    // Copies the argument into argumentVector
	strcpy(argumentVector[argumentCount], newArgument);

	++argumentCount; // Increments number of stored arguments
}

char** Param::getArguments()
{
	// Dynamically allocate memory for argList of size argument count + 1
	char** argList = new char*[argumentCount + 1];
	
	// Copy the pointers from argumentVector to argList
	for (int i = 0; i < argumentCount; ++i) {
		argList[i] = argumentVector[i];
	}

	// Sets the last element to NULL to indicate the end of the list
	argList[argumentCount] = NULL;

	return argList;
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
	inputRedirect = newInputRedirect;
}

void Param::setOutputRedirect(char *newOutputRedirect)
{
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
