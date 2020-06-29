#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#define NULL nullptr
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30; // Bricks LEGO
const int CAPACITY = 1200; // Budget
const int POP_SIZE = 20; // Maximum population
const int VALUE[GENE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
						 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
						 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}; // Values for each LEGO bricks
const float PRICE[GENE] = { 0.11, 0.13, 0.15, 0.17, 0.19, 0.21, 0.23, 0.25, 0.27, 0.29,
						 0.31, 0.33, 0.35, 0.37, 0.39, 0.41, 0.43, 0.45, 0.47, 0.49,
						 0.51, 0.53, 0.55, 0.57, 0.59, 0.61, 0.63, 0.65, 0.67, 0.69 }; // Prices for each LEGO bricks
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
			randNum = rand() % 100;
			chromosome[c][i] = randNum;
		}
	}
}


void evaluateChromosome() {
	float eachChromosome = 0.0, eachBricks = 0.0;
	for (int c = 0; c < POP_SIZE; c++) {
		eachChromosome = 0.0;
		for (int i = 0; i < GENE; i++) {
			eachBricks = 0.0;
			eachBricks = chromosome[c][i] * PRICE[i];
			eachChromosome = eachBricks + eachChromosome;
		}
		fitness[c] = eachChromosome / (float)CAPACITY;
		cout << "\tC" << c << "\tDifference\t" << eachChromosome << "\tFV\t" << fitness[c] << endl;
	}

}


void printChromosome() {
	for (int c = 0; c < POP_SIZE; c++) {
		cout << "\tC" << c << "\t";
		for (int i = 0; i < GENE; i++) {
			cout << chromosome[c][i] << " ";
		}
		cout << endl;
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


			if (fitness[player1] >= fitness[player2]) {
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


int main() {
	cout << "\nGA START! \n";

	cout << "\nINITIALIZATION... \n";
	initializePopulation();
	printChromosome();
	getchar();

	cout << "\EVALUATING... \n";
	evaluateChromosome();
	getchar();

	cout << "\SELECTING... \n";
	parentSelection();
	getchar();

	return 0;
}