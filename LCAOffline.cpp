#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
class LCA {
    int numOfQuery;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<std::pair<int,int>>> query;
public :
    LCA (int n){
        numOfQuery = 0;
        adj.resize(n);
        query.resize(n);
    }
    void addEdge (int x,int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void addQuery(int x,int y,int z){
        query[x].push_back({y,z});
        query[y].push_back({x,z});
        numOfQuery++;
    }
    std::vector<int> Tarjan (int s){
        std::vector<int> ans(numOfQuery);
        std::vector<int> p(adj.size());
        std::vector<bool> vis(adj.size());
        std::iota(p.begin(),p.end(),0);
        auto find = [&](auto self,int x) -> int {
            return p[x] == x ? x : p[x] = self(self,p[x]);
        };
        auto dfs = [&](auto self,int u) -> void {
            vis[u] = 1;
            for(auto t : adj[u]){
                if(vis[t])continue;
                self(self,t);
                p[t] = u;
            }
            for(auto [x,y] : query[u]){
                if(vis[x]){
                    ans[y] = find(find,x);
                }
            }
        };
        dfs(dfs,s);
        return ans;
    }
};
int main(){
    int n;
    std::cin>>n;
    std::vector<std::vector<int>> adj(n);
    for(int i = 0;i < n - 1;i++){
        int x,y;
        std::cin>>x>>y;
        adj[x].push_back(y);
    }
    return 0;
}
