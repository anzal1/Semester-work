
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

string to_binary(int a)
{
    string binary_rep = "";
    while (a)
    {
        if (a % 2 == 1)
        {
            binary_rep = 'b' + binary_rep;
        }
        else
        {
            binary_rep = 'a' + binary_rep;
        }
        a /= 2;
    }
    int diff = 5 - binary_rep.length();
    reverse(binary_rep.begin(), binary_rep.end());
    while (diff--)
    {
        binary_rep += 'a';
    }
    reverse(binary_rep.begin(), binary_rep.end());
    return binary_rep;
}

char to_char(string target)
{
    int ascii_value = 97;
    for (int i = 0; i < target.length(); i++)
    {
        if (target[i] == 'b')
        {
            ascii_value += pow(2, i);
        }
    }

    return (char)ascii_value;
}
// Attack Now

string cleaner(string a, bool removespace, bool removecapital)
{
    string cleaned = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (removespace)
        {
            if (a[i] != ' ' && a[i] != '#' && a[i] != '@' && a[i] != '%' && a[i] != '&' && a[i] != '!' && a[i] != '.' && a[i] != '*')
            {
                if (removecapital)
                {
                    if (a[i] >= 'A' && a[i] <= 'Z')
                    {
                        cleaned += ((a[i] - 'A') + 'a');
                    }
                    else
                    {
                        cleaned += a[i];
                    }
                }
                else
                {
                    cleaned += a[i];
                }
            }
        }
        else
        {
            if (a[i] != '#' && a[i] != '@' && a[i] != '%' && a[i] != '&' && a[i] != '!' && a[i] != '.' && a[i] != '*')
            {
                if (removecapital)
                {
                    if (a[i] >= 'A' && a[i] <= 'Z')
                    {
                        cleaned += ((a[i] - 'A') + 'a');
                    }
                    else
                    {
                        cleaned += a[i];
                    }
                }
                else
                {
                    cleaned += a[i];
                }
            }
        }
    }
    return cleaned;
}

string encrypt_baconian(string s, string intake)
{
    s = cleaner(s, true, true);
    string encrypted = "";
    for (int i = 0; i < s.length(); i++)
    {
        encrypted += to_binary(int(s[i] - 'a'));
    }
    string to_parse = intake.substr(0, encrypted.length());
    for (int i = 0; i < encrypted.length(); i++)
    {
        if (encrypted[i] == 'b')
        {
            if (to_parse[i] >= 'a' && to_parse[i] <= 'z')
            {
                to_parse[i] = ((to_parse[i] - 'a') + 'A');
            }
            else if (to_parse[i] == ' ')
            {
                to_parse[i] = 'b';
            }
        }
        else
        {
            if (to_parse[i] == ' ')
            {
                to_parse[i] == 'a';
            }
        }
    }
    cout << encrypted << endl;
    return to_parse;
}

string decrypt(string target)
{
    string parsed = cleaner(target, true, false);
    string to_ab = "";
    for (int i = 0; i < parsed.length(); i++)
    {
        if (parsed[i] >= 'A' && parsed[i] <= 'Z')
        {
            to_ab += 'b';
        }
        else
        {
            to_ab += 'a';
        }
    }
    string changedstring = "";
    int start = 0;
    while (start <= to_ab.length())
    {
        changedstring += to_char(to_ab.substr(start, start + 5));
        start += 5;
    }
    return changedstring;
}

int main()
{

    // // aaaaabaabbbaabbaaaaaaaabaababaabbababbbababba
    string intake = "the quick brown fox jumps over the lazy dog and then it went on to attend a class";
    cout << encrypt_baconian("Test", intake) << endl;
    // cout<<to_binary("TEST")
    // // cout<<to_char("aaaaa")<<endl;
    // cout<<decrypt("the qUicKbBroWN fox jumPs OvEr THeblAZY DoGba")<<endl;

    return 0;
}
