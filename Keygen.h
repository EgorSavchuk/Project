#ifndef KEYGEN_H
#define KEYGEN_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

/**Эффективная реализация (x ^ y) % N
 \param x - число, которое возводят в степень
 \param y - степень
 \param N - число, на которое делят по модулю
 \return результат формулы*/
boost::multiprecision::cpp_int modexp(const boost::multiprecision::cpp_int &x, boost::multiprecision::cpp_int y,
                                      const boost::multiprecision::cpp_int &N);

/**Генератор огромных случайных чисел от min до max
 \param min - число, больше которого должно генерироваться число
 \param max - число, меньше которого должно генерироваться число
 \return случайное число из заданного диапазона*/
boost::multiprecision::cpp_int random(const int &min, const boost::multiprecision::cpp_int max);

/**Алгоритм, с высокой точностью проверяющий на простоту число num (используется в isPrime)
 \param num - число, которое проверяем на простоту
 \param repeat - количество проверок(влияет на вероятность того, что число простое, по умолчанию стоит 5, что вполне достаточно)
 \return true или false (простое или нет)*/
bool MillerRabin(const boost::multiprecision::cpp_int &num, const int &repeat = 5);

/**Алгоритм, с высокой точностью проверяющий на простоту число num, использует алогритм Миллера-Рабина (описан выше),
 но, чтобы быстрее вычислять точно не простые числа, выполняет деление на первые простые чилса до 997
 \param num - число, которое проверяем на простоту
 \return true или false (простое или нет)*/
bool isPrime(const boost::multiprecision::cpp_int &num);

/**Генерирует большое простое число
 \param size_bit - количество бит нашего большого простого числа (по умолчанию 1024бит)
 \return Большое простое число заданой величины*/
boost::multiprecision::cpp_int GeneratingBigPrime(const int &size_bit = 1024);

/**Проверка числа z и E на взаимную простоту
 \param z - первое число для проверки на взаимную простоту
 \param E - второе число для проверки на взаимную простоту
 \return true или false (взаимно простые или нет)*/
bool CoprimeTest(boost::multiprecision::cpp_int z, boost::multiprecision::cpp_int E);

/**Генерируется число E (часть открытого ключа) взаимно простое c числом z.
 Проверка произодится с помощью функции CoprimeTest
 \param z = (p-1) * (q-1), проверяется на взаимную простоту с E*/
boost::multiprecision::cpp_int GeneratingE(const boost::multiprecision::cpp_int &z);

/**Модернезированный алгоритм Евклида - находит НОД и коэффициенты x и y такие, что: a * x + b * y = gcd(a, b).
 Функция взята из интернета и переделана под необходимый тип целочисленных цифр.
 \param a первое число для поиска НОД
 \param b второе число для поиска НОД
 \param x - число из формулы a * x + b * y = gcd(a, b)
 \param y - число из формулы a * x + b * y = gcd(a, b)
 \return НОД для a и b*/
boost::multiprecision::cpp_int
gcd(const boost::multiprecision::cpp_int &a, const boost::multiprecision::cpp_int &b, boost::multiprecision::cpp_int &x,
    boost::multiprecision::cpp_int &y);

/**Генерирует число D (одно из двух чисел закрытого ключа)
 \param E - часть открытого ключа, нужен для генерации числа D
 \param z - z = (p-1) * (q-1), нужен для генерации числа D
 \return число D - часть закрытого ключа*/
boost::multiprecision::cpp_int
GeneratingD(const boost::multiprecision::cpp_int &E, const boost::multiprecision::cpp_int &z);

struct keys {
    /// Число n - входит в состав открытого и закрытого ключа.
    boost::multiprecision::cpp_int n;
    /// Число E - входит в состав открытого ключа.
    boost::multiprecision::cpp_int E;
    /// Число D - входит в состав закрытого ключа.
    boost::multiprecision::cpp_int D;
};

struct PublicKeys {
    /// Число E - входит в состав открытого ключа.
    boost::multiprecision::cpp_int E;
    /// Число n - входит в состав открытого и закрытого ключа.
    boost::multiprecision::cpp_int n;
};

struct PrivateKeys {
    /// Число D - входит в состав закрытого ключа.
    boost::multiprecision::cpp_int D;
    /// Число n - входит в состав открытого и закрытого ключа.
    boost::multiprecision::cpp_int n;
};

/**Генерирует все ключи
 \param size_bit - количество бит наших ключей (по умолчанию 1024бит)
 \return структура из всех ключей*/
keys newkeys(const int &size_bit = 1024);

/**Читает ключи из файла
 \param name - Путь к файлу
 \return структура PublicKeys, открытый ключ*/
PublicKeys PublicKeysReading(const std::string &name);

/**Шифрует число, используется при шифровании текста
 \param num - Число, которое мы хотим зашифровать
 \param keys - структура публичных ключей
 \return зашифрованное число*/
boost::multiprecision::cpp_int EncryptionNum(const boost::multiprecision::cpp_int &num, const PublicKeys &keys);

/**Шифрует текст
 \param message - сообщение, которое мы хотим зашифровать
 \param keys - структура публичных ключей
 \return зашифрованное сообщение*/
std::string Encryption(const std::string &message, const PublicKeys &keys);

/**Дешифрует число, используется при дешифровании текста
 \param num - Число, которое мы хотим дешифровать
 \param keys - структура приватных ключей
 \return дешифрованное число*/
boost::multiprecision::cpp_int DecryptionNum(const boost::multiprecision::cpp_int &num, const PrivateKeys &keys);

/**Дешифрует текст
 \param message - сообщение, которое мы хотим дешифровать
 \param keys - структура приватных ключей
 \return дешифрованное сообщение*/
std::string Decryption(std::string message, const PrivateKeys &keys);

/**Читает ключи из файла
 \param name - Путь к файлу
 \return структура PrivateKeys, открытый ключ*/
PrivateKeys PrivateKeysReading(const std::string &name);

/**Записывает файл publickey.txt в указанную директорию
 \param directory - Путь к файлу
 \param keys - структура PublicKeys, открытый ключ
 \return true если файл publickey.txt открылся*/
bool PublicKeysRecording(const PublicKeys &keys, const std::string &directory);

/**Записывает файл privatekey.txt в указанную директорию
 \param directory - Путь к файлу
 \param keys - структура PrivateKeys, открытый ключ
 \return true если файл privatekey.txt открылся*/
bool PrivateKeysRecording(const PrivateKeys &keys, const std::string &directory);

#endif // KEYGEN_H
