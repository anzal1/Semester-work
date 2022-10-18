#include <bits/stdc++.h>
using namespace std;

struct node
{
    int id;
    string name;
    node *next;
};
// overload all logical operators
class overload
{
    node *head;

public:
    overload()
    {
        head = NULL;
    }
    void operator+=(node *x)
    {
        if (head == NULL)
        {
            head = x;
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = x;
        }
    }
    bool operator!()
    {
        if (head == NULL)
        {
            return true;
        }
        return false;
    }
    bool operator&&(overload x)
    {
        if (head == NULL && x.head->id == -1)
        {
            return false;
        }
        return true;
    }
    bool operator||(overload x)
    {
        if (head == NULL || x.head->id == 0)
        {
            return false;
        }

        return true;
    }

    void display()
    {
        node *temp = head;
        while (temp != NULL)
        {
            cout << temp->id << " " << temp->name << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    cout << "Enter number of nodes: ";
    int n;
    cin >> n;
    cout << "Enter the id and name of the nodes: ";
    overload o;
    for (int i = 0; i < n; i++)
    {
        node *x = new node;
        cin >> x->id >> x->name;
        o += x;
    }
    cout << "Enter the id and name of the nodes: ";
    overload p;
    for (int i = 0; i < n; i++)
    {
        node *x = new node;
        cin >> x->id >> x->name;
        p += x;
    }
    cout << "o: " << endl;
    o.display();
    cout << "p: " << endl;
    p.display();
    cout << "!o: " << !o << endl;
    cout << "!p: " << !p << endl;
    cout << "o && p: " << (o && p) << endl;
    cout << "o || p: " << (o || p) << endl;
    return 0;
    
}