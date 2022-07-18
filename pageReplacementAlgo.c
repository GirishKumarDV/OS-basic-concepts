#include <stdio.h>
#include <stdlib.h>

int ref[30], p[50], pgfaultcnt = 0, hit = 0, i;
int n, nf,j,k;
void getData()
{
    printf("\nEnter the length of the reference sequence :");
    scanf("%d", &n);
    printf("\nEnter the number of frames : ");
    scanf("%d", &nf);
    printf("\nEnter the reference sequence : \n");
    for (i = 0; i < n; i++)
        scanf("%d", &ref[i]);
}

void initialize()
{
    pgfaultcnt = 0;
    for (i = 0; i < nf; i++)
    {
        p[i] = 9999;
    }
}

void dispages()
{
    for (k = 0; k < nf; k++)
    {
        if (p[k] != 9999)
            printf("%d", p[k]);
    }
}

int isHit(int data)
{
    hit = 0;
    for (j = 0; j < nf; j++)
    {
        if (p[j] == data)
        {
            hit = 1;
            break;
        }
    }
    return hit;
}

void fifo()
{
    int j = 0;
    initialize();
    printf("\n\tPAGES\tFRAMES\tFAULTS\n\n");
    for (i = 0; i < n; i++)
    {
        printf("\n\t%d\t", ref[i]);
        if (isHit(ref[i]) == 0)
        {
            p[j] = ref[i];
            j++;
            dispages();
            printf("\tPage fault %d", pgfaultcnt);
            pgfaultcnt++;
        }
        else
        {
            dispages();
            printf("\tNo page faults");
        }
        if (j == nf)
            j = 0;
    }
    printf("\n\nTotal number of page faults = %d", pgfaultcnt);
}

void lru()
{
    int least[50], j, k;
    initialize();
    printf("\n\tPAGES\tFRAMES\tFAULTS\n");
    for (i = 0; i < n; i++)
    {
        printf("\n\t%d\t", ref[i]);
        if (isHit(ref[i]) == 0)
        {
            for (j = 0; j < nf; j++)
            {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (pg == ref[k])
                    {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                    else
                    {
                        found = 0;
                    }
                }
                if (!found)
                    least[j] = -9999;
            }
            int min = 9999;
            int repindex;
            for (j = 0; j < nf; j++)
            {
                if (least[j] < min)
                {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = ref[i];
            dispages();
            printf("\tPage fault %d", pgfaultcnt);
            pgfaultcnt++;
        }
        else
        {
            dispages();
            printf("\tNo page faults");
        }
    }
    printf("\nTotal number of page faults is %d", pgfaultcnt);
}

int main()
{
    int yn, choice;
    do
    {
        printf("\n---PAGE REPLACEMENT ALGOS--\n");
        printf("1.Enter Data\n2.FIFO\n3.LRU\n4.Exit\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            getData();
            break;
        case 2:
            fifo();
            break;
        case 3:
            lru();
            break;
        case 4:
            exit(0);
            break;
        }
        printf("\nPress 1 if you wish to continue else press 0 :");
        scanf("%d", &yn);
    } while (yn == 1);
    return (0);
}