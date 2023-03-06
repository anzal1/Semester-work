#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int stoic(string line)
{
	int i = 0;
	int num = 0;
	while (line[i] != 0)
	{
		if (line[0] == '-')
		{
			return -1;
		}
		num *= 10;
		num += (line[i] - '0');
		i++;
	}
	return num;
}

int main()
{
	ifstream file;
	string line;
	file.open("input.txt");
	int i = 0;
	int initial;
	vector<vector<int>> MEALY;
	vector<vector<string>> OUT;
	while (getline(file, line))
	{
		if (i == 0)
		{
			initial = stoic(line);
		}
		else
		{
			vector<int> temp1;
			vector<string> temp2;
			int x = 0;
			int y = 0;
			string num = "";
			string outNum = "";
			while (line[x] != 0)
			{
				if (line[x] == ' ')
				{
					if (y % 2 == 0)
					{
						temp1.push_back(stoic(num));
						num = "";
					}
					else
					{
						temp2.push_back(outNum);
						outNum = "";
					}
					x++;
					y++;
					continue;
				}
				if (y % 2 == 0)
				{
					num += line[x++];
				}
				else
				{
					outNum += line[x++];
				}
			}
			temp2.push_back(outNum);
			MEALY.push_back(temp1);
			OUT.push_back(temp2);
		}
		i++;
	}

	file.close();
xy:
	int curr = initial;
	cout << "Enter String : ";
	string s;
	getline(cin, s);
	if (s.length() == 0)
	{
		cout << "Retry, wrong or null input" << endl;
		goto xy;
	}
	if (s == "-1")
	{
		cout << "Exiting";
		return 0;
	}
	int size = s.size(), k = 0;
	string output = "";
	while (curr != -1 && k < size)
	{
		string t = "";
		t += s[k++];
		if (OUT[curr][stoic(t)] != "-1")
		{
			cout << "q" << curr << " -> ";
			output += OUT[curr][stoic(t)];
			cout << "on input " << t << " ";
			cout << "gives output " << OUT[curr][stoic(t)];
		}
		curr = MEALY[curr][stoic(t)];
		if (curr != -1)
			cout << " and goes to q" << curr << endl;
		else
		{
			cout << "reaches end" << endl;
		}
	}

	cout << "Output is : " << output << endl;
	goto xy;
}

/*
Input file contents:
0
1 A -1 -1
-1 -1 2 AB
3 B 11 B
-1 -1 4 AB
5 A -1 -1
-1 -1 6 B
4 A 7 BA
8 A -1 -1
-1 -1 9 B
10 A -1 -1
-1 -1 11 B
1 A -1 -1

*/