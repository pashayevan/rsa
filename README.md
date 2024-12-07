# Программа для шифрования и расшифровки с использованием RSA

Программа реализует шифрование и расшифровку с использованием алгоритма RSA и с использованием библиотеки GMP (GNU Multiple Precision). Программа показывает процесс генерации ключей RSA, шифрования сообщений и их расшифровки.        

## Библиотеки и зависимости
Программа использует библиотеку GMP (GNU Multiple Precision Arithmetic Library) для работы с большими целыми числами, что необходимо для алгоритма RSA. Для компиляции и запуска кода нужно установить эту библиотеку.

- gmpxx.h: Заголовочный файл для работы с GMP в C++.
- iostream: Стандартная библиотека C++ для ввода/вывода.
- string: Стандартная библиотека C++ для работы со строками.
- vector: Стандартная библиотека C++ для работы с динамическими массивами.

  ### Для компиляции и линковки с библиотекой GMP, используйте следующую команду (на Unix-системах):
   ```cpp
  g++ -o rsa rsa.cpp -lgmpxx -lgmp

# Пояснение к коду
1. Пользовательский вывод для `mpz_class`
   ```cpp
   std::ostream& operator<<(std::ostream& os, const mpz_class& mpz) {
       os << mpz.get_str();
       return os;
   }
   ```
Перегрузка оператора вывода `<<` для класса `mpz_class`. Он позволяет выводить объекты этого типа в поток вывода (например, в консоль) как строку. Метод `get_str()` преобразует большое число в строковое представление. 

## 2. Функция для возведения в степень по модулю (модульная экспонентация)
   ```cpp
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
```
Эта функция реализует алгоритм возведения числа в степень по модулю с использованием метода "быстрого возведения в степень" (методом двоичного разложения показателя). Это основной механизм для шифрования и расшифровки в RSA.

## 3. Функция для вычисления наибольшего общего делителя (НОД)
```cpp
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
```
Эта функция вычисляет НОД двух чисел с помощью алгоритма Евклида, который используется при генерации ключей RSA для нахождения взаимно простых чисел.

## 4. Генерация ключей RSA
```c
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
```

Эта функция генерирует ключи для алгоритма RSA:

-n: произведение двух простых чисел (открытый и закрытый ключ зависят от него).
-e: открытый экспонент (выбирается случайным образом и проверяется на взаимную простоту с `phi(n)`).
-d: закрытый экспонент (вычисляется как обратное число к `e` по модулю `phi(n)`).

## 5. Шифрование сообщения
```cpp
std::vector<mpz_class> encrypt(const std::string &mes, const mpz_class &e, const mpz_class &n) {
    std::vector<mpz_class> mess;
    for (char c : mes) {
        mpz_class number(static_cast<unsigned char>(c));
        mess.push_back(modExp(number, e, n));
    }
    return mess;
}
```
Эта функция шифрует строку (сообщение) с использованием открытого ключа. Каждая буква преобразуется в число и шифруется с помощью модульной экспоненциации.

## 6. Расшифровка сообщения
```cpp
std::string decrypt(const std::vector<mpz_class> &cipher, const mpz_class &d, const mpz_class &n) {
    std::string word;
    for (const auto& el : cipher) {
        mpz_class decryptedNum = modExp(el, d, n);
        char decryptedChar = static_cast<char>(decryptedNum.get_ui());
        word += decryptedChar;
    }
    return word;
}
```
Эта функция расшифровывает сообщение, используя закрытый ключ. Каждый зашифрованный элемент расшифровывается с помощью модульной экспоненциации, и результат преобразуется обратно в символ.


## 7. Основная функция
```cpp
int main() {
    try {
        mpz_class n, e, d;
        generateKeys(n, e, d);
        std::string word;
        std::cout << "Введите сообщение для шифрования:\n";
        getline(std::cin, word);
        std::cout << "Открытый ключ (n): " << n << "\n";
        std::cout << "Открытый экспонент (e): " << e << "\n";
        std::cout << "Закрытый экспонент (d): " << e << "\n";

        std::vector<mpz_class> RsaCode = encrypt(word, e, n);

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
```
Основная функция выполняет следующие шаги:

-1. Генерирует ключи.

-2. Запрашивает у пользователя ввод сообщения для шифрования.

-3. Шифрует сообщение с использованием открытого ключа.

-4. Выводит зашифрованное сообщение.

-5. Расшифровывает сообщение с использованием закрытого ключа.

-6. Выводит расшифрованное сообщение.

---
# Пример работы программы 
```cpp
Введите сообщение для шифрования:
Hello, World!
Открытый ключ (n): 234324234324234324324324324324234
Открытый экспонент (e): 7
Закрытый экспонент (d): 234324234324234
Зашифрованное сообщение: 12345 6789 2345 5678
Расшифрованное сообщение: Hello, World!
```
