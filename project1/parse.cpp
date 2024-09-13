#include "./parse.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void Parse::setCommandInput(const char* commandInput) {
    // Copy the input command into the class member variable `commandInput`
    strncpy(this->commandInput, commandInput, sizeof(this->commandInput) - 1);
    this->commandInput[sizeof(this->commandInput) - 1] = '\0';  // Ensure null termination
}

void Parse::promptUser(bool debug) {
    char commandInput[MAXARGS];

    param.clearArguments();

    cout << "$$$ ";
    cin.getline(commandInput, MAXARGS);

    setCommandInput(commandInput);
    parseTokens();

    if (debug) param.printParams();
}

void Parse::parseTokens() {
    char* token = strtok(commandInput, " "); // Tokenize first argument
    
    // Loops until no more tokens are found
    while (token != nullptr) {
        // Ensures that '&' must be the last argument if used
        if (param.getBackground() == 1) {
            cout << "Invalid args : To indicate a background process, use a single '&' as the final argument" << endl;
            return;
        }

        // Exits on exit token
        if (strcmp(token, "exit") == 0) {
            exit(0);
        }

        // Parses token types and adds them to param class
        if (token[0] == '<') {
            param.setInputRedirect(&token[1]);
        } else if (token[0] == '>') {
            param.setOutputRedirect(&token[1]);
        } else if (strcmp(token, "&") == 0) {
            param.setBackground(true);
        } else {
            param.addArgument(token);
        }

        token = strtok(nullptr, " "); // Tokenize next argument
    }
}