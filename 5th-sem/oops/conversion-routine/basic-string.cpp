#include <bits/stdc++.h>
using namespace std;

// write a program to perform conversion between basic string and string class

class convert
{
public:
    string basic_to_string(char *s)
    {
        string str;
        int i = 0;
        while (s[i] != '\0')
        {
            str.push_back(s[i]);
            i++;
        }
        return str;
    }
    char *string_to_basic(string s)
    {
        char *str = new char[s.length() + 1];
        int i = 0;
        while (s[i] != '\0')
        {
            str[i] = s[i];
            i++;
        }
        str[i] = '\0';
        return str;
    }
};

int main()
{
    convert c;
    char *s = "hello";
    string str = c.basic_to_string(s);
    cout << str << endl;
    cout << "Enter a string to convert to basic string" << endl;
    // take input with multiple words
    getline(cin, str);
    s = c.string_to_basic(str);
    cout << s << endl;
    return 0;
}