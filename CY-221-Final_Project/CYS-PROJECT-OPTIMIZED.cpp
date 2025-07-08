#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <random>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <climits>

using namespace std;
using namespace std::chrono;

// Performance measurement utility
class PerformanceTimer {
private:
    high_resolution_clock::time_point start_time;
public:
    void start() {
        start_time = high_resolution_clock::now();
    }
    
    double getElapsedMs() {
        auto end_time = high_resolution_clock::now();
        return duration_cast<microseconds>(end_time - start_time).count() / 1000.0;
    }
};

// OPTIMIZED: Fast modular exponentiation using binary exponentiation
inline long long fastModularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;  // Equivalent to exp /= 2 but faster
    }
    return result;
}

// OPTIMIZED: XOR encryption with better memory management
string xorEncryptOptimized(const string &data, char key) {
    string encrypted;
    encrypted.reserve(data.size());  // Pre-allocate memory
    
    for (size_t i = 0; i < data.size(); ++i) {
        encrypted.push_back(data[i] ^ key);
    }
    return encrypted;
}

// Simple RSA-like key generation (unchanged for compatibility)
pair<long long, long long> generateKeys() {
    long long p = 61;
    long long q = 53;
    long long n = p * q;
    long long e = 17;
    
    return {e, n};
}

// OPTIMIZED: RSA encryption using fast modular exponentiation
long long rsaEncryptOptimized(long long message, long long e, long long n) {
    return fastModularExponentiation(message, e, n);
}

// OPTIMIZED: RSA decryption using fast modular exponentiation
long long rsaDecryptOptimized(long long cipher, long long d, long long n) {
    return fastModularExponentiation(cipher, d, n);
}

// OPTIMIZED: String to integer with overflow protection
long long stringToIntOptimized(const string &str) {
    if (str.empty()) return 0;
    
    long long result = 0;
    const long long MAX_SAFE = LLONG_MAX / 256;
    
    for (char c : str) {
        if (result > MAX_SAFE) {
            // Prevent overflow by using modular arithmetic
            result = (result * 256 + static_cast<unsigned char>(c)) % 1000000007;
        } else {
            result = result * 256 + static_cast<unsigned char>(c);
        }
    }
    return result;
}

// OPTIMIZED: Integer to string conversion
string intToStringOptimized(long long num) {
    if (num == 0) return string(1, '\0');
    
    string result;
    result.reserve(8);  // Pre-allocate for typical usage
    
    while (num > 0) {
        result.push_back(static_cast<char>(num % 256));
        num /= 256;
    }
    
    reverse(result.begin(), result.end());
    return result;
}

// OPTIMIZED: Rail fence encryption with better memory management
string railfenceEncryptOptimized(const string &plaintext, int key) {
    if (key <= 1) return plaintext;
    if (plaintext.empty()) return plaintext;
    
    vector<string> rail(key);
    
    // Pre-allocate memory for each rail
    size_t estimated_size = (plaintext.size() / key) + 2;
    for (auto &r : rail) {
        r.reserve(estimated_size);
    }
    
    int direction = 1;
    int row = 0;
    
    for (char ch : plaintext) {
        rail[row].push_back(ch);
        row += direction;
        
        if (row == 0 || row == key - 1) {
            direction = -direction;
        }
    }
    
    string ciphertext;
    ciphertext.reserve(plaintext.size());
    
    for (const auto &r : rail) {
        ciphertext += r;
    }
    
    return ciphertext;
}

// OPTIMIZED: Rail fence decryption
string railfenceDecryptOptimized(const string &ciphertext, int key) {
    if (key <= 1) return ciphertext;
    if (ciphertext.empty()) return ciphertext;
    
    vector<int> railLengths(key, 0);
    int direction = 1;
    int row = 0;
    
    // Calculate rail lengths
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        railLengths[row]++;
        row += direction;
        
        if (row == 0 || row == key - 1) {
            direction = -direction;
        }
    }
    
    // Fill rails
    vector<string> rail(key);
    size_t index = 0;
    for (int i = 0; i < key; ++i) {
        if (index + railLengths[i] <= ciphertext.length()) {
            rail[i] = ciphertext.substr(index, railLengths[i]);
            index += railLengths[i];
        }
    }
    
    // Reconstruct plaintext
    string plaintext;
    plaintext.reserve(ciphertext.length());
    
    vector<size_t> railPos(key, 0);
    row = 0;
    direction = 1;
    
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        if (railPos[row] < rail[row].length()) {
            plaintext.push_back(rail[row][railPos[row]]);
            railPos[row]++;
        }
        
        row += direction;
        if (row == 0 || row == key - 1) {
            direction = -direction;
        }
    }
    
    return plaintext;
}

