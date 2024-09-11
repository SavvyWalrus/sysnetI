#include "./param.hpp"
#include <iostream>

Param::Param() {
    setInputRedirect("");
    setOutputRedirect("");
    background = false;
    argumentCount = 0;
}

void Param::printParams() {
    cout << "Input Redirect: " << getInputRedirect() << endl;
    cout << "Output Redirect: " << getOutputRedirect() << endl;
    cout << "Background Process: " << getBackground() << endl;

    for (int i = 1; i <= argumentCount; ++i) {
        cout << "arg " << i << ": " << argumentVector[i - 1] << endl;
    }
}