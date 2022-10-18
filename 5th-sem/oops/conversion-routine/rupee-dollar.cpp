#include <bits/stdc++.h>
using namespace std;

// design a classes such that they support following statements
//  Rupee r1 ,r2 ; Dollar d1,d2;
// d1=r1 //convert r1 to dollar and store in d1
// r2=d2 //convert d2 to rupee and store in r2
// write the program such that
// case 1 :when conversion routines are in source class
// case 2 :when conversion routines are in  destination class
// 1 rupee = 0.014 dollar

class Rupee;
class Dollar
{

public:
    float dollar;
    Dollar()
    {
        dollar = 0;
    }
    Dollar(float d)
    {
        dollar = d;
    }
    void display()
    {
        cout << dollar << endl;
    }
    operator Rupee();
};

class Rupee
{

public:
    float rupee;
    Rupee()
    {
        rupee = 0;
    }
    Rupee(float r)
    {
        rupee = r;
    }
    void display()
    {
        cout << rupee << endl;
    }
    operator Dollar();
};

Dollar::operator Rupee()
{
    Rupee r;
    r.rupee = dollar / 0.014;
    return r;
}

Rupee::operator Dollar()
{
    Dollar d;
    d.dollar = rupee * 0.014;
    return d;
}

int main()
{
    cout << "Enter the amount in rupees" << endl;
    float r;
    cin >> r;
    Rupee r1(r);
    Dollar d1;
    d1 = r1;
    cout << "The amount in dollars is" << endl;
    d1.display();
    cout << "Enter the amount in dollars" << endl;
    float d;
    cin >> d;
    Dollar d2(d);
    Rupee r2;
    r2 = d2;
    cout << "The amount in rupees is" << endl;
    r2.display();
    return 0;
}
