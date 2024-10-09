#include <bits/stdc++.h>
using namespace std;

set<string> dictionary;

void loadDictionary(const string &filename)
{
    ifstream file(filename);
    string word;
    while (file >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary.insert(word);
    }
    file.close();
}

bool isValidWord(string word)
{
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    return dictionary.find(word) != dictionary.end();
}

bool containsValidWords(string text)
{
    stringstream ss(text);
    string word;
    int validWordCount = 0;
    while (ss >> word)
    {
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

        if (isValidWord(word))
        {
            validWordCount++;
        }
    }

    // true if we found at least one valid word in the decrypted text
    return validWordCount > 0;
}

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
            decrypted_text += c; // Non-alphabetic characters remain unchanged
        }
    }
    return decrypted_text;
}

// Brute-force decryption with heuristic filtering
void bruteForce(string cipher_text)
{
    cout << "Attempting brute-force decryption:" << endl;
    for (int key = 0; key < 26; key++)
    {
        string decrypted_text = decrypt(cipher_text, key);

        // Print only if the decrypted text contains valid words
        if (containsValidWords(decrypted_text))
        {
            cout << "Key " << key << ": " << decrypted_text << endl;
        }
    }
}

int main()
{
    loadDictionary("dictionary.txt"); // dictionary file contains one word per line

    string cipher_text;
    cout << "Enter Cipher Text: ";
    getline(cin, cipher_text);

    bruteForce(cipher_text);

    return 0;
}
