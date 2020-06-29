#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30; // Bricks LEGO
const int CAPACITY = 104; // Budget
const int POP_SIZE = 10; // Maximum population
const int WEIGHT[GENE] = { 25, 35, 45, 5, 25, 3, 2, 2 }; // Value for each LEGO bricks
const float CO_probability = 0.9; // Parameter 1
const float MUT_PROBABILITY = 0.9; // Parameter 2

// Chromosome representation
int chromosome[POP_SIZE][GENE];

// Fitness value
double fitness[POP_SIZE];

//declare parents data str
int parents[2][GENE];

//declre children data str
int children[2][GENE];

void initializePopulation() {
	int randNum;
	//initialize random seed
	srand(time(NULL));
	for (int c = 0; c < POP_SIZE; c++) {
		for (int i = 0; i < GENE; i++) {
			randNum = rand() % 2;
			chromosome[c][i] = randNum;
		}
	}
}

/*
rand(): Returns a pseudo-random integral number in the range between 0 and RAND_MAX.
RAND_MAX: This value is library-dependent, but is guaranteed to be at least 32767 on any standard library implementation.
example:
v1 = rand() % 100;         // v1 in the range 0 to 99
v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014
*/
void printChromosome() {
	for (int c = 0; c < POP_SIZE; c++) {
		cout << "\tC" << c << "\t";
		for (int i = 0; i < GENE; i++) {
			cout << chromosome[c][i] << " ";
		}
		cout << endl;
	}
}
void evaluateChromosome() {
	int accumulatedWeight = 0;
	for (int c = 0; c < POP_SIZE; c++) {
		accumulatedWeight = 0;
		for (int i = 0; i < GENE; i++) {
			if (chromosome[c][i] == 1) {
				accumulatedWeight = accumulatedWeight + WEIGHT[i];
			}
		}
		fitness[c] = abs(CAPACITY - accumulatedWeight) / (float)CAPACITY;
		cout << "\tC" << c << "\tDifference\t" << abs(CAPACITY - accumulatedWeight) << "\tFV\t" << fitness[c] << endl;
	}

}

void parentSelection() {
	int player1, player2;
	int indexParents[2];

	do {
		for (int p = 0; p < 2; p++) { //tournament selection
			player1 = rand() % POP_SIZE;
			do {
				player2 = rand() % POP_SIZE;
			} while (player1 == player2);


			if (fitness[player1] <= fitness[player2]) {
				indexParents[p] = player1;
			}
			else {
				indexParents[p] = player2;
			}

			cout << "\n\t Players: " << player1 << " VS " << player2;
			cout << "\n\t Fitness: " << fitness[player1] << " VS " << fitness[player2];
			cout << "\n\t Winner: " << indexParents[p];
		}//end of tournament
	} while (indexParents[0] == indexParents[1]);

	for (int p = 0; p < 2; p++) {
		cout << "\n\t Parents " << p + 1 << " : ";

		for (int g = 0; g < GENE; g++) {
			parents[p][g] = chromosome[indexParents[p]][g];
			cout << parents[p][g] << " ";
		}
	}
}

void crossOver() {
	float prob = 0.0;
	int co_point;

	for (int p = 0; p < 2; p++) {//Copy parents to children
		for (int g = 0; g < GENE; g++) {
			children[p][g] = parents[p][g];
		}
	}

	//generate 0-1
	prob = ((rand() % 10) + 1) / 10.0;
	if (prob < CO_probability) {//crossover happen
		co_point = rand() % GENE;
		cout << "\n\t Children crossover at " << co_point;

		for (int g = co_point; g < GENE; g++) {
			children[0][g] = parents[1][g];
			children[1][g] = parents[0][g];
		}
	}
	else {//crossover did not crossover
		cout << "\n\t Crossover did not happen ";
	}

	//output

	for (int c = 0; c < 2; c++) {
		cout << "\n\t Children " << c + 1;

		for (int g = 0; g < GENE; g++) {
			cout << children[c][g] << " ";
		}
	}
}

void mutation() {
	float prob;
	int mut_point;
	for (int c = 0; c < 2; c++) {
		prob = (rand() % 11) / 10.0; // generating the probability value
		if (prob < MUT_PROBABILITY) {
			mut_point = rand() % GENE;
			cout << "\n\t Mutation at gene = " << mut_point;
			if (children[c][mut_point] == 0)
				children[c][mut_point] = 1;
			else
				children[c][mut_point] = 0;
		}
		else {
			cout << "\n\t mutation not happen";
		}
	}//End of For
	for (int c = 0; c < 2; c++) {
		cout << "\n\t Children " << c + 1 << " after mutation ";
		for (int g = 0; g < GENE; g++) {
			cout << children[c][g] << " ";
		}
	}
}

int main() {
	cout << "\nGA START! \n";
	cout << "First generation \n\n";
	cout << "\nINITIALIZATION... \n";

	//LAB 3
	initializePopulation();
	getchar();

	//LAB 3
	cout << "\nPRINT INITIAL POPULATION \n";
	printChromosome();
	getchar();

	//LAB 4
	cout << "\nEVALUATE CHROMOSOME \n";
	evaluateChromosome();
	getchar();

	//LAB 5
	cout << "\nPARENT SELECTION \n";
	parentSelection();
	getchar();

	//LAB 6
	cout << "\nCROSSOVER \n";
	crossOver();
	getchar();

	//LAB 7
	cout << "\nMUTATION \n";
	mutation();
	getchar();
}