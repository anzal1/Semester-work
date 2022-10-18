#include <bits/stdc++.h>
using namespace std;

struct node
{
    int id;
    string name;
    node *next;
};

// overload subscript operator
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
    node *operator[](int x)
    {
        node *temp = head;
        while (temp != NULL)
        {
            if (temp->id == x)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    node *operator[](string name)
    {
        node *temp = head;
        while (temp != NULL)
        {
            if (temp->name == name)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
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
    overload o;
    cout << "Enter the number of nodes: ";
    int n;
    cin >> n;
    cout << "Enter the id and name of the nodes: ";
    for (int i = 0; i < n; i++)
    {
        node *temp = new node;
        cin >> temp->id >> temp->name;
        temp->next = NULL;
        o += temp;
    }
    cout << "Enter the id of the node to be searched: ";
    int x;
    cin >> x;
    node *temp = o[x];
    if (temp != NULL)
    {
        cout << temp->id << " " << temp->name << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
    cout << "Enter the name of the node to be searched: ";
    string name;
    cin >> name;
    temp = o[name];
    if (temp != NULL)
    {
        cout << temp->id << " " << temp->name << endl;
    }
    else
    {
        cout << "Not found" << endl;
    }
}
