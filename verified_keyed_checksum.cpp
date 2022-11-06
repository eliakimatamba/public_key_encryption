
#include <iostream> 
#include<fstream>
#include<string>
#include<openssl/hmac.h>
#include<openssl/sha.h>
#include<iomanip>
using namespace std; 
int main() 
{ 
    string checkSum, text; 
    unsigned char checksum[SHA256_DIGEST_LENGTH]; 
    HMAC_CTX ctx; 
    HMAC_CTX_init(&ctx); 
    ifstream file1, file2; 
    file1.open("sensitive.txt"); 
    file2.open("key.bin", ios::binary); 
    getline(file2, checkSum); 
    unsigned char key[256]; 
    file2.read((char*)key, 256); 
    HMAC_Init_ex(&ctx, key, 256, EVP_sha256(), NULL); 
    while (getline(file1, text)) 
    { 
        HMAC_Update(&ctx, (unsigned char*)text.c_str(), 
                    text.length()); 
    } 
    HMAC_Final(&ctx, checksum, &len); 
    HMAC_CTX_cleanup(&ctx); 
    for (int i = 0; i < len; i++) 
        checkSum[i] = checkSum[i] ^ checksum[i]; 
    file1.close(); 
    file2.close(); 
    if (checkSum == "Accept!") 
        cout << "Accept!"; 
    else
        cout << "Reject!"; 
    return 0; 
}