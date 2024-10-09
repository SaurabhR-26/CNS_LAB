#include <bits/stdc++.h>
using namespace std;

void printUtil(vector<vector<char>> &dp)
{
    int n = dp.size();
    int depth = dp[0].size();
    cout << "Printing the cipher util array:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < depth; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

string encrypt(string plain_text, int depth, vector<vector<char>> &dp)
{
    int n = plain_text.size();
    int i = 0;
    int j = 0;
    bool isdesc = true;
    for (char ch : plain_text)
    {
        dp[i][j] = ch;
        if (isdesc)
        {
            if (i == depth - 1)
            {
                isdesc = false;
                i--;
            }
            else
                i++;
        }
        else
        {
            if (i == 0)
            {
                isdesc = true;
                i++;
            }
            else
                i--;
        }
        j++;
    }

    printUtil(dp);

    string ans = "";
    for (int a = 0; a < depth; a++)
    {
        for (int b = 0; b < n; b++)
        {
            if (dp[a][b] != '*')
                ans.push_back(dp[a][b]);
        }
    }
    return ans;
}

string decrypt(string cipher_text, int depth, vector<vector<char>> &dp)
{
    bool flag = true;
    int i = 0;
    int j = 0;
    int dep = 0;
    int n = cipher_text.size();
    // printUtil(dp);

    for (char ch : cipher_text)
    {
        // if (i == depth - 2)
        //     cout << "values:" << i << " " << j << endl;
        dp[i][j] = ch;
        if (flag) // then difference between max value and current depth
        {
            int diff = abs((depth - 1) - i);
            if (diff == 0)
                diff = (depth - 1) * 2;
            else
                diff *= 2;
            j += diff;
            if (j >= n)
            {
                i++;
                j = i;
                flag = true;
            }
            else
                flag = !flag;
        }
        else // then difference between 0 value and current depth
        {
            int diff = abs(0 - i);
            if (diff == 0)
                diff = (depth - 1) * 2;
            else
                diff *= 2;
            j += diff;
            if (j >= n)
            {
                i++;
                j = i;
                flag = true;
            }
            else
                flag = !flag;
        }
    }

    printUtil(dp);

    int a = 0;
    int b = 0;
    bool isdesc = true;
    string ans = "";
    while (b < n)
    {
        ans.push_back(dp[a][b]);
        if (isdesc)
        {
            if (a == depth - 1)
            {
                isdesc = false;
                a--;
            }
            else
                a++;
        }
        else
        {
            if (a == 0)
            {
                isdesc = true;
                a++;
            }
            else
                a--;
        }
        b++;
    }

    return ans;
}

int main()
{
    while (true)
    {
        cout << endl
             << "Choice:" << endl;
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter Option Num: ";
        int opt = 1;
        cin >> opt;
        if (opt == 3)
            break;
        if (opt < 1 || opt > 3)
            break;

        string cipher_text;
        string plain_text;
        int depth = 0;

        vector<vector<char>> dp;

        switch (opt)
        {
        case 1:
            cout << "Enter Plain Text: ";
            cin >> plain_text;
            cout << endl
                 << "Enter Depth: ";
            cin >> depth;
            if (depth >= plain_text.size() / 2)
            {
                cout << "Enter depth > 0 and depth < text_size/2" << endl;
                break;
            }
            for (int i = 0; i < depth; i++)
            {
                vector<char> tmp(plain_text.size(), '*');
                dp.push_back(tmp);
            }
            cipher_text = encrypt(plain_text, depth, dp);
            dp.clear();
            cout << "Encrypted Text: " << cipher_text;
            break;
        case 2:
            cout << "Enter Cipher Text: ";
            cin >> cipher_text;
            cout << endl
                 << "Enter Depth: ";
            cin >> depth;
            if (depth >= cipher_text.size() / 2)
            {
                cout << "Enter depth > 0 and depth < text_size/2" << endl;
                break;
            }
            for (int i = 0; i < depth; i++)
            {
                vector<char> tmp(cipher_text.size(), '#');
                dp.push_back(tmp);
            }
            plain_text = decrypt(cipher_text, depth, dp);
            dp.clear();
            cout << "Decrypted Text: " << plain_text;
            break;
        }
    }
    return 0;
}