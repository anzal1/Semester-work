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

    int operator==(matrix m)
    {
        // return  -1 if matrix can neither be mulitplied nor added
        //  return 0 if matrix can be added but not multiplied
        //  return 1 if matrix can be multiplied but not added
        //  return 2 if matrix can be multiplied and added
        if (row == m.row && col == m.col)
        {
            if (col == m.row)
            {
                return 2;
            }
            else
            {
                return 0;
            }
        }
        else if (col == m.row)
        {
            return 1;
        }

        else
        {
            return -1;
        }
    }
};

int main()
{
    cout << "Enter the number of rows and columns of first matrix" << endl;
    int r1, c1;
    cin >> r1 >> c1;
    matrix m1(r1, c1);
    cout << "Enter the number of rows and columns of second matrix" << endl;
    int r2, c2;
    cin >> r2 >> c2;
    matrix m2(r2, c2);
    cout << "Enter the elements of first matrix" << endl;
    m1.getdata();
    cout << "Enter the elements of second matrix" << endl;
    m2.getdata();
    cout << "The first matrix is" << endl;
    m1.display();
    cout << "The second matrix is" << endl;
    m2.display();
    int ch = m1 == m2;
    if (ch == 0)
    {
        cout << "Addition is possible" << endl;
        matrix m3 = m1 + m2;
        cout << "The sum of the two matrix is" << endl;
        m3.display();
    }
    else if (ch == 1)
    {
        cout << "Multiplication is possible" << endl;
        matrix m3 = m1 * m2;
        cout << "The product of the two matrix is" << endl;
        m3.display();
    }
    else if (ch == 2)
    {
        cout << "Addition and Multiplication is possible" << endl;
        matrix m3 = m1 + m2;
        cout << "The sum of the two matrix is" << endl;
        m3.display();
        matrix m4 = m1 * m2;
        cout << "The product of the two matrix is" << endl;
        m4.display();
    }
    else
    {
        cout << "Addition and Multiplication is not possible" << endl;
    }
    return 0;
}