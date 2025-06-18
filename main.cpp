#include <bits/stdc++.h>
using namespace std;

int pos=0;
string input;

void skipw()
{
    while(pos<input.size()&&isspace(input[pos]))
        pos++;
}
int getnum()
{
    skipw();
    int num=0;
    while(pos<input.size()&&isdigit(input[pos]))
    {
        num=num*10+(input[pos]-'0');//parsing string to integer
        pos++;

    }
    return num;
}
//forward declarations
int expression();
int term();
int factor();

//function to handle the rounded brackets
int factor()
{
    skipw();
    if(input[pos]=='(')
    {
        pos++;
        skipw();
        int result=expression();
        skipw();
        if(input[pos]==')')
            pos++;
        return result;
    }
    else
        return getnum();
}
//function to handle the * and / operations
int term()
{
    int result=factor();
    while(true)
    {
        if(input.size()<=pos)
            break;
        char op=input[pos];
        if(op=='*'||op=='/')
        {
            pos++;
            int nextterm=factor();
            if(op=='*')
                result*=nextterm;
            else
            {
                if(nextterm==0)
                {
                    cout<<"Error : Division by 0"<<endl;
                    exit(1);
                }
                result/=nextterm;
            }
        }
        else{
            break;
        }
    }
    return result;
}
//function to handle + and - operations
int expression()
{
    int result=term();
    while(true)
    {
        skipw();
        if(pos>=input.size())
            break;
        char op=input[pos];
        if(op=='+'||op=='-')
        {
            pos++;
            int nextterm=term();
            result=op=='+'?result+nextterm:result-nextterm;
        }
        else
            break;
    }
    return result;

}
int main()
{
    cout<<"Enter an Arithematic Expression :"<<endl;
    getline(cin,input);

    int result=expression();
    skipw();
    if(pos!=input.size())
        cout<<"Not a Valid Expression use (digits , ( , ), + , - , * , / )"<<endl;
    else
        cout<<"\n\nResult of Expression : "<<result<<endl;
    return 0;
}