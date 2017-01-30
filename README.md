# **Genetic Algorithm Applied to the N-Queens Problem** #

Application of the Genetic Algorithm to solve the N-Queens problem. 

It uses the basic GA, with the following configuration:

* Tournament Selection to choose the parents of the next generation;
* One-point crossover generating two children from two parents;
* Two mutation operators (swap and flip);
* The 50% worst individuals from the current population are replaced by the 50% best individuals of the new population;
* The first solution found is returned.

A table with results is presented under *results*. The program works even for big values of N, such as 100. The maximum N tested was 150.
Implemented in C++11.

Done for the "INF01037-Evolutionary Computing" discipline, 2016, at UFRGS.