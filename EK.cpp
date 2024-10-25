#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdint>
#include <array>
#include <cmath>
#include <queue>
#include <map>
class EK{
    std::vector<std::vector<long long>> g;
public : 
    EK(int n){
        g.assign(n,std::vector<long long>(n));
    }
    void addedge(int u,int v,long long w){
        g[u][v] += w;
    }
    long long maxflow(const int& s,const int& t){
        long long res = 0;
        int n = g.size();
        std::vector<int> pre(n,-1);
        auto bfs = [&]() -> int {
            // std::cout<<"XXX\n";
            pre.assign(n,-1);
            std::queue<int> q;
            pre[s] = s;
            q.push(s);
            // for(int i = 0;i < n;i++){
            //     for(int j = 0;j < n;j++){
            //         std::cout<<g[i][j]<<" \n"[j == n - 1];
            //     }
            // }
            while(q.size()){
                int p = q.front();
                q.pop();
                for(int i = 0 ;i < n;i++){
                    if(g[p][i] > 0 && pre[i] == -1){
                        pre[i] = p;
                        // std::cout<<"P:"<<p<<" "<<i<<" "<<g[p][i]<<"\n";
                        q.push(i);
                        if(i == t)return 1;
                    }
                }
            }
            // for(int i = 0;i < n;i++)std::cout<<pre[i]<<" \n"[i == n - 1];
            return 0;
        };
        int p;
        while(bfs()){
            long long mn = INT64_MAX / 2;
            p = t;
            while(p != s){
                mn = std::min(mn,g[pre[p]][p]);
                p = pre[p];
            }
            p = t;
            // std::cout<<"MIN:"<<mn<<"\n";
            while(p != s){
                g[pre[p]][p] -= mn;
                g[p][pre[p]] += mn;
                p = pre[p];
            }
            res += mn;
            // for(int i = 0;i < n;i++){
            //     for(int j = 0;j < n;j++){
            //         std::cout<<g[i][j]<<" \n"[j == n - 1];
            //     }
            // }
        }
        return res;
    }
};
void solve(){
    int n,m,s,t;
    std::cin>>n>>m>>s>>t;
    s--;
    t--;
    EK ek(n);
    for(int i = 0;i < m;i++){
        int u,v;
        long long w;
        std::cin>>u>>v>>w;
        u--;
        v--;
        ek.addedge(u,v,w);
    }
    std::cout<<ek.maxflow(s,t)<<"\n";
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    solve();
    return 0;
}
