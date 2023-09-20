#include <iostream>
#include <string.h>
using namespace std;

int strLen(string &str);
string checkKeyword(string str);
string checkPlainText(string str);
bool checkExistence(char ch, string str);
void Playfair(string plain, string kword);

int main(){
    string Kword="";
    cout<<"Keyword: ";
    getline(cin,Kword);
    Kword=checkKeyword(Kword);
    cout<<Kword<<endl;

    string PlainText="";
    cout<<"Plain Text: ";
    getline(cin,PlainText);
    PlainText=checkPlainText(PlainText);
    cout<<PlainText<<endl;

    Playfair(PlainText,Kword);

    return 0;
}
void Playfair(string plain, string kword){

    char Matrix[5][5];
    // int strlen=strLen(kword);
    int count=0;
    int alphabets=97;
    for(int i=0; i<5; ++i){
        for(int j=0; j<5; ++j){
            if(count<strLen(kword))
                Matrix[i][j]=kword[count++];
            else{
                while(alphabets<=122){
                    if(checkExistence(char(alphabets),kword)==false){
                        Matrix[i][j]=char(alphabets);
                        ++alphabets;
                        if(alphabets==106)  //for i/j case skipping j char
                            ++alphabets;
                        break;
                    }
                    ++alphabets;
                }
            }
            cout<<Matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    string temp="";
    for(int i=0; i<strLen(plain); i+=2){
        int positions[2][2];
        for(int j=0; j<5; ++j){
            for(int k=0; k<5; ++k){
                if(plain[i]==Matrix[i][j]){
                    positions[0][0]=i;  //row in 0 index
                    positions[0][1]=j;  //col in 1 index
                }
                else if(plain[i+1]==Matrix[i][j]){
                    positions[1][0]=i;  //row in 0 index
                    positions[1][1]=j;  //col in 1 index
                }
            }
        }
        if(positions[0][0]==positions[1][0]){ //present in same row
            temp+=
        }
        else if(positions[0][1]==positions[1][1]){  //present in same column

        }
    }
    

}

string checkKeyword(string str){

    string temp="";
    for(int i=0; i<strLen(str); ++i){
        int flag=0;
        for(int j=i+1; j<strLen(str); ++j){
            if(str[i]==str[j]){
                flag=1;
                break;
            }
        }
        if(flag==0)
            temp+=str[i];
    }
    return temp;
}

string checkPlainText(string str){

    string temp="";
    for(int i=0; i<strLen(str); ++i){
        if(i%2==0){
            if(str[i]==str[i+1]){
                temp+=str[i];
                temp+='x';
            }
            else
                temp+=str[i];
        }
        else
            temp+=str[i];
    }
    if(strLen(temp)%2==1)   //to make string length even by adding x at end
        temp+='x';
    return temp;
}

bool checkExistence(char ch, string str){

    for(int i=0; i<strLen(str); ++i)
        if(ch==str[i])
            return true;    //if char present in string
    return false;   //if char not in string
}

int strLen(string &str){    //to find string length
    int len=0;
    while(str[len]!='\0')
        ++len;
    return len;
}