#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <fstream>
#include <locale>
#include <string>
#include <random>

using namespace std;
int bit = 0;



/**Эффективная реализация (x ^ y) % N */
boost::multiprecision::cpp_int modexp(const boost::multiprecision::cpp_int& x, boost::multiprecision::cpp_int y, const boost::multiprecision::cpp_int& N)
{
    if (y == 0) return 1;
    boost::multiprecision::cpp_int z = modexp(x, y / 2, N);
    if (y % 2 == 0)
        return (z*z) % N;
    else
        return (x*z*z) % N;
}

/**Генератор огромных случайных чисел от min до max */
boost::multiprecision::cpp_int random(const int& min, const boost::multiprecision::cpp_int max) {
    namespace mp = boost::multiprecision;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    typedef boost::uniform_int<mp::cpp_int> NumberDistribution;
    typedef boost::mt19937 RandomNumberGenerator;
    typedef boost::variate_generator<RandomNumberGenerator&, NumberDistribution> Generator;
    NumberDistribution distribution(min, max);
    RandomNumberGenerator generator;
    Generator numberGenerator(generator, distribution);
    generator.seed(clock() + time(0) + dis(gen));
    return numberGenerator();
}

/**Алгоритм, с высокой точностью, проверяющий на простоту число num (используется в isPrime) */
bool MillerRabin(const boost::multiprecision::cpp_int& num,const int& repeat = 5) {
    namespace mp = boost::multiprecision;
    mp::cpp_int d = num - 1;
    mp::cpp_int s = 0;
    while (d % 2 == 0) {
        d = d / 2;
        s += 1;
    }
    for (int i = 0; i < repeat; i++) {
        mp::cpp_int a = random(2, num - 1);
        mp::cpp_int v = modexp(a, d, num);
        if (v != 1) {
            i = 0;
            while (v != (num -1)) {
                if (i == (s - 1)) {
                    return false;
                }
                else {
                    i += 1;
                    v = modexp(v, 2, num);
                }
            }
        }
    }
    return true;
}


/**Алгоритм, с высокой точностью, проверяющий на простоту число num, использует алогритм Миллера-Рабина (описан выше),
но, чтобы быстрее вычислять точно не простые числа, выполняет деление на первые простые чилса до 997  */
bool isPrime(const boost::multiprecision::cpp_int& num) {
    if (num < 2) {
        return false;
    }

    vector <int> lowPrimes = {
            2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,
            47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107,
            109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
            191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
            269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
            353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
            439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
            523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
            617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
            709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
            811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
            907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    for (const int& i : lowPrimes) {
        if (num == i) {
            return true;
        }
    }
    for (const int& i : lowPrimes) {
        if (num % i == 0) {
            return false;
        }
    }
    return MillerRabin(num);
}



/**Генерирует большие простые числа*/
boost::multiprecision::cpp_int GeneratingBigPrime(const int& size_bit = 1024) {
    namespace mp = boost::multiprecision;
    while (1) {
        mp::cpp_int num = random(0, mp::pow(mp::cpp_int(2), size_bit));
        if (isPrime(num)) {
            return num;
        }
    }
}



/**Проверка числа z и E на взаимную простоту */
bool CoprimeTest(boost::multiprecision::cpp_int z, boost::multiprecision::cpp_int E) {
    while (z != 0 and E != 0) {
        if (z > E) {
            z %= E;
        }
        else {
            E %= z;
        }
    }
    if ((z + E) == 1) {
        return true;
    }
    else {
        return false;
    }
}
/**Генерируется число e (открытый ключ), проверяя, взаимно ли простое оно
с помощью функции на основе функции Mutual_prime_numbers_test*/
boost::multiprecision::cpp_int GeneratingE(const boost::multiprecision::cpp_int& z) {
    namespace mp = boost::multiprecision;
    while (1) {
        mp::cpp_int E = random(1000000000, mp::pow(mp::cpp_int(10), 11));
        if (CoprimeTest(z, E) and E < z) {
            return E;
        }
    }
}

/**Модернезированный алгоритм Евклида - находит НОД и коэффициенты x и y такие, что: a * x + b * y = gcd(a, b).
 Функция взята из интернета и переделана под необходимый тип целочисленных цифр.
 \param a первое число для поиска НОД
 \param x
 \return НОД для a и b*/
boost::multiprecision::cpp_int gcd(const boost::multiprecision::cpp_int& a, const boost::multiprecision::cpp_int& b, boost::multiprecision::cpp_int &x, boost::multiprecision::cpp_int &y) {
    boost::multiprecision::cpp_int x1;
    boost::multiprecision::cpp_int y1;
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    boost::multiprecision::cpp_int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

/**Генерирует число D (одно из двух чисел закрытого ключа)*/
boost::multiprecision::cpp_int GeneratingD(const boost::multiprecision::cpp_int& E, const boost::multiprecision::cpp_int& z) {
    while (1) {
        boost::multiprecision::cpp_int x;
        boost::multiprecision::cpp_int y;
        boost::multiprecision::cpp_int g = gcd(E, z, x, y);
        if (g == 1) {
            x = (x % z + z) % z;
            return x;
        }
    }
}

/**Структура всех ключей*/
struct keys {
    boost::multiprecision::cpp_int n;
    boost::multiprecision::cpp_int E;
    boost::multiprecision::cpp_int D;
};

/**Структура открытых ключей*/
struct PublicKeys {
    boost::multiprecision::cpp_int E;
    boost::multiprecision::cpp_int n;
};

/**Структура закрытых ключей*/
struct PrivateKeys {
    boost::multiprecision::cpp_int D;
    boost::multiprecision::cpp_int n;
};

/**Генерирует все ключи*/
keys newkeys(const int& size_bit = 1024) {
    boost::multiprecision::cpp_int p = 2;
    boost::multiprecision::cpp_int q = 2;
    while (p == q) {
        p = GeneratingBigPrime(size_bit);
        q = GeneratingBigPrime(size_bit);
    }
    boost::multiprecision::cpp_int z = (p-1) * (q-1);
        boost::multiprecision::cpp_int n = (p * q);
        boost::multiprecision::cpp_int E = GeneratingE(z);
        boost::multiprecision::cpp_int D = GeneratingD(E, z);
        keys k = {n, E, D};
        return k;
    }

