#include <bits/stdc++.h>
using namespace std;

// overload allocation and free operators

struct Tree
{
    int data;
    Tree *left;
    Tree *right;
};

class overload
{
    Tree *root;

public:
    overload()
    {
        root = NULL;
    }
    void *operator new(size_t size)
    {
        void *p = malloc(size);
        if (!p)
        {
            bad_alloc ba;
            throw ba;
        }
        return p;
    }
    void operator delete(void *p)
    {
        free(p);
    }
    void insert(int x)
    {
        Tree *temp = new Tree;
        temp->data = x;
        temp->left = NULL;
        temp->right = NULL;
        if (root == NULL)
        {
            root = temp;
        }
        else
        {
            Tree *temp1 = root;
            while (1)
            {
                if (x < temp1->data)
                {
                    if (temp1->left == NULL)
                    {
                        temp1->left = temp;
                        break;
                    }
                    else
                    {
                        temp1 = temp1->left;
                    }
                }
                else
                {
                    if (temp1->right == NULL)
                    {
                        temp1->right = temp;
                        break;
                    }
                    else
                    {
                        temp1 = temp1->right;
                    }
                }
            }
        }
    }
    void display()
    {
        // display tree with each level in a new line and connected with a / and space formatted such that it looks like a tree
        queue<Tree *> q;
        q.push(root);
        q.push(NULL);
        while (!q.empty())
        {
            Tree *temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << endl;
                if (!q.empty())
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout << temp->data << " ";
                if (temp->left != NULL)
                {
                    q.push(temp->left);
                }
                if (temp->right != NULL)
                {
                    q.push(temp->right);
                }
            }
        }
    }
};

int main()
{
    overload a;
    cout << "Enter number of elements: ";
    int n;
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a.insert(x);
    }
    a.display();
    return 0;
}