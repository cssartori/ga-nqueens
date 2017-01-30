/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#ifndef __GENETIC_ALGORITHM_H
#define __GENETIC_ALGORITHM_H

#include <random>
#include "queenarray.hpp"
#include <vector>
 
/*Class to implement the Genetic Algorithm procedures*/
class GeneticAlgorithm{
private:
	int randSeed; /*Seed used for random number generation*/
	int size_n;	/*The problem size N*/
	int populationSize; /*Population size*/
	int tournamentSize; /*Size of the tournament*/
	double crossp; 	/*crossover probability*/
	double mutp;	/*mutation probability*/  
	int maxIterations; /*max iterations of the algorithm*/
	int initialFitness; /*fitness of the initial best array*/
	int iterationsRan; /*number of iterations the algorithm has run to find the solution*/
	QueenArray bestArray; /*best array found by the algorithm*/
	std::default_random_engine *generator; /*Random number generator engine*/
	std::uniform_real_distribution<double> randomp; /*Random probability generator*/



	/*Runs a tournament of size k to select a queen array*/
	QueenArray tournament(std::vector<QueenArray> population, int k);
	
	/*Makes the crossover between parent 1 and parent 2, given the crossover probability. If crossover does not occur, the "childs" returned
  	  are parent 1 and parent 2*/
	std::vector<QueenArray> crossover(QueenArray parent1, QueenArray parent2);


	/*
		Makes a mutation in queen array q given the mutation probability. If mutation does not occur, the same q is returned.
		Two types of mutations used:
	*/
	/*Select two random positions in the queen array and exchange its values*/
	QueenArray mutationExchange(QueenArray q);
	/*Selects one random position in the queen array and generates a new random value for this position*/
	QueenArray mutationFlip(QueenArray q);

public:
	/*Constructor*/
	GeneticAlgorithm(int size_n, int populationSize, int maxIterations, int tournamentSize, double crossp, double mutp, int randSeed);
	/*Run the genetic algorithm returning the best queen array it could find*/
	QueenArray run();
	/*Returns the number of iterations the algorithm has run to find the solution*/
	int getIterationsRan();
	/*Returns the fitness of the first best solution*/
	int getInitialFitness();
	/*Returns the best solution found by the algorithm*/
	QueenArray getBestArray();

};


 #endif