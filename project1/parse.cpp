#include "./parse.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>

void Parse::promptUser(bool debug) {
    string command = "";

    do {
        cout << "$$$ ";
        getline(cin, command);
    } while (command == "");

    setCommand(command);
    parseTokens();

    if (debug) param.printParams();
}

void Parse::parseTokens() {
    istringstream buffer(command);
    string tempToken;
    
    while (buffer >> tempToken) {
        if (tempToken == "exit") {
            EXIT_SUCCESS;
        }

        if (tempToken[0] == '<') {
            param.setInputRedirect(tempToken.substr(1));
        } else if (tempToken[0] == '>') {
            param.setOutputRedirect(tempToken.substr(1));
        } else if (tempToken == "&") {
            param.setBackground(true);
        } else {
            param.addArgument(tempToken);
        }
    }
}