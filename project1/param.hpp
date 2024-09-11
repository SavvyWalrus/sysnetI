#ifndef PARAM_HPP
#define PARAM_HPP
#define MAXARGS 32
#include <string>
using namespace std;

class Param {
    public:
        Param();
        void printParams();
        void setInputRedirect(string fileName) {inputRedirect = fileName;}
        string getInputRedirect() {return inputRedirect;}
        void setOutputRedirect(string fileName) {outputRedirect = fileName;}
        string getOutputRedirect() {return outputRedirect;}
        void setBackground(bool isBackground) {background = isBackground;}
        int getBackground() {return background;}
        void addArgument(string arg) {argumentVector[argumentCount++] = arg;}
        int getArgumentCount() {return argumentCount;}
    private:
        string inputRedirect; /* file name or NULL */
        string outputRedirect; /* file name or NULL */
        int background; /* either 0 (false) or 1 (true) */
        int argumentCount; /* number of tokens in argument vector */
        string argumentVector[MAXARGS]; /* array of strings */
};

#endif