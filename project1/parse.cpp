#include "./parse.hpp"
#include <iostream>
#include <sstream>

void Parse::promptUser() {
    string command = "";

    do {
        cout << "$$$ ";
        getline(cin, command);
    } while (command == "");

    setCommand(command);
    parseTokens();
}

void Parse::parseTokens() {
    istringstream buffer(command);
    string tempToken;
    
    while (getline(buffer, tempToken)) {
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