#include<vector>
#include<algorithm>
#include<cstring>
#include<iostream>
class LCA{
    std::vector<std::vector<std::pair<int,long long>>> adj;
    std::vector<int> depth;
    std::vector<std::vector<int>> fa;
public :
    LCA (int n){
        adj.resize(n);
        depth.resize(n);
        fa.resize(n,std::vector<int>(31));
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
            }
            for(auto [x,y] : adj[u]){
                if(x == v)continue;
                self(self,x,u);
            }
        };
        dfs(dfs,s,-1);
    }
    auto query(int x,int y){
        if(depth[x] < depth[y])std::swap(x,y);
        for(int i = 30;i >= 0;i--){
            if(depth[x] - depth[y] >= (1 << i)){
                x = fa[x][i];
            }
        }
        if(x == y)return x;
        for(int i = 30;i >= 0;i--){
            if(fa[x][i] == fa[y][i])continue;
            x = fa[x][i];
            y = fa[y][i];
        }
        return fa[x][0];
    }
};
int main(){
    int n,m,s;
    std::cin>>n>>m>>s;
    LCA lca(n);
    for(int i = 0;i < n - 1;i++){
        int x,y;
        std::cin>>x>>y;
        x--;y--;
        lca.add(x,y,1);
    }
    s--;
    lca.init(s);
    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;y--;
        std::cout<<lca.query(x,y) + 1<<"\n";
    }
    return 0;
}
