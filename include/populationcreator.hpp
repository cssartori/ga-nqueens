/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#ifndef __POPULATION_CREATOR_H
#define __POPULATION_CREATOR_H

#include "queenarray.hpp"
#include <random>
#include <vector>

/*Class to create populations of queen arrays by different methods.*/
class PopulationCreator {
private:
	/*Number of arrays to be created*/
	int popSize;
	/*The size N of the problem*/
	int size_n;

	/*Variables of the random number generator*/
	std::default_random_engine generator;
	std::uniform_int_distribution<int> *rand;

public:
	/*Constructor*/
	PopulationCreator(int popSize, int n, std::default_random_engine generator);
	/*Creates a completely random population*/
	std::vector<QueenArray> createRandomPopulation();

};

#endif