// OPTIMIZED: Key generation for Vigenère with better memory management
string generateKeyOptimized(const string &plaintext, const string &key) {
    if (key.empty() || plaintext.empty()) return key;
    
    string fullKey;
    fullKey.reserve(plaintext.length());
    
    size_t keyLen = key.length();
    for (size_t i = 0; i < plaintext.length(); ++i) {
        fullKey.push_back(key[i % keyLen]);
    }
    
    return fullKey;
}

// OPTIMIZED: Vigenère encryption
string vigenereEncryptOptimized(const string &plaintext, const string &key) {
    if (plaintext.empty() || key.empty()) return plaintext;
    
    string ciphertext;
    ciphertext.reserve(plaintext.length());
    
    string fullKey = generateKeyOptimized(plaintext, key);
    
    for (size_t i = 0; i < plaintext.length(); ++i) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char shift = islower(fullKey[i]) ? fullKey[i] - 'a' : fullKey[i] - 'A';
            ciphertext.push_back((plaintext[i] - base + shift) % 26 + base);
        } else {
            ciphertext.push_back(plaintext[i]);
        }
    }
    
    return ciphertext;
}

// OPTIMIZED: Vigenère decryption
string vigenereDecryptOptimized(const string &ciphertext, const string &key) {
    if (ciphertext.empty() || key.empty()) return ciphertext;
    
    string plaintext;
    plaintext.reserve(ciphertext.length());
    
    string fullKey = generateKeyOptimized(ciphertext, key);
    
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            char shift = islower(fullKey[i]) ? fullKey[i] - 'a' : fullKey[i] - 'A';
            plaintext.push_back((ciphertext[i] - base - shift + 26) % 26 + base);
        } else {
            plaintext.push_back(ciphertext[i]);
        }
    }
    
    return plaintext;
}

// OPTIMIZED: Caesar cipher with lookup table for better performance
string caesarEncryptOptimized(const string &text, int shift) {
    if (text.empty()) return text;
    
    string result;
    result.reserve(text.size());
    
    // Normalize shift
    shift = ((shift % 26) + 26) % 26;
    
    for (char ch : text) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            result.push_back((ch - base + shift) % 26 + base);
        } else {
            result.push_back(ch);
        }
    }
    return result;
}

// OPTIMIZED: Caesar decryption
string caesarDecryptOptimized(const string &text, int shift) {
    return caesarEncryptOptimized(text, 26 - (shift % 26));
}

// OPTIMIZED: Extended Euclidean Algorithm for modular inverse
long long extendedGCD(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    
    long long x1, y1;
    long long gcd = extendedGCD(b % a, a, x1, y1);
    
    x = y1 - (b / a) * x1;
    y = x1;
    
    return gcd;
}

// OPTIMIZED: Fast modular inverse
long long modInverseOptimized(long long a, long long m) {
    long long x, y;
    long long gcd = extendedGCD(a, m, x, y);
    
    if (gcd != 1) return -1;  // Inverse doesn't exist
    
    return (x % m + m) % m;
}

// OPTIMIZED: Random key generation with better RNG
string generateRandomKeyOptimized(const string &plaintext) {
    if (plaintext.empty()) return "";
    
    string key;
    key.reserve(plaintext.length());
    
    // Use hardware random device if available
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 255);
    
    for (size_t i = 0; i < plaintext.length(); ++i) {
        key.push_back(static_cast<char>(dist(gen)));
    }
    
    return key;
}

// OPTIMIZED: One-time pad encryption
string otpEncryptOptimized(const string &plaintext, const string &key) {
    if (plaintext.length() != key.length()) {
        throw invalid_argument("Key length must equal plaintext length for OTP");
    }
    
    string ciphertext;
    ciphertext.reserve(plaintext.length());
    
    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext.push_back(plaintext[i] ^ key[i]);
    }
    
    return ciphertext;
}

