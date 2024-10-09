#include <bits/stdc++.h>
using namespace std;

string encrypt(string plain_text, int cols)
{
    int n = plain_text.size();

    if ((n % cols) != 0)
    {
        int diff = (n % cols);
        diff = cols - diff;
        while (diff > 0)
        {
            plain_text.push_back('$');
            diff--;
        }
    }
    // hel
    // low
    // orl
    // d$$

    int cnt = 0;
    string ans = "";
    while (cnt < cols)
    {
        for (int i = cnt; i < plain_text.length(); i += cols)
            ans.push_back(plain_text[i]);
        cnt++;
    }

    return ans;
}

string decrypt(string cipher_text, int cols)
{
    int cnt = 0;
    string ans = "";
    int gap = cipher_text.length() / cols;
    while (cnt < gap)
    {
        for (int i = cnt; i < cipher_text.length(); i += gap)
            ans.push_back(cipher_text[i]);
        cnt++;
    }

    while (ans.length() > 0 && ans[ans.length() - 1] == '$')
        ans.pop_back();

    return ans;
}

int main()
{
    while (true)
    {
        cout << endl
             << "Columnar Transpose:" << endl;
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
        int cols = 0;

        switch (opt)
        {
        case 1:
            cout << "Enter Plain Text: ";
            cin >> plain_text;
            cout << endl
                 << "Enter Columns: ";
            cin >> cols;
            if (cols < 2 || cols >= plain_text.length())
            {
                cout << endl
                     << "Warning ! : Give proper value for cols (>=2 and < plain_text length)" << endl;
                break;
            }

            cipher_text = encrypt(plain_text, cols);

            cout << "Encrypted Text: " << cipher_text;
            break;
        case 2:
            cout << "Enter Cipher Text: ";
            cin >> cipher_text;
            cout << endl
                 << "Enter Columns: ";
            cin >> cols;
            if (cols < 2 || cols >= cipher_text.length())
            {
                cout << endl
                     << "Warning ! : Give proper value for cols (>=2 and < cipher_text length)" << endl;
                break;
            }

            plain_text = decrypt(cipher_text, cols);

            cout << "Decrypted Text: " << plain_text;
            break;
        }
    }
    return 0;
}