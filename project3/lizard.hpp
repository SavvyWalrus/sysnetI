#ifndef LIZARD_HPP
#define LIZARD_HPP

#include <thread>
using namespace std;

class Lizard {
	int     _id;      // the Id of the lizard
	thread* _aLizard; // the thread simulating the lizard

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
        * 
        * Status: Incomplete - Make changes to this code.
        */
        void run();

        /**
        * Waits for a lizard to finish running.
        *
        * Status: Incomplete - Make changes to this code.
        */
        void wait();

    private:
        /**
        * Returns when it is safe for this lizard to cross from the sago
        * to the monkey grass.   Should use some synchronization 
        * facilities (lock/semaphore) here.
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void sago2MonkeyGrassIsSafe();

        /**
        * Delays for 1 second to simulate crossing from the sago to
        * the monkey grass. 
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void crossSago2MonkeyGrass();

        /**
        * Tells others they can go now
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void madeIt2MonkeyGrass();

        /**
        * Simulate a lizard eating for a random amount of time
        *
        * Status: Completed - No need to change any of this code.
        */
		void eat();

        /**
        * Returns when it is safe for this lizard to cross from the monkey
        * grass to the sago.   Should use some synchronization 
        * facilities (lock/semaphore) here.
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void monkeyGrass2SagoIsSafe();

        /**
        * Delays for 1 second to simulate crossing from the monkey
        * grass to the sago. 
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void crossMonkeyGrass2Sago();

        /**
        * Tells others they can go now
        *
        * Status: Incomplete - Make changes as you see are necessary.
        */
		void madeIt2Sago();

        /**
        * Simulate a lizard sleeping for a random amount of time
        *
        * Status: Completed - No need to change any of this code.
        */
		void sleepNow();

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
        static void lizardThread(Lizard *aLizard);
};

#endif