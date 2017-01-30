/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#ifndef __QUEEN_ARRAY_H
#define __QUEEN_ARRAY_H

#include <vector>

/*
	Class that describes the positions of N queens in a NxN chess Board.
	For N=8, we have the following representation:
	|2|4|7|0|5|1|6|3|		-> this is a QueenArray
	Which means that the first queen is at column 0 and row 2. The second queen is at column 1 and row 4.
	In the board, it would be like:

	0 0 0 1 0 0 0 0
	0 0 0 0 0 1 0 0
	1 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 1
	0 1 0 0 0 0 0 0
	0 0 0 0 1 0 0 0
	0 0 0 0 0 0 1 0
	0 0 1 0 0 0 0 0

	0's are empty spaces and 1's are queens.

*/
class QueenArray {
private:
	/*Each queen has its own colums and cannot change it. Each position is the row in which the ith queen is.*/
	std::vector<int> position; /*N positions, one for each queen/column*/
	int size_n;	/*The size N of the problem*/
	int fitness; /*The fitness, i.e. how good is this solution (small values are better, 0 is the best)*/

public:
	/*Creates a basic queen array with no size*/
	QueenArray();
	/*Creates a basic queen array filled with no specific positions*/
	QueenArray(int n);
	/*Creates a queen array merging two vectors v1 and v2*/
	QueenArray(std::vector<int> v1, std::vector<int> v2);
	/*Access element in poisition i. Out of range elements generate undefined behaviour*/
	int& operator[](int i);
	/*Splits the queen array into 2 arrays. First from position 0 to index (included), the second from index+1 to N.*/
	std::vector< std::vector<int> > splitOn(int index);
	/*Checks if two queen arrays are equal*/
	bool operator==(QueenArray q);
	/*Returns the size of the queen array*/
	int size();
	/*Sets the fitness of this queen array*/
	void setFitness(int f);
	/*Returns the fitness of this queen array*/
	int getFitness();
	/*Prints the queen array specified*/
	void print();

};

#endif