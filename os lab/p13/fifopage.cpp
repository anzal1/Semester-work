#include <bits/stdc++.h>
using namespace std;

int present(int table_frame[], int nf, int page)
{
	for (int i = 0; i < nf; i++)
		if (page == table_frame[i])
			return 1;
	return 0;
}

void printtable(int table_frame[], int nf)
{
	for (int i = 0; i < nf; i++)
	{
		if (table_frame[i] == -1)
			printf("-- ");
		else
			printf("%2d ", table_frame[i]);
	}
	printf("||");
}

int main()
{
	int n, nf, i, pos = 0;

	printf("Enter number of frames\n");
	cin>>nf;
	int table_frame[nf];
	for (i = 0; i < nf; i++)
	{
		table_frame[i] = -1;
	}

	printf("Enter total number of page requests\n");
	cin>>n;
	int pages[n];
	printf("Enter reference string :\n");
	for (i = 0; i < n; i++)
	{
		cin>>pages[i];
	}

	int count1 = 0;
	printf("Position of frame table after each request\n\n");
	for (i = 0; i < n; i++)
	{
		printf("Page table after request from %2d || ", pages[i]);
		if (!present(table_frame, nf, pages[i]))
		{
			table_frame[pos] = pages[i];
			pos = (pos + 1) % nf;
			printtable(table_frame, nf);
			printf("page fault\n");
			count1++;
			continue;
		}

		printtable(table_frame, nf);
		printf("\n");
	}
	printf("\nNumber of page faults : %d\n\n", count1);
	float average=(float)count1/(float)n;
	printf("\nAverage page faults : %.4f\n\n", average);
    return 0;
}