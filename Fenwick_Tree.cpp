//
//  main.cpp
//  P3374 【模板】树状数组 1
//
//  Created by William on 2023/12/7.
//

#include<iostream>
#include<vector>
#include<algorithm>
std::vector<long long> sum;
int n,m;
long long lowbit(int x)
{
    return x & (-x);
}
int getsum(int u)
{
    int res = 0;
    while(u)
    {
        res += sum[u];
        u -= lowbit(u);
    }
    return res;
}
void add(int u,int k)
{
    while(u <= n)
    {
        sum[u] += k;
        u += lowbit(u);
    }
}
int main()
{
    std::cin>>n>>m;
    sum.resize(n + 1);
    for(int i = 1;i <= n;i++)
    {
        int a;
        std::cin>>a;
        add(i,a);
    }
//    for(int i = 1;i <= n;i++)
//    {
//        std::cout<<getsum(i)<<std::endl;
//    }
    while(m--)
    {
        int op,a,b;
        std::cin>>op>>a>>b;
        if(op == 1)
        {
            add(a,b);
        }
        else
        {
            std::cout<<getsum(b) - getsum(a - 1)<<std::endl;
        }
    }
    return 0;
}

