#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <array>
#include <cstdint>
class LCA{
    std::vector<std::vector<std::pair<int,long long>>> adj;
    std::vector<int> depth;
    std::vector<std::vector<int>> fa,mx;
public :
    void print_mx(){
        for(int i = 0;i < mx.size();i++){
            for(int j = 0;j < 3;j++){
                std::cout<<mx[i][j]<<" ";
            }
            std::cout<<"\n";
        }
    }
    LCA (int n){
        adj.resize(n);
        depth.resize(n);
        fa.resize(n,std::vector<int>(31));
        mx.resize(n,std::vector<int>(31));
    }
    void add(int x,int y,int z){
        adj[x].push_back({y,z});
        adj[y].push_back({x,z});
    }
    void init(int s){
        auto dfs = [&](auto self,int u,int v) -> void {
            if(v == -1)depth[u] = 1;
            else depth[u] = depth[v] + 1;
            fa[u][0] = v;
            for(int i = 1;i < 31;i++){
                fa[u][i] = fa[u][i - 1] == -1 ? -1 : fa[fa[u][i - 1]][i - 1];
                mx[u][i] = mx[u][i - 1];
                if(fa[u][i - 1] >= 0){
                    mx[u][i] = std::min(mx[u][i - 1],mx[fa[u][i - 1]][i - 1]);
                }
            }
            for(auto [x,y] : adj[u]){
                if(x == v)continue;
                mx[x][0] = y;
                self(self,x,u);
            }
        };
        dfs(dfs,s,-1);
    }
    auto query(int x,int y){
        int ans = INT32_MAX;
        if(depth[x] < depth[y])std::swap(x,y);
        for(int i = 30;i >= 0;i--){
            if(depth[x] - depth[y] >= (1 << i)){
                ans = std::min(ans,mx[x][i]);
                x = fa[x][i];
            }
        }
        if(x == y)return ans;
        for(int i = 30;i >= 0;i--){
            if(fa[x][i] == fa[y][i])continue;
            ans = std::min(ans,mx[x][i]);
            ans = std::min(ans,mx[y][i]);
            x = fa[x][i];
            y = fa[y][i];
        }
        return std::min({ans,mx[x][0],mx[y][0]});
    }
};
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::vector<std::array<int,3>> e;
    int n,m;
    std::cin>>n>>m;
    LCA lca(n);
    for(int i = 0;i < m;i++){
        int x,y,z;
        std::cin>>x>>y>>z;
        x--;y--;
        e.push_back({x,y,z});
    }
    sort(e.begin(),e.end(),[&](std::array<int,3> a,std::array<int,3> b){
        return a[2] > b[2];
    });
    std::vector<int> fa(n);
    std::iota(fa.begin(),fa.end(),0);
    auto find = [&](auto self,int x) -> int {
        return fa[x] == x ? x : fa[x] = self(self,fa[x]);
    };
    for(int i = 0;i < e.size();i++){
        int f1 = find(find,e[i][0]),f2 = find(find,e[i][1]);
        if(f1 == f2)continue;
        fa[f1] = f2;
        lca.add(e[i][0],e[i][1],e[i][2]);
    }
    std::vector<bool> vis(n);
    for(int i = 0;i < n;i++){
        int f = find(find,i);
        if(vis[f] == 0){
            lca.init(i);
            vis[f] = 1;
        }
    }
    int q;
    std::cin>>q;
    while(q--){
        int x,y;
        std::cin>>x>>y;
        x--;y--;
        if(find(find,x) != find(find,y)){
            std::cout<<-1<<"\n";
            continue;
        }
        std::cout<<lca.query(x,y)<<"\n";
    }
    return 0;
}
