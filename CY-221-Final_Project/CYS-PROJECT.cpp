#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;

// Simple symmetric encryption using XOR
string xorEncrypt(const string &data, char key)
{
    string encrypted = data;
    for (size_t i = 0; i < data.size(); i++)
    {
        // XOR with the key
        encrypted[i] ^= key;
    }
    return encrypted;
}

// Simple RSA-like key generation
pair<int, int> generateKeys()
{
    // Example prime number
    int p = 61;

    // Example prime number
    int q = 53;

    // Modulus for public and private keys
    int n = p * q;

    // Euler's totient function
    int phi = (p - 1) * (q - 1);

    // Public exponent (must be coprime with phi)
    int e = 17;

    // Private exponent (calculated using modular inverse of e mod phi)
    int d = 2753;

    // Return public key (e, n)
    return {e, n};
}

// Simple RSA-like encryption (asymmetric encryption)
int rsaEncrypt(int message, int e, int n)
{
    int result = 1;
    for (int i = 0; i < e; i++)
    {
        // Modular exponentiation
        result = (result * message) % n;
    }
    return result;
}

// Simple RSA-like decryption
int rsaDecrypt(int cipher, int d, int n)
{
    int result = 1;
    for (int i = 0; i < d; i++)
    {
        // Modular exponentiation
        result = (result * cipher) % n;
    }
    return result;
}

// Convert string to integer
int stringToInt(const string &str)
{
    int result = 0;
    for (char c : str)
    {
        result = result * 256 + c;
    }
    return result;
}

// Convert integer back to string
string intToString(int num)
{
    string result;
    while (num > 0)
    {
        result = char(num % 256) + result;
        num /= 256;
    }
    return result;
}

