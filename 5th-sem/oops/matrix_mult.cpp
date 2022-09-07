// Write a program to multiply two n * m and m * p matrix and calculate the number of multiplication performed in the implementation.
//  follow the oops principles
//  static data member should be there
//  copy constructor
//  pointer to object
#include <bits/stdc++.h>
using namespace std;
int c = 0;
class multiplication
{
    int n, m;
    vector<vector<int>> a;

public:
    static int count;
    multiplication(int n, int m)
    {
        this->n = n;
        this->m = m;
        a.resize(n, vector<int>(m));
    }
    void getdata()
    {
        cout << "Enter the elements of the matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> a[i][j];
            }
        }
    }
    // read the input from the file
    // void getdata()
    // {
    //     ifstream fin;
    //     fin.open("input.txt");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < m; j++)
    //         {
    //             fin >> a[i][j];
    //         }
    //     }
    //     fin.close();
    // }

    multiplication(const multiplication &obj)
    {
        this->n = obj.n;
        this->m = obj.m;
        a.resize(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                a[i][j] = obj.a[i][j];
            }
        }
    }

    multiplication operator*(multiplication &obj)
    {
        multiplication temp(n, obj.m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < obj.m; j++)
            {
                for (int k = 0; k < m; k++)
                {
                    temp.a[i][j] += a[i][k] * obj.a[k][j];
                    c++;
                }
            }
        }
        return temp;
    }

    void display()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
    }
    static void displaycount()
    {
        count = c;
        cout << "The number of multiplications performed are " << count << endl;
    }
};

int main()
{
    int n, m, p;
    cout << "Enter the size of first matrix: ";
    cin >> n >> m;
    cout << "Enter the size of second matrix: ";
    cin >> m >> p;
    multiplication *obj1 = new multiplication(n, m);
    obj1->getdata();
    multiplication *obj2 = new multiplication(m, p);
    obj2->getdata();
    multiplication obj3 = *obj1 * *obj2;
    cout << "First matrix is: " << endl;
    obj1->display();
    cout << "Second matrix is: " << endl;
    obj2->display();
    cout << "Multiplication of two matrix is: " << endl;
    obj3.display();
    cout << "Number of multiplication performed: " << c << endl;

    return 0;
}
