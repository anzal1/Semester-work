#include <bits/stdc++.h>
using namespace std;

// wap to concatenate two strings using operator overloading

class string1
{
    string s;

public:
    string1()
    {
        s = "";
    }
    string1(string str)
    {
        s = str;
    }
    void display()
    {
        cout << s << endl;
    }
    string1 operator+(string1 str)
    {
        string1 temp;
        temp.s = this->s + str.s;
        return temp;
    }
    string1(string1 &str)
    {
        s = str.s;
    }
};

int main()
{
    string a, b;
    cout << "\nEnter the first string :";
    cin >> a;
    cout << "\nEnter the second string :";
    cin >> b;
    string1 s1(a), s2(b), s3;
    s3 = s1 + s2;
    cout << "\nThe concatenated string is :";
    s3.display();
    return 0;
}