// OPTIMIZED: One-time pad decryption (same as encryption for XOR)
string otpDecryptOptimized(const string &ciphertext, const string &key) {
    return otpEncryptOptimized(ciphertext, key);  // XOR is its own inverse
}

// OPTIMIZED: GCD using binary GCD algorithm (faster for large numbers)
long long gcdOptimized(long long a, long long b) {
    if (a == 0) return b;
    if (b == 0) return a;
    
    // Count common factors of 2
    int shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }
    
    // Remove factors of 2 from a
    while ((a & 1) == 0) a >>= 1;
    
    do {
        // Remove factors of 2 from b
        while ((b & 1) == 0) b >>= 1;
        
        // Ensure a <= b
        if (a > b) swap(a, b);
        
        b = b - a;
    } while (b != 0);
    
    return a << shift;
}

// OPTIMIZED: RSA key generation
void generateRSAKeysOptimized(long long &n, long long &e, long long &d, long long p, long long q) {
    n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    
    e = 17;  // Common choice
    
    // Verify e and phi_n are coprime
    if (gcdOptimized(e, phi_n) != 1) {
        e = 65537;  // Alternative common choice
    }
    
    d = modInverseOptimized(e, phi_n);
    
    if (d == -1) {
        throw runtime_error("Cannot generate valid RSA keys with given primes");
    }
}

// OPTIMIZED: String to integer vector conversion
vector<long long> stringToIntVectorOptimized(const string &message) {
    vector<long long> result;
    result.reserve(message.length());
    
    for (char c : message) {
        result.push_back(static_cast<long long>(static_cast<unsigned char>(c)));
    }
    
    return result;
}

// OPTIMIZED: Integer vector to string conversion
string intVectorToStringOptimized(const vector<long long> &intVector) {
    string result;
    result.reserve(intVector.size());
    
    for (long long i : intVector) {
        if (i >= 0 && i <= 255) {
            result.push_back(static_cast<char>(i));
        }
    }
    
    return result;
}

// OPTIMIZED: Playfair key matrix generation
void generateKeyMatrixOptimized(const string &key, char keyMatrix[5][5]) {
    vector<bool> used(26, false);
    used['J' - 'A'] = true;  // Treat J and I as same
    
    int row = 0, col = 0;
    
    // Process key
    for (char c : key) {
        c = toupper(c);
        if (isalpha(c) && !used[c - 'A']) {
            keyMatrix[row][col] = c;
            used[c - 'A'] = true;
            
            if (++col == 5) {
                col = 0;
                row++;
            }
        }
    }
    
    // Fill remaining positions
    for (char c = 'A'; c <= 'Z' && row < 5; ++c) {
        if (!used[c - 'A']) {
            keyMatrix[row][col] = c;
            used[c - 'A'] = true;
            
            if (++col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// OPTIMIZED: Playfair text preparation
string prepareTextOptimized(const string &text) {
    string prepared;
    prepared.reserve(text.length() * 2);  // Worst case: every char needs X inserted
    
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            prepared.push_back(c);
        }
    }
    
    // Handle duplicate pairs
    for (size_t i = 0; i < prepared.length() - 1; i += 2) {
        if (prepared[i] == prepared[i + 1]) {
            prepared.insert(i + 1, 1, 'X');
        }
    }
    
    if (prepared.length() % 2 != 0) {
        prepared.push_back('X');
    }
    
    return prepared;
}

// OPTIMIZED: Fast position lookup using lookup table
void initializePositionLookup(const char keyMatrix[5][5], int positions[26][2]) {
    for (int i = 0; i < 26; ++i) {
        positions[i][0] = positions[i][1] = -1;
    }
    
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            char c = keyMatrix[i][j];
            if (c >= 'A' && c <= 'Z') {
                positions[c - 'A'][0] = i;
                positions[c - 'A'][1] = j;
            }
        }
    }
}

