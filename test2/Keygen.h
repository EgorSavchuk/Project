#ifndef KEYGEN_H
#define KEYGEN_H
struct PublicKey{
    int e = 0;
    int n = 0;
};
struct PrivateKey{
    int d = 0;
    int n = 0;
};

void SetBitSize (int x);
int ShowBitSize();
PublicKey GenerationPublicKey(int i);
PrivateKey GenerationPrivateKey(int i);
#endif // KEYGEN_H
