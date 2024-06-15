#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#pragma GCC optimize(2)
using namespace std;
long long int p[30000110];
void ma(string s)
{
    string t="$#";
    memset(p,0,sizeof(p));
    for(int i=0;i<s.length();i++)
    {
        t+=s[i];
        t+="#";
    }
    long long int mx=0;
    long long int id=0;
    long long int rc=0,rl=0;
    for(int i=1;i<t.length();i++)
    {
        if(mx>i)p[i]=min(p[2*id-i],mx-i);
        else p[i]=1;
        while(i-p[i]>=1&&i+p[i]<=t.length()&&t[i-p[i]]==t[i+p[i]])++p[i];
        if(mx<p[i]+i)
        {
            mx=p[i]+i;
            id=i;
        }
        if(rl<p[i])
        {
            rl=p[i];
            rc=i;
        }
    }
    printf("%lld\n",rl-1);
}
int main()
{
    string s;
    cin>>s;
    ma(s);
    return 0;
}
 
