#ifndef GLOBALS_H
#define GLOBALS_H

#include <mutex>
#include <condition_variable>
using namespace std;

/*
 * Define "global" variables here
 */

/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
extern int numCrossingSago2MonkeyGrass;
extern int numCrossingMonkeyGrass2Sago;
extern int debug;
extern int running;
/**************************************************/

extern mutex crossingMutex; // SW
extern condition_variable crossingCondition; // SW

#endif