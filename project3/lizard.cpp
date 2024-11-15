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

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

using namespace std;

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */


/*
 * Define "constant" values here
 */

/*
 * Make this 1 to check for lizards travelling in both directions
 * Leave it 0 to allow bidirectional travel
 */
#define UNIDIRECTIONAL       0

/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
#define WORLDEND             120

/*
 * Number of lizard threads to create
 */
#define NUM_LIZARDS          20

/*
 * Number of cat threads to create
 */
#define NUM_CATS             2

/*	
 * Maximum lizards crossing at once before alerting cats
 */
#define MAX_LIZARD_CROSSING  4

/*
 * Maximum seconds for a lizard to sleep
 */
#define MAX_LIZARD_SLEEP     3

/*
 * Maximum seconds for a cat to sleep
 */
#define MAX_CAT_SLEEP        3

/*
 * Maximum seconds for a lizard to eat
 */
#define MAX_LIZARD_EAT       5

/*
 * Number of seconds it takes to cross the driveway
 */
#define CROSS_SECONDS        2


/*
 * Declare global variables here
 */
mutex crossingMutex; // SW DE
condition_variable crossingCondition; // SW DE

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



/**
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	
	int       _id;        // the Id of the cat
	thread*   _catThread; // the thread simulating the cat
	
	public:
		Cat (int id);
		int getId();
		void run();
		void wait();
    
    private:
		void sleepNow();

        static void catThread (Cat *aCat); 
};

/**
 * Constructs a cat.
 *
 * @param id - the Id of the cat 
 */
Cat::Cat (int id)
{
	_id = id;
}

/**
 * Returns the Id of the cat.
 *
 * @return the Id of a cat
 */
int Cat::getId()
{
	return _id;
}


/**
 * Launches a cat thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Cat::run() 
 {
    // launch the thread to simulate the cat's behavior	 
    _catThread = new thread(catThread, this); // SW DE
 }
 
 /**
  * Waits for a cat to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
 void Cat::wait()
 {
    // wait for the thread to terminate
    if (_catThread && _catThread->joinable()) { // SW DE
        _catThread->join(); // SW DE
        delete _catThread; // SW DE
        _catThread = nullptr; // SW DE
    } // SW DE
 }
 
 
/**
 * Simulate a cat sleeping for a random amount of time
 *
 *
 * @return N/A
 *
 * Status: Completed - No need to change any of this code.
 */
void Cat::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug)
    {
		cout << "[" << _id << "] cat sleeping for " << sleepSeconds << " seconds" << endl;
		cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
		cout << "[" << _id << "] cat awake" << endl;
		cout << flush;
    }
}

/**
  *
  * This simulates a cat that is sleeping and occasionally checking on
  * the driveway on lizards.
  * 
  * @param aCat - a cat that is being run concurrently
  * 
  * @return - N/A
  *
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Cat::catThread (Cat *aCat)
{
  unique_lock<mutex> lock(crossingMutex, defer_lock); // SW DE

	if (debug)
    {
		cout << "[" << aCat->getId() << "] cat is alive\n";
		cout << flush;
    }

	while(running)
    {
		aCat->sleepNow();

    lock.lock(); // SW DE
    int crossingNum = numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago; // SW DE
    lock.unlock(); // SW DE

		/*
	     * Check for too many lizards crossing
	     */
		if (crossingNum > MAX_LIZARD_CROSSING)
		{
		  cout << "\tThe cats are happy - they have toys.\n";
		  exit( -1 );
		}
    }
}

 

class Lizard {
	int     _id;      // the Id of the lizard
	thread* _aLizard; // the thread simulating the lizard

	public:
		Lizard(int id);
		int getId();
        void run();
        void wait();

