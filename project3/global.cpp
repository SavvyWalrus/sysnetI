#include "./global.hpp"

int numCrossingSago2MonkeyGrass = 0;
int numCrossingMonkeyGrass2Sago = 0;
int debug = 0;
int running = 1;
mutex crossingMutex;
condition_variable crossingCondition;