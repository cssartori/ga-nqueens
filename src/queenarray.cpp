/* Genetic ALgorithm for the N-Queens Problem
 * Developed by:
 * Carlo Sulzbach Sartori
 * Project done for "INF01037-Evolutionary Computing"
 * 2016 - UFRGS
 */
#include "../include/queenarray.hpp"
#include "../include/constants.hpp"
#include <iostream>

/*Creates a basic queen array with no size*/
QueenArray::QueenArray(){

}

/*Creates a basic queen array filled with no specific positions*/
QueenArray::QueenArray(int n){
	this->position.resize(n, NO_POSITION);
	this->size_n = n;
	this->fitness = n*n+1;
}

/*Creates a queen array merging two vectors v1 and v2*/
QueenArray::QueenArray(std::vector<int> v1, std::vector<int> v2){
	this->position.resize(v1.size() + v2.size(), NO_POSITION);
	this->size_n = v1.size() + v2.size();
	for(unsigned int i=0;i<v1.size();i++){
		this->position[i] = v1[i];
	}for(unsigned int i=0;i<v2.size();i++){
		this->position[i+v1.size()] = v2[i];
	}
}

/*Access element in poisition i. Out of range elements generate undefined behaviour*/
int& QueenArray::operator[](int i){
	return this->position[i];
}

/*Splits the queen array into 2 arrays. First from position 0 to index (included), the second from index+1 to N.*/
std::vector< std::vector<int> > QueenArray::splitOn(int index){
	std::vector< std::vector<int> > split;
	std::vector<int> v1;
	std::vector<int> v2;
	for(int i=0;i<this->size_n;i++){
		if(i <= index)
			v1.push_back(this->position[i]);
		else
			v2.push_back(this->position[i]);
	}
	split.push_back(v1);
	split.push_back(v2);
	return split;
}

/*Returns the size of the queen array*/
int QueenArray::size(){
	return this->size_n;
}

/*Checks if two queen arrays are equal*/
bool QueenArray::operator==(QueenArray q){
	if(q.size() != this->size_n)
		return false;

	for(int i=0;i<this->size_n;i++)
		if(this->position[i] != q[i])
			return false;

	return true;
}

/*Sets the fitness of this queen array*/
void QueenArray::setFitness(int f){
	this->fitness = f;
}

/*Returns the fitness of this queen array*/
int QueenArray::getFitness(){
	return this->fitness;
}

/*Prints the queen array specified*/
void QueenArray::print(){
	for(int i=0;i<this->size_n;i++){
		for(int j=0;j<this->size_n;j++){
			if(this->position[j] == i)
				std::cout << "1" << " ";
			else
				std::cout << "0" << " ";
		}
		std::cout << std::endl;
	}
}