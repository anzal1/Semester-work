#include <bits/stdc++.h>
using namespace std;

// write a program to highlight the use of copy constructor and overloaded '==' operator

class comp
{
    int real;
    int img;

public:
    comp(int r, int i)
    {
        real = r;
        img = i;
    }
    comp(comp &c)
    {
        real = c.real;
        img = c.img;
    }
    void display()
    {
        cout << real << " + " << img << "i" << endl;
    }
    comp operator==(comp c)
    {
        if (real == c.real && img == c.img)
        {
            cout << "equal" << endl;
        }
        else
        {
            cout << "not equal" << endl;
        }
        return c;
    }
};

int main()
{
    comp c1(2, 3), c2(2, 3), c3(3, 4);
    c1.display();
    c2.display();
    c3.display();
    c3 = c1 == c2;
    c1 == c3;
    return 0;
}
