#include <bits/stdc++.h>
using namespace std;
#define NOV 20

void input_processor_task(vector<vector<int>> &input_processor_task, int n, int m)
{
    cout << "Enter the input processor task\n";
    for (int i = 0; i < n; i++)
    {
        vector<int> v;
        for (int j = 0; j < m; j++)
        {
            cout << "Enter the value for processor " << i + 1 << " and task " << j + 1 << "\n";
            int x;
            cin >> x;
            v.push_back(x);
        }
        input_processor_task.push_back(v);
    }
}

bool CheckAcyclic(int edge[][2], int ed, bool check[], int v)
{
    int i;
    bool value;
    if (check[v] == true)
    {
        return false;
    }
    else
    {
        check[v] = true;
        for (i = ed; i >= 0; i--)
        {
            if (edge[i][0] == v)
            {
                return CheckAcyclic(edge, ed, check, edge[i][1]);
            }
        }
    }
    check[v] = false;

    if (i == 0)
        return true;
    else
        return true;
}

void GenerateRandGraphs(int e)
{
    int i, j, edge[e][2], count;

    bool check[21];

    i = 0;
    while (i < e)
    {
        edge[i][0] = rand() % NOV + 1;
        edge[i][1] = rand() % NOV + 1;

        for (j = 1; j <= 20; j++)
            check[j] = false;

        if (CheckAcyclic(edge, i, check, edge[i][0]) == true)
            i++;
    }

    cout << "\nThe generated random random graph is: ";
    for (i = 0; i < NOV; i++)
    {
        count = 0;
        cout << "\n\t" << i + 1 << "-> { ";
        for (j = 0; j < e; j++)
        {
            if (edge[j][0] == i + 1)
            {
                cout << edge[j][1] << "  ";
                count++;
            }
            else if (edge[j][1] == i + 1)
            {
                count++;
            }
            else if (j == e - 1 && count == 0)
                cout << "Isolated Vertex!";
        }
        cout << " }";
    }
}

void create_matrix_tt(int n, vector<vector<int>> &matrix)
{
    int arr[n + 1];
    int start = -1;
    for (int i = 0; i < n + 1; i++)
    {
        arr[i] = start;
        start++;
    }
    // print the random value array
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    for (int i = 0; i < n; i++)
    {
        vector<int> v;
        for (int j = 0; j < n; j++)
        {
            int random_value = rand() % n + 1;
            cout << "random value :" << i + 1 << arr[random_value] << "\n";
            v.push_back(arr[random_value]);
        }
        matrix.push_back(v);
    }
}

void print_matrix(vector<vector<int>> &matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    vector<int> task_arr;
    vector<int> processor_arr;
    vector<vector<int>> tp_matrix;
    vector<vector<int>> task_matrix;
    cout << "Enter number of tasks: ";
    int n;
    cin >> n;
    cout << "Enter the tasks :" << endl;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        task_arr.push_back(x);
    }
    cout << "Enter number of processors: ";
    int m;
    cin >> m;
    cout << "Enter the processors :" << endl;
    for (int i = 0; i < m; i++)
    {
        int x;
        cin >> x;
        processor_arr.push_back(x);
    }
    input_processor_task(tp_matrix, task_arr.size(), processor_arr.size());
    print_matrix(tp_matrix);
    create_matrix_tt(n, task_matrix);
    print_matrix(task_matrix);
    GenerateRandGraphs(n);
}

//  0   1   3
// -1   0   2
// -1  -1   0