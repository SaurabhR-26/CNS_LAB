#include <bits/stdc++.h>
using namespace std;

string decrypt(string cipher_text, int key)
{
    string decrypted_text = "";
    for (char c : cipher_text)
    {
        if (isalpha(c))
        {
            char offset = isupper(c) ? 'A' : 'a';
            decrypted_text += (c - offset - key + 26) % 26 + offset;
        }
        else
        {
            decrypted_text += c; // Non-alphabetic characters remain unchanged (e.g., spaces)
        }
    }
    return decrypted_text;
}

void bruteForce(string cipher_text)
{
    cout << "Attempting brute-force decryption:" << endl;
    for (int key = 0; key < 26; key++)
    {
        string decrypted_text = decrypt(cipher_text, key);
        cout << "Key " << key << ": " << decrypted_text << endl;
    }
}

int main()
{
    string cipher_text;
    cout << "Enter Cipher Text: ";
    getline(cin, cipher_text); // Get full line including spaces

    bruteForce(cipher_text);

    return 0;
}