// Function to encrypt the plaintext using Rail Fence Cipher
string railfenceencrypt(string plaintext, int key)
{
    if (key <= 1)

        // No encryption for key <= 1
        return plaintext;

    // Create a vector of strings for each rail
    vector<string> rail(key);

    // 1 means moving down, -1 means moving up
    int direction = 1;
    int row = 0;

    // Fill the rails with characters in a zigzag pattern
    for (char ch : plaintext)
    {
        rail[row] += ch;
        row += direction;

        // Reverse direction when reaching the top or bottom rail
        if (row == 0 || row == key - 1)
        {
            direction *= -1;
        }
    }

    // Combine all rails into the ciphertext
    string ciphertext = "";
    for (const string &r : rail)
    {
        ciphertext += r;
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Rail Fence Cipher
string railfencedecrypt(string ciphertext, int key)
{
    if (key <= 1)
        // No decryption for key <= 1
        return ciphertext;

    // Track the number of characters in each rail
    vector<int> railLengths(key, 0);

    // 1 means moving down, -1 means moving up
    int direction = 1;
    int row = 0;

    // Calculate the length of each rail based on the zigzag pattern
    for (char ch : ciphertext)
    {
        railLengths[row]++;
        row += direction;

        if (row == 0 || row == key - 1)
        {
            direction *= -1;
        }
    }

    // Fill the rails with characters from the ciphertext
    vector<string> rail(key);
    int index = 0;
    for (int i = 0; i < key; i++)
    {
        rail[i] = ciphertext.substr(index, railLengths[i]);
        index += railLengths[i];
    }

    // Reconstruct the plaintext by following the zigzag pattern
    string plaintext = "";
    row = 0;
    direction = 1;

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        // Take the first character of the current rail
        plaintext += rail[row][0];

        // Remove the used character
        rail[row] = rail[row].substr(1);
        row += direction;

        if (row == 0 || row == key - 1)
        {
            direction *= -1;
        }
    }

    return plaintext;
}

// Function to generate the full key based on the plaintext length
string generateKey(string plaintext, string key)
{
    int textLength = plaintext.length();
    int keyLength = key.length();
    string fullKey = key;

    // Repeat the key until it matches the length of the plaintext
    for (int i = 0; fullKey.length() < textLength; i++)
    {
        fullKey += key[i % keyLength];
    }

    return fullKey;
}

// Function to encrypt the plaintext using Vigenère Cipher
string vigencrypt(string plaintext, string key)
{
    string ciphertext = "";
    key = generateKey(plaintext, key);

    for (size_t i = 0; i < plaintext.length(); i++)
    {
        if (isalpha(plaintext[i]))
        {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char shift = islower(key[i]) ? key[i] - 'a' : key[i] - 'A';
            ciphertext += (plaintext[i] - base + shift) % 26 + base;
        }
        else
        {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Vigenère Cipher
string vigdecrypt(string ciphertext, string key)
{
    string plaintext = "";
    key = generateKey(ciphertext, key);

    for (size_t i = 0; i < ciphertext.length(); i++)
    {
        if (isalpha(ciphertext[i]))
        {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            char shift = islower(key[i]) ? key[i] - 'a' : key[i] - 'A';
            plaintext += (ciphertext[i] - base - shift + 26) % 26 + base;
        }
        else
        {
            plaintext += ciphertext[i];
        }
    }

    return plaintext;
}

// Function to encrypt the plaintext using Caesar Cipher
string caesar_encrypt(string text, int shift)
{
    string result = "";
    for (char ch : text)
    {
        if (isalpha(ch))
        {
            char base = islower(ch) ? 'a' : 'A';
            result += (ch - base + shift) % 26 + base;
        }
        else
        {
            result += ch;
        }
    }
    return result;
}

// Function to decrypt the ciphertext using Caesar Cipher
string caesar_decrypt(string text, int shift)
{
    // Reverse the shift for decryption
    return caesar_encrypt(text, 26 - (shift % 26));
}

// Helper function to calculate determinant of a 2x2 matrix
int determinant(int matrix[2][2])
{
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

// Helper function to find the adjugate of a 2x2 matrix
void adjugate(int matrix[2][2], int adj[2][2])
{
    adj[0][0] = matrix[1][1];
    adj[0][1] = -matrix[0][1];
    adj[1][0] = -matrix[1][0];
    adj[1][1] = matrix[0][0];
}

// Function to compute modular inverse of a number under modulo m for rsa
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;

    // Inverse does not exist
    return -1;
}

// Efficient modular exponentiation
int modularExponentiation(int base, int exp, int mod)
{
    int result = 1;

    // Reduce base if it's greater than mod
    base = base % mod;
    while (exp > 0)
    {
        // If exponent is odd, multiply the base with the result
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        // Square the base and halve the exponent
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Function to generate a random key of the same length as the plaintext
string generateRandomKey(const string &plaintext)
{
    string key = "";

    // Random number generator
    mt19937 gen(static_cast<unsigned long>(time(nullptr)));

    // Generate random values in the byte range (0-255)
    uniform_int_distribution<int> dist(0, 255);

    for (size_t i = 0; i < plaintext.length(); ++i)
    {
        // Random number Generator
        key += static_cast<char>(dist(gen));
    }

    return key;
}

// Function to encrypt the plaintext using the OTP
string encrypt(const string &plaintext, const string &key)
{
    string ciphertext = "";

    for (size_t i = 0; i < plaintext.length(); ++i)
    {
        // XOR each character of the plaintext with the key
        ciphertext += plaintext[i] ^ key[i];
    }
    return ciphertext;
}

// Function to decrypt the ciphertext using the OTP
string decrypt(const string &ciphertext, const string &key)
{
    string decryptedText = "";

    for (size_t i = 0; i < ciphertext.length(); ++i)
    {
        // XOR again to get the original plaintext
        decryptedText += ciphertext[i] ^ key[i];
    }

    return decryptedText;
}
// Function to compute the greatest common divisor (gcd)
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to encrypt a message (integer) using RSA
int encrypt(int message, int e, int n)
{
    int result = 1;
    for (int i = 0; i < e; i++)
    {
        result = (result * message) % n;
    }
    return result;
}

// Function to decrypt a ciphertext (integer) using RSA
int decrypt(int ciphertext, int d, int n)
{
    int result = 1;
    for (int i = 0; i < d; i++)
    {
        result = (result * ciphertext) % n;
    }
    return result;
}

// Function to generate RSA keys
void generateRSAKeys(int &n, int &e, int &d, int p, int q)
{
    // Calculate n = p * q
    n = p * q;

    // Calculate Euler's totient function phi(n) = (p-1) * (q-1)
    int phi_n = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi(n) and gcd(e, phi(n)) = 1

    // Common choice for e is 17, it satisfies gcd(e, phi(n)) = 1
    e = 17;

    // Calculate d such that (d * e) % phi(n) = 1 (d is modular inverse of e mod phi(n))
    d = modInverse(e, phi_n);
}

// Function to convert a string to a vector of integers (based on ASCII values)
vector<int> stringToIntVector(const string &message)
{
    vector<int> result;
    for (char c : message)
    {
        result.push_back(static_cast<int>(c)); // Convert each character to its ASCII integer value
    }
    return result;
}

// Function to convert a vector of integers back to a string
string intVectorToString(const vector<int> &intVector)
{
    string result;
    for (int i : intVector)
    {
        // Convert each integer back to a character
        result.push_back(static_cast<char>(i));
    }
    return result;
}
// Function to prepare the key matrix
void generateKeyMatrix(string key, char keyMatrix[5][5])
{
    vector<bool> used(26, false);

    // Treat 'J' and 'I' as the same
    used['J' - 'A'] = true;

    int row = 0, col = 0;

    for (char c : key)
    {
        c = toupper(c);
        if (!used[c - 'A'] && isalpha(c))
        {
            keyMatrix[row][col++] = c;
            used[c - 'A'] = true;
            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }

    for (char c = 'A'; c <= 'Z'; ++c)
    {
        if (!used[c - 'A'])
        {
            keyMatrix[row][col++] = c;
            used[c - 'A'] = true;
            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }
}

// Function to prepare the plaintext for Playfair cipher rules
string prepareText(string text)
{
    string prepared = "";
    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            if (c == 'J')

                // Replace 'J' with 'I'
                c = 'I';
            prepared += c;
        }
    }

    for (size_t i = 0; i < prepared.length() - 1; i += 2)
    {
        if (prepared[i] == prepared[i + 1])
        {
            // Add filler 'X' for duplicate letters
            prepared.insert(i + 1, "X");
        }
    }
    if (prepared.length() % 2 != 0)
    {
        // Add filler 'X' if length is odd
        prepared += "X";
    }
    return prepared;
}

// Function to find position of a character in the key matrix
void findPosition(char keyMatrix[5][5], char c, int &row, int &col)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (keyMatrix[i][j] == c)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Function to encrypt plaintext using Playfair cipher
string encrypt(string plaintext, char keyMatrix[5][5])
{
    plaintext = prepareText(plaintext);
    string ciphertext = "";

    for (size_t i = 0; i < plaintext.length(); i += 2)
    {
        char first = plaintext[i];
        char second = plaintext[i + 1];
        int r1, c1, r2, c2;

        findPosition(keyMatrix, first, r1, c1);
        findPosition(keyMatrix, second, r2, c2);

        if (r1 == r2)
        {
            // Same row
            ciphertext += keyMatrix[r1][(c1 + 1) % 5];
            ciphertext += keyMatrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            // Same column
            ciphertext += keyMatrix[(r1 + 1) % 5][c1];
            ciphertext += keyMatrix[(r2 + 1) % 5][c2];
        }
        else
        {
            // Rectangle rule
            ciphertext += keyMatrix[r1][c2];
            ciphertext += keyMatrix[r2][c1];
        }
    }
    return ciphertext;
}

// Function to decrypt ciphertext using Playfair cipher
string decrypt(string ciphertext, char keyMatrix[5][5])
{
    string plaintext = "";

    for (size_t i = 0; i < ciphertext.length(); i += 2)
    {
        char first = ciphertext[i];
        char second = ciphertext[i + 1];
        int r1, c1, r2, c2;

        findPosition(keyMatrix, first, r1, c1);
        findPosition(keyMatrix, second, r2, c2);

        if (r1 == r2)
        {
            // Same row
            plaintext += keyMatrix[r1][(c1 + 4) % 5];
            plaintext += keyMatrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            // Same column
            plaintext += keyMatrix[(r1 + 4) % 5][c1];
            plaintext += keyMatrix[(r2 + 4) % 5][c2];
        }
        else
        {
            // Rectangle rule
            plaintext += keyMatrix[r1][c2];
            plaintext += keyMatrix[r2][c1];
        }
    }
    return plaintext;
}
// Main function
int main()
{
    char option;

    cout << "\n\t\t\t\t\tWelcome to the Cryptography System!" << endl;
    do
    {
        cout << "\nWhich method would you like to use?" << endl;
        cout << "1. Symmetric" << endl;
        cout << "2. Asymmetric" << endl;
        cout << "3. Hybrid" << endl;

        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            cout << "\nSymmetric Encryption selected. Which technique do you want to use?" << endl;
            cout << "1. Caesar Cipher" << endl;
            cout << "2. Vigenere Cipher" << endl;
            cout << "3. Rail Fence Cipher" << endl;
            cout << "4. Playfair  Cipher" << endl;
            cout << "5. OTP " << endl;

            int technique;
            cin >> technique;
            cin.ignore();

            string plaintext;
            cout << "\nEnter the plaintext: ";
            getline(cin, plaintext);

            if (technique == 1)
            {
                int shift;
                cout << "Enter Caesar Cipher shift value:(integer) ";
                cin >> shift;
                string ciphertext = caesar_encrypt(plaintext, shift);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << caesar_decrypt(ciphertext, shift) << endl;
            }
            else if (technique == 2)
            {
                string key;
                cout << "Enter Vigenere Cipher key:(string) ";
                cin >> key;
                string ciphertext = vigencrypt(plaintext, key);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << vigdecrypt(ciphertext, key) << endl;
            }
            else if (technique == 3)
            {
                int key;
                cout << "Enter Rail Fence Cipher key:(integer) ";
                cin >> key;
                string ciphertext = railfenceencrypt(plaintext, key);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << railfencedecrypt(ciphertext, key) << endl;
            }
            else if (technique == 4)
            {
                string key;
                char keyMatrix[5][5];

                cout << "Enter the key:(string) ";
                cin >> key;
                generateKeyMatrix(key, keyMatrix);

                string ciphertext = encrypt(plaintext, keyMatrix);
                cout << "Encrypted text: " << ciphertext << endl;

                string decryptedText = decrypt(ciphertext, keyMatrix);
                cout << "Decrypted text: " << decryptedText << endl;
            }
            else if (technique == 5)
            {

                // Generate a random key of the same length as the plaintext
                string key = generateRandomKey(plaintext);

                // Encrypt the plaintext using the generated key
                string ciphertext = encrypt(plaintext, key);
                cout << "Encrypted ciphertext: ";

                // Output ciphertext as raw bytes (for demonstration purposes)
                for (char c : ciphertext)
                {
                    // Print as hexadecimal
                    cout << hex << (int)(unsigned char)c;
                }
                cout << dec << std::endl; // Back to decimal format

                // Decrypt the ciphertext using the same key
                string decryptedText = decrypt(ciphertext, key);
                cout << "Decrypted text: " << decryptedText << endl;
            }

            else
            {
                cout << "Invalid choice. Exiting..." << endl;
            }
        }
        else if (choice == 2)
        {
            int n, e, d;

            // Input the prime numbers p and q from the user
            int p, q;
            cout << "Enter a prime number p: ";
            cin >> p;
            cout << "Enter a prime number q: ";
            cin >> q;

            // Generate RSA keys based on user input primes
            generateRSAKeys(n, e, d, p, q);
            cout << "Public Key (n, e): (" << n << ", " << e << ")\n";
            cout << "Private Key (n, d): (" << n << ", " << d << ")\n";

            // To clear the buffer before taking a string input
            cin.ignore();
            string message;
            cout << "Enter the message (string) to encrypt: ";
            getline(cin, message);

            // Convert the message string to a vector of integers (ASCII values)
            vector<int> messageVector = stringToIntVector(message);

            cout << "Original Message: " << message << endl;

            // Encrypt each integer in the message vector
            vector<int> encryptedMessage;
            for (int m : messageVector)
            {
                encryptedMessage.push_back(encrypt(m, e, n));
            }

            // Display encrypted message
            cout << "Encrypted Message (in integers): ";
            for (int enc : encryptedMessage)
            {
                cout << enc << " ";
            }
            cout << endl;

            // Decrypt each integer in the encrypted message vector
            vector<int> decryptedMessage;
            for (int enc : encryptedMessage)
            {
                decryptedMessage.push_back(decrypt(enc, d, n));
            }

            // Convert decrypted integers back to a string
            string decryptedMessageStr = intVectorToString(decryptedMessage);
            cout << "Decrypted Message: " << decryptedMessageStr << endl;
        }
        else if (choice == 3)
        {
            // Step 1: User input for plaintext
            string plaintext;
            cout << "Enter a message to encrypt: ";
            getline(cin, plaintext);

            // Step 2: Generate a symmetric key (simple XOR key)
            // Example symmetric key
            char symmetricKey = 'K';

            // Step 3: Encrypt the symmetric key with RSA-like public key

            // Get public key
            auto keys = generateKeys();

            // Public exponent
            int e = keys.first;

            // Modulus
            int n = keys.second;

            // Private key (example for educational purposes)
            int d = 2753;

            int encryptedSymmetricKey = rsaEncrypt(symmetricKey, e, n);
            cout << "Encrypted Symmetric Key: " << encryptedSymmetricKey << endl;

            // Step 4: Encrypt the data using the symmetric key
            string encryptedData = xorEncrypt(plaintext, symmetricKey);
            cout << "Encrypted Data: " << encryptedData << endl;

            // Step 5: Decrypt the symmetric key using the private key
            char decryptedSymmetricKey = rsaDecrypt(encryptedSymmetricKey, d, n);
            cout << "Decrypted Symmetric Key: " << decryptedSymmetricKey << endl;

            // Step 6: Decrypt the data using the decrypted symmetric key
            string decryptedData = xorEncrypt(encryptedData, decryptedSymmetricKey);
            cout << "Decrypted Data: " << decryptedData << endl;
        }

        else
        {
            cout << "Invalid choice. Exiting..." << endl;
        }

        cout << "Do you want to continue (y/n) ? ";
        cin >> option;

    } while (option == 'y' || option == 'Y');

    return 0;
}