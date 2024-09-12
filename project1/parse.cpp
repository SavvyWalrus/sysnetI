#include "./parse.hpp"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

void Parse::setCommandInput(const char* commandInput) {
    // Copy the input command into the class member variable `commandInput`
    strncpy(this->commandInput, commandInput, sizeof(this->commandInput) - 1);
    this->commandInput[sizeof(this->commandInput) - 1] = '\0';  // Ensure null termination
}

void Parse::promptUser(bool debug) {
    char commandInput[1024];

    do {
        cout << "$$$ ";
        cin.getline(commandInput, 1024);
    } while (strlen(commandInput) == 0);

    setCommandInput(commandInput);
    parseTokens();

    if (debug) param.printParams();
}

void Parse::parseTokens() {
    char* token = strtok(commandInput, " ");
    
    while (token != nullptr) {
        if (strcmp(token, "exit")) {
            EXIT_SUCCESS;
        }

        if (token[0] == '<') {
            param.setInputRedirect(&token[1]);
        } else if (token[0] == '>') {
            param.setOutputRedirect(&token[1]);
        } else if (strcmp(token, "&")) {
            param.setBackground(true);
        } else {
            param.addArgument(token);
        }

        token = strtok(nullptr, " ");
    }
}