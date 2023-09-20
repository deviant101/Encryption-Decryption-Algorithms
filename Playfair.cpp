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
int findloc(char** m, char ch)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(ch == m[i][j])
            {
                return (i*10)+j;
            }
        }
    }
    return 0;
}
void Playfair(string plain, string kword){

    char **Matrix;
    Matrix = new char*[5];
    for(int i=0; i<5; i++)
        Matrix[i]= new char[5];
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
    string pair[strLen(plain)/2];
    for(int i=0,j=0;i<strLen(plain);i+=2,j++)
    {
        pair[j]+=plain[i];
        pair[j]+=plain[i+1];
    }
    string cypher="";
    for(int i=0;i<strLen(plain)/2;i++)
    {
        temp=pair[i];
        int r1=findloc(Matrix,temp[0])/10;
        int c1=findloc(Matrix,temp[0])%10;
        int r2=findloc(Matrix,temp[1])/10;
        int c2=findloc(Matrix,temp[1])%10;
        if(r1 == r2)
        {
            if(c1 == 4)
                cypher+=Matrix[r1][0];
            else
                cypher+=Matrix[r1][c1+1];
            if(c2 == 4)
                cypher+=Matrix[r1][0];
            else
                cypher+=Matrix[r1][c2+1];
        }
        else if(c1 == c2)
        {
            if(r1 == 4)
                cypher+=Matrix[0][c1];
            else
                cypher+=Matrix[r1+1][c1];
            if(r2 == 4)
                cypher+=Matrix[0][c2];
            else
                cypher+=Matrix[r2+1][c2];
        }
        else
        {
            cypher+=Matrix[r1][c2];
            cypher+=Matrix[r2][c1];
        }
    }
    cout<<cypher<<endl;
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
            if(str[i]==str[i+1]){
                temp+=str[i];
                temp+='x';
            }
            else
            {
                temp+=str[i];
                temp+=str[i+1];
                i++;
            }
    }
    if(strLen(temp)%2==1)   //to make string length even by adding x at end
        temp+='x';
    string temp2="";
    for(int i=0;i<temp.length();i++)
    {
        if(temp[i]==0)
            continue;
        else
            temp2+=temp[i];
    }
    return temp2;
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
