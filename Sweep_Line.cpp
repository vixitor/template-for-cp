//
//  main.cpp
//  sweep line
//
//  Created by William on 2023/11/8.
//

#include <iostream>
#include <algorithm>
#include <vector>
struct Sweep_Line {
public : 
    struct Node {
        int l,r;
        long long sum;
        int len;
    };
    std::vector<Node> tr;
    std::vector<int> X;
    struct line{
        int x1,x2,y,mark;
    };
    std::vector<line> lines;
    void addLine(int x1,int y1,int x2,int y2){
        X.push_back(x1);
        X.push_back(x2);
        if(y1 > y2)std::swap(y1,y2);
        lines.push_back({x1,x2,y1,1});
        lines.push_back({x1,x2,y2,-1});
    }
    void build(int u,int l,int r){
        tr[u].l = l,tr[u].r = r;
        tr[u].sum = tr[u].len = 0;
        if(l == r)return;
        int mid = l + r >> 1;
        build(u << 1,l,mid);
        build(u << 1 | 1,mid + 1,r);
    }
    void pushup(int u){
        if(tr[u].sum){
            tr[u].len = X[tr[u].r + 1] - X[tr[u].l];
        }
        else {
            tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
        }
    }
    void edit(int u,int l,int r,int mark){
        if(X[tr[u].l] >= r || X[tr[u].r + 1] <= l)return;
        if(X[tr[u].l] >= l && X[tr[u].r + 1] <= r){
            tr[u].sum += mark;
            pushup(u);
            return;
        }
        edit(u << 1,l,r,mark);
        edit(u << 1 | 1,l,r,mark);
        pushup(u);
    }
    long long work(){
        sort(X.begin(),X.end());
        int tot = std::unique(X.begin(),X.end()) - X.begin() - 1;
        tr.resize(tot * 8);// * 8
        build(1,0,tot - 1);
        sort(lines.begin(),lines.end(),[](line a,line b){
            return a.y < b.y;
        });
        long long res = 0;
        for(int i = 0;i < (int)lines.size() - 1;i++){
            edit(1,lines[i].x1,lines[i].x2,lines[i].mark);
            res += 1LL * tr[1].len * (lines[i + 1].y - lines[i].y);
        }
        return res;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin>>n;
    Sweep_Line sl;
    for(int i = 0;i < n;i++){
        int x1,x2,y1,y2;
        std::cin>>x1>>y1>>x2>>y2;
        sl.addLine(x1,y1,x2,y2);
    }
    std::cout<<sl.work()<<"\n";
    return 0;
}

