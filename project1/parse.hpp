/**
 * param.hpp
 * 
 * @authors Sarah Wallis, Dustin Evans
 * @date 9/22/2024
 * @info Course COP4634
 */

#ifndef PARSE_HPP
#define PARSE_HPP
#include "./param.hpp"

class Parse {
    public:
        void promptUser(bool debug);
        void setCommandInput(const char* commandInput);
        char** getArguments();
        char* getInputRedirect();
        char* getOutputRedirect();
        int getBackground();
    private:
        Param param;
        char commandInput[MAXARGS]; // Stores user entered command
        void parseTokens(); // Parses and stores command tokens into the param object
};

#endif