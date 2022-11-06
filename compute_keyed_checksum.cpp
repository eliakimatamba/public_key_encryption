#include <iostream> 
#include<fstream>
#include<string>
#include<openssl/hmac.h>

#include<openssl/sha.h>
#include<iomanip>
using namespace std; 
int main() 
{ 
unsigned char checksum[SHA256_DIGEST_LENGTH]; 
HMAC_CTX ctx; 
HMAC_CTX_init(&ctx); 
ifstream file1, file2; 
ofstream file3; 
file1.open("sensitive.txt"); 
file2.open("key.bin", ios::binary); 
file3.open("sensitive_keyed_checksum.txt"); 
string text; 
unsigned char key[256]; 
file2.read((char*)key, 256); 
HMAC_Init_ex(&ctx, key, 256, EVP_sha256(), NULL); 
while (getline(file1, text)) 
{ 
HMAC_Update(&ctx, (unsigned char*)text.c_str(), 
text.length()); 
} 
int len;
HMAC_Final(&ctx, checksum, &len); 
HMAC_CTX_cleanup(&ctx); 
for (int i = 0; i < len; i++) 
file3 << hex << setw(2) << setfill('0') << (int)checksum[i]; 
file1.close(); 
file2.close(); 
file3.close(); 
return 0; 
}
