/**
 * param.cpp
 * 
 * @authors Sarah Wallis, Dustin Evans
 * @date 9/22/2024
 * @info Course COP4634
 */

#include "./parse.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

/**
 * Copies the input command provided by the user to the class member variable `commandInput`.
 * 
 * @param commandInput The input command string entered by the user.
 */
void Parse::setCommandInput(const char *commandInput)
{
    // Copy the input command into the class member variable `commandInput`
    strncpy(this->commandInput, commandInput, sizeof(this->commandInput) - 1);
    this->commandInput[sizeof(this->commandInput) - 1] = '\0'; // Ensure null termination
}

/**
 * Prompts the user for a command and parses it.
 * 
 * @param debug If true, prints the parsed parameters after parsing the input.
 */
void Parse::promptUser(bool debug) 
{
    char commandInput[MAXARGS];

    // Clears previous arguments
    param.clearArguments();

    // Sets command prompt and takes in user input
    cout << "$$$ ";
    cin.getline(commandInput, MAXARGS);

    // Store input and parse
    setCommandInput(commandInput);
    parseTokens();

    // If true, prints the parsed parameters
    if (debug)
        param.printParams();
}

/**
 * Tokenizes and processes the command input.
 * 
 */
void Parse::parseTokens()
{
    char *token = strtok(commandInput, " "); // Tokenize first argument

    // Loops until no more tokens are found
    while (token != nullptr) {
        // Ensures that '&' must be the last argument if used
        if (param.getBackground() == 1) {
            cout << "Invalid args : To indicate a background process, use a single '&' as the final argument" << endl;
            return;
        }

        // Exits on exit token
        if (strcmp(token, "exit") == 0)
        {
            exit(0);
        }

        // Parses token types and adds them to param class
        if (strcmp(token, "<") == 0)
        {
            token = strtok(nullptr, " "); // Get next token for the filename
            if (token != nullptr)
            {
                param.setInputRedirect(token); // Store input refirect
            }
            else
            {
                std::cerr << "Error: No input file specified after '<'\n";
            }
        }
        else if (strcmp(token, ">") == 0)
        {
            token = strtok(nullptr, " ");
            if (token != nullptr)
            {
                param.setOutputRedirect(token); // Store output redirection
            }
            else
            {
                std::cerr << "Error: No output file specified after '>'\n";
            }
        }
        else if (token[0] == '<')
        {
            param.setInputRedirect(&token[1]); // Store everything after '<'
        }
        else if (token[0] == '>')
        {
            param.setOutputRedirect(&token[1]); // Store everything after '>'
        }
        else if (strcmp(token, "&") == 0)
        {
            param.setBackground(true);
        }
        else
        {
            param.addArgument(token);
        }

        token = strtok(nullptr, " "); // Tokenize next argument
    }
}

/**
 * Returns the parsed arguments as a list of strings.
 */
char** Parse::getArguments() {
    return param.getArguments();
}

/**
 * Retrieves the input redirection file, if specified.
 */
char* Parse::getInputRedirect() {
    return param.getInputRedirect();
}

/**
 * Retrieves the output redirection file, if specified.
 */
char* Parse::getOutputRedirect() {
    return param.getOutputRedirect();
}

/**
 * Retrieves the background execution flag.
 */
int Parse::getBackground() {
    return param.getBackground();
}