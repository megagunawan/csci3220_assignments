/* CSCI3220 2016-17 First Term Assignment 2
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
#include <stdlib.h>
#include <string.h>

typedef struct Node // Node for the trie
{
	char value;
	struct Node *A;
	struct Node *G;
	struct Node *C;
	struct Node *T;
	struct Node *dollar;
} Node;

Node* buildNode() // malloc a node and set all values to NULL
{
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->value = NULL;
	temp->A = NULL;
	temp->G = NULL;
	temp->C = NULL;
	temp->T = NULL;
	temp->dollar = NULL;

	return temp;
}

Node* buildTrie(char* input, int length, Node* head) // building the Trie
{
	int i;
	Node *temp = head;
	for (i = 0; i < length; i++)
	{
		if (input[i] == 'A')
		{
			if (temp->A == NULL)
			{
				temp->A = buildNode();
				temp = temp->A;
				temp->value = 'A';
			}
			else temp = temp->A;
		}
		else if (input[i] == 'G')
		{
			if (temp->G == NULL)
			{
				temp->G = buildNode();
				temp = temp->G;
				temp->value = 'G';
			}
			else temp = temp->G;
		}
		else if (input[i] == 'C')
		{
			if (temp->C == NULL)
			{
				temp->C = buildNode();
				temp = temp->C;
				temp->value = 'C';
			}
			else temp = temp->C;
		}
		else if (input[i] == 'T')
		{
			if (temp->T == NULL)
			{
				temp->T = buildNode();
				temp = temp->T;
				temp->value = 'T';
			}
			else temp = temp->T;
		}
		else if (input[i] == '$')
		{
			if (temp->dollar == NULL)
			{
				temp->dollar = buildNode();
				temp = temp->dollar;
				temp->value = '$';
			}
			else temp = temp->dollar;
		}
	}
	return head;
}

void search(Node* head, char* sequence, int length, int pos) // searching if the short string exists in the long string
{
	if (pos == length) // if position of char in short string currently searched equals to the length of the short string, then short string exists.
	{
		printf("Yes\n");
		return;
	}

	if (sequence[pos] == 'A')
	{
		if (head->A != NULL)
		{
			//printf("go to node A\n");
			search(head->A, sequence, length, pos + 1);
		}
		else
		{
			printf("No\n");
			return;
		}
	}
	else if (sequence[pos] == 'C')
	{
		if (head->C != NULL)
		{
			//printf("go to node C\n");
			search(head->C, sequence, length, pos + 1);
		}
		else
		{
			printf("No\n");
			return;
		}
	}
	else if (sequence[pos] == 'G')
	{
		if (head->G != NULL)
		{
			//printf("go to node G\n");
			search(head->G, sequence, length, pos + 1);
		}
		else
		{
			printf("No\n");
			return;

		}
	}
	else if (sequence[pos] == 'T')
	{
		if (head->T != NULL)
		{
			//printf("go to node T\n");
			search(head->T, sequence, length, pos + 1);
		}
		else
		{
			printf("No\n");
			return;
		}
	}
	else if (sequence[pos] == '$')
	{
		printf("Yes\n");
		return;
	}
	
}

int main(int argc, char* argv[])
{
	//char long_s[100000];
	//char short_s[1000];

	//scanf("%s", long_s);
	//scanf("%s", short_s);
	char *long_s = argv[1];
	char *short_s = argv[2];

	char suffix[100000];
	Node *head = buildNode();
	int i;
	for (i = 0; i < strlen(long_s); i++)
	{
		strcpy(suffix, long_s+i);
		head = buildTrie(suffix,strlen(suffix),head);
	}

	search(head, short_s, strlen(short_s), 0);

	return 0;
}