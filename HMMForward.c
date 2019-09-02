/*
CSCI3220 2016-17 First Term Assignment 3
I declare that the assignment here submitted is original except for source
material explicitly acknowledged, and that the same or closely related material
has not been previously submitted for another course. I also acknowledge that I
am aware of University policy and regulations on honesty in academic work, and
of the disciplinary guidelines and procedures applicable to breaches of such
policy and regulations, as contained in the following websites.
University Guideline on Academic Honesty:
http://www.cuhk.edu.hk/policy/academichonesty/
Faculty of Engineering Guidelines to Academic Honesty:
http://www.erg.cuhk.edu.hk/erg-intra/upload/documents/ENGG_Discipline.pdf
Student Name: Mega Gunawan
Student ID : 1155072307
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// initial probabilities, init[0] = s1, init[1] = s2
	double init[2];
	init[0] = strtod(argv[1], NULL);
	init[1] = strtod(argv[2], NULL);

	// transition probabilities
	double p1[2], p2[2];
	p1[0] = strtod(argv[3], NULL); // p11
	p1[1] = strtod(argv[4], NULL); // p12
	p2[0] = strtod(argv[5], NULL); // p21
	p2[1] = strtod(argv[6], NULL); // p22

	// emission probabilities
	double e1[4], e2[4];
	e1[0] = strtod(argv[7], NULL); // e1(A)
	e1[1] = strtod(argv[8], NULL); // e1(C)
	e1[2] = strtod(argv[9], NULL); // e1(G)
	e1[3] = strtod(argv[10], NULL); // e1(T)
	e2[0] = strtod(argv[11], NULL); // e2(A)
	e2[1] = strtod(argv[12], NULL); // e2(C)
	e2[2] = strtod(argv[13], NULL); // e2(G)
	e2[3] = strtod(argv[14], NULL); // e2(T)

	double A[2], C[2], G[2], T[2];
	A[0] = e1[0]; // e1(A)
	A[1] = e2[0]; // e2(A)
	C[0] = e1[1]; // e1(C)
	C[1] = e2[1]; // e2(C)
	G[0] = e1[2]; // e1(G)
	G[1] = e2[2]; // e2(G)
	T[0] = e1[3]; // e1(T)
	T[1] = e2[3]; // e2(T)

	int len = strlen(argv[15]); // length of DNA sequence
	int i;

	double *table[2]; // table to calculate the likelihood, similar to Chapter 7 slide 32
	for (i = 0; i < 2; i++)
		table[i] = malloc(len*sizeof(double));

	for (i = 0; i < len; i++)
	{
		if (i == 0) // first row
		{
			if (argv[15][i] == 'A')
			{
				table[0][0] = init[0] * A[0];
				table[1][0] = init[1] * A[1];
			}
			else if (argv[15][i] == 'C')
			{
				table[0][0] = init[0] * C[0];
				table[1][0] = init[1] * C[1];
			}
			else if (argv[15][i] == 'G')
			{
				table[0][0] = init[0] * G[0];
				table[1][0] = init[1] * G[1];
			}
			else if (argv[15][i] == 'T')
			{
				table[0][0] = init[0] * T[0];
				table[1][0] = init[1] * T[1];
			}
		}
		else // other rows except for first row
		{
			if (argv[15][i] == 'A')
			{
				table[0][i] = table[0][i - 1] * A[0] * p1[0] + table[1][i - 1] * A[0] * p2[0];
				table[1][i] = table[0][i - 1] * A[1] * p1[1] + table[1][i - 1] * A[1] * p2[1];
			}
			else if (argv[15][i] == 'C')
			{
				table[0][i] = table[0][i - 1] * C[0] * p1[0] + table[1][i - 1] * C[0] * p2[0];
				table[1][i] = table[0][i - 1] * C[1] * p1[1] + table[1][i - 1] * C[1] * p2[1];
			}
			else if (argv[15][i] == 'G')
			{
				table[0][i] = table[0][i - 1] * G[0] * p1[0] + table[1][i - 1] * G[0] * p2[0];
				table[1][i] = table[0][i - 1] * G[1] * p1[1] + table[1][i - 1] * G[1] * p2[1];
			}
			else if (argv[15][i] == 'T')
			{
				table[0][i] = table[0][i - 1] * T[0] * p1[0] + table[1][i - 1] * T[0] * p2[0];
				table[1][i] = table[0][i - 1] * T[1] * p1[1] + table[1][i - 1] * T[1] * p2[1];
			}
		}
	}

	printf("%.15g\n", table[0][len - 1] + table[1][len - 1]); // likelihood

}