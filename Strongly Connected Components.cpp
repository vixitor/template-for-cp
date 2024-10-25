#include <iostream>
#include <stack>
#include <vector>
class SCC{
    std::vector<std::vector<int>> adj;
public : 
    SCC(int n){
        adj.resize(n);
    }
    void addEdge(int x,int y){
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    std::vector<std::vector<int>> work(){
        std::vector<std::vector<int>> res;
        int n = adj.size();
        std::vector<int> dfn(n),low(n);
        std::vector<bool> vis(n);
        int time = 0;
        std::stack<int> stk;
        auto tarjan = [&](auto self,int u) -> void {
            dfn[u] = low[u] = ++time;
            vis[u] = 1;
            stk.push(u);
            for(auto t : adj[u]){
                if(dfn[t]){
                    self(self,t);
                    low[u] = std::min(low[u],low[t]);
                }
                else if(vis[t]){
                    low[u] = std::min(low[u],low[t]);
                }
            }
            if(dfn[u] == low[u]){
                res.push_back({});
                while(stk.top() != u){
                    res.back().push_back(stk.top());
                    stk.pop();
                }
                res.back().push_back(stk.top());
                stk.pop();
            }
        };
        tarjan(tarjan,0);
        std::cout<<n<<"\n";
        for(int i = 0;i < n;i++)std::cout<<dfn[i]<<" \n"[i == n - 1];
        return res;
    }
};
int main(){
    int n,m;
    std::cin>>n>>m;
    std::vector<int> a(n);
    SCC scc(n);
    for(int i = 0;i < n;i++)std::cin>>a[i];
    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;y--;
        scc.addEdge(x,y);
    }
    auto res = scc.work();
    for(auto x : res){
        for(int i = 0;i < x.size();i++){
            std::cout<<x[i]<<" \n"[i == x.size() - 1];
        }
    }
    return 0;
}