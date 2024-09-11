#ifndef PARSE_HPP
#define PARSE_HPP
#include "./param.hpp"

class Parse {
    public:
        void promptUser();
        void setCommand(string command) {this->command = command;}
    private:
        Param param;
        string command; // Stores user entered command
        void parseTokens(); // Parses and stores command tokens into the param object
};

#endif