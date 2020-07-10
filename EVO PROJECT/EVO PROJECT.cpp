#include <iostream>
#include<fstream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#define NULL nullptr
using namespace std;

//declare constant - problem specification, population size
const int GENE = 30; // Bricks LEGO
const int CAPACITY = 2200; // Budget
const int POP_SIZE = 1000; // Maximum population
const float MUT_PROBABILITY = 0.1;
const float CO_probability = 0.9;
double bestFitness = 0.0;
double avgFitness = 0.0;
const int MAX_GENERATION = 100;
int bestChromosome[GENE];
ofstream avgBestFitnessFile;

const float PRICE[GENE] = { 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4, 2.6, 2.8,
						 3, 1.3, 1.5, 1.7, 1.9, 2.1, 2.3, 2.5, 2.7, 2.9,
						 0.2, 0.4, 0.6, 0.8, 0.1, 0.3, 0.5, 0.7, 0.9, 1.1}; // Prices for each LEGO bricks
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
			randNum = rand() % 100;
			chromosome[c][i] = randNum;
		}
	}
	cout << endl;
}


void evaluateChromosome() {
	float totalPrice = 0.0, totalPriceEachBricks = 0.0, totalBricks = 0.0;
	for (int c = 0; c < POP_SIZE; c++) {
		totalPrice = 0.0, totalBricks = 0.0;
		for (int i = 0; i < GENE; i++) {
			totalPriceEachBricks = 0.0;
			totalBricks = chromosome[c][i] + totalBricks;
			totalPriceEachBricks = chromosome[c][i] * PRICE[i];
			totalPrice = totalPriceEachBricks + totalPrice;
		}
		float X = abs((float)CAPACITY - totalPrice) / (float)CAPACITY;
		float Y = totalBricks/(100 * GENE);
		fitness[c] = (X + Y) / 2;
		//cout << "\tC" << c << "\tDifference\t" << X << "\tFV\t" << fitness[c] << endl;
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

			//cout << "\n\t Players: " << player1 << " VS " << player2;
			//cout << "\n\t Fitness: " << fitness[player1] << " VS " << fitness[player2];
			//cout << "\n\t Winner: " << indexParents[p];
		}//end of tournament
	} while (indexParents[0] == indexParents[1]);

	for (int p = 0; p < 2; p++) {
		//cout << "\n\t Parents " << p + 1 << " : ";

		for (int g = 0; g < GENE; g++) {
			parents[p][g] = chromosome[indexParents[p]][g];
			//cout << parents[p][g] << " ";
		}
	}
	//cout << endl;
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
			//cout << "\n\t Children crossover at " << co_point;
			//cout << "\n\t Children crossover at " << co_point1;
			//cout << endl;
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
			//cout << "\n\t Children crossover at " << co_point1;
			//cout << "\n\t Children crossover at " << co_point;
			//cout << endl;
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
	//else
	//{
	//	cout << "\n\t Crossover did not happen ";
	//}
	//for (int c = 0; c < 2; c++)
	//{
		//cout << "\n\t Children " << c + 1 << ": ";
		//for (int g = 0; g < GENE; g++)
		//{
		//	cout << children[c][g] << " ";
		//}
	//}
}                  // end crossover function


void mutation()
{
	float prob;
	int mut_point;
	for (int c = 0; c < 2; c++) {
		prob = (rand() % 11) / 20.0;
		if (prob < MUT_PROBABILITY) {
			mut_point = rand() % GENE;
			//cout << "\n\t Mutation at gene " << mut_point;
			if (children[c][mut_point] == 1)
				children[c][mut_point] = 0;
			else
				children[c][mut_point] = 1;
		}
		//else
			//cout << "\n\t Mutation did not happen.\n";
	}
	/*for (int c = 0; c < 2; c++)
	{
		cout << "\n\t Children" << c + 1 << " " << "after mutation: ";
		for (int g = 0; g < GENE; g++)
		{
			cout << children[c][g] << " ";
		}
	}
	cout << endl;*/
}                       //end of mutation


void survivalSelection()
{
	for (int c = 0; c < 2; c++) {//copy children to newChromosome
		for (int g = 0; g < GENE; g++) {
			newChromosome[newChromoCounter][g] = children[c][g];
		}
		newChromoCounter++;
	}
	//for (int c = 0; c < newChromoCounter; c++)
	//{
		//cout << "\n\t New Chromosome " << c << ": ";
		//for (int g = 0; g < GENE; g++)
		//{
		//	cout << newChromosome[c][g] << " ";
		//}
	//}
	//cout << endl;
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
		if (fitness[c] >= bestFitness) {
			bestFitness = fitness[c];
			for (int g = 0; g < GENE; g++) {
				bestChromosome[g] = chromosome[c][g];
			}//close for gene
		}//close for if
	}//close for c

	//output for the best chromosome to monitor
	//cout << "\n\t Best Fitness: " << bestFitness;
	//cout << "\n\t Best Chromosome: ";
	//for (int g = 0; g < GENE; g++) {
	//	cout << bestChromosome[g] << " ";
	//}
	//cout << endl;

	return bestFitness;
}
float calcAvgFitness() {
	double sum = 0;
	for (int c = 0; c < POP_SIZE; c++) {
		sum = sum + fitness[c];
	}
	avgFitness = sum / POP_SIZE;

	//output to monitor
	//cout << "\n\t Average Fitness: " << avgFitness << endl;

	return avgFitness;
}

int main()
{
	float averageFitness[MAX_GENERATION];
	float bestFitness[MAX_GENERATION];

	cout << "\nGA START! \n";
	//cout << "\nINITIALIZATION... \n";
	initializePopulation();
	//getchar();

	for (int g = 0; g < MAX_GENERATION; g++) {//start of generation

		cout << "\nGENERATION" << " " << g + 1;
		//cout << "\n\tPRINT POPULATION \n";
		//printChromosome();
		//cout << "\n\tEVALUATE CHROMOSOME \n";
		evaluateChromosome();
		//getchar();

		newChromoCounter = 0;
		for (int i = 0; i < POP_SIZE / 2; i++) {
			//cout << "\n\tPARENT SELECTION \n";
			parentSelection();
			//cout << "\n\tCROSSOVER \n";
			crossover();
			//cout << "\n\n\tMUTATION \n";
			mutation();
			//cout << "\n\tSURVIVAL SELECTION \n";
			survivalSelection();
		}
		//cout << "\n\tBEST FITNESS AND BEST CHROMOSOME \n";
		bestFitness[g] = recordBestFitness();
		//cout << "\n\tAVERAGE FITNESS \n";
		averageFitness[g] = calcAvgFitness();

		//cout << "\n\tNEW CHROMOSOMES COPIED TO CHROMOSOME\n";
		copyChromosome();
		//getchar();
	}


	avgBestFitnessFile.open("averageBest_Fitness.csv");
	avgBestFitnessFile << "Average, Best\n";
	cout << "\n\n\nAverage\t\tBest\n";
	for (int j = 0; j < MAX_GENERATION; j++) {
		cout << averageFitness[j] << "\t";
		cout << bestFitness[j] << "\n";

		avgBestFitnessFile << averageFitness[j] << "," << bestFitness[j] << "\n";
	}
	avgBestFitnessFile.close();

	return 0;
}