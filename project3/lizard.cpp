/***************************************************************/
/*                                                             */
/* lizard.cpp                                                  */
/*                                                             */
/* To compile, you need all the files listed below             */
/*   lizard.cpp                                                */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   g++ -g -Wall -std=c++11 lizard.cpp -o lizard -pthread     */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mutex>
#include <vector>
#include "./lizard.hpp"
#include "./constants.hpp"
#include "./global.hpp"

using namespace std;

Lizard::Lizard (int id) {
	_id = id;
}

int Lizard::getId() {
	return _id;
}

void Lizard::run() {
    // launch the thread to simulate the lizard's behavior
    _aLizard = new thread(lizardThread, this);
}

void Lizard::wait() {
    // wait for the thread to terminate
    if (_aLizard && _aLizard->joinable()) { // SW
        _aLizard->join();
        delete _aLizard; // SW
        _aLizard = nullptr; // SW
    } 
}

void Lizard::sago2MonkeyGrassIsSafe(unique_lock<mutex>& lock) { // SW
	if (debug) {
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

    lock.lock(); // SW

    crossingCondition.wait(lock, [] { // SW
        return numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass < MAX_LIZARD_CROSSING; // SW
    }); // SW

	if (debug) {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}

void Lizard::crossSago2MonkeyGrass(unique_lock<mutex>& lock) { // SW
	if (debug) {
        cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
        cout << flush;
    }

    if (!lock.owns_lock()) { // SW
        cout << "ERROR: Lock not kept between method calls" << endl; // SW
        exit(1); // SW
    } // SW

    /*
    * One more crossing this way
    */
    numCrossingSago2MonkeyGrass++;

    /*
    * Check for lizards cross both ways
    */
    if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL) {
        cout << "\tCrash!  We have a pile-up on the concrete." << endl;
        cout << "\t" << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
        cout << "\t" << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
        exit( -1 );
    }

    lock.unlock(); // SW

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

    /*
    * That one seems to have made it
    */
    lock.lock(); // SW
    numCrossingSago2MonkeyGrass--;
}

void Lizard::madeIt2MonkeyGrass(unique_lock<mutex>& lock) { // SW
	/*
     * Whew, made it across
     */
	if (debug) {
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
    }

    lock.unlock(); // SW
    crossingCondition.notify_all(); // SW
}

void Lizard::eat() {
	int eatSeconds;

	eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug) {
		cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << endl;
		cout << flush;
    }

	/*
     * Simulate eating by blocking for a few seconds
     */
	sleep( eatSeconds );

	if (debug) {
        cout << "[" << _id << "] finished eating" << endl;
        cout << flush;
    }
}

void Lizard::monkeyGrass2SagoIsSafe(unique_lock<mutex>& lock) { // SW
	if (debug) {
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
    }

    lock.lock(); // SW

    crossingCondition.wait(lock, [] { // SW
        return numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass < MAX_LIZARD_CROSSING; // SW
    }); // SW

	if (debug) {
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
    }
}

void Lizard::crossMonkeyGrass2Sago(unique_lock<mutex>& lock) { // SW
	if (debug) {
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
    }

    if (!lock.owns_lock()) { // SW
        cout << "ERROR: Lock not kept between method calls" << endl; // SW
        exit(1); // SW
    } // SW

    /*
     * One more crossing this way
     */
	numCrossingMonkeyGrass2Sago++;

  
    /*
     * Check for lizards cross both ways
     */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL) {
		cout << "\tOh No!, the lizards have cats all over them." << endl;
		cout << "\t " << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t " << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

    lock.unlock(); // SW

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

	/*
     * That one seems to have made it
     */
    lock.lock(); // SW
	numCrossingMonkeyGrass2Sago--;
}

void Lizard::madeIt2Sago(unique_lock<mutex>& lock) { // SW
	/*
     * Whew, made it across
     */
	if (debug) {
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
    }

    lock.unlock(); // SW
    crossingCondition.notify_all(); // SW
}

void Lizard::sleepNow() {
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug) {
        cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << endl;
        cout << flush;
    }

	sleep( sleepSeconds );

	if (debug) {
        cout << "[" << _id << "] awake" << endl;
        cout << flush;
    }
}

void Lizard::lizardThread(Lizard *aLizard) { // SW
	unique_lock<mutex> lock(crossingMutex, defer_lock); // SW
    
    if (debug) {
        cout << "[" << aLizard->getId() << "] lizard is alive" << endl;
        cout << flush;
    }

	while(running) {
      /* 
       * Follow the algorithm given in the assignment
       * using calls to the functions declared above.
       * You'll need to complete the implementation of
       * some functions by filling in the code.  Some  
       * are already completed - see the comments.
       */
        aLizard->sleepNow(); // SW
        aLizard->sago2MonkeyGrassIsSafe(lock); // SW
        aLizard->crossSago2MonkeyGrass(lock); // SW
        aLizard->madeIt2MonkeyGrass(lock); // SW
        aLizard->eat(); // SW
        aLizard->monkeyGrass2SagoIsSafe(lock); // SW
        aLizard->crossMonkeyGrass2Sago(lock); // SW
        aLizard->madeIt2Sago(lock); // SW
    }
}
