#include "Keygen.h"
#include "doctest/doctest.h"

/*
    Данная программа расчитана на работу с очень большими числами, в особенности - простыми.
    Поэтому большинство функций можно протестировать применяя именно такие числа(несколько сотен символов),
    но прям в тестах не удаётся задать такие числа. Случайные большие числа ещё можно задать с помощью степенных фунций,
    но именно простые - не удаётся.
    Поэтому тестируются не все функции, а только те, которые возможно тестировать с небольшими числами.
    Но коректная работа финального теста гарантирует коректную работу бОльшей части программы.
*/


TEST_CASE ("isPrime test") {
    REQUIRE(isPrime(3) == true);
    REQUIRE(isPrime(7) == true);
    REQUIRE(isPrime(877) == true);
    REQUIRE(isPrime(10) == false);
    REQUIRE(isPrime(9110371) == true);
    REQUIRE(isPrime(100000) == false);
    REQUIRE(isPrime(2442019) == true);
}

TEST_CASE ("modexp test") {
     REQUIRE(modexp(2, 3, 4) == 0);
     REQUIRE(modexp(80, 90, 30) == 10);
     REQUIRE(modexp(3457, 684246, 813354) == 594841);
}

TEST_CASE ("CoprimeTest test") {
    REQUIRE(CoprimeTest(245, 243) == 1);
    REQUIRE(CoprimeTest(23634745, 8767456) == 1);
    REQUIRE(CoprimeTest(4, 16) == 0);
}

TEST_CASE ("gcd test") {
    boost::multiprecision::cpp_int a, b, c, d;
    a = 15;
    b = 60;
    REQUIRE(gcd(a, b, c, d) == 15);
    REQUIRE(a * c + b * d == 15);
    a = 45;
    b = 450;
    REQUIRE(gcd(a, b, c, d) == 45);
    REQUIRE(a * c + b * d == 45);
}


TEST_CASE ("Final test") {
    keys k = newkeys();
    PublicKeys publ = {k.E, k.n};
    PrivateKeys priv = {k.D, k.n};
    PrivateKeysRecording(priv, "");
    PublicKeysRecording(publ, "");
    std::string text = "QWERTYUIOPASDFGHJKLZXCVBNM\nqwertyuioplkjhgfdsazxcvbnm123456789!@#$%^&&*()_-+=/?";
    std::string x = Encryption(text, PublicKeysReading("publickey.txt"));
    REQUIRE(Decryption(x, PrivateKeysReading("privatekey.txt")) == text);
    remove("publickey.txt");
    remove("privatekey.txt");
}
