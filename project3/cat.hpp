#ifndef CAT_HPP
#define CAT_HPP

#include <thread>
using namespace std;

/**
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	public:
        /**
        * Constructs a cat.
        *
        * @param id - the Id of the cat 
        */
		Cat (int id);

        /**
        * Returns the Id of the cat.
        *
        * @return the Id of a cat
        */
		int getId();

        /**
        * Launches a cat thread.
        */
		void run();

        /**
        * Waits for a cat to finish running.
        */
		void wait();
    
    private:
        int       _id;        // the Id of the cat
	    thread*   _catThread; // the thread simulating the cat

        /**
        * Simulate a cat sleeping for a random amount of time
        */
		void sleepNow();

        /**
        * This simulates a cat that is sleeping and occasionally checking on
        * the driveway on lizards.
        * 
        * @param aCat - a cat that is being run concurrently
        */
        static void catThread (Cat *aCat); 
};

#endif