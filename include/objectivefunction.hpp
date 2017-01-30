/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#ifndef __OBJECTIVE_FUNCTION_H
#define __OBJECTIVE_FUNCTION_H

#include "queenarray.hpp"

/*Class to evaluate a queen array, returning its fitness (i.e, how good is the array. Small values are better, 0 is the best)*/
class ObjectiveFunction {
private:
	/*The size N of the problem*/
	int size_n;

	/*Checks for diagonal conflicts between two queens*/
	bool diagonalConflict(int c1, int r1, int c2, int r2);
	/*Checks for row conflicts between two queens*/
	bool rowConflict(int r1, int r2);

public:
	/*Constructor*/
	ObjectiveFunction(int n);
	/*Evaluates the queen array returnting its fitness*/
	int evaluateQueenArray(QueenArray q);



};

#endif