#include <bits/stdc++.h>
using namespace std;

string transposemat(vector<vector<char>> mat)
{
    int row = mat.size();
    int key = mat[0].size();
    string s = "";
    vector<vector<char>> transposed(key, vector<char>(row, ' '));
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < row; j++)
        {
            s += mat[j][i];
        }
    }
    return s;
}

void printmat(vector<vector<char>> mat)
{
    int row = mat.size();
    int key = mat[0].size();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < key; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void encrypt(string &s, int key)
{
    int len = s.length();
    int row = ceil(len / (float)key);
    int n = 0;
    vector<vector<char>> mat(row, vector<char>(key, 'x'));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < key; j++)
        {
            if (j + n < len)
            {
                mat[i][j] = s[j + n];
            }
            else
            {
                mat[i][j] = 'x';
            }
        }
        n += key;
    }

    //	printmat(mat);
    s = transposemat(mat);
    //	printmat(mat);
    cout << endl;
    cout << "The encrypted string is : " << s << endl;
}

void decrypt(string s, int key)
{
    int len = s.length();
    int row = ceil(len / (float)key);
    int n = 0;
    vector<vector<char>> mat(key, vector<char>(row, ' '));
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < row; j++)
        {
            mat[i][j] = s[j + n];
        }
        n += row;
    }
    s = transposemat(mat);
    int trail = s.length() - 1;
    while (s[trail] == 'x')
    {
        trail--;
    }
    s = s.substr(0, trail + 1);
    cout << endl;
    cout << "The decrypted string is : " << s << endl;
}

int main()
{

    //	string s="thisisateststring";
    //	string s1="tstnhasgittxserxisix";
    //	int key= 5;
    string inp;
    int key;
    char a;
    int choice;
    while (true)
    {
        cout << "\nMenu";
        cout << "\n1. Encrypt";
        cout << "\n2. Decrypt";
        cout << "\n3. Terminate";
        cout << "\n";
        cout << "\nEnter your choice : ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "\nEnter the key : ";
            cin >> key;
            cout << "\nEnter the string to be encrypted :";
            cin.get();
            getline(cin, inp);
            encrypt(inp, key);
        }
        else if (choice == 2)
        {
            //			cout<<"\nEnter the key and the string to be decrypted : ";
            //			cin>>key;
            //			cin>>a;
            //			getline(cin,inp,'\n');
            //			cout<<inp<<endl;
            decrypt(inp, key);
        }

        else if (choice == 3)
        {
            cout << "Terminating.....";
            break;
        }
        else
        {
            cout << "\n Try again wrong choice.....";
        }
    }
    //		encrypt(s,key);
    //		decrypt(s1,key);
    return 0;
}

// T h i s i
// s a t e s
// t s t r i
// n g