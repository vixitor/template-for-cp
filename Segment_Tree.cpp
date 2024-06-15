//
//  main.cpp
//  segment tree
//
//  Created by William on 2023/11/5.
//
#include<iostream>
#include<algorithm>
#include<vector>
struct Segment_Tree
{
    struct Node
    {
        int l,r;
        long long sum,lazy;
    };
    std::vector<Node> tr;
    void build(int u,int l,int r)
    {
        tr[u] = {l,r,0,0};
        if(l == r)return;
        int mid = l + r >> 1;
        build(u << 1,l,mid);
        build(u << 1 | 1,mid + 1,r);
    }
    void pushup(int u)
    {
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }
    void init(int n)
    {
        tr.resize(n * 5);
        build(1,0,n - 1);
    }
    void insert(int u,int l,int r,long long d)
    {
        if(tr[u].l >= l && tr[u].r <= r)
        {
            tr[u].lazy += d;
            tr[u].sum += (tr[u].r - tr[u].l + 1) * d;
        }
        else
        {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if(l <= mid)insert(u << 1,l,r,d);
            if(r > mid)insert(u << 1 | 1,l,r,d);
            pushup(u);
        }
    }
    void pushdown(int u)
    {
        tr[u << 1].lazy += tr[u].lazy;
        tr[u << 1 | 1].lazy += tr[u].lazy;
        tr[u << 1].sum += tr[u].lazy * (tr[u << 1].r - tr[u << 1].l + 1);
        tr[u << 1 | 1].sum += tr[u].lazy * (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1);
        tr[u].lazy = 0;
    }
    long long query(int u,int l,int r)
    {
        if(tr[u].l >= l && tr[u].r <= r)
            return tr[u].sum;
        else
        {
            pushdown(u);
            long long res = 0;
            int mid = tr[u].l + tr[u].r >> 1;
            if(l <= mid)res += query(u << 1,l,r);
            if(r > mid)res += query(u << 1 | 1,l,r);
            return res;
        }
    }
};
int main()
{
    int n,m;
    std::cin>>n>>m;
    Segment_Tree a;
    a.init(n);
    for(int i = 0;i < n;i++)
    {
        int x;
        std::cin>>x;
        a.insert(1, i, i, x);
    }
    while(m--)
    {
        int op;
        std::cin>>op;
        if(op == 1)
        {
            int x,y;
            long long k;
            std::cin>>x>>y>>k;
            x--;
            y--;
            a.insert(1, x, y, k);
        }
        else
        {
            int x,y;
            std::cin>>x>>y;
            x--;
            y--;
            std::cout<<a.query(1, x, y)<<"\n";
        }
    }
    return 0;
}

