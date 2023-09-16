#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

string CaesarEncryption(string plain);
void Cracker(string cipher);
int strLen(string &str);

int main(){

    string PlainText;
    cout<<"Plain Text: ";
    getline(cin,PlainText);

    string cipher=CaesarEncryption(PlainText);
    cout<<"\nCipher Text: "<<cipher<<endl;
    cout<<"\nKeys\tCombinations\n\n";
    Cracker(cipher);

    return 0;
}
//----------------//Functions//----------------//
string CaesarEncryption(string plain){

    string cipher="";
    srand(time(0));
    int key=1+rand()%26;
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

void Cracker(string cipher){

    for(int key=1; key<=26; ++key){
        string plain="";
        for(int i=0; i<strLen(cipher); ++i){

            if(cipher[i]>=65 && cipher[i]<=90){       //upper case letter with upper case substitution
                char chr=char(65+(cipher[i]-65-key)%26);
                if(chr<65)
                    chr=char(chr+26);   //to keep in appropriate alphabets char range
                plain+=chr;
            }
            else if(cipher[i]>=97 && cipher[i]<=122){      //lower case letter with lower case substitution
                char chr=char(97+(cipher[i]-97-key)%26);
                if(chr<97)
                    chr=char(chr+26);   //to keep in appropriate alphabets char range
                plain+=chr;
            }
            else if(cipher[i]=='!')               //'!'if there is space in string
                plain+=char(cipher[i]-1);
        }
        cout<<key<<"\t"<<plain<<endl;
    }
}

int strLen(string &str){    //to find string length
    int len=0;
    while(str[len]!='\0')
        ++len;
    return len;
}
