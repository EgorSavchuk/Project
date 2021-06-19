struct PublicKey{
    int e = 0;
    int n = 0;
};
struct PrivateKey{
    int d = 0;
    int n = 0;
};
int c = 0;
void SetBitSize (int x){
    c = x;
}
int ShowBitSize (){
    return c;
}
PublicKey GenerationPublicKey(int i){
    int p = 29;
    int q = 43;
    int n = p * q;
    PublicKey key;
    key.e = 5 * i;
    key.n = n;
    return key;
}
PrivateKey GenerationPrivateKey(int i){
    int p = 29;
    int q = 43;
    int n = p * q;
    PrivateKey key2;
    key2.d = 941 * i;
    key2.n = n;
    return key2;
}
