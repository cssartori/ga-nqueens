/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#include "../include/geneticalgorithm.hpp"
#include "../include/populationcreator.hpp"
#include "../include/objectivefunction.hpp"
#include "../include/constants.hpp"
#include <algorithm>
#include <iostream>

bool compareQueenArray(QueenArray q1, QueenArray q2);

/*Constructor*/
GeneticAlgorithm::GeneticAlgorithm(int size_n, int populationSize, int maxIterations, int tournamentSize, double crossp, double mutp, int randSeed){
	this->size_n = size_n;
	this->populationSize = populationSize;
	this->maxIterations = maxIterations;
	this->tournamentSize = tournamentSize;
	this->crossp = crossp;
	this->mutp = mutp;
	this->randSeed = randSeed;

	this->generator = new std::default_random_engine(randSeed);
	this->randomp = std::uniform_real_distribution<double>(0,1);

}


/*Run the genetic algorithm returning the best queen array it could find*/
QueenArray GeneticAlgorithm::run(){
	/*Creates initial population*/
	PopulationCreator populator(this->populationSize, this->size_n, *(this->generator));
	std::vector<QueenArray> population = populator.createRandomPopulation();

	/*Sort in increasing order of fitness (the first individual is the best so far)*/
	std::sort(std::begin(population), std::end(population), compareQueenArray);

	/*Best individual of the population is the first one*/
	this->bestArray = population[0];
	this->initialFitness = this->bestArray.getFitness();

	ObjectiveFunction evaluator(this->size_n);

	bool solutionFound = false;
	/*If the best solution generated randomly is already a valid solution, just return it*/
	if(this->bestArray.getFitness() == 0)
		solutionFound = true;

	int iterations = 0;

	/*While no solution was found and the algorithm has run for fewer iterations than the maximum*/
	while(iterations < this->maxIterations && !solutionFound){
		/*Vector of childs*/
		std::vector<QueenArray> childs;

		/*Generates N childs*/
		while((int)childs.size() < this->populationSize){
			/*Select two parents*/
			QueenArray parent1 = tournament(population, this->tournamentSize);
			QueenArray parent2 = tournament(population, this->tournamentSize);

			/*Crossover of parents 1 and 2 to create two new individuals*/			
			std::vector<QueenArray> c = crossover(parent1, parent2);

			/*Mutation of the childs*/
			c[0] = mutationExchange(c[0]);
			c[0] = mutationFlip(c[0]);

			c[1] = mutationExchange(c[1]);
			c[1] = mutationFlip(c[1]);

			/*Evaluate each new child*/
			c[0].setFitness(evaluator.evaluateQueenArray(c[0]));
			c[1].setFitness(evaluator.evaluateQueenArray(c[1]));

			/*Add new childs to the childs array*/
			childs.push_back(c[0]);
			childs.push_back(c[1]);
		}

		/*Sort the childs array in increasing order*/
		std::sort(std::begin(childs), std::end(childs), compareQueenArray);

		/*Checks if the best child is better than the best array so far*/
		if(childs[0].getFitness() < this->bestArray.getFitness()){
			/*If it is, update the best array*/
			this->bestArray = childs[0];
			if(this->bestArray.getFitness() == 0)/*checks if the new best array is not a solution already*/
				solutionFound = true;
		}

		/*Number of childs to be used in the new population*/
		int nChilds = this->populationSize*0.5;

		/*Update the population with nChilds new individuals (replacing the worst)*/
		for(int i=0;i<nChilds;i++){
			population[this->populationSize-1-i] = childs[i];
		}
		
		//std::cout << "Iterations " << iterations << " | " << this->bestArray.getFitness() << std::endl;
		/*Sort in increasing order of fitness (the first individual is the best so far)*/
		std::sort(std::begin(population), std::end(population), compareQueenArray);

		/*Update the iteration counter*/
		iterations++;
	}

	this->iterationsRan = iterations;

	return bestArray;
}

bool compareQueenArray(QueenArray q1, QueenArray q2){
	return (q1.getFitness() < q2.getFitness());
}

/*Makes a mutation in queen array q given the mutation probability. If mutation does not occur, the same q is returned.*/
QueenArray GeneticAlgorithm::mutationExchange(QueenArray q){
	double mp = this->randomp(*(this->generator)); /*generates random probability*/

	if(mp <= this->mutp){
		/*Generates a random position*/
		std::uniform_int_distribution<int> random(0, this->size_n-1);
		int p1 = random(*(this->generator));
		int p2 = random(*(this->generator));

		int temp = q[p1];
		q[p1] = q[p2];
		q[p2] = temp;
	}

	return q;
}

QueenArray GeneticAlgorithm::mutationFlip(QueenArray q){
	double mp = this->randomp(*(this->generator)); /*generates random probability*/

	if(mp <= this->mutp){
		/*Generates a random queen*/
		std::uniform_int_distribution<int> random(0, this->size_n-1);
		int rq = random(*(this->generator));
		int rp = random(*(this->generator));
		q[rq] = rp;	
	}

	return q;
}



/*Makes the crossover between parent 1 and parent 2, given the crossover probability. If crossover does not occur, the "childs" returned
  are parent 1 and parent 2*/
std::vector<QueenArray> GeneticAlgorithm::crossover(QueenArray parent1, QueenArray parent2){
	/*Generates random split point. It only makes sense to split a queen array after the first position (0) and before the last position(n-1).*/
	std::uniform_int_distribution<int> random(1, this->size_n-2); 

	std::vector<QueenArray> childs;
	double cp = this->randomp(*(this->generator)); /*generates random probability*/

	if(cp <= this->crossp){ /*If the random probability is smaller than the crossover probability, crossover happens*/
		int splitPoint = random(*(this->generator));
		std::vector< std::vector<int> > split1 = parent1.splitOn(splitPoint);
		std::vector< std::vector<int> > split2 = parent2.splitOn(splitPoint);
		QueenArray child1(split1[0], split2[1]);
		QueenArray child2(split1[1], split2[0]);
		childs.push_back(child1);
		childs.push_back(child2);
	}else{
		childs.push_back(parent1);
		childs.push_back(parent2);
	}

	return childs;
}


/*Runs a tournament of size k to select a queen array*/
QueenArray GeneticAlgorithm::tournament(std::vector<QueenArray> population, int k){
	std::uniform_int_distribution<int> random(0, this->populationSize-1);

	int r = random(*(this->generator));
	QueenArray winner = population[r];

	for(int i=1;i<k;i++){
		r = random(*(this->generator));
		if(winner.getFitness() > population[r].getFitness())
			winner = population[r];
	}
	
	return winner;
}

/*Returns the number of iterations the algorithm has run to find the solution*/
int GeneticAlgorithm::getIterationsRan(){
	return this->iterationsRan;
}

/*Returns the fitness of the first best solution*/
int GeneticAlgorithm::getInitialFitness(){
	return this->initialFitness;
}

/*Returns the best solution found by the algorithm*/
QueenArray GeneticAlgorithm::getBestArray(){
	return this->bestArray;
}