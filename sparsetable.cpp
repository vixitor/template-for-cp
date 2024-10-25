#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdint>
#include <array>
#include <cmath>
#include <queue>
#include <map>
class sparseTable { 
    std::vector<int> a;
    std::vector<std::vector<int>> f;
    int flag = 0;
public : 
    sparseTable(){}
    sparseTable(std::vector<int> x) : a(x){}
    void add(int u){
        a.push_back(u);
        flag = 0;
    }
    void init(){
        int n = a.size();
        flag = 1;
        f.assign(a.size(),std::vector<int>(std::log2(a.size()) + 1));
        for(int j = 0;(1 << j) <= a.size();j++){
            for(int i = 0;i + (1 << j) - 1 < n;i++){
                if(j == 0){
                    f[i][j] = a[i];
                }
                else {
                    f[i][j] = std::max(f[i][j - 1],f[i + (1 << j - 1)][j - 1]);
                }
            }
        }
    }
    int query(int l,int r){
        if(flag == 0){
            init();
        }
        int t = std::log2(r - l + 1);
        return std::max(f[l][t],f[r - (1 << t) + 1][t]);
    }
};
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n,m;
    std::cin>>n>>m;
    sparseTable st;
    for(int i = 0;i < n;i++){
        int a;
        std::cin>>a;
        st.add(a);
    }
    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        std::cout<<st.query(x,y)<<"\n";
    }
    return 0;
}
