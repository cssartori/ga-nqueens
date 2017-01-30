/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#include "../include/objectivefunction.hpp"
#include <cstdlib>
#include <iostream>

/*Constructor*/
ObjectiveFunction::ObjectiveFunction(int n){
	this->size_n = n;
}

/*Checks for diagonal conflicts between two queens*/
bool ObjectiveFunction::diagonalConflict(int c1, int r1, int c2, int r2){
	if(abs(c1-c2) == abs(r1-r2))
		return true;

	return false;
}

/*Checks for row conflicts between two queens*/
bool ObjectiveFunction::rowConflict(int r1, int r2){
	if(r1 == r2)
		return true;

	return false;
}

/*Evaluates the queen array returnting its fitness*/
int ObjectiveFunction::evaluateQueenArray(QueenArray q){
	int conflicts = 0;
	/*For each queen in the array*/
	for(int i=0;i<q.size();i++){
		/*For each other queen, checks if there is a conflict*/
		for(int j=i+1;j<q.size();j++){
			/*Checks if there is any conflict*/
			if(diagonalConflict(i, q[i], j, q[j]) || rowConflict(q[i], q[j])){
				conflicts++; /*Update the conflict counter if positive*/
			}
		}
	}

	return conflicts;
}

