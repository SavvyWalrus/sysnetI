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
    if (_aLizard != NULL) {
        _aLizard->join();
    } 
}

void Lizard::sago2MonkeyGrassIsSafe() {
	if (debug) {
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

	


	if (debug) {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}

void Lizard::crossSago2MonkeyGrass() {
	if (debug) {
        cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
        cout << flush;
    }

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


	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

    /*
     * That one seems to have made it
     */
    numCrossingSago2MonkeyGrass--;
}

void Lizard::madeIt2MonkeyGrass() {
	/*
     * Whew, made it across
     */
	if (debug) {
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
    }





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

void Lizard::monkeyGrass2SagoIsSafe() {
	if (debug) {
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
    }





	if (debug) {
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
    }
}

void Lizard::crossMonkeyGrass2Sago() {
	if (debug) {
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
    }

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

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

	/*
     * That one seems to have made it
     */
	numCrossingMonkeyGrass2Sago--;
}

void Lizard::madeIt2Sago() {
	/*
     * Whew, made it across
     */
	if (debug) {
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
    }
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

void Lizard::lizardThread(Lizard *aLizard) {	
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


















    }
}
