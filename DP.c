/*
	CSCI3220 2016 - 17 First Term Assignment 1
	I declare that the assignment here submitted is original except for source
	material explicitly acknowledged, and that the same or closely related material
	has not been previously submitted for another course.I also acknowledge that I
	am aware of University policy and regulations on honesty in academic work, and
	of the disciplinary guidelines and procedures applicable to breaches of such
	policy and regulations, as contained in the following websites.
	University Guideline on Academic Honesty :
	http ://www.cuhk.edu.hk/policy/academichonesty/
	Faculty of Engineering Guidelines to Academic Honesty :
	http ://www.erg.cuhk.edu.hk/erg-intra/upload/documents/ENGG_Discipline.pdf
	  Student Name : Mega Gunawan
	  Student ID : 1155072307
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int maximum(int a, int b, int c) // finding maximum of 3 integer values
{
	if (a >= b && a >= c)
		return a;
	else if (b >= a && b >= c)
		return b;
	else return c;
}

typedef struct cell //structure for table for directions to traceback
{ 
	int down;
	int right;
	int diagonal;
} Cell;

Cell initialize(Cell a) // initializing all elements inside structure Cell to 0
{
	a.down = 0;
	a.right = 0;
	a.diagonal = 0;
	return a;
}

void printstring(Cell **array, int i, int j, int k, char first[], char second[], char first_str[], char second_str[]) // printing all the possible pairwise sequences using recursion
{
	if (i == strlen(first) && j == strlen(second))
	{
		int a = 0;
		while ((first_str[a] >= 'A' && first_str[a] <= 'Z') || first_str[a] == '_') // printing the first sequence
		{
			printf("%c", first_str[a]);
			a++;
		}

		printf("\n");
		int b = 0;
		while ((second_str[b] >= 'A' && second_str[b] <= 'Z') || second_str[b] == '_') // printing the second sequence
		{
			printf("%c", second_str[b]);
			b++;
		}
		printf("\n\n");
		return;
	}

	if (array[i][j].down == 1) // if arrow points to cell downwards
	{
		first_str[k] = '_';
		if (array[i][j].right == 0) second_str[k] = second[j];
	
		printstring(array, i, j + 1, k + 1, first, second, first_str, second_str);
	}

	if (array[i][j].right == 1) // if arrow points to the cell on its right
	{
		second_str[k] = '_';
		if (array[i][j].down == 0) first_str[k] = first[i];

		printstring(array, i + 1, j, k + 1, first, second, first_str, second_str);
	}

	if (array[i][j].diagonal == 1) // if arrow points to the diagonal cell
	{
		first_str[k] = first[i];
		second_str[k] = second[j];
		printstring(array, i + 1, j + 1, k + 1, first, second, first_str, second_str);
	}
}

int main(int argc, char *argv[])
{
	int match, mismatch, indel;

	// converting string to integer using strtol
	char *eptr, *fptr, *gptr;
	match = strtol(argv[3], &eptr, 10);
	mismatch = strtol(argv[4], &fptr, 10);
	indel = strtol(argv[5], &gptr, 10);

	int first = strlen(argv[1]) + 1; // number of columns in the score table
	int second = strlen(argv[2]) + 1; // number of rows in the score table
	
	// making an empty score table
	int i;
	int **table = malloc(first*sizeof(int));
	if (table)
	{
		for (i = 0; i < first; i++)
			table[i] = malloc(second*sizeof(int));
	}

	// making an empty direction table to contain the arrows
	Cell **directions = malloc(first*sizeof(Cell));
	if (directions)
	{
		for (i = 0; i < first; i++)
			directions[i] = malloc(second*sizeof(Cell));
	}

	// inserting the scores in the score table
	int j;
	for (i = strlen(argv[1]); i >= 0; i--)
		for (j = strlen(argv[2]); j >= 0; j--)
		{
			directions[i][j] = initialize(directions[i][j]);

			if (i == strlen(argv[1]) && j == strlen(argv[2]))
			{
				table[i][j] = 0;
				continue;
			}

			if (i == strlen(argv[1]))
			{
				table[i][j] = table[i][j + 1] + indel;
				continue;
			}
			
			if (j == strlen(argv[2]))
			{
				table[i][j] = table[i + 1][j] + indel;
				continue;
			}

			int temp = 0;
			if (argv[1][i] == argv[2][j]) temp = match;
			else temp = mismatch;

			table[i][j] = maximum(table[i][j + 1] + indel, table[i + 1][j] + indel, table[i + 1][j + 1] + temp);
			
			if (table[i][j] == table[i][j + 1] + indel)	directions[i][j].down = 1;
			if (table[i][j] == table[i + 1][j] + indel)	directions[i][j].right = 1;
			if (table[i][j] == table[i + 1][j + 1] + temp) directions[i][j].diagonal = 1;
		}

	printf("%d\n\n", table[0][0]); // printing the optimal score

	// empty strings to contain the pairwise sequences
	char *first_str = (char*)malloc((strlen(argv[1]) + strlen(argv[2]))*sizeof(char));
	char *second_str = (char*)malloc((strlen(argv[1])+strlen(argv[2]))*sizeof(char));

	printstring(directions, 0, 0, 0, argv[1], argv[2], first_str, second_str);

	return 0;
}