#include <iostream>
#include <fstream>
#include <string>

std::string encryptText(const std::string& plaintext, int key) {
    std::string ciphertext = "";
    for (char c : plaintext) {
        if (isalpha(c)) { 
            char base = isupper(c) ? 'A' : 'a'; 
            ciphertext += static_cast<char>((c - base + key + 26) % 26 + base);
        } else {
            ciphertext += c; 
        }
    }
    return ciphertext;
}

std::string decryptText(const std::string& ciphertext, int key) {
    return encryptText(ciphertext, -key); // Decrypt by shifting in the opposite direction
}

std::string readTextFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: Could not open file." << std::endl;
        exit(1);
    }

    std::string text;
    char c;
    while (file.get(c)) {
        text += c;
    }
    file.close();

    return text;
}

void writeTextToFile(const std::string& fileName, const std::string& text) {
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error: Could not create/write to file." << std::endl;
        exit(1);
    }

    file << text;
    file.close();
}

int main() {
    std::string inputFileName, outputFileName;
    int key;
    char choice;

    std::cout << "Choose an operation (E for encryption, D for decryption): ";
    std::cin >> choice;

    if (choice == 'E' || choice == 'e') {
        std::cout << "Enter the name of the input file: ";
        std::cin >> inputFileName;
        std::cout << "Enter the name of the output file: ";
        std::cin >> outputFileName;
        std::cout << "Enter the encryption key (an integer): ";
        std::cin >> key;

        std::string plaintext = readTextFromFile(inputFileName);

        std::string ciphertext = encryptText(plaintext, key);

        writeTextToFile(outputFileName, ciphertext);

        std::cout << "Encryption completed successfully." << std::endl;
    } else if (choice == 'D' || choice == 'd') {
        std::cout << "Enter the name of the input file (ciphertext): ";
        std::cin >> inputFileName;
        std::cout << "Enter the name of the output file (plaintext): ";
        std::cin >> outputFileName;
        std::cout << "Enter the decryption key (an integer): ";
        std::cin >> key;

        std::string ciphertext = readTextFromFile(inputFileName);

        std::string plaintext = decryptText(ciphertext, key);

        writeTextToFile(outputFileName, plaintext);

        std::cout << "Decryption completed successfully." << std::endl;
    } else {
        std::cout << "Invalid choice. Please choose E for encryption or D for decryption." << std::endl;
    }

    return 0;
}
