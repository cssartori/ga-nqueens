/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#include "../include/populationcreator.hpp"
#include "../include/objectivefunction.hpp"

/*Constructor*/
PopulationCreator::PopulationCreator(int popSize, int n, std::default_random_engine generator){
	this->popSize = popSize;
	this->size_n = n;
	this->generator = generator;
	this->rand = new std::uniform_int_distribution<int>(0, n-1);
}

/*Creates a completely random population*/
std::vector<QueenArray> PopulationCreator::createRandomPopulation(){
	/*Vector to store the arrays*/
	std::vector<QueenArray> population;
	/*Evaluator to calculate the fitness of each new array*/
	ObjectiveFunction of(this->size_n);

	/*While the number of arrays is not equal the population size*/
	for(int i=0;i<this->popSize;i++){
		/*Vector to avoid placing two queens in the same position. N array indicating wheter a 
		  row already has a queen or not (avoid row conflicts)*/
		std::vector<bool> placeUsed(this->size_n, false);
		/*The new queen array */
		QueenArray queens(this->size_n);

		/*For each queen in the array*/
		for(int q=0;q<this->size_n;q++){
			/*generate a new random position for the qth queen*/
			int place = (*this->rand)(generator);
			queens[q] = place;
		}
		/*Evaluate the array*/
		queens.setFitness(of.evaluateQueenArray(queens));
		/*Insert in the population*/
		population.push_back(queens);
	}
	return population;
}