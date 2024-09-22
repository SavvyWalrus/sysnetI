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

class Parse
{
public:
    /**
     * Prompts the user for a command and parses it.
     *
     * @param debug If true, prints the parsed parameters after parsing the input.
     */
    void promptUser(bool debug);

    /**
     * Copies the input command provided by the user to the class member variable `commandInput`.
     *
     * @param commandInput The input command string entered by the user.
     */
    void setCommandInput(const char *commandInput);

    /**
     * Returns the parsed arguments as a list of strings.
     */
    char **getArguments();

    /**
     * Retrieves the input redirection file, if specified.
     */
    char *getInputRedirect();

    /**
     * Retrieves the output redirection file, if specified.
     */
    char *getOutputRedirect();

    /**
     * Retrieves the background execution flag.
     */
    int getBackground();

private:
    Param param;
    char commandInput[MAXARGS]; // Stores user entered command

    /**
     * Parses and stores command tokens into the param object
     */
    void parseTokens();
};

#endif