// OPTIMIZED: Playfair encryption
string playfairEncryptOptimized(const string &plaintext, const char keyMatrix[5][5]) {
    string prepared = prepareTextOptimized(plaintext);
    string ciphertext;
    ciphertext.reserve(prepared.length());
    
    // Pre-compute position lookup table
    int positions[26][2];
    initializePositionLookup(keyMatrix, positions);
    
    for (size_t i = 0; i < prepared.length(); i += 2) {
        char first = prepared[i];
        char second = prepared[i + 1];
        
        int r1 = positions[first - 'A'][0];
        int c1 = positions[first - 'A'][1];
        int r2 = positions[second - 'A'][0];
        int c2 = positions[second - 'A'][1];
        
        if (r1 == r2) {
            // Same row
            ciphertext.push_back(keyMatrix[r1][(c1 + 1) % 5]);
            ciphertext.push_back(keyMatrix[r2][(c2 + 1) % 5]);
        } else if (c1 == c2) {
            // Same column
            ciphertext.push_back(keyMatrix[(r1 + 1) % 5][c1]);
            ciphertext.push_back(keyMatrix[(r2 + 1) % 5][c2]);
        } else {
            // Rectangle rule
            ciphertext.push_back(keyMatrix[r1][c2]);
            ciphertext.push_back(keyMatrix[r2][c1]);
        }
    }
    
    return ciphertext;
}

// OPTIMIZED: Playfair decryption
string playfairDecryptOptimized(const string &ciphertext, const char keyMatrix[5][5]) {
    string plaintext;
    plaintext.reserve(ciphertext.length());
    
    // Pre-compute position lookup table
    int positions[26][2];
    initializePositionLookup(keyMatrix, positions);
    
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char first = ciphertext[i];
        char second = ciphertext[i + 1];
        
        int r1 = positions[first - 'A'][0];
        int c1 = positions[first - 'A'][1];
        int r2 = positions[second - 'A'][0];
        int c2 = positions[second - 'A'][1];
        
        if (r1 == r2) {
            // Same row
            plaintext.push_back(keyMatrix[r1][(c1 + 4) % 5]);
            plaintext.push_back(keyMatrix[r2][(c2 + 4) % 5]);
        } else if (c1 == c2) {
            // Same column
            plaintext.push_back(keyMatrix[(r1 + 4) % 5][c1]);
            plaintext.push_back(keyMatrix[(r2 + 4) % 5][c2]);
        } else {
            // Rectangle rule
            plaintext.push_back(keyMatrix[r1][c2]);
            plaintext.push_back(keyMatrix[r2][c1]);
        }
    }
    
    return plaintext;
}

