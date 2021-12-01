#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	//loop variable
	int i = 0;
	//Variable to store integral value of string argument after ./a.out
	int argF;				
	//Variables for fibonacci series computation
	int term1 = 0, term2 = 1, sum = 1;
	int nextTerm;

	printf("\nFibonacci Process id = %d\nParent Process id = %d\n",getpid(),getppid());

	//When 2 arguments input to CL, treat it as valid entry and check for following conditions

	if (argc == 2)
	{
		printf("Arguments supplied = %d\n", argc);
		
		/*atoi function is used to convert string to integer, argF now stores the integer value entered in argument after (./a.out)*/

		argF = atoi(argv[1]);

		//check condition for negative and zero input, print error message

		if (argF <= 0)
		{
			fprintf(stderr, "Invalid Input! '%s'\nFibonacci Series cannot be determined\nEnter positive integer as argument!\n", argv[1]);
			exit(0);
		}

		//if input is a positive integer print the fibonacci sequece
		//the integer input in CL serves as terms upto which the series will be generated

		else
		{
			printf("Fibonacci Series for %d terms is :\n", argF);

			//--------------------------------
			//Code to Generate Fibonacci Series
			//---------------------------------

			if (argF == 1)
			{
				//First Term is 0, print directly

				printf("\n0 \n\nSum of terms in series= 0\n");
				exit(0);
			}
			else if (argF == 2)
			{
				//First two terms are 0, 1(constant), print directly

				printf("\n0, 1\n\nSum of terms in series= 1\n");
				exit(0);
			}

			//For terms after 2 terms(0, 1), generate series

			else
			{
				//next term of the sequence is the sum of previous 2 terms

				nextTerm = term1 + term2;

				//First 2 terms are alwyas same i.e. 0 and 1

				printf("\n0, 1");
				for (i = 3; i <= argF; i++)
				{
					sum += nextTerm;
					printf(", %d", nextTerm);
					term1 = term2;
					term2 = nextTerm;
					nextTerm = term1 + term2;
				}
				printf("\n\nSum of %d terms in series = %d\n", argF, sum);
				exit(0);
			}
		}
	}

	//IF only 1 Argument is input i.e. (./a.out) prompt user to enter another argument to command line
	
	else
	{
		printf("Given argument = %s\nSupply one more argument!(positive integer)\n", argv[1]);
	}
}
