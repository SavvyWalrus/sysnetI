#include "./param.hpp"
#include "./parse.hpp"

int main(int argc, char **argv) {
    bool debug = false;

    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-Debug") debug = true;
    }

    Parse parse;
    parse.promptUser(debug);
    
    return 0;
}