#include <stdio.h>
#include <stdlib.h>

void rr(int, int, int[], int[]);
void srtf();

int main()
{
    int st[10], bt[10], n, i, choice, tq;
    while (1)
    {
        printf("\n1.Round Robin\n2.Shortest Remaining Time First\n3.Exit");
        printf("\nEnter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nROUND ROBIN SCHEDULING ALGORITHM\n");
            printf("Enter the number of Processes : ");
            scanf("%d", &n);
            printf("\nEnter the burst time for the sequence\n");
            for (i = 0; i<n; i++)
            {
                scanf("%d", &bt[i]);
                st[i] = bt[i];
            }
            printf("\nEnter the time Quantum : ");
            scanf("%d", &tq);
            rr(n, tq, st, bt);
            break;

        case 2:
            printf("\nSHORTEST TIME REMAINING FIRST SCHEDULING ALGORITHM\n");
            srtf();
            break;

        case 3:
            exit(0);
            break;
        }
    }
}

void rr(int n, int tq, int st[], int bt[])
{
    int count = 0, wt[10], tat[10], temp1, sq = 0, i, swt = 0, stat = 0;
    float awt = 0.0, atat = 0.0;
    while (1)
    {
        for (i = 0, count = 0; i < n; i++)
        {
            temp1 = tq;
            if (st[i] == 0)
            {
                count++;
                continue;
            }
            if (st[i] > tq)
                st[i] -= tq;
            else if (st[i] >= 0)
            {
                temp1 = st[i];
                st[i] = 0;
            }
            sq = sq + temp1;
            tat[i] = sq;
        }
        if (n==count)
            break;
    }
    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i];
        swt += wt[i];
        stat += tat[i];
    }
    awt = (float)swt /n;
    atat = (float)stat /n;
    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURN AROUND TIME\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }
    printf("AVERAGE WAITING TIME = %f\nAVERAGE TURN AROUND TIME = %f\n", awt, atat);
}

void srtf()
{
    int at[10], bt[10], rt[10], remain = 0, time, smallest,endtime = 0, swt = 0, stat = 0,j, i, n;
    printf("\nEnter the number of processes : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        printf("\nEnter arrival time for P%d    : ",i+1);
        scanf("%d",&at[i]);
        printf("\nEnter burst time for P%d      : ",i+1);
        scanf("%d",&bt[i]);
        rt[i]=bt[i];
    }

    rt[100]=9999;
    printf("\nPROCESS\tWAITING TIME\tTURN AROUND TIME\n");
    for(time=0;remain!=n;time++){
        smallest = 100;
        for(i=0;i<n;i++){
            if(at[i]<=time && rt[i]<rt[smallest] && rt[i]>0){
                smallest = i;
            }
        }
        rt[smallest]--;
        if(rt[smallest]==0){
            remain++;
            endtime = time +1;
            j = smallest;
            printf("%d\t%d\t\t%d\n",smallest+1,endtime-bt[j]-at[j],endtime-at[j]);
            swt += endtime -bt[j] - at[j];
            stat += endtime - at[j];
        }
    }
    float atat=0.0,awt=0.0;
    awt = (float)swt/n;
    atat = (float)stat/n;
    printf("\nAVERAGE WAITING TIME=%f\nAVERAGE TURN AROUND TIME=%f",awt,atat);
}