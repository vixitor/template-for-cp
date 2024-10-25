//区间修改为定值
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <map>
#include <numeric>
#include <array>
#include <cmath>
#include <set>
#include <queue>
#include <cstdint>
#include <queue>
#include <set>
#include<iostream>
#include<algorithm>
#include<vector>
struct segmentTree{
    struct node{
        int l,r;
        int sum,cover = INT32_MIN;
    };
    void build(int l,int r,int u = 1){
        tr[u].l = l;
        tr[u].r = r;
        if(l == r)return;
        int mid = l + r >> 1;
        build(l,mid,u << 1);
        build(mid + 1,r,u << 1 | 1);
    }
    std::vector<node> tr;
    segmentTree (int n){
        tr.resize(1 << (int)(std::ceil(std::log2(n)) + 1));
        build(0,n - 1);
    }
    void pushup(int u){
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }
    void pushdown(int u){
        if(tr[u].cover == INT32_MIN)return;
        tr[u << 1].cover = tr[u << 1 | 1].cover = tr[u].cover;
        tr[u << 1].sum = (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].cover;
        tr[u << 1 | 1].sum = (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].cover;
        tr[u].cover = INT32_MIN;
    }
    void modify(int l,int r,long long d,int u = 1){
        if(tr[u].l >= l && tr[u].r <= r){
            tr[u].cover = d;
            tr[u].sum = (tr[u].r - tr[u].l + 1) * d;
        }
        else {
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if(l <= mid){
                modify(l,r,d,u << 1);
            }
            if(r > mid){
                modify(l,r,d,u << 1 | 1);
            }
            pushup(u);
        }
    }
    long long query(int l,int r,int u = 1){
        if(tr[u].l >= l && tr[u].r <= r){
            return tr[u].sum;
        }
        else {
            long long res = 0;
            pushdown(u);
            int mid = tr[u].l + tr[u].r >> 1;
            if(l <= mid){
                res += query(l,r,u << 1);
            }
            if(r > mid){
                res += query(l,r,u << 1 | 1);
            }
            return res;
        }
    }
};