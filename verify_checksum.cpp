#include <iostream> 
#include<fstream>
#include<string>
using namespace std; 
int main() 
{ 
    string checkSum, text; 
    ifstream file1, file2; 
    file1.open("sensitive.txt"); 
    file2.open("sensitive_checksum.txt"); 
    getline(file2, checkSum); 
    while (getline(file1, text)) 
    { 
        for (int i = 0; i < text.length(); i++) 
            checkSum[i] = checkSum[i] ^ text[i]; 
    } 
    file1.close(); 
    file2.close(); 
    if (checkSum == "Accept!") 
        cout << "Accept!"; 
    else
        cout << "Reject!"; 
    return 0; 
}