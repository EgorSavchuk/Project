#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <fstream>
#include <string>
#include <random>
using namespace std;


boost::multiprecision::cpp_int modexp(const boost::multiprecision::cpp_int &x, boost::multiprecision::cpp_int y,
                                      const boost::multiprecision::cpp_int &N) {
    if (y == 0) return 1;
    boost::multiprecision::cpp_int z = modexp(x, y / 2, N);
    if (y % 2 == 0)
        return (z * z) % N;
    else
        return (x * z * z) % N;
}


boost::multiprecision::cpp_int random(const int &min, const boost::multiprecision::cpp_int &max) {
    namespace mp = boost::multiprecision;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    typedef boost::uniform_int<mp::cpp_int> NumberDistribution;
    typedef boost::mt19937 RandomNumberGenerator;
    typedef boost::variate_generator<RandomNumberGenerator &, NumberDistribution> Generator;
    NumberDistribution distribution(min, max);
    RandomNumberGenerator generator;
    Generator numberGenerator(generator, distribution);
    generator.seed(clock() + time(0) + dis(gen));
    return numberGenerator();
}


bool MillerRabin(const boost::multiprecision::cpp_int &num, const int &repeat = 5) {
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
            while (v != (num - 1)) {
                if (i == (s - 1)) {
                    return false;
                } else {
                    i += 1;
                    v = modexp(v, 2, num);
                }
            }
        }
    }
    return true;
}


bool isPrime(const boost::multiprecision::cpp_int &num) {
    if (num < 2) {
        return false;
    }

    vector<int> lowPrimes = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
            47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,
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
    for (const int &i : lowPrimes) {
        if (num == i) {
            return true;
        }
    }
    for (const int &i : lowPrimes) {
        if (num % i == 0) {
            return false;
        }
    }
    return MillerRabin(num);
}


boost::multiprecision::cpp_int GeneratingBigPrime(const int &size_bit = 1024) {
    namespace mp = boost::multiprecision;
    while (1) {
        mp::cpp_int num = random(0, mp::pow(mp::cpp_int(2), size_bit));
        if (isPrime(num)) {
            return num;
        }
    }
}


bool CoprimeTest(boost::multiprecision::cpp_int z, boost::multiprecision::cpp_int E) {
    while (z != 0 and E != 0) {
        if (z > E) {
            z %= E;
        } else {
            E %= z;
        }
    }
    if ((z + E) == 1) {
        return true;
    } else {
        return false;
    }
}

boost::multiprecision::cpp_int GeneratingE(const boost::multiprecision::cpp_int &z) {
    namespace mp = boost::multiprecision;
    while (1) {
        mp::cpp_int E = random(1000000000, mp::pow(mp::cpp_int(10), 11));
        if (CoprimeTest(z, E) and E < z) {
            return E;
        }
    }
}


