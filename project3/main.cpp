#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <vector>
#include "./lizard.hpp"
#include "./cat.hpp"
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
	if (argc > 1 && strncmp(argv[1], "-d", 2) == 0) {
        debug = 1;
    }

	/*
     * Initialize variables
     */
	

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
	vector<Cat*> allCats; // SW
    for (int i=0; i < NUM_CATS; i++) { // SW
	    allCats.push_back(new Cat(i)); // SW
    } // SW

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */
    for (int i=0; i < NUM_LIZARDS; i++) {
        allLizards[i]->run();
    }
    for (int i = 0; i < NUM_CATS; ++i) { // SW
        allCats[i]->run(); // SW
    } // SW

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
    for (int i = 0; i < NUM_LIZARDS; ++i) { // SW
        allLizards[i]->wait(); // SW
    } // SW
    for (int i = 0; i < NUM_CATS; ++i) { // SW
        allCats[i]->wait(); // SW
    } // SW





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