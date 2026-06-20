#include "testlib.h"
#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
bool isp(string s)
{
    int a=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='+')a++;
        else a--;
        if(a<0)return false;
    }
    return a==0;
}
int main(int argc, char * argv[])
{
    registerTestlibCmd(argc, argv);
    for(;;)
    {
        int mx=inf.readInt(),my=inf.readInt();
        //cerr<<mx<<" "<<my<<endl;
        if(mx==0&&my==0)
        {
            ouf.seekEof();
            quitf(_ok,"correct");
        }
        string a=inf.readToken();
        string b=inf.readToken();
        //cerr<<a<<endl;
        //cerr<<b<<endl;
        string r=ouf.readToken();
        string cor=ans.readToken();
        //cerr<<r<<" "<<cor<<endl;
        ouf.ensuref(r==cor, "Wrong Possibility");
        if(r=="No")continue;
        string ret[111];
        for(int i=0;i<mx;i++)
        {
            ret[i]=ouf.readToken();
            ans.readToken();
            ouf.ensuref(ret[i].size()==my, "Wrong length");
            for(int j=0;j<my;j++)ouf.ensuref(ret[i][j]=='+'||ret[i][j]=='-', "Invalid character");
        }
        for(int i=0;i<mx;i++)
        {
            string s;
            for(int j=0;j<my;j++)s.push_back(ret[i][j]);
            ouf.ensuref((a[i]=='1')==(isp(s)), "West-east condition fails");
        }
        for(int j=0;j<my;j++)
        {
            string s;
            for(int i=0;i<mx;i++)s.push_back(ret[i][j]);
            ouf.ensuref((b[j]=='1')==(isp(s)), "North-south condition fails");
        }
    }
}