boost::multiprecision::cpp_int
gcd(const boost::multiprecision::cpp_int &a, const boost::multiprecision::cpp_int &b, boost::multiprecision::cpp_int &x,
    boost::multiprecision::cpp_int &y) {
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


boost::multiprecision::cpp_int
GeneratingD(const boost::multiprecision::cpp_int &E, const boost::multiprecision::cpp_int &z) {
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


struct keys {
    boost::multiprecision::cpp_int n;
    boost::multiprecision::cpp_int E;
    boost::multiprecision::cpp_int D;
};


struct PublicKeys {
    boost::multiprecision::cpp_int E;
    boost::multiprecision::cpp_int n;
};


struct PrivateKeys {
    boost::multiprecision::cpp_int D;
    boost::multiprecision::cpp_int n;
};

PublicKeys PublicKeysReading(const string &name) {
    ifstream input(name);
    string inp;
    getline(input, inp);
    string e_str = "";
    string n_str = "";
    bool b = 1;
    for (const char &i : inp) {
        if (i == '/') {
            b = 0;
            continue;
        }
        (b ? e_str += i : n_str += i);
    }
    boost::multiprecision::cpp_int E(e_str);
    boost::multiprecision::cpp_int n(n_str);
    PublicKeys keys = {E, n};
    return keys;
}

PrivateKeys PrivateKeysReading(const string &name) {
    ifstream input(name);
    string inp;
    getline(input, inp);
    string d_str = "";
    string n_str = "";
    bool b = 1;
    for (const char &i : inp) {
        if (i == '/') {
            b = 0;
            continue;
        }
        (b ? d_str += i : n_str += i);
    }
    boost::multiprecision::cpp_int D(d_str);
    boost::multiprecision::cpp_int n(n_str);
    PrivateKeys keys = {D, n};
    return keys;
}

boost::multiprecision::cpp_int EncryptionNum(const boost::multiprecision::cpp_int &num, const PublicKeys &keys) {
    return modexp(num, keys.E, keys.n);
}

string Encryption(const string &message, const PublicKeys &keys) {
    string x;
    int ch = 0;
    ostringstream ss;
    ostringstream ss2;
    ss << setfill('0');
    for (const char &i : message) {
        x = to_string((int) i);
        ss << setw(4) << x;
        ch++;
        if (ch == 100) {
            string str = '1' + ss.str();
            ss.str("");
            ss.clear();
            boost::multiprecision::cpp_int res(str);
            ss2 << EncryptionNum(res, keys) << ' ';
            ch = 0;
        }
    }
    if (ch != 0) {
        string str = '1' + ss.str();
        boost::multiprecision::cpp_int res(str);
        ss2 << EncryptionNum(res, keys);
    }
    string result = ss2.str();
    return result;
}

boost::multiprecision::cpp_int DecryptionNum(const boost::multiprecision::cpp_int &num, const PrivateKeys &keys) {
    return modexp(num, keys.D, keys.n);
}

string Decryption(string message, const PrivateKeys &keys) {
    string num = "";
    string result = "";
    ostringstream ss;
    message += ' ';
    ss.str("");
    ss.clear();
    for (const char &i : message) {
        if (i != ' ') {
            num += i;
        } else {
            boost::multiprecision::cpp_int res(num);
            num = "";
            ss << DecryptionNum(res, keys);
            string preres = ss.str();
            ss.str("");
            ss.clear();
            preres.erase(0, 1);
            int ch = 0;
            string tmp = "";
            for (const char &j : preres) {
                tmp += j;
                ch++;
                if (ch == 4) {
                    char t = stoi(tmp);
                    tmp = "";
                    ch = 0;
                    result += t;
                }
            }
        }
    }
    return result;
}

keys newkeys(const int &size_bit = 1024) {
    boost::multiprecision::cpp_int p = 2;
    boost::multiprecision::cpp_int q = 2;
    while (p == q) {
        p = GeneratingBigPrime(size_bit);
        q = GeneratingBigPrime(size_bit);
    }
    boost::multiprecision::cpp_int z = (p - 1) * (q - 1);
    boost::multiprecision::cpp_int n = (p * q);
    boost::multiprecision::cpp_int E = GeneratingE(z);
    boost::multiprecision::cpp_int D = GeneratingD(E, z);
    keys k = {n, E, D};
    return k;
}

bool PublicKeysRecording(const PublicKeys &keys, const std::string &directory) {
    std::string dir_for_pub = directory + "publickey.txt";
    std::ofstream fout;
    fout.open(dir_for_pub);
    if (fout.is_open()) {
        fout << keys.E << '/' << keys.n;
        return true;
    }
}

bool PrivateKeysRecording(const PrivateKeys &keys, const std::string &directory) {
    std::string dir_for_pub = directory + "privatekey.txt";
    std::ofstream fout;
    fout.open(dir_for_pub);
    if (fout.is_open()) {
        fout << keys.D << '/' << keys.n;
        return true;
    }
}

