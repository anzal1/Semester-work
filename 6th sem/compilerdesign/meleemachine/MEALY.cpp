#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int stoi(string line)
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
	file.open("MEALY.txt");
	int i = 0;
	int initial;
	vector<vector<int>> MEALY;
	vector<vector<string>> OUT;
	while (getline(file, line))
	{
		if (i == 0)
		{
			initial = stoi(line, 0);
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
						temp1.push_back(stoi(num,0));
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
	cin >> s;
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
		if (OUT[curr][stoi(t,0)] != "-1")
		{
			output += OUT[curr][stoi(t,0)];
		}
		curr = MEALY[curr][stoi(t,0)];
	}

	cout << "Output is : " << output << endl;
	goto xy;
}
