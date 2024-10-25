//
//  main.cpp
//  segment tree
//
//  Created by William on 2023/11/5.
//
#include<iostream>
#include<algorithm>
#include<vector>
class Segment_Tree{
    struct Node{
        int l ,r;
        long long lazy = 0,sum = 0;
    };
    std::vector<Node> tr;
    void init(int u,int l,int r){
        tr[u].l = l;
        tr[u].r = r;
        if(l == r)return;
        int mid = l + r >> 1;
        init(u << 1,l,mid);
        init(u << 1 | 1,mid + 1,r);
    }
    void pushup(int u){
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }
    void pushdown(int u){
        tr[u << 1].lazy += tr[u].lazy;
        tr[u << 1].sum += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].lazy;
        tr[u << 1 | 1].lazy += tr[u].lazy;
        tr[u << 1 | 1].sum += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].lazy;
        tr[u].lazy = 0;
    }
public : 
    Segment_Tree(int n){
        tr.resize(n * 5);
        init(1,0,n);
    }
    void add(int l,int r,long long d,int u = 1){
        if(tr[u].l >= l && tr[u].r <= r){
            tr[u].sum += (tr[u].r - tr[u].l + 1) * d;
            tr[u].lazy += d;
        }
        else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if(l <= mid)add(l,r,d,u << 1);
            if(r > mid)add(l,r,d,u << 1 | 1);
            pushup(u);
        }
    }
    long long query(int l,int r,int u = 1){
        if(tr[u].l >= l && tr[u].r <= r){
            return tr[u].sum;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        long long res = 0;
        if(l <= mid)res += query(l,r,u << 1);
        if(r > mid)res += query(l,r,u << 1 | 1);
        return res;
    }
};
int main(){}