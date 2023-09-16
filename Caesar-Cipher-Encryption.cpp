#include <iostream>
#include <string.h>
using namespace std;

string CaesarEncryption(string plain);
int strLen(string &str);

int main(){

    string PlainText;
    cout<<"Plain Text: ";
    getline(cin,PlainText);

    cout<<"\nCipher Text: "<<CaesarEncryption(PlainText)<<endl;

    return 0;
}
//----------------//Functions//----------------//
string CaesarEncryption(string plain){

    int key=3;
    string cipher="";
    for(int i=0; i<strLen(plain); ++i){
        if(plain[i]>=65 && plain[i]<=90)        //upper case letter with upper case substitution
            cipher+=char(65+(plain[i]-65+key)%26);
        else if(plain[i]>=97 && plain[i]<=122)      //lower case letter with lower case substitution
            cipher+=char(97+(plain[i]-97+key)%26);
        else if(plain[i]==32)               //'!'if there is space in string
            cipher+=char(plain[i]+1);
    }
    return cipher;
}

int strLen(string &str){    //to find string length
    int len=0;
    while(str[len]!='\0')
        ++len;
    return len;
}