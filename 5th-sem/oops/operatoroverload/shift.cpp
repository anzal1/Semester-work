#include <bits/stdc++.h>
using namespace std;

// overload all shift operators
class overload
{
    bitset<8> a;

public:
    overload(int x)
    {
        a = x;
    }
    overload operator<<(int x)
    {
        overload temp(0);
        temp.a = a << x;
        return temp;
    }
    overload operator>>(int x)
    {
        overload temp(0);
        temp.a = a >> x;
        return temp;
    }
    void display()
    {
        cout << a << endl;
    }
};

int main()
{
    cout << "Enter two numbers: ";
    int x, y;
    cin >> x >> y;
    overload a(x), b(y);
    overload c(0);
    c = a << 2;
    cout << "a: ";
    a.display();
    cout << "b: ";
    b.display();
    cout << "a << 2: ";
    c.display();
    c = a >> 2;
    cout << "a >> 2: ";
    c.display();
    return 0;
}