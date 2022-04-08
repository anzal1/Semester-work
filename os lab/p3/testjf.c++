// C++ implementation of shortest job first
// using the concept of segment tree

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define z 1000000007
#define sh 100000
#define pb push_back
#define pr(x) printf("%d ", x)

struct util {

	// Process ID
	int id;
	// Arrival time
	int at;
	// Burst time
	int bt;
	// Completion time
	int ct;
	// Turnaround time
	int tat;
	// Waiting time
	int wt;
}

// Array to store all the process information
// by implementing the above struct util
ar[sh + 1];

struct util1 {

	// Process id
	int p_id;
	// burst time
	int bt1;
};

util1 range;

// Segment tree array to
// process the queries in nlogn
util1 tr[4 * sh + 5];

// To keep an account of where
// a particular process_id is
// in the segment tree base array
int mp[sh + 1];

// Comparator function to sort the
// struct array according to arrival time
bool cmp(util a, util b)
{
	if (a.at == b.at)
		return a.id < b.id;
	return a.at < b.at;
}

// Function to update the burst time and process id
// in the segment tree
void update(int node, int st, int end,
			int ind, int id1, int b_t)
{
	if (st == end) {
		tr[node].p_id = id1;
		tr[node].bt1 = b_t;
		return;
	}
	int mid = (st + end) / 2;
	if (ind <= mid)
		update(2 * node, st, mid, ind, id1, b_t);
	else
		update(2 * node + 1, mid + 1, end, ind, id1, b_t);
	if (tr[2 * node].bt1 < tr[2 * node + 1].bt1) {
		tr[node].bt1 = tr[2 * node].bt1;
		tr[node].p_id = tr[2 * node].p_id;
	}
	else {
		tr[node].bt1 = tr[2 * node + 1].bt1;
		tr[node].p_id = tr[2 * node + 1].p_id;
	}
}

// Function to return the range minimum of the burst time
// of all the arrived processes using segment tree
util1 query(int node, int st, int end, int lt, int rt)
{
	if (end < lt || st > rt)
		return range;
	if (st >= lt && end <= rt)
		return tr[node];
	int mid = (st + end) / 2;
	util1 lm = query(2 * node, st, mid, lt, rt);
	util1 rm = query(2 * node + 1, mid + 1, end, lt, rt);
	if (lm.bt1 < rm.bt1)
		return lm;
	return rm;
}

// Function to perform non_preemptive
// shortest job first and return the
// completion time, turn around time and
// waiting time for the given processes
void non_preemptive_sjf(int n)
{

	// To store the number of processes
	// that have been completed
	int counter = n;

	// To keep an account of the number
	// of processes that have been arrived
	int upper_range = 0;

	// Current running time
	int tm = min(INT_MAX, ar[upper_range + 1].at);

	// To find the list of processes whose arrival time
	// is less than or equal to the current time
	while (counter) {
		for (; upper_range <= n;) {
			upper_range++;
			if (ar[upper_range].at > tm || upper_range > n) {
				upper_range--;
				break;
			}

			update(1, 1, n, upper_range,
				ar[upper_range].id, ar[upper_range].bt);
		}

		// To find the minimum of all the running times
		// from the set of processes whose arrival time is
		// less than or equal to the current time
		util1 res = query(1, 1, n, 1, upper_range);

		// Checking if the process has already been executed
		if (res.bt1 != INT_MAX) {
			counter--;
			int index = mp[res.p_id];
			tm += (res.bt1);

			// Calculating and updating the array with
			// the current time, turn around time and waiting time
			ar[index].ct = tm;
			ar[index].tat = ar[index].ct - ar[index].at;
			ar[index].wt = ar[index].tat - ar[index].bt;

			// Update the process burst time with
			// infinity when the process is executed
			update(1, 1, n, index, INT_MAX, INT_MAX);
		}
		else {
			tm = ar[upper_range + 1].at;
		}
	}
}

// Function to call the functions and perform
// shortest job first operation
void execute(int n)
{

	// Sort the array based on the arrival times
	sort(ar + 1, ar + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		mp[ar[i].id] = i;

	// Calling the function to perform
	// non-preemptive-sjf
	non_preemptive_sjf(n);
}

// Function to print the required values after
// performing shortest job first
void print(int n)
{

	cout << "ProcessId "
		<< "Arrival Time "
		<< "Burst Time "
		<< "Completion Time "
		<< "Turn Around Time "
		<< "Waiting Time\n";
	for (int i = 1; i <= n; i++) {
		cout << ar[i].id << " \t\t "
			<< ar[i].at << " \t\t "
			<< ar[i].bt << " \t\t "
			<< ar[i].ct << " \t\t "
			<< ar[i].tat << " \t\t "
			<< ar[i].wt << " \n";
	}
}

// Driver code
int main()
{
	// Number of processes
	int n = 4;

	// Initializing the process id
	// and burst time
	range.p_id = INT_MAX;
	range.bt1 = INT_MAX;

	for (int i = 1; i <= 4 * sh + 1; i++) {
		tr[i].p_id = INT_MAX;
		tr[i].bt1 = INT_MAX;
	}

	// Arrival time, Burst time and ID
	// of the processes on which SJF needs
	// to be performed
	ar[1].at = 0;
	ar[1].bt = 4;
	ar[1].id = 1;

	ar[2].at = 6;
	ar[2].bt = 5;
	ar[2].id = 2;

	ar[3].at = 6;
	ar[3].bt = 8;
	ar[3].id = 3;

	ar[4].at = 30;
	ar[4].bt = 63;
	ar[4].id = 4;

	// ar[5].at = 5;
	// ar[5].bt = 8;
	// ar[5].id = 5;

	execute(n);

	// Print the calculated time
	print(n);
}
