
#include <bits/stdc++.h>
using namespace std;

class ABC
{

public:
    int x2, y2;
    void set_data(int a, int b)
    {
        this->x2 = a;
        this->y2 = b;
    }
};


class XYZ
{

public:
    int x1, y1;
    void set_data(int a, int b)
    {
        this->x1 = a;
        this->y1 = b;
    }

    friend void distance(XYZ t1, ABC t2)
    {
        cout << sqrt(pow(t2.x2 - t1.x1, 2) + pow(t1.y1 - t2.y2, 2));
    }
};

int main()
{
    ABC _abc;
    XYZ _xyz;
    _xyz.set_data(1, 2);
    _abc.set_data(3, 4);
    cout << "The distance between the two points is: ";
    distance(_xyz, _abc); // callin friend function
    cout << endl;
    return 0;
}
