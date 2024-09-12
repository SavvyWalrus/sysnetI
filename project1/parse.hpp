#ifndef PARSE_HPP
#define PARSE_HPP
#include "./param.hpp"
#include <string>
using namespace std;

class Parse {
    public:
        void promptUser(bool debug);
        void setCommandInput(const char* commandInput);
    private:
        Param param;
        char commandInput[32]; // Stores user entered command
        void parseTokens(); // Parses and stores command tokens into the param object
};

#endif