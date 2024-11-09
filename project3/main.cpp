#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "./lizard.hpp"
#include "./constants.hpp"
#include "./global.hpp"

/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv) {
	/*
	 * Declare local variables
     */




	/*
     * Check for the debugging flag (-d)
     */
	debug = 0;
	if (argc > 1 && strncmp(argv[1], "-d", 2) == 0) {
        debug = 1;
    }

	/*
     * Initialize variables
     */
	numCrossingSago2MonkeyGrass = 0;
	numCrossingMonkeyGrass2Sago = 0;
	running = 1;

	/*
     * Initialize random number generator
	 */
	srandom( (unsigned int)time(NULL) );

	/*
     * Initialize locks and/or semaphores
     */




	/*
     * Create NUM_LIZARDS lizard threads
     */
    vector<Lizard*> allLizards;
    for (int i=0; i < NUM_LIZARDS; i++) {
	    allLizards.push_back(new Lizard(i));
    }    

    /*
     * Create NUM_CATS cat threads
     */
	

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */
    for (int i=0; i < NUM_LIZARDS; i++) {
        allLizards[i]->run();
    }

	/*
     * Now let the world run for a while
     */
	sleep( WORLDEND );

	/*
     * That's it - the end of the world
     */
	running = 0;

    /*
     * Wait until all threads terminate
     */






	/*
     * Delete the locks and semaphores
     */
	 
	 
	 
	/*
	 * Delete all cat and lizard objects
	 */
 



	/*
     * Exit happily
     */
	return 0;
}