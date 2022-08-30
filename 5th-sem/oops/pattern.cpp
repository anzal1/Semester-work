#include <bits/stdc++.h>
using namespace std;

class pattern
{
public:
    int n;
    pattern(int n)
    {
        this->n = n;
    }

    void printPattern(char c = '$')
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++)
            {
                if (j == 1 || j == 2 * i - 1)
                    cout << c;
                else
                    cout << " ";
            }
            cout << endl;
        }

        // reverse hollow diamond
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++)
            {
                if (j == 1 || j == 2 * i - 1)
                    cout << c;
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
    void printPattern(char c, char a = '*')
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++)
            {
                if (j == 1 || j == 2 * i - 1)
                    cout << c;
                else
                    cout << " ";
            }
            cout << endl;
        }

        // reverse hollow diamond
        for (int i = n - 1; i >= 1; i--)
        {
            for (int j = 1; j <= n - i; j++)
            {
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++)
            {
                if (j == 1 || j == 2 * i - 1)
                    cout << c;
                else
                    cout << " ";
            }
            cout << endl;
        }
    }
    int printPattern(char, int);
};

int pattern::printPattern(char c = '^', int x = 10)
{
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= x - i; j++)
        {
            cout << " ";
        }
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            if (j == 1 || j == 2 * i - 1)
                cout << c;
            else
                cout << " ";
        }
        cout << endl;
    }

    // reverse hollow diamond
    for (int i = x - 1; i >= 1; i--)
    {
        for (int j = 1; j <= x - i; j++)
        {
            cout << " ";
        }
        for (int j = 1; j <= 2 * i - 1; j++)
        {
            if (j == 1 || j == 2 * i - 1)
                cout << c;
            else
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}

int main()
{
    int x = 0;
    int n;
    cout << "Enter the number of rows: ";
    cin >> n;
    pattern p(n);
    cout << "Default argument: ";
    cout << endl;
    p.printPattern('*', '$');
    char c;
    cout << "Enter the the other character: ";
    cin >> c;
    cout << endl;
    p.printPattern(c, '%');

    cout << endl;
    cout << "Inline functioni example : ";
    cout << endl;
    cout << p.printPattern('^', 10);
    cout << endl;
    if (x == 1)
    {
        return 0;
    }
    else
    {
        x++;
        cout << main() << endl;
    }
}

//       *
//     *   *
//   *       *
// *           *
//   *       *
//     *   *
//       *