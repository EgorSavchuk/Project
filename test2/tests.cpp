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


TEST_CASE("isPrime test") {
    int a, b, c, d, e, f, g;
    a = 3;
    b = 7;
    c = 877;
    d = 10;
    e = 9110371;
    f = 100000;
    g = 2442019;
    REQUIRE((isPrime(a) * isPrime(b) * isPrime(c) * !isPrime(d) * isPrime(e) * !isPrime(f) * isPrime(g)) == true);
}

TEST_CASE("modexp test") {
    bool b = 1;
    b *= (modexp(2, 3, 4) == 0);
    b *= (modexp(80, 90, 30) == 10);
    b *= (modexp(3457, 684246, 813354) == 594841);
    REQUIRE(b == true);
}

TEST_CASE("CoprimeTest test") {
    bool b = 1;
    b *= (CoprimeTest(245, 243) == 1);
    b *= (CoprimeTest(23634745, 8767456) == 1);
    b *= (CoprimeTest(4, 16) == 0);
    REQUIRE(b == true);
}

TEST_CASE("gcd test") {
    boost::multiprecision::cpp_int a, b, c, d;
    a = 15;
    b = 60;
    REQUIRE(gcd(a, b, c, d) == 15);
    a = 45;
    b = 450;
    REQUIRE(gcd(a, b, c, d) == 45);
}


/*TEST_CASE("Final test") {
    keys k = newkeys(1024);
    PublicKeys publ = {k.E, k.n};
    PrivateKeys priv = {k.D, k.n};
    PrivateKeyRecording(priv, "Testpri");
    PublicKeysRecording(publ, "Testpub");
    std::string text = "QWERTYUIOPASDFGHJKLZXCVBNM\nqwertyuioplkjhgfdsazxcvbnm123456789!@#$%^&&*()_-+=/?";
    std::string x = Encryption(text, PublicKeysReading("Testpub"));
    REQUIRE(Decryption(x, PrivateKeysReading("Testpri")) == text);
}
*/
