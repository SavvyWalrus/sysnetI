#include <iostream>
#include <unistd.h>
#include "./cat.hpp"
#include "./constants.hpp"
using namespace std;

/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
int numCrossingSago2MonkeyGrass;
int numCrossingMonkeyGrass2Sago;
int debug;
int running;
/**************************************************/

Cat::Cat (int id) {
	_id = id;
}

int Cat::getId() {
	return _id;
}

void Cat::run() {
    // launch the thread to simulate the cat's behavior	 
    
}

void Cat::wait() {
    // wait for the thread to terminate
}

void Cat::sleepNow() {
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug) {
		cout << "[" << _id << "] cat sleeping for " << sleepSeconds << " seconds" << endl;
		cout << flush;
    }

	sleep( sleepSeconds );

	if (debug) {
		cout << "[" << _id << "] cat awake" << endl;
		cout << flush;
    }
}

void Cat::catThread (Cat *aCat) {
	
	if (debug) {
		cout << "[" << aCat->getId() << "] cat is alive\n";
		cout << flush;
    }

	while(running) {
		aCat->sleepNow();



		/*
	     * Check for too many lizards crossing
	     */
		if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING) {
            cout << "\tThe cats are happy - they have toys.\n";
            exit( -1 );
		}
    }
}