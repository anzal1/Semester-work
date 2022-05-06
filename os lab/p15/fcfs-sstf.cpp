#include <bits/stdc++.h>
using namespace std;

void fcfs()
{

    int n, head, i, j, k, seek = 0,diff;
    float avg;

    cout<<"\nEnter the size of queue request :";
    cin>>n;

    int queue[n + 1];

    cout<<"\nEnter the queue :";
    for (i = 1; i <= n; i++)
    {
        cin>>queue[i];
    }

    printf("\nEnter the initial head position :");
    cin>>head;
    cout<<endl;
    queue[0] = head;

    for (j = 0; j <= n - 1; j++)
    {
        diff = abs(queue[j + 1] - queue[j]);
        seek += diff;
        printf("move is from %d to %d with seek %3d\n", queue[j], queue[j + 1], diff);
    }
    cout<<"\n";
    printf("Total seek time is : %d\n", seek);
    avg = seek / (float)n;

    printf("Average seek time is : %f\n", avg);
}

void sstf()
{

    int head;
    printf("\nEnter head position: ");
    cin >> head;

    int n, i;
    cout << "\nEnter total requests" << endl;
    cin >> n;
    int queue1[n], done[n];
    printf("\nEnter requests: ");
    for (i = 0; i < n; i++)
    {
        cin>>queue1[i];
        done[i] = 0;
    }

    printf("%d->", head);

    int temp1 = head;
    int count1 = 0, j, sum = 0;
    while (count1 != n)
    {
        int temp = 100000;
        int k = -1;
        for (j = 0; j < n; j++)
        {
            if (temp1 != queue1[j] && done[j] == 0)
            {
                if (temp > abs(temp1 - queue1[j]))
                {
                    temp = abs(temp1 - queue1[j]);
                    k = j;
                }
            }
        }
        sum += temp;
        printf("%d->", queue1[k]);
        count1++;
        temp1 = queue1[k];
        done[k] = 1;
        // cout<<temp1<<endl;
    }
    cout << endl;
    cout << "Total head movement is=" << sum << endl;
    cout << "Average head movement is=" << sum/float(n) << endl;

}

int main()
{
    cout<<"\n";
    cout << "Enter 1 for FCFS and 2 for SSTF" << endl;
    cout << "\n";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        fcfs();
    }
    else if (choice == 2)
    {
        sstf();
    }
    else
    {
        cout << "Wrong Choice" << endl;
    }
    return 0;
}