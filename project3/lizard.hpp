#ifndef LIZARD_HPP
#define LIZARD_HPP

#include <thread>
#include <mutex>
using namespace std;

class Lizard {
	public:
        /**
        * Constructs a lizard.
        *
        * @param id - the Id of the lizard 
        */
		Lizard(int id);

        /**
        * Returns the Id of the lizard.
        *
        * @return the Id of a lizard
        */
		int getId();

        /**
        * Launches a lizard thread.
        */
        void run();

        /**
        * Waits for a lizard to finish running.
        */
        void wait();

    private:
        int     _id;      // the Id of the lizard
	    thread* _aLizard; // the thread simulating the lizard

        /**
        * Returns when it is safe for this lizard to cross from the sago
        * to the monkey grass.   Should use some synchronization 
        * facilities (lock/semaphore) here.
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void sago2MonkeyGrassIsSafe(unique_lock<mutex>& lock); // SW

        /**
        * Delays for 1 second to simulate crossing from the sago to
        * the monkey grass. 
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void crossSago2MonkeyGrass(unique_lock<mutex>& lock); // SW

        /**
        * Tells others they can go now
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void madeIt2MonkeyGrass(unique_lock<mutex>& lock); // SW

        /**
        * Simulate a lizard eating for a random amount of time
        */
		void eat();

        /**
        * Returns when it is safe for this lizard to cross from the monkey
        * grass to the sago.   Should use some synchronization 
        * facilities (lock/semaphore) here.
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void monkeyGrass2SagoIsSafe(unique_lock<mutex>& lock); // SW

        /**
        * Delays for 1 second to simulate crossing from the monkey
        * grass to the sago. 
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void crossMonkeyGrass2Sago(unique_lock<mutex>& lock); // SW

        /**
        * Tells others they can go now
        *
        * @param lock - The mutex needed to manage crossing variables race conditions
        */
		void madeIt2Sago(unique_lock<mutex>& lock); // SW

        /**
        * Simulate a lizard sleeping for a random amount of time
        */
		void sleepNow();

        /**
        * Follows the algorithm provided in the assignment
        * description to simulate lizards crossing back and forth
        * between a sago palm and some monkey grass. 
        *  
        * @param aLizard - the lizard to be executed concurrently
        */
        static void lizardThread(Lizard *aLizard); // SW
};

#endif