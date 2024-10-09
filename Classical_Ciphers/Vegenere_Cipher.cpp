#include <iostream>
#include <string>
using namespace std;

string generateKey(const string &plaintext, const string &keyword)
{
    string key = keyword;
    while (key.length() < plaintext.length())
    {
        key += keyword;
    }
    return key.substr(0, plaintext.length());
}

string encrypt(const string &plaintext, const string &key)
{
    string ciphertext;
    for (size_t i = 0; i < plaintext.length(); i++)
    {
        char p = plaintext[i];
        char k = key[i];
        char c = ((p - 'A') + (k - 'A')) % 26 + 'A';
        ciphertext += c;
    }
    return ciphertext;
}

string decrypt(const string &ciphertext, const string &key)
{
    string plaintext;
    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        char c = ciphertext[i];
        char k = key[i];
        char p = ((c - 'A') - (k - 'A') + 26) % 26 + 'A';
        plaintext += p;
    }
    return plaintext;
}

int main()
{
    string plaintext, keyword;
    cout << "Enter the plaintext (uppercase only): ";
    cin >> plaintext;
    cout << "Enter the keyword (uppercase only): ";
    cin >> keyword;

    string key = generateKey(plaintext, keyword);

    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted ciphertext: " << ciphertext << endl;

    string decryptedText = decrypt(ciphertext, key);
    cout << "Decrypted plaintext: " << decryptedText << endl;

    return 0;
}
