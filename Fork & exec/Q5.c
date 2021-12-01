#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	/*pid_t is a datatype which is the return type of functions like:
	getpid() - returns process id of calling function to pid_t
	getppid() - returns the process id of parent in which the function is calling*/

	pid_t pid;
	int i = 0;

	//array of strings which are commands to be passed to the filename in execvp syscall

	char *args[] = {"./fibonacci", argv[1], NULL};

	//Code has to take only one extra argument in command line, for more arguments show error message

	if (argc > 2)
	{
		fprintf(stderr, "Argument limit exceeded!\n");
		printf("Arguments supplied = %d\n", argc);
		while (argv[i] != NULL)
		{
			printf("%d : %s\n", i + 1, argv[i]);
			i++;
		}

		exit(0);
	}

	//fork() creates a child process and its process id is stored in pid

	pid = fork();
	if (pid < 0)
	{

		//Error Message : fork() returns negative if process not created

		fprintf(stderr, "Child Process could not be created!\n");
	}

	//fork() returns 0 , if process creation successful hence child process is called(in this case execvp syscall executes file ./fibonacci - output file for fibonacci.c program)

	else if (pid == 0)
	{
		printf("\nForked Successfully, child process created...\n\n");
		execv("./fibonacci", args);
	}

	//fork() returns positive value i.e. the process id of child to parent after executing child process(./fibonacci)

	else
	{
		//Wait till child process is completed(fibonacci returns 0(NULL) on successful completion)

		wait(NULL);
		printf("-------------------------------------------------\nProcess Completed!\nParent Process ID : %d\nChild Process ID : %d\n", getpid(), pid);
	}

	return 0;
}
