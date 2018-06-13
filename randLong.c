
#include "passwordManager.h"

long randLong(const long max) {

	//if the maximum allowed value is the same as RAND_MAX
	if (max-1 == RAND_MAX)

		//return a random number in the range [0,max)
		return rand();

	else {

		//max must be less than RAND_MAX otherwise this won't work
		assert(max < RAND_MAX);

		//integer division will make sure their is even distribution of the numbers
		long maxValid = RAND_MAX / max;
		//maxValid must be greater than 0
		assert(maxValid > 0);

		//this is the actual maximum
		maxValid *= max;

		//variable for the randomly generated number to be stored into
		long num;
		//while num is not valid, continue to regenerate it a new value
		while ( (num=rand()) >= maxValid );

		//return a number that is in the range [0,max)
		return num % max;

	}

}