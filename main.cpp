#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>

bool performCipher(std::string& content, bool enc)
{
    int shift_num = enc ? 10 : -10;

    for (char& ch : content)
    {
        if (isalpha(ch))
        {
            char base = isupper(ch) ? 'A' : 'a';
            ch = static_cast<char>((ch - base + shift_num + 26) % 26 + base);
        }
    }
    return true;
}

bool encFile(const std::string& file, bool enc)
{
    std::ifstream ifile(file);
    if (!ifile) {
        std::cerr << "File not found or failed to open: " << file << "\n";
        return false;
    }
    std::string content((std::istreambuf_iterator<char>(ifile)), {});
    if (content.empty()) {
        std::cerr << "File is empty: " << file << "\n";
        return false;
    }
    ifile.close();
    if (performCipher(content, enc)) {
        std::string outputFile = enc ? "encrypted_" + file : "decrypted_" + file;

        std::cout << "Saving to: " << outputFile << "\n";

        std::ofstream ofile(outputFile);
        if (!ofile) {
            std::cerr << "Failed to open output file for writing: " << outputFile << "\n";
            return false;
        }
        ofile << content;
        ofile.close();
        return true;
    }
    return false;
}


int main()
{
    std::string file;
    char mode;

    std::cout << "Enter filename (with full path if necessary): ";
    std::getline(std::cin >> std::ws, file);
    std::cout << "(e) Encrypt | (d) Decrypt? ";
    std::cin >> mode;

    if (mode == 'e' || mode == 'E') {
        if (encFile(file, true)) {
            std::cout << "Encryption complete! File saved as 'encrypted_" << file << "'\n";
        } else {
            std::cerr << "An error occurred during encryption.\n";
        }
    } else if (mode == 'd' || mode == 'D') {
        if (encFile(file, false)) {
            std::cout << "complete! File saved as 'decrypted_" << file << "'\n";
        } else {
            std::cerr << "error\n";
        }
    } else {
        std::cerr << "Invalid input.\n";
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}
