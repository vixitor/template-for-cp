#include<vector>
#include<algorithm>
#include<cstring>
#include<iostream>
int main()
{
    int n,m,root;
    std::cin>>n>>m>>root;
    root--;
    std::vector<std::vector<int>> adj(n);
    for(int i = 0;i < n - 1;i++)
    {
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    std::vector fa(n,std::vector<int>(31));
    std::vector<int> depth(n);
    auto dfs = [&](auto self,int u,int v) -> void
    {
        depth[u] = v == -1 ? 0 : depth[v] + 1;
        fa[u][0] = v;
        for(int i = 1;i < 31;i++)
        {
            fa[u][i] = fa[u][i - 1] == -1 ? -1 : fa[fa[u][i - 1]][i - 1];
        }
        for(int i : adj[u])
        {
            if(i == v)continue;
            self(self,i,u);
        }
    };
    dfs(dfs,root,-1);
    auto lca = [&](int u,int v)
    {
        if(depth[u] < depth[v])std::swap(u,v);
        for(int i = 30;i >= 0;i--)
        {
            if(depth[u] - depth[v] >= (1 << i))u = fa[u][i];
        }
        if(u == v)return u;
        for(int i = 30;i >= 0;i--)
        {
            if(fa[u][i] == fa[v][i])continue;
            u = fa[u][i];
            v = fa[v][i];
        }
        return fa[u][0];
    };
    while(m--)
    {
        int x,y;
        std::cin>>x>>y;
        x--;y--;
        std::cout<<lca(x,y) + 1<<"\n";
    }
    return 0;
}
