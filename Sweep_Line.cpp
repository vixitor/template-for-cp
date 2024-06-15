//
//  main.cpp
//  sweep line
//
//  Created by William on 2023/11/8.
//

#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int l,r,cnt,len;
};
vector<Node> tr;
struct Segment
{
    int x,y1,y2,d;
};
vector<Segment> seg;
vector<int> ys;
bool cmp(Segment a,Segment b)
{
    return a.x < b.x;
}
void build(int u,int l,int r)
{
    tr[u] = {l,r,0,0};
    if(l == r)return;
    int mid = l + r >> 1;
    build(u * 2,l,mid);
    build(u * 2 + 1,mid + 1,r);
}
int find(int x)
{
    return lower_bound(ys.begin(),ys.end(),x) - ys.begin();
}
void pushup(int u)
{
    if(tr[u].cnt)
    {
        tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
    }
    else if(tr[u].l != tr[u].r)
    {
        tr[u].len = tr[u * 2].len + tr[u * 2 + 1].len;
    }
    else tr[u].len = 0;
}
void modify(int u,int l,int r,int d)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].cnt += d;
        pushup(u);
    }
    else
    {
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid)modify(u * 2,l,r,d);
        if(r > mid)modify(u * 2 + 1,l,r,d);
        pushup(u);
    }
}
int main()
{
    int n;
    cin>>n;
    tr.resize(n * 8);
    for(int i = 0;i < n;i++)
    {
        int x1,y1,y2,x2;
        cin>>x1>>y1>>x2>>y2;
        seg.push_back({x1,y1,y2,1});
        seg.push_back({x2,y1,y2,-1});
        ys.push_back(y1);
        ys.push_back(y2);
    }
    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    sort(seg.begin(),seg.end(),cmp);
    build(1,0,ys.size() - 2);
    long long ans = 0;
    for(int i = 0;i < seg.size();i++)
    {
        if(i)
        {
            ans += (long long)tr[1].len * (seg[i].x - seg[i - 1].x);
        }
        modify(1,find(seg[i].y1),find(seg[i].y2) - 1,seg[i].d);
    }
    cout<<ans<<endl;
    return 0;
}

