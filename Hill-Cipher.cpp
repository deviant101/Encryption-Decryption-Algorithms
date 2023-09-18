#include <iostream>
using namespace std;

int strLen(string &str);
string Hill_Cipher_Encryption(string plain, int key[2][2]);
void Hill_Cipher_Decryption(string cipher, int key[2][2]);

int main(){

    string PlainText="";
    cout<<"Enter Plain Text: ";
    getline(cin,PlainText);
    
    int Key[2][2];
    cout<<"\nEnter 4 Numbers for Key\n";
    for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
            cin>>Key[i][j];
    // if(strLen(PlainText)%2!=0)
    //     PlainText+='!';
    
    PlainText=Hill_Cipher_Encryption(PlainText,Key);
    cout<<PlainText<<endl;

    Hill_Cipher_Decryption(PlainText,Key);
    


    return 0;
}
string Hill_Cipher_Encryption(string plain, int key[2][2]){

    string cipher="";
    for(int p=0; p<strLen(plain); p+=2){

        // cout<<"P "<<p<<endl;
        int ct[2][2]={plain[p]-97,plain[p+1]-97,0,0};
        // cout<<ct[0][0]<<" "<<ct[0][1]<<endl;

        for(int i=0; i<2; ++i){
            for(int j=0; j<2; ++j){
                ct[1][i]+= ct[0][j] * key[j][i];
            }
        }
        // cout<<ct[1][0]<<" "<<ct[1][1]<<endl;
        cipher+=char((ct[1][0]%26)+97);
        cipher+=char((ct[1][1]%26)+97);
    }
    return cipher;
}
void Hill_Cipher_Decryption(string cipher, int key[2][2]){

    int det=0;
    det+=(key[0][0]*key[1][1]);
    det-=(key[0][1]*key[1][0]);

    if(det<0 && (det*-1)>26){
        int temp=det*-1;
        temp%=26;
        temp=temp*-1;
        det=temp+26;
    }
    else if(det<0 && (det*-1)<26)
        det+=26;
    else
        det%=26;

    int temp=key[0][0];
    key[0][0]=key[1][1];
    key[1][1]=temp;

    key[0][1]*=(-1);
    key[1][0]*=(-1);

    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){

            int det = key[i][j];
            if(det<0 && (det*-1)>26){
                int temp=det*-1;
                temp%=26;
                temp=temp*-1;
                det=temp+26;
            }
            else if(det<0 && (det*-1)<26)
                det+=26;
            else
                det%=26;
            key[i][j]=det;
            cout<<key[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Det: "<<det<<endl;

}
int strLen(string &str){    //to find string length
    int len=0;
    while(str[len]!='\0')
        ++len;
    return len;
}