#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <openssl/sha.h>
using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("sensitive.txt");
    fout.open("sensitive_checksum.txt");
    string line;
    while(getline(fin, line))
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, line.c_str(), strlen(line.c_str()));
        SHA256_Final(hash, &sha256);
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            fout << hex << (int)hash[i];
        }
        fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}


