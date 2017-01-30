/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#include "../include/queenarray.hpp"
#include "../include/geneticalgorithm.hpp"
#include <iostream>

using namespace std;

int randSeed = 1;
int populationSize = 200;
int NQueens = 1;
int maxIterations = 200000;
int torunamentSize = 4;
double crossp = 0.7;
double mutp = 0.1;

/*Reads the parameter for the problem*/
void readParameter(int argc, char **argv);


int main(int argc, char **argv){

	readParameter(argc, argv);

	/*Creates the Genetic Algorithm object to run*/
	GeneticAlgorithm ga(NQueens, populationSize, maxIterations, torunamentSize, crossp, mutp, randSeed);

	time_t startTtime;
	time_t endTime;

	time(&startTtime); /*Get time of start*/

	/*Run the GA, returning the best solution found with the given parameters*/
	QueenArray best = ga.run();

	time(&endTime); /*Time of end*/

	cout << "N = " << NQueens << endl << "F(s*) = " << best.getFitness() << endl << "Iterations = "<< ga.getIterationsRan() << endl << "Time(s) = " << difftime(endTime, startTtime) << endl;
		
	/*Uncomment line below if want to print the best solution found*/
	//best.print();

	return 0;

}


/*Reads the parameter for the problem*/
void readParameter(int argc, char **argv){

	if(argc < 3){
		cout << "Usage:\n" << argv[0] << " -n [N-Queens]" << endl;
		exit(-1);
	}

	int i=1;
	if(argv[i][0] != '-'){
		cout << "Parameter " << argv[i] << "not defined." << endl;
		exit(-1);
	}else if(argv[i][1] != 'n'){
		cout << "Expected first parameter -n [N-Queens], found " << argv[i] << "." << endl;
		exit(-1);
	}
	i++;
	NQueens = atoi(argv[i]); //reads number of queens in the problem

	for(i=3;i<argc;i++){
		if(argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'p'://population size
					i++;
					populationSize = atoi(argv[i]);
					break;
				case 's'://random seed
					i++;
					randSeed = atoi(argv[i]);
					break;
				case 'i'://max iterations
					i++;
					maxIterations = atoi(argv[i]);
					break;
				case 'c'://crossover probability
					i++;
					crossp = atof(argv[i]);
					break;
				case 'm'://mutation probability
					i++;
					mutp = atof(argv[i]);
					break;
				case 'k'://tournament size
					i++;
					torunamentSize = atoi(argv[i]);
					break;
				default:
					cout << "Parameter " << argv[i] << "not defined." << endl;
					exit(-1);
			}
		}else{
			cout << "Parameter " << argv[i] << "not defined." << endl;
			exit(-1);
		}
	}
}