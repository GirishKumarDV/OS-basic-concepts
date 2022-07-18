#include <stdio.h>
#include <stdlib.h>

int alloc[10][10], max[10][10], need[10][10], avail[10], completed[10], request[10], sseq[10];
int p, q, r, i, j, k, new, ch1;

int safeseq();
int main()
{
    int violationCheck, waitCheck;
    printf("Enter the number of processes : ");
    scanf("%d", &p);
    printf("\nEnter the number of resources : ");
    scanf("%d", &r);
    printf("\nEnter the max matrix for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor Process %d : ", i + 1);
        for (j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the Allocation for each process : ");
    for (i = 0; i < p; i++)
    {
        printf("\nFor process %d : ", i + 1);
        for (j = 0; j < r; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter the available resources : ");
    for (i = 0; i < r; i++)
    {
        scanf("%d", &avail[i]);
    }

    for (i = 0; i < p; i++)
    {
        for (j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nPROCESS\tMAX MATRIX\tALLOCATION MATRIX\tNEED MATRIX\n");
    for (i = 0; i < p; i++)
    {
        printf("\n%d\t", i + 1);
        for (j = 0; j < r; j++)
        {
            printf("%d", max[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++)
        {
            printf("%d", alloc[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++)
        {
            printf("%d", need[i][j]);
        }
        printf("\t\t");
    }

    ch1 = safeseq();

    if (ch1 == 0)
    {
        printf("System is not in safe state\n");
        exit(0);
    }
    else
    {
        violationCheck = 0;
        waitCheck = 0;
        printf("\nRequesting process id : ");
        scanf("%d", &new);
        printf("\nEnter the request for process : ");
        for (j = 0; j < r; j++)
        {
            scanf("%d", &request[j]);
        }
        for (i = 0; i < p; i++)
        {
            if (i == new)
            {
                for (j = 0; j < r; j++)
                {
                    if (request[j] > need[i][j])
                        violationCheck = 1;
                    if (request[j] > avail[j])
                        waitCheck = 1;
                }
                if (violationCheck)
                {
                    printf("\nProcess exceeds its max needs::TERMINATED\n");
                    exit(0);
                }
                else if (waitCheck)
                {
                    printf("\nLack of resources, process state-WAIT\n");
                    exit(0);
                }
                else
                {
                    for (j = 0; j < r; j++)
                    {
                        avail[j] = avail[j] - request[j];
                        alloc[i][j] = alloc[i][j] + request[j];
                        need[i][j] = need[i][j] - request[j];
                    }
                }
            }
        }
        ch1 = safeseq();
        if (ch1 == 0)
        {
            for (j = 0; j < r; j++)
            {
                avail[j] = avail[j] + request[j];
                alloc[new][j] = alloc[new][j] - request[j];
                need[new][j] = need[new][j] + request[j];
            }
        }
        else if (ch1 == 1)
            printf("\nRequest Committed\n");
    }
}

int safeseq()
{
    int tj, tk, i, j, k, work[10];
    int check1, check2, ss = 0;
    for (j = 0; j < r; j++)
        work[j] = avail[j];
    for (i = 0; i < p; i++)
        completed[i] = 0;

    for (tk = 0; tk < r; tk++)
    {
        for (j = 0; j < p; j++)
        {
            if (completed[j] == 0)
            {
                check1 = 0;
                for (k = 0; k < r; k++)
                {
                    if (need[j][k] <= work[k])
                        check1++;
                }
                if (check1 == r)
                {
                    for (k = 0; k < r; k++)
                    {
                        work[k] = work[k] + alloc[j][k];
                        completed[j] = 1;
                    }
                    sseq[ss] = j;
                    ss++;
                }
            }
        }
    }
    check2 = 0;
    for (i = 0; i < p; i++)
        if (completed[i] == 1)
            check2++;
    printf("\n");
    if (check2 >= p)
    {
        printf("System is in safe state\n");
        for (tj = 0; tj < p; tj++)
            printf("P%d ", sseq[tj]);
        return 1;
    }
    else
    {
        printf("System not in safe state\n");
        return 0;
    }
}
