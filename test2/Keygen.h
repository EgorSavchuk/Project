#ifndef KEYGEN_H
#define KEYGEN_H
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

boost::multiprecision::cpp_int modexp(const boost::multiprecision::cpp_int& x, boost::multiprecision::cpp_int y, const boost::multiprecision::cpp_int& N);
boost::multiprecision::cpp_int random(const int& min, const boost::multiprecision::cpp_int max);
bool MillerRabin(const boost::multiprecision::cpp_int& num,const int& repeat = 5);
bool isPrime(const boost::multiprecision::cpp_int& num);
boost::multiprecision::cpp_int GeneratingBigPrime(const int& size_bit = 1024);
bool CoprimeTest(boost::multiprecision::cpp_int z, boost::multiprecision::cpp_int E);
boost::multiprecision::cpp_int GeneratingE(const boost::multiprecision::cpp_int& z);
boost::multiprecision::cpp_int gcd(const boost::multiprecision::cpp_int& a, const boost::multiprecision::cpp_int& b, boost::multiprecision::cpp_int &x, boost::multiprecision::cpp_int &y);
boost::multiprecision::cpp_int GeneratingD(const boost::multiprecision::cpp_int& E, const boost::multiprecision::cpp_int& z);

struct keys {
    /// число
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

keys newkeys(const int& size_bit = 1024);

#endif // KEYGEN_H
