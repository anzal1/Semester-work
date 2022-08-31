#include <bits/stdc++.h>
using namespace std;

class Account
{
private:
    int acc;
    float balance;

public:
    Account()
    {
        acc = 0;
        balance = 0;
    }
    Account(int accno)
    {
        acc = accno;
        balance = 0;
    }
    Account(int a, float b)
    {
        acc = a;
        balance = b;
    }

    void display()
    {
        cout << "Account no: " << acc << endl;
        cout << "Balance: " << balance << endl;
    }

    void amountTransfer(Account &a, Account &b, float amt)
    {
        if (a.balance >= amt)
        {
            a.balance -= amt;
            b.balance += amt;
        }
        else
        {
            cout << "Insufficient balance" << endl;
        }
    }
};


int main()
{
    Account a1(1234, 1000);
    Account a2(5678, 2000);
    a1.display();
    a2.display();
    a1.amountTransfer(a1, a2, 500);
    a1.display();
    a2.display();
    return 0;
}