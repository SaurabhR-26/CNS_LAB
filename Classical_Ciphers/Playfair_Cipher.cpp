#include <bits/stdc++.h>
using namespace std;

string formatText(string text)
{
    string formatted = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == 'j')
            text[i] = 'i';

        if (formatted.length() > 0 && formatted.back() == text[i])
        {
            formatted.push_back('x');
        }
        formatted.push_back(text[i]);
    }

    if (formatted.length() % 2 != 0)
    {
        formatted.push_back('x');
    }

    return formatted;
}

void generateKeyMatrix(string key, char keyMatrix[5][5])
{
    unordered_set<char> used;
    int x = 0, y = 0;

    for (char c : key)
    {
        if (c == 'j')
            c = 'i';

        if (used.find(c) == used.end())
        {
            keyMatrix[x][y++] = c;
            used.insert(c);
            if (y == 5)
            {
                y = 0;
                x++;
            }
        }
    }

    for (char c = 'a'; c <= 'z'; c++)
    {
        if (c == 'j')
            continue;

        if (used.find(c) == used.end())
        {
            keyMatrix[x][y++] = c;
            used.insert(c);
            if (y == 5)
            {
                y = 0;
                x++;
            }
        }
    }
}

pair<int, int> findPosition(char keyMatrix[5][5], char c)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (keyMatrix[i][j] == c)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

string encrypt(string plain_text, string key)
{
    char keyMatrix[5][5];
    generateKeyMatrix(key, keyMatrix);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << keyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    plain_text = formatText(plain_text);

    string cipher_text = "";
    for (int i = 0; i < plain_text.length(); i += 2)
    {
        pair<int, int> p1 = findPosition(keyMatrix, plain_text[i]);
        pair<int, int> p2 = findPosition(keyMatrix, plain_text[i + 1]);

        if (p1.first == p2.first)
        {
            // Same row
            cipher_text.push_back(keyMatrix[p1.first][(p1.second + 1) % 5]);
            cipher_text.push_back(keyMatrix[p2.first][(p2.second + 1) % 5]);
        }
        else if (p1.second == p2.second)
        {
            // Same column
            cipher_text.push_back(keyMatrix[(p1.first + 1) % 5][p1.second]);
            cipher_text.push_back(keyMatrix[(p2.first + 1) % 5][p2.second]);
        }
        else
        {
            // Rectangle
            cipher_text.push_back(keyMatrix[p1.first][p2.second]);
            cipher_text.push_back(keyMatrix[p2.first][p1.second]);
        }
    }

    return cipher_text;
}

string decrypt(string cipher_text, string key)
{
    char keyMatrix[5][5];
    generateKeyMatrix(key, keyMatrix);

    string plain_text = "";
    for (int i = 0; i < cipher_text.length(); i += 2)
    {
        pair<int, int> p1 = findPosition(keyMatrix, cipher_text[i]);
        pair<int, int> p2 = findPosition(keyMatrix, cipher_text[i + 1]);

        if (p1.first == p2.first)
        {
            // Same row
            plain_text.push_back(keyMatrix[p1.first][(p1.second + 4) % 5]);
            plain_text.push_back(keyMatrix[p2.first][(p2.second + 4) % 5]);
        }
        else if (p1.second == p2.second)
        {
            // Same column
            plain_text.push_back(keyMatrix[(p1.first + 4) % 5][p1.second]);
            plain_text.push_back(keyMatrix[(p2.first + 4) % 5][p2.second]);
        }
        else
        {
            // Rectangle
            plain_text.push_back(keyMatrix[p1.first][p2.second]);
            plain_text.push_back(keyMatrix[p2.first][p1.second]);
        }
    }

    // Remove 'x' used for padding
    return plain_text;
}

int main()
{
    while (true)
    {
        cout << endl
             << "Playfair Cipher:" << endl;
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

        string key, cipher_text, plain_text;

        switch (opt)
        {
        case 1:
            cout << "Enter Plain Text: ";
            cin >> plain_text;
            cout << "Enter Key: ";
            cin >> key;
            cipher_text = encrypt(plain_text, key);
            cout << "Encrypted Text: " << cipher_text;
            break;

        case 2:
            cout << "Enter Cipher Text: ";
            cin >> cipher_text;
            cout << "Enter Key: ";
            cin >> key;
            plain_text = decrypt(cipher_text, key);
            cout << "Decrypted Text: " << plain_text;
            break;
        }
    }
    return 0;
}