    private:
		void sago2MonkeyGrassIsSafe(unique_lock<mutex>& lock); // SW DE
		void crossSago2MonkeyGrass(unique_lock<mutex>& lock); // SW DE
		void madeIt2MonkeyGrass(unique_lock<mutex>& lock); // SW DE
		void eat();
		void monkeyGrass2SagoIsSafe(unique_lock<mutex>& lock); // SW DE
		void crossMonkeyGrass2Sago(unique_lock<mutex>& lock); // SW DE
		void madeIt2Sago(unique_lock<mutex>& lock); // SW DE
		void sleepNow();

        static void lizardThread(Lizard *aLizard);
	
};


/**
 * Constructs a lizard.
 *
 * @param id - the Id of the lizard 
 */
Lizard::Lizard (int id)
{
	_id = id;
}

/**
 * Returns the Id of the lizard.
 *
 * @return the Id of a lizard
 */
int Lizard::getId()
{
	return _id;
}

/**
 * Launches a lizard thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Lizard::run() 
 {
	 // launch the thread to simulate the lizard's behavior
    _aLizard = new thread ( lizardThread, this); 
 }
 
 /**
  * Waits for a lizard to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
void Lizard::wait() {
    // wait for the thread to terminate
    if (_aLizard && _aLizard->joinable()) { // SW DE
        _aLizard->join();
    } 
}
 





/**
 * Simulate a lizard sleeping for a random amount of time
 *
 * Status: Completed - No need to change any of this code.
 */
void Lizard::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug)
    {
      cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << endl;
      cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
      cout << "[" << _id << "] awake" << endl;
      cout << flush;
    }
}



 
/**
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::sago2MonkeyGrassIsSafe(unique_lock<mutex>& lock) // SW DE
{
	if (debug)
    {
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

	lock.lock(); // SW DE

    crossingCondition.wait(lock, [] { // SW DE
        return numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass < MAX_LIZARD_CROSSING; // SW DE
    }); // SW DE

	if (debug)
    {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}


/**
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossSago2MonkeyGrass(unique_lock<mutex>& lock) // SW DE
{
	if (debug)
    {
      cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
      cout << flush;
    }

    if (!lock.owns_lock()) { // SW DE
        cout << "ERROR: Lock not kept between method calls" << endl; // SW DE
        exit(1); // SW DE
    } // SW DE

	/*
	 * One more crossing this way
	 */
	numCrossingSago2MonkeyGrass++;

  /*
   * Output the total count of liards currently crossing
   */
  int totalCrossing = numCrossingSago2MonkeyGrass + numCrossingMonkeyGrass2Sago; //SW DE
  cout << "Current total lizards crossing: " << totalCrossing << endl; // SW DE
  

	/*
     * Check for lizards cross both ways
     */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL)
    {
		cout << "\tCrash!  We have a pile-up on the concrete." << endl;
		cout << "\t" << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t" << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

    lock.unlock(); // SW DE

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

    /*
     * That one seems to have made it
     */
    lock.lock(); // SW DE
    numCrossingSago2MonkeyGrass--;
}


/**
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2MonkeyGrass(unique_lock<mutex>& lock) // SW DE
{
	/*
     * Whew, made it across
     */
	if (debug)
    {
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
    }

    lock.unlock(); // SW DE
    crossingCondition.notify_all(); // SW DE
}


/**
 * Simulate a lizard eating for a random amount of time
 *
 * Status: Completed - No need to change any of this code.
 */
void Lizard::eat()
{
	int eatSeconds;

	eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug)
    {
		cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << endl;
		cout << flush;
    }

	/*
     * Simulate eating by blocking for a few seconds
     */
	sleep( eatSeconds );

	if (debug)
    {
      cout << "[" << _id << "] finished eating" << endl;
      cout << flush;
    }
}


