
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
    int index = 0;
    reverse(target.begin(), target.end());
    for (int i = 0; i < target.length(); i++)
    {
        if (target[i] == 'b')
        {
            index += pow(2, i);
        }
    }
    // cout << "place index : " << index << endl;
    return (char)(ascii_value + index);
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
                to_parse[i] = '1';
            }
        }
        else if (to_parse[i] == ' ' && encrypted[i] == 'a')
        {
            to_parse[i] = '0';
        }
    }
    // cout << encrypted << endl;
    return to_parse;
}

string decrypt(string target)
{
    string parsed = cleaner(target, true, false);
    string to_ab = "";
    for (int i = 0; i < parsed.length(); i++)
    {
        if ((parsed[i] >= 'A' && parsed[i] <= 'Z') || parsed[i] == '1')
        {
            to_ab += 'b';
        }
        else if ((parsed[i] >= 'a' && parsed[i] <= 'z') || parsed[i] == '0')
        {
            to_ab += 'a';
        }
    }
    // cout<<"parsed : "<<to_ab<<endl;
    string changedstring = "";
    int start = 0;
    while (start < to_ab.length())
    {

        changedstring += to_char(to_ab.substr(start, 5));
        // cout << changedstring << endl;
        start += 5;
    }
    return changedstring;
}

int main()
{

    // // aaaaabaabbbaabbaaaaaaaabaababaabbababbbababba
    string intake = "the quick brown fox jumps over the lazy dog and then it went on to attend a class";
    string encrypted_display = encrypt_baconian("Attack &now", intake);
    string decrypted_final = decrypt(encrypted_display);
    for (int i = 0; i < encrypted_display.length(); i++)
    {
        if (encrypted_display[i] == '0' || encrypted_display[i] == '1')
        {
            cout << " ";
        }
        else
        {
            cout << encrypted_display[i];
        }
    }
    cout << "\n\n";
    cout << decrypted_final << endl;

    return 0;
}
