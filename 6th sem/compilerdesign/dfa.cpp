// write a program that reads a dfa from file and checks whether a given string is accepted by the dfa or not
#include <bits/stdc++.h>
using namespace std;

// take input from file
void takeInput(ifstream &fin, int &n, int &m, int &q0, int &f, int &k, vector<int> &final, vector<vector<int>> &delta)
{
    fin >> n >> m >> q0 >> f >> k;
    final.resize(f);
    for (int i = 0; i < f; i++)
    {
        fin >> final[i];
    }
    delta.resize(n);
    for (int i = 0; i < n; i++)
    {
        delta[i].resize(m);
        for (int j = 0; j < m; j++)
        {
            fin >> delta[i][j];
        }
    }
}

// check whether a given string is accepted by the dfa or not

bool checkString(string s, int n, int m, int q0, int f, int k, vector<int> final, vector<vector<int>> delta)
{
    int q = q0;
    for (int i = 0; i < s.length(); i++)
    {
        q = delta[q][s[i] - 'a'];
    }
    for (int i = 0; i < f; i++)
    {
        if (q == final[i])
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    int n, m, q0, f, k;
    vector<int> final;
    vector<vector<int>> delta;
    takeInput(fin, n, m, q0, f, k, final, delta);
    cout << "Enter the string to check: ";
    string s;
    cin >> s;
    if (checkString(s, n, m, q0, f, k, final, delta))
    {
        cout << "Accepted" << endl;
    }
    else
    {
        cout << "Not Accepted" << endl;
    }
    return 0;
}
