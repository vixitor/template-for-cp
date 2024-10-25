class Tarjan{
public :
    std::vector<std::vector<int>> adj;
    Tarjan(int n){
        adj.resize(n);
    }
    void addEdge(int x,int y){
        adj[x].push_back(y);
    }
    std::vector<std::vector<int>> scc(){
        int n = adj.size();
        std::vector<std::vector<int>> res;
        std::vector<int> dfn(n),low(n);
        std::vector<bool> vis(n);
        int time = 0;
        std::stack<int> stk;
        auto tarjan = [&](auto self,int u) -> void {
            dfn[u] = low[u] = ++time;
            vis[u] = 1;
            stk.push(u);
            for(auto t : adj[u]){
                if(!dfn[t]){
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
                    vis[stk.top()] = 0;
                    stk.pop();
                }
                res.back().push_back(stk.top());
                vis[stk.top()] = 0;
                stk.pop();
            }
        };
        for(int i = 0;i < adj.size();i++)if(!dfn[i])tarjan(tarjan,i);
        return res;
    }
    std::vector<bool> cut_Vertices(){
        int n = adj.size();
        std::vector<bool> flag(n);
        std::vector<int> dfn(n),low(n);
        std::vector<bool> vis(n);
        int time = 0;
        auto tarjan = [&](auto self,int u,int v) -> void {
            vis[u] = 1;
            dfn[u] = low[u] = ++time;
            int child = 0;
            for(auto t : adj[u]){
                if(vis[t] == 0){
                    child++;
                    self(self,t,u);
                    low[u] = std::min(low[u],low[t]);
                    if(u != v && low[t] >= dfn[u] && flag[u] == 0){
                        flag[u] = 1;
                    }
                }
                else if(t != v)low[u] = std::min(low[u],dfn[t]);//must be dfn[t]
            }
            if(v == u && child >= 2 && flag[u] == 0){
                flag[u] = 1;
            }
        };
        for(int i = 0;i < n;i++){
            if(vis[i] == 0)tarjan(tarjan,i,i);
        }
        return flag;
    }
    std::pair<std::vector<bool>,std::vector<int>> cut_Edges(){
        int n = adj.size();
        std::vector<int> dfn(n),low(n);
        int timestamp = 0;
        std::vector<int> fa(n);
        std::vector<bool> res(n);
        auto tarjan = [&](auto self,int u,int v) -> void {
            fa[u] = v;
            dfn[u] = low[u] = ++timestamp;
            for(auto t : adj[u]){
                if(dfn[t] == 0) {
                    self(self, t, u);
                    low[u] = std::min(low[u], low[t]);
                    if (low[t] > dfn[u]) {
                        res[t] = 1;
                    }
                }
                else if(dfn[t] < dfn[u] && t != v){
                    low[u] = std::min(low[u],dfn[t]);
                }
            }
        };
        tarjan(tarjan,0,-1);
        return {res,fa};
    }
};