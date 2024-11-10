#include <iostream>
#include <unistd.h>
#include <mutex>
#include "./cat.hpp"
#include "./constants.hpp"
#include "./global.hpp"
using namespace std;

Cat::Cat (int id) {
	_id = id;
}

int Cat::getId() {
	return _id;
}

void Cat::run() {
    // launch the thread to simulate the cat's behavior	 
    _catThread = new thread(catThread, this); // SW
}

void Cat::wait() {
    // wait for the thread to terminate
    if (_catThread && _catThread->joinable()) { // SW
        _catThread->join(); // SW
		delete _catThread; // SW
		_catThread = nullptr; // SW
    } // SW
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
	unique_lock<mutex> lock(crossingMutex, defer_lock); // SW

	if (debug) {
		cout << "[" << aCat->getId() << "] cat is alive\n";
		cout << flush;
    }

	while(running) {
		aCat->sleepNow();

		lock.lock(); // SW
		/*
	     * Check for too many lizards crossing
	     */
		if (numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago > MAX_LIZARD_CROSSING) {
            cout << "\tThe cats are happy - they have toys.\n";
            exit( -1 );
		}
		lock.unlock(); // SW
    }
}
