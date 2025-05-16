#include <iostream>
#include <fstream>
#include <cstring>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/twofish.h>
#include <cryptopp/des.h>
#include <cryptopp/blowfish.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;

void banner() {
    std::cout << R"(
    
    
$$$$$$$$\ $$\                        $$$$$$\                                      $$\ $$\                            $$$$$$\                                $$\ 
\__$$  __|$$ |                      $$  __$$\                                     $$ |\__|                          $$  __$$\                               $$ |
   $$ |   $$$$$$$\   $$$$$$\        $$ /  \__|$$\   $$\  $$$$$$\   $$$$$$\   $$$$$$$ |$$\  $$$$$$\  $$$$$$$\        $$ /  $$ |$$$$$$$\   $$$$$$\   $$$$$$\  $$ |
   $$ |   $$  __$$\ $$  __$$\       $$ |$$$$\ $$ |  $$ | \____$$\ $$  __$$\ $$  __$$ |$$ | \____$$\ $$  __$$\       $$$$$$$$ |$$  __$$\ $$  __$$\ $$  __$$\ $$ |
   $$ |   $$ |  $$ |$$$$$$$$ |      $$ |\_$$ |$$ |  $$ | $$$$$$$ |$$ |  \__|$$ /  $$ |$$ | $$$$$$$ |$$ |  $$ |      $$  __$$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ |
   $$ |   $$ |  $$ |$$   ____|      $$ |  $$ |$$ |  $$ |$$  __$$ |$$ |      $$ |  $$ |$$ |$$  __$$ |$$ |  $$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |
   $$ |   $$ |  $$ |\$$$$$$$\       \$$$$$$  |\$$$$$$  |\$$$$$$$ |$$ |      \$$$$$$$ |$$ |\$$$$$$$ |$$ |  $$ |      $$ |  $$ |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ $$ |
   \__|   \__|  \__| \_______|       \______/  \______/  \_______|\__|       \_______|\__| \_______|\__|  \__|      \__|  \__|\__|  \__| \____$$ | \_______|\__|
                                                                                                                                        $$\   $$ |              
                                                                                                                                        \$$$$$$  |              
                                                                                                                                         \______/               
                                                      +-+-+-+ +-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+-+-+
                                                      |T|h|e| |G|a|t|e| |O|f| |E|n|c|r|y|p|t|i|o|n|
                                                      +-+-+-+ +-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+-+-+-+
                                                                                                                                                                          
 
 Author : Mohamed Ashraf [TheKnower0x0] - Shady Salem - Ahmed Amin - Saleh Ayoub - Mokhtar Khalifa
 Version: 1.1                                                            
 GitHub : https://github.com/TheKnower0x0/The-Guardian-Angel
 
)" << '\n';
}

void PrintEncryptBanner() {
    cout << R"(
██╗  ██╗ █████╗ ██████╗ ██████╗ ██╗   ██╗    ███████╗███╗   ██╗ ██████╗██████╗ ██╗   ██╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗    ██╗
██║  ██║██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝████╗  ██║██╔════╝██╔══██╗╚██╗ ██╔╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║    ██║
███████║███████║██████╔╝██████╔╝ ╚████╔╝     █████╗  ██╔██╗ ██║██║     ██████╔╝ ╚████╔╝ ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║    ██║
██╔══██║██╔══██║██╔═══╝ ██╔═══╝   ╚██╔╝      ██╔══╝  ██║╚██╗██║██║     ██╔══██╗  ╚██╔╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║    ╚═╝
██║  ██║██║  ██║██║     ██║        ██║       ███████╗██║ ╚████║╚██████╗██║  ██║   ██║   ██║        ██║   ██║╚██████╔╝██║ ╚████║    ██╗
╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝        ╚═╝       ╚══════╝╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝    ╚═╝
    )" << '\n';
}

void printDecryptionBanner() {
    cout << R"(
██╗  ██╗ █████╗ ██████╗ ██████╗ ██╗   ██╗    ██████╗ ███████╗ ██████╗██████╗ ██╗   ██╗██████╗ ████████╗██╗ ██████╗ ███╗   ██╗    ██╗
██║  ██║██╔══██╗██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔════╝██╔════╝██╔══██╗╚██╗ ██╔╝██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║    ██║
███████║███████║██████╔╝██████╔╝ ╚████╔╝     ██║  ██║█████╗  ██║     ██████╔╝ ╚████╔╝ ██████╔╝   ██║   ██║██║   ██║██╔██╗ ██║    ██║
██╔══██║██╔══██║██╔═══╝ ██╔═══╝   ╚██╔╝      ██║  ██║██╔══╝  ██║     ██╔══██╗  ╚██╔╝  ██╔═══╝    ██║   ██║██║   ██║██║╚██╗██║    ╚═╝
██║  ██║██║  ██║██║     ██║        ██║       ██████╔╝███████╗╚██████╗██║  ██║   ██║   ██║        ██║   ██║╚██████╔╝██║ ╚████║    ██╗
╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝        ╚═╝       ╚═════╝ ╚══════╝ ╚═════╝╚═╝  ╚═╝   ╚═╝   ╚═╝        ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝    ╚═╝
)" << '\n';
}

