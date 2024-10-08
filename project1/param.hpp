/**
 *  param.hpp
 *  
 *  Thomas Reichherzer
 *  Copyright 2009 UWF - CS. All rights reserved.
 *
 */

#ifndef _PARAM_HPP
#define _PARAM_HPP

/* Don't test program with more than this many tokens for input  */
const int MAXARGS = 32;

/* Class to hold input data                                  */
class Param
{
	private:
		char *inputRedirect;           /* file name or NULL            */
		char *outputRedirect;          /* file name or NULL            */
		int   background;              /* either 0 (false) or 1 (true) */
		int   argumentCount;           /* same as argc in main()       */
		char *argumentVector[MAXARGS]; /* array of strings             */
		
	public:
		
		/**
		 * Constructs an empty Param object.
		 */
		Param();

		/**
		 * Destructor for the object
		 */
		~Param();

		/**
		 * Returns the maximum number of allowed arguments
		 *
		 * @return an int representing the maximum number of allowed arguments
		 */
		int getMaxArgs() {return MAXARGS;}

		/**
		 * Adds an argument string to the argument list in this object. This function
		 * does not create a string copy of the original string. 
		 * 
         * @param newArgument a new argument to be added to the argument list; 
		 *                    if NULL nothing will be added		 
         */
		void addArgument (char* newArgument);
		
		/**
		 * Returns an argument list referencing char* strings. The last element in the 
		 * list is NULL to mark the end of list elements. This makes the size of 
		 * the list one larger than the number of arguments added to this object.
		 * 
		 * Note: 
		 *   Caller must deallocate memory for the list.
		 */
		char** getArguments();

        /**
         * Clears the list of arguments.
         */
         void clearArguments();
	
		// getter & setter functions
		
		/**
		 * Sets the filename for input redirection.
		 *
		 * @param newInputRedirect a string specifying the input redirect filename
		 */
		void setInputRedirect(char *newInputRedirect);
		
		/**
		 * Sets the filename for output redirection.
		 *
		 * @param newOutputRedirect a string specifying the output redirect filename
		 */
		void setOutputRedirect(char *newOutputRedirect);
		
		/**
		 * Sets an int for if the process is to run in the backround
		 *
		 * @param newBackground an int specifying whether it's a background process
		 *						either 0 (false) or 1 (true)
		 */
		void setBackground(int newBackground);
		
		/**
		 * Returns the filename for input redirection.
		 *
		 * @return a string representing a filename
		 */
		char* getInputRedirect();
		
		
		/**
		 * Returns the filename for output redirection.
		 *
		 * @return a string representing a filename
		 */
		char* getOutputRedirect();
		
		/**
		 * Returns an int for if it's a background process.
		 *
		 * @return an int representing if it's a background process
		 */
		int getBackground();
		
	
		/**
		 * Prints the information in the specified structure to standard out.
         */
		void printParams();
};

#endif