/**
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::monkeyGrass2SagoIsSafe(unique_lock<mutex>& lock) // SW DE
{
	if (debug)
    {
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
    }

    lock.lock(); // SW DE

    crossingCondition.wait(lock, [] { // SW DE
        return numCrossingMonkeyGrass2Sago + numCrossingSago2MonkeyGrass < MAX_LIZARD_CROSSING; // SW DE
    }); // SW DE

	if (debug)
    {
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
    }
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago(unique_lock<mutex>& lock) // SW DE
{
	if (debug)
    {
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
    }

    if (!lock.owns_lock()) { // SW DE
        cout << "ERROR: Lock not kept between method calls" << endl; // SW DE
        exit(1); // SW DE
    } // SW DE

    /*
     * One more crossing this way
     */
	numCrossingMonkeyGrass2Sago++;

  
    /*
     * Check for lizards cross both ways
     */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL)
    {
		cout << "\tOh No!, the lizards have cats all over them." << endl;
		cout << "\t " << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t " << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
    }

    lock.unlock(); // SW DE

	/*
     * It takes a while to cross, so simulate it
     */
	sleep( CROSS_SECONDS );

	/*
     * That one seems to have made it
     */
    lock.lock(); // SW DE
	numCrossingMonkeyGrass2Sago--;
}


/**
 *
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2Sago(unique_lock<mutex>& lock) // SW DE
{
	/*
     * Whew, made it across
     */
	if (debug)
    {
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
    }

    lock.unlock(); // SW DE
    crossingCondition.notify_all(); // SW DE
}

/**
  * Follows the algorithm provided in the assignment
  * description to simulate lizards crossing back and forth
  * between a sago palm and some monkey grass. 
  *  
  * @param aLizard - the lizard to be executed concurrently
  *
  * @return N/A
  
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Lizard::lizardThread(Lizard *aLizard)
{	
    unique_lock<mutex> lock(crossingMutex, defer_lock); // SW DE

	if (debug)
    {
      cout << "[" << aLizard->getId() << "] lizard is alive" << endl;
      cout << flush;
    }

	while(running)
    {
      /* 
       * Follow the algorithm given in the assignment
       * using calls to the functions declared above.
       * You'll need to complete the implementation of
       * some functions by filling in the code.  Some  
       * are already completed - see the comments.
       */
        aLizard->sleepNow(); // SW DE
        aLizard->sago2MonkeyGrassIsSafe(lock); // SW DE
        aLizard->crossSago2MonkeyGrass(lock); // SW DE
        aLizard->madeIt2MonkeyGrass(lock); // SW DE
        aLizard->eat(); // SW DE
        aLizard->monkeyGrass2SagoIsSafe(lock); // SW DE
        aLizard->crossMonkeyGrass2Sago(lock); // SW DE
        aLizard->madeIt2Sago(lock); // SW DE
    }

}
 



/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv)
{
	/*
	 * Declare local variables
     */




	/*
     * Check for the debugging flag (-d)
     */
	debug = 0;
	if (argc > 1)
		if (strncmp(argv[1], "-d", 2) == 0)
			debug = 1;


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
	vector<Cat*> allCats; // SW DE
    for (int i=0; i < NUM_CATS; i++) { // SW DE
        allCats.push_back(new Cat(i)); // SW DE
    } // SW DE

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */
    for (int i=0; i < NUM_LIZARDS; i++) {
        allLizards[i]->run();
    }
    for (int i = 0; i < NUM_CATS; ++i) { // SW DE
        allCats[i]->run(); // SW DE
    } // SW DE

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
    for (int i = 0; i < NUM_LIZARDS; ++i) { // SW DE
        allLizards[i]->wait(); // SW DE
    } // SW DE
    for (int i = 0; i < NUM_CATS; ++i) { // SW DE
        allCats[i]->wait(); // SW DE
    } // SW DE


	/*
     * Delete the locks and semaphores
     */
	 
	 
	 
	/*
	 * Delete all cat and lizard objects
	 */
    for (int i = 0; i < NUM_LIZARDS; ++i) { // SW DE
        delete allLizards[i]; // SW DE
        allLizards[i] = nullptr; // SW DE
    } // SW DE
    for (int i = 0; i < NUM_CATS; ++i) { // SW DE
        delete allCats[i]; // SW DE
        allLizards[i] = nullptr; // SW DE
    } // SW DE


	/*
     * Exit happily
     */
	return 0;
}






