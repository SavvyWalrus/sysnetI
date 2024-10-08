/**
 * myshell.cpp
 * 
 * @authors Sarah Wallis, Dustin Evans
 * @date 9/22/2024
 * @info Course COP4634
 */

#include "./parse.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

/**
 * Execute commands from input and output redirection, handles whether the command runs in the background
 * or foreground.
 * @param command 
 * @param inputArguments
 * @param inputRedirect
 * @param outputRedirect
 * @param background
 */
void executeCommand(char* command, char** inputArguments, char* inputRedirect, char* outputRedirect, int background) {
    int status;

    // Create new process to execute command
    pid_t pid = fork(); 

    if (pid == -1) { // Check for error during fork
        cout << "Error forking process" << endl;
        exit(EXIT_FAILURE);
    }
    
    // Child process
    if (pid == 0) {  
        // Handle input redirection
        if (inputRedirect != NULL) {
            if (freopen(inputRedirect, "r", stdin) == NULL) {
                perror("Failed to open file");
                exit(EXIT_FAILURE);
            }
        }

        // Handle output redirection
        if (outputRedirect != NULL) {
            if (freopen(outputRedirect, "w", stdout) == NULL) {
                perror("Failed to redirect output");
                exit(EXIT_FAILURE);
            }
        }

        // Execute the command
        if (execvp(inputArguments[0], inputArguments) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }

    // If 'background' is false, wait for the child process to finish
    if (!background) {
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char **argv) {
    Parse parse;
    bool debug = false;

    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-Debug") debug = true;
    }

    while (true) {
        parse.promptUser(debug);
        char** inputArguments = parse.getArguments();
        char* inputRedirect = parse.getInputRedirect();
        char* outputRedirect = parse.getOutputRedirect();
        int background = parse.getBackground();
        
        executeCommand(inputArguments[0], inputArguments, inputRedirect, outputRedirect, background);
    }
    
    return 0;
}
