#include <iostream>
using namespace std;

int strLen(string &str);
string Hill_Cipher_Encryption(string plain, int key[2][2]);
string Hill_Cipher_Decryption(string cipher, int key[2][2]);

int main(){

    string PlainText="";
    cout<<"Enter Plain Text: ";
    getline(cin,PlainText);
    
    int Key[2][2];
    cout<<"\nEnter 4 Numbers for Key\n";
    for(int i=0; i<2; ++i)
        for(int j=0; j<2; ++j)
            cin>>Key[i][j];
    if(strLen(PlainText)%2!=0)
        PlainText+='x';
    
    PlainText=Hill_Cipher_Encryption(PlainText,Key);
    cout<<"Encrypted Text: "<<PlainText<<endl;

    cout<<"\nDo You Want to Decrypt the Cipher Text to Plain Text (Y/N) : ";
    char choice;
    cin>>choice;
    if(choice=='Y' || choice=='y')
        cout<<"\nDecrypted Text: "<<Hill_Cipher_Decryption(PlainText,Key)<<endl;
    else
        cout<<"\nExiting...\n";

    return 0;
}
string Hill_Cipher_Encryption(string plain, int key[2][2]){

    string cipher="";
    for(int p=0; p<strLen(plain); p+=2){

        int ct[2][2]={plain[p]-97,plain[p+1]-97,0,0};

        for(int i=0; i<2; ++i){
            for(int j=0; j<2; ++j){
                ct[1][i]+= ct[0][j] * key[j][i];
            }
        }
        cipher+=char((ct[1][0]%26)+97);
        cipher+=char((ct[1][1]%26)+97);
    }
    return cipher;
}
string Hill_Cipher_Decryption(string cipher, int key[2][2]){

    int det=0;
    det+=(key[0][0]*key[1][1]);     //taking determinant
    det-=(key[0][1]*key[1][0]);

    if(det<0 && (det*-1)>26){       //making valid in range
        int temp=det*-1;
        temp%=26;
        temp=temp*-1;
        det=temp+26;
    }
    else if(det<0 && (det*-1)<26)
        det+=26;
    else
        det%=26;

    int temp=key[0][0];     //taking adjoint
    key[0][0]=key[1][1];
    key[1][1]=temp;
    key[0][1]*=(-1);
    key[1][0]*=(-1);

    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){     //making every element of matrix valid and in range

            int val = key[i][j];
            if(val<0 && (val*-1)>26){
                int temp=val*-1;
                temp%=26;
                temp=temp*-1;
                val=temp+26;
            }
            else if(val<0 && (val*-1)<26)
                val+=26;
            else
                val%=26;
            key[i][j]=val;
            // cout<<key[i][j]<<" ";
        }
        // cout<<endl;
    }
    int i=1;
    while(1){                        //finding multiplicative inverse of 1/det
        // cout<<i<<" "<<i*det%26<<endl;
        if((i*det)%26==1){           //can use Extended Euclidean Algorithm for large numbers
            det=i;
            break;
        }
        ++i;
    }

    for(int i=0; i<2; ++i){
        for(int j=0; j<2; ++j){
            key[i][j]=(key[i][j]*det)%26;
        }
    }

    string plain="";
    int pt[2]={0,0};
    for(int c=0; c<strLen(cipher); c+=2){           //using reverse generated key to decrypt
        int pt[2][2]={cipher[c]-97,cipher[c+1]-97,0,0};
        for(int i=0; i<2; ++i){
            for(int j=0; j<2; ++j){
                pt[1][i]+= pt[0][j] * key[j][i];
            }
        }
        plain+=char((pt[1][0]%26)+97);
        plain+=char((pt[1][1]%26)+97);
    }
    return plain;
}
int strLen(string &str){    //to find string length
    int len=0;
    while(str[len]!='\0')
        ++len;
    return len;
}