#include <iostream>
#include <string>
#include <vector>
#include "rsa_utils.h"

std::ostream& operator<<(std::ostream& os, const mpz_class& mpz) {
    os << mpz.get_str();
    return os;
}

int main() {
    try {
        mpz_class n, e, d;
        generateKeys(n, e, d);
        std::string word;
        std::cout << "Введите сообщение: ";
        getline(std::cin, word);

        std::cout << "n: " << n << "\n";
        std::cout << "e: " << e << "\n";
        std::cout << "d: " << d << "\n";

        std::vector<mpz_class> RsaCode = encrypt(word, e, n);

        std::cout << "Зашифрованное сообщение: ";
        for (const auto& el : RsaCode) {
            std::cout << el << " ";
        }
        std::cout << "\n";

        std::string decryptedMessage = decrypt(RsaCode, d, n);
        std::cout << "Расшифрованное сообщение: " << decryptedMessage << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
