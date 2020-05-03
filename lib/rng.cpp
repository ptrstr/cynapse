#include "rng.hpp"
#include <cstdlib>
#include <ctime>
RNG rng;

RNG::RNG(unsigned seed) {
	if (seed == 0)
		this->seed = time(NULL);
	else
		this->seed = seed;

	srand(this->seed);
}

unsigned RNG::getSeed() {
	return this->seed;
}

void RNG::setSeed(unsigned newSeed) {
	this->seed = newSeed;
}

double RNG::genRange(double min, double max) {
	double diff = max - min;
	return (((double)rand() / (double)(RAND_MAX)) * diff) - min;
}