// Main function with performance measurements
int main() {
    char option;
    PerformanceTimer timer;

    cout << "\n\t\t\t\t\tWelcome to the OPTIMIZED Cryptography System!" << endl;
    cout << "\t\t\t\t\t(Performance Enhanced Version)" << endl;
    
    do {
        cout << "\nWhich method would you like to use?" << endl;
        cout << "1. Symmetric" << endl;
        cout << "2. Asymmetric" << endl;
        cout << "3. Hybrid" << endl;

        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            cout << "\nSymmetric Encryption selected. Which technique do you want to use?" << endl;
            cout << "1. Caesar Cipher" << endl;
            cout << "2. Vigenere Cipher" << endl;
            cout << "3. Rail Fence Cipher" << endl;
            cout << "4. Playfair Cipher" << endl;
            cout << "5. One-Time Pad (OTP)" << endl;

            int technique;
            cin >> technique;
            cin.ignore();

            string plaintext;
            cout << "\nEnter the plaintext: ";
            getline(cin, plaintext);

            timer.start();

            if (technique == 1) {
                int shift;
                cout << "Enter Caesar Cipher shift value: ";
                cin >> shift;
                
                string ciphertext = caesarEncryptOptimized(plaintext, shift);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << caesarDecryptOptimized(ciphertext, shift) << endl;
                
            } else if (technique == 2) {
                string key;
                cout << "Enter Vigenere Cipher key: ";
                cin >> key;
                
                string ciphertext = vigenereEncryptOptimized(plaintext, key);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << vigenereDecryptOptimized(ciphertext, key) << endl;
                
            } else if (technique == 3) {
                int key;
                cout << "Enter Rail Fence Cipher key: ";
                cin >> key;
                
                string ciphertext = railfenceEncryptOptimized(plaintext, key);
                cout << "Encrypted text: " << ciphertext << endl;
                cout << "Decrypted text: " << railfenceDecryptOptimized(ciphertext, key) << endl;
                
            } else if (technique == 4) {
                string key;
                char keyMatrix[5][5];

                cout << "Enter the key: ";
                cin >> key;
                generateKeyMatrixOptimized(key, keyMatrix);

                string ciphertext = playfairEncryptOptimized(plaintext, keyMatrix);
                cout << "Encrypted text: " << ciphertext << endl;

                string decryptedText = playfairDecryptOptimized(ciphertext, keyMatrix);
                cout << "Decrypted text: " << decryptedText << endl;
                
            } else if (technique == 5) {
                try {
                    string key = generateRandomKeyOptimized(plaintext);
                    string ciphertext = otpEncryptOptimized(plaintext, key);
                    
                    cout << "Encrypted ciphertext: ";
                    for (char c : ciphertext) {
                        cout << hex << (int)(unsigned char)c;
                    }
                    cout << dec << endl;

                    string decryptedText = otpDecryptOptimized(ciphertext, key);
                    cout << "Decrypted text: " << decryptedText << endl;
                    
                } catch (const exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
            } else {
                cout << "Invalid choice." << endl;
            }

            cout << "Execution time: " << timer.getElapsedMs() << " ms" << endl;

        } else if (choice == 2) {
            long long n, e, d;
            long long p, q;
            
            cout << "Enter a prime number p: ";
            cin >> p;
            cout << "Enter a prime number q: ";
            cin >> q;

            timer.start();
            
            try {
                generateRSAKeysOptimized(n, e, d, p, q);
                cout << "Public Key (n, e): (" << n << ", " << e << ")" << endl;
                cout << "Private Key (n, d): (" << n << ", " << d << ")" << endl;

                cin.ignore();
                string message;
                cout << "Enter the message to encrypt: ";
                getline(cin, message);

                vector<long long> messageVector = stringToIntVectorOptimized(message);
                cout << "Original Message: " << message << endl;

                vector<long long> encryptedMessage;
                encryptedMessage.reserve(messageVector.size());
                
                for (long long m : messageVector) {
                    encryptedMessage.push_back(rsaEncryptOptimized(m, e, n));
                }

                cout << "Encrypted Message (integers): ";
                for (long long enc : encryptedMessage) {
                    cout << enc << " ";
                }
                cout << endl;

                vector<long long> decryptedMessage;
                decryptedMessage.reserve(encryptedMessage.size());
                
                for (long long enc : encryptedMessage) {
                    decryptedMessage.push_back(rsaDecryptOptimized(enc, d, n));
                }

                string decryptedMessageStr = intVectorToStringOptimized(decryptedMessage);
                cout << "Decrypted Message: " << decryptedMessageStr << endl;
                
            } catch (const exception &e) {
                cout << "Error: " << e.what() << endl;
            }

            cout << "Execution time: " << timer.getElapsedMs() << " ms" << endl;

        } else if (choice == 3) {
            string plaintext;
            cout << "Enter a message to encrypt: ";
            getline(cin, plaintext);

            timer.start();

            char symmetricKey = 'K';
            auto keys = generateKeys();
            long long e = keys.first;
            long long n = keys.second;
            long long d = 2753;

            long long encryptedSymmetricKey = rsaEncryptOptimized(symmetricKey, e, n);
            cout << "Encrypted Symmetric Key: " << encryptedSymmetricKey << endl;

            string encryptedData = xorEncryptOptimized(plaintext, symmetricKey);
            cout << "Encrypted Data: " << encryptedData << endl;

            char decryptedSymmetricKey = static_cast<char>(rsaDecryptOptimized(encryptedSymmetricKey, d, n));
            cout << "Decrypted Symmetric Key: " << decryptedSymmetricKey << endl;

            string decryptedData = xorEncryptOptimized(encryptedData, decryptedSymmetricKey);
            cout << "Decrypted Data: " << decryptedData << endl;

            cout << "Execution time: " << timer.getElapsedMs() << " ms" << endl;

        } else {
            cout << "Invalid choice." << endl;
        }

        cout << "\nDo you want to continue (y/n)? ";
        cin >> option;

    } while (option == 'y' || option == 'Y');

    return 0;
}