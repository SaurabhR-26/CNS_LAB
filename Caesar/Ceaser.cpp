#include <iostream>
#include <string>
using namespace std;

// Encryption function
string encryptCaesarCipher(string text, int shift)
{
    string result = "";
    
    for (char charac : text)
    {
        if (isupper(charac))
        {
            result += char((charac - 'A' + shift) % 26 + 'A');
        }
        else if (islower(charac))
        {
            result += char((charac - 'a' + shift) % 26 + 'a');
        }
        else if (isdigit(charac))
        {
            result += char((charac - '0' + shift) % 10 + '0');
        }
        else
        {
            result += charac;
        }
    }
    return result;
}

// Decryption function
string decryptCaesarCipher(string text, int shift)
{
    string result = "";
    
    for (char charac : text)
    {
        if (isupper(charac))
        {
            result += char((charac - 'A' - shift + 26) % 26 + 'A');
        }
        else if (islower(charac))
        {
            result += char((charac - 'a' - shift + 26) % 26 + 'a');
        }
        else if (isdigit(charac))
        {
            result += char((charac - '0' - shift + 20) % 10 + '0');
        }
        else
        {
            result += charac;
        }
    }
    return result;
}

int main()
{
    string text;
    int shift;

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the shift: ";
    cin >> shift;

    string encryptedText = encryptCaesarCipher(text, shift);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = decryptCaesarCipher(encryptedText, shift);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}