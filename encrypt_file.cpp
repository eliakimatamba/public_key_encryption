
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class RSA
{
public:
    RSA();
    RSA(int, int);
    int encrypt(int);
    int decrypt(int);
    int gcd(int, int);
    int fastExponentiation(int, int, int);
    void generateKeys();
private:
    int p, q, d, e, n, phiN;
};

RSA::RSA()
{
    srand(time(NULL));
    p = rand() % 10000 + 1;
    q = rand() % 10000 + 1;
    n = p * q;
    phiN = (p - 1) * (q - 1);
    d = 0;
    e = 0;
}

RSA::RSA(int x, int y)
{
    p = x;
    q = y;
    n = p * q;
    phiN = (p - 1) * (q - 1);
    d = 0;
    e = 0;
}

int RSA::gcd(int a, int b)
{
    if(a == 0)
        return b;
    return gcd(b%a, a);
}

int RSA::fastExponentiation(int base, int exp, int mod)
{
    int result = 1;
    base = base % mod;
    while(exp > 0)
    {
        if(exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

void RSA::generateKeys()
{
    ofstream fout1, fout2;
    fout1.open("pub_key");
    fout2.open("priv_key");
    for(int i = 2; i < phiN; i++)
    {
        if(gcd(i, phiN) == 1)
        {
            e = i;
            break;
        }
    }
    for(int i = 2; i < phiN; i++)
    {
        if((i * e) % phiN == 1)
        {
            d = i;
            break;
        }
    }
    fout1 << e << " " << n << endl;
    fout2 << d << " " << n << endl;
    fout1.close();
    fout2.close();
}

int RSA::encrypt(int message)
{
    return fastExponentiation(message, e, n);
}

int RSA::decrypt(int encryptedMessage)
{
    return fastExponentiation(encryptedMessage, d, n);
}

int main()
{
    RSA rsa;
    rsa.generateKeys();
    ifstream fin;
    ofstream fout;
    fin.open("pub_key");
    fout.open("encrypted.txt");
    int e, n;
    fin >> e >> n;
    fin.close();
    fin.open("sensitive.txt");
    string line;
    while(getline(fin, line))
    {
        for(int i = 0; i < line.length(); i++)
        {
            int message = (int)line[i];
            int encryptedMessage = rsa.encrypt(message);
            fout << encryptedMessage << " ";
        }
        fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
