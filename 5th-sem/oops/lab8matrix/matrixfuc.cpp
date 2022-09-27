#include <bits/stdc++.h>
using namespace std;

// write a program to take two matrix as input and check if they can be multiplied or not.if they can be mulitplied then add and mutliply them using '+' and '*' operator overloading

class matrix
{
    int row;
    int col;
    int **mat;

public:
    matrix(int r, int c)
    {
        row = r;
        col = c;
        mat = new int *[row];
        for (int i = 0; i < row; i++)
        {
            mat[i] = new int[col];
        }
    }
    void getdata()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cin >> mat[i][j];
            }
        }
    }
    void display()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    matrix operator+(matrix m)
    {
        matrix temp(row, col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                temp.mat[i][j] = mat[i][j] + m.mat[i][j];
            }
        }
        return temp;
    }
    matrix operator*(matrix m)
    {
        matrix temp(row, m.col);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < m.col; j++)
            {
                temp.mat[i][j] = 0;
                for (int k = 0; k < col; k++)
                {
                    temp.mat[i][j] += mat[i][k] * m.mat[k][j];
                }
            }
        }
        return temp;
    }
    bool operator==(matrix m)
    {
        if (row == m.row && col == m.col)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    int r1, c1, r2, c2;
    cout << "Enter the number of rows and columns of first matrix" << endl;
    cin >> r1 >> c1;
    matrix m1(r1, c1);
    cout << "Enter the elements of first matrix" << endl;
    m1.getdata();
    cout << "Enter the number of rows and columns of second matrix" << endl;
    cin >> r2 >> c2;
    matrix m2(r2, c2);
    cout << "Enter the elements of second matrix" << endl;
    m2.getdata();
    if (m1 == m2)
    {
        cout << "Addition of two matrix is" << endl;
        matrix m3 = m1 + m2;
        m3.display();
        cout << "Multiplication of two matrix is" << endl;
        matrix m4 = m1 * m2;
        m4.display();
    }
    else
    {
        cout << "Matrix cannot be multiplied" << endl;
    }
    return 0;
}