void printExitBanner() {
    cout << R"(
░▒▓███████▓▒░▒▓████████▓▒░▒▓████████▓▒░      ░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░       ░▒▓█▓▒░ 
░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░ 
░▒▓█▓▒░      ░▒▓█▓▒░      ░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░ 
 ░▒▓██████▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░         ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░ 
       ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░                ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░ 
       ░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░                ░▒▓█▓▒░   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░              
░▒▓███████▓▒░░▒▓████████▓▒░▒▓████████▓▒░         ░▒▓█▓▒░    ░▒▓██████▓▒░ ░▒▓██████▓▒░       ░▒▓█▓▒░ 
                                                                                                    
                                                                                                    )" << '\n';
}

void AdjustKeyForAlgorithm(int choice, const string& password, SecByteBlock& key) {
    switch (choice) {
        case 2:  // Twofish
            key.CleanNew(Twofish::DEFAULT_KEYLENGTH);
            break;
        case 3:  // Triple DES
            key.CleanNew(DES_EDE3::DEFAULT_KEYLENGTH);
            break;
        case 4:  // Blowfish
            key.CleanNew(Blowfish::DEFAULT_KEYLENGTH);
            break;
        default:  // AES
            key.CleanNew(AES::DEFAULT_KEYLENGTH);
            break;
    }
    size_t bytesToCopy = std::min(password.size(), key.size());
    memcpy(key, password.data(), bytesToCopy);
}

void EncryptOrDecrypt(const string& filepath, int choice, const string& password, bool encrypt) {
    string inputFile = filepath;
    string outputFile = filepath + (encrypt ? ".enc" : ".dec");

    ifstream inFile(inputFile, ios::binary);
    ofstream outFile(outputFile, ios::binary);

    string input((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    string output;

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    AdjustKeyForAlgorithm(choice, password, key);

    CryptoPP::byte iv[AES::BLOCKSIZE];
    memset(iv, 0x00, AES::BLOCKSIZE);

    try {
        if (choice == 1) { // AES
            if (encrypt) {
                CBC_Mode<AES>::Encryption enc;
                enc.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(enc, new StringSink(output)));
            } else {
                CBC_Mode<AES>::Decryption dec;
                dec.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(dec, new StringSink(output)));
            }
        } else if (choice == 2) { // Twofish
            if (encrypt) {
                CBC_Mode<Twofish>::Encryption enc;
                enc.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(enc, new StringSink(output)));
            } else {
                CBC_Mode<Twofish>::Decryption dec;
                dec.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(dec, new StringSink(output)));
            }
        } else if (choice == 3) { // Triple DES
            if (encrypt) {
                CBC_Mode<DES_EDE3>::Encryption enc;
                enc.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(enc, new StringSink(output)));
            } else {
                CBC_Mode<DES_EDE3>::Decryption dec;
                dec.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(dec, new StringSink(output)));
            }
        } else if (choice == 4) { // Blowfish
            if (encrypt) {
                CBC_Mode<Blowfish>::Encryption enc;
                enc.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(enc, new StringSink(output)));
            } else {
                CBC_Mode<Blowfish>::Decryption dec;
                dec.SetKeyWithIV(key, key.size(), iv);
                StringSource s(input, true, new StreamTransformationFilter(dec, new StringSink(output)));
            }
        }

        outFile.write(output.data(), output.size());
        cout << (encrypt ? "Encryption" : "Decryption") << " completed successfully." << endl;
        if (encrypt) {
            PrintEncryptBanner();
        } else {
          printDecryptionBanner();
        }
    } catch (const CryptoPP::Exception& e) {
        cerr << (encrypt ? "Encryption" : "Decryption") << " failed: " << e.what() << endl;
    }

    inFile.close();
    outFile.close();
}

int main() {
    banner();
    cout << "Enter 'e' to encrypt or 'd' to decrypt: ";
    char option;
    cin >> option;
    bool encrypt = (option == 'e');

    if (option != 'e' && option != 'd') {
        cerr << "Invalid option." << endl;
        return 1;
    }

    cout << "[1] AES" << endl;
    cout << "[2] Twofish" << endl;
    cout << "[3] Triple DES" << endl;
    cout << "[4] Blowfish" << endl;
    cout << "[0] Exit" << endl;
    cout << "Choose an algorithm: ";
    int algoChoice;
    cin >> algoChoice;

    if (algoChoice == 0) {
        cout << "Exiting the tool." << endl;
        printExitBanner();
        return 0;
    }

    if (algoChoice < 1 || algoChoice > 4) {
        cerr << "Invalid algorithm choice." << endl;
        return 1;
    }

    string filepath;
    cout << "Enter the file path: ";
    cin >> filepath;

    string password;
    cout << "Enter the security key password: ";
    cin >> password;

    EncryptOrDecrypt(filepath, algoChoice, password, encrypt);

    return 0;
}

