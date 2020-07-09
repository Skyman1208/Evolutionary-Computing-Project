#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#define NULL nullptr
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30; // Bricks LEGO
const int CAPACITY = 1200; // Budget
const int POP_SIZE = 30; // Maximum population
const float MUT_PROBABILITY = 0.3;
const float CO_probability = 0.8;
double bestFitness = 99.9;
double avgFitness = 0.0;
const int MAX_GENERATION = 10;
int bestChromosome[GENE];

const int VALUE[GENE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
						 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
						 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 }; // Values for each LEGO bricks
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
//declare chromosomes data structure = buffer
int newChromosome[POP_SIZE][GENE];
//declare the new hromosome counter
int newChromoCounter = 0;




void initializePopulation() {
	int randNum;
	//initialize random seed
	srand(time(NULL));
	for (int c = 0; c < POP_SIZE; c++) {
		for (int i = 0; i < GENE; i++) {
			randNum = rand() % 150;
			chromosome[c][i] = randNum;
		}
	}
	cout << endl;
}


void evaluateChromosome() {
	float totalPrice = 0.0, totalBricks = 0.0;
	for (int c = 0; c < POP_SIZE; c++) {
		totalPrice = 0.0;
		for (int i = 0; i < GENE; i++) {
			totalBricks = 0.0;
			totalBricks = chromosome[c][i] * PRICE[i];
			totalPrice = totalBricks + totalPrice;
		}
		float X = 1 - (abs((float)CAPACITY - totalPrice) / (float)CAPACITY);
		float Y = totalBricks / (150 * 30);
		fitness[c] = (X + Y) / 2;
		cout << "\tC" << c << "\tDifference\t" << totalPrice << "\tFV\t" << fitness[c] << endl;
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

			if (fitness[player1] > 1) {
				indexParents[p] = player2;
			}

			if (fitness[player2] > 1) {
				indexParents[p] = player1;
			}

			if (fitness[player1] <= 1 && fitness[player2] <= 1) {
				if (fitness[player1] <= fitness[player2]) {
					indexParents[p] = player1;
				}
				else {
					indexParents[p] = player2;
				}
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
	cout << endl;
}


void crossover()
{
	float prob;
	int co_point;
	int co_point1;
	for (int p = 0; p < 2; p++)
	{
		for (int g = 0; g < GENE; g++)
		{
			children[p][g] = parents[p][g];
		}
	}
	prob = (((rand() % 10) + 1) / 10.0);
	if (prob < CO_probability)
	{
		co_point = rand() % GENE;
		co_point1 = rand() % GENE;
		if (co_point < co_point1)
		{
			cout << "\n\t Children crossover at " << co_point;
			cout << "\n\t Children crossover at " << co_point1;
			cout << endl;
			for (int g = co_point; g < GENE; g++)
			{
				children[0][g] = parents[1][g];
				children[1][g] = parents[0][g];
			}
			for (int g = co_point1 - 1; g < GENE; g++)
			{
				children[0][g] = parents[0][g];
				children[1][g] = parents[1][g];
			}
		}
		else if (co_point > co_point1)
		{
			cout << "\n\t Children crossover at " << co_point1;
			cout << "\n\t Children crossover at " << co_point;
			cout << endl;
			for (int g = co_point1 - 1; g < GENE; g++)
			{
				children[0][g] = parents[1][g];
				children[1][g] = parents[0][g];
			}
			for (int g = co_point; g < GENE; g++)
			{
				children[0][g] = parents[0][g];
				children[1][g] = parents[1][g];
			}
		}
	}
	else
	{
		cout << "\n\t Crossover did not happen ";
	}
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\t Children " << c + 1 << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
	}
}                  // end crossover function


void mutation()
{
	float prob;
	int mut_point;
	for (int c = 0; c < 2; c++) {
		prob = (rand() % 11) / 20.0;
		if (prob < MUT_PROBABILITY) {
			mut_point = rand() % GENE;
			cout << "\n\t Mutation at gene " << mut_point;
			if (children[c][mut_point] == 1)
				children[c][mut_point] = 0;
			else
				children[c][mut_point] = 1;
		}
		else
			cout << "\n\t Mutation did not happen.\n";
	}
	for (int c = 0; c < 2; c++)
	{
		cout << "\n\t Children" << c + 1 << " " << "after mutation: ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
	}
	cout << endl;
}                       //end of mutation


void survivalSelection()
{
	for (int c = 0; c < 2; c++) {//copy children to newChromosome
		for (int g = 0; g < GENE; g++) {
			newChromosome[newChromoCounter][g] = children[c][g];
		}
		newChromoCounter++;
	}
	for (int c = 0; c < newChromoCounter; c++)
	{
		cout << "\n\t New Chromosome " << c << ": ";
		for (int g = 0; g < GENE; g++)
		{
			cout << newChromosome[c][g] << " ";
		}
	}
	cout << endl;
}


void copyChromosome() {
	for (int c = 0; c < POP_SIZE; c++) {
		for (int g = 0; g < GENE; g++) {
			chromosome[c][g] = newChromosome[c][g];
		}
	}
}

float recordBestFitness() {
	for (int c = 0; c < POP_SIZE; c++) {
		if (bestFitness > fitness[c]) {
			bestFitness = fitness[c];
			for (int g = 0; g < GENE; g++) {
				bestChromosome[g] = chromosome[c][g];
			}//close for gene
		}//close for if
	}//close for c

	//output for the best chromosome to monitor
	cout << "\n\t Best Fitness: " << bestFitness;
	cout << "\n\t Best Chromosome: ";
	for (int g = 0; g < GENE; g++) {
		cout << bestChromosome[g] << " ";
	}
	cout << endl;

	return bestFitness;
}
float calcAvgFitness() {
	double sum = 0;
	for (int c = 0; c < POP_SIZE; c++) {
		sum += fitness[c];
	}
	avgFitness = sum / POP_SIZE;

	//output to monitor
	cout << "\n\t Average Fitness: " << avgFitness << endl;

	return avgFitness;
}

int main()
{
	float averageFitness[MAX_GENERATION], AF = 0;
	float bestFitness[MAX_GENERATION], BF = 0;

	cout << "\nGA START! \n";
	cout << "\nINITIALIZATION... \n";
	initializePopulation();
	//getchar();

	for (int g = 0; g < MAX_GENERATION; g++) {//start of generation

		cout << "\nGENERATION" << " " << g + 1 << endl;
		cout << "\n\tPRINT POPULATION \n";
		printChromosome();
		cout << "\n\tEVALUATE CHROMOSOME \n";
		evaluateChromosome();
		//getchar();

		newChromoCounter = 0;
		for (int i = 0; i < POP_SIZE / 2; i++) {
			cout << "\n\tPARENT SELECTION \n";
			parentSelection();
			cout << "\n\tCROSSOVER \n";
			crossover();
			cout << "\n\n\tMUTATION \n";
			mutation();
			cout << "\n\tSURVIVAL SELECTION \n";
			survivalSelection();
			cout << "\n\tBEST FITNESS AND BEST CHROMOSOME \n";
			BF = recordBestFitness();
			cout << "\n\tAVERAGE FITNESS \n";
			AF = calcAvgFitness();
		}
		cout << "\n\tNEW CHROMOSOMES COPIED TO CHROMOSOME\n";
		copyChromosome();
		//getchar();

		averageFitness[g] = AF;
		bestFitness[g] = BF;
	}


	cout << "\n\n\nAverage\t\tBest\n";
	for (int j = 0; j < MAX_GENERATION; j++) {
		cout << averageFitness[j] << "\t";
		cout << bestFitness[j] << "\n";
	}

	return 0;
}