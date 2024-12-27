#ifndef RSA_UTILS_H
#define RSA_UTILS_H

#include <gmpxx.h>
#include <string>
#include <vector>

mpz_class modExp(const mpz_class &base, const mpz_class &exp, const mpz_class &mod);
mpz_class gcd(const mpz_class &aa, const mpz_class &ab);
void generateKeys(mpz_class &n, mpz_class &e, mpz_class &d);
std::vector<mpz_class> encrypt(const std::string &mes, const mpz_class &e, const mpz_class &n);
std::string decrypt(const std::vector<mpz_class> &cipher, const mpz_class &d, const mpz_class &n);

#endif // RSA_UTILS_H
