#include "rsa_utils.h"

mpz_class modExp(const mpz_class &base, const mpz_class &exp, const mpz_class &mod) {
    mpz_class res("1");
    mpz_class base_mod = base % mod;

    mpz_class exp_temp = exp;
    while (exp_temp > 0) {
        if (exp_temp % 2 == 1) {
            res = (res * base_mod) % mod;
        }
        base_mod = (base_mod * base_mod) % mod;
        exp_temp = exp_temp / 2;
    }
    return res;
}

mpz_class gcd(const mpz_class &aa, const mpz_class &ab) {
    mpz_class a = aa;
    mpz_class b = ab;
    mpz_class temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void generateKeys(mpz_class &n, mpz_class &e, mpz_class &d) {
    mpz_class p("11111111111111111111111111111111111111116661111111111111111111111111111111111111111");
    mpz_class q("14361817905487073108115025320764062442342597502003905253144371337891157457030439301");
    n = p * q;
    mpz_class phi = (p - 1) * (q - 1);

    e = 7;

    while (gcd(e, phi) != 1) {
        e = e + 1;
    }
    d = 0;
    mpz_class k = 1;
    while (true) {
        if ((1 + k * phi) % e == 0) {
            d = (1 + k * phi) / e;
            break;
        }
        k = k + 1;
    }
}

std::vector<mpz_class> encrypt(const std::string &mes, const mpz_class &e, const mpz_class &n) {
    std::vector<mpz_class> mess;
    for (char c : mes) {
        mpz_class number(static_cast<unsigned char>(c));
        mess.push_back(modExp(number, e, n));
    }
    return mess;
}

std::string decrypt(const std::vector<mpz_class> &cipher, const mpz_class &d, const mpz_class &n) {
    std::string word;
    for (const auto& el : cipher) {
        mpz_class decryptedNum = modExp(el, d, n);
        char decryptedChar = static_cast<char>(decryptedNum.get_ui());
        word += decryptedChar;
    }
    return word;
}
