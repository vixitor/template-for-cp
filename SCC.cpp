#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdint>
#include <map>
struct SCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;

    SCC() {}
    SCC(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }

    std::vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n,m;
    std::cin>>n>>m;
    SCC scc(n);
    for(int i = 0;i < m;i++){
        int x,y;
        std::cin>>x>>y;
        x--;
        y--;
        scc.addEdge(x,y);
    }
    auto ans = scc.work();
    std::vector<int> mrk(n);
    int size = 0;
    std::vector<std::vector<int>> res(n);
    for(int i = 0;i < ans.size();i++){
        res[ans[i]].push_back(i);
        size = std::max(size,ans[i]);
    }
    std::cout<<size + 1<<"\n";
    std::vector<int> vis(n);
    for(int i = 0;i < ans.size();i++){
        if(vis[ans[i]] == 0){
            for(int j = 0;j < res[ans[i]].size();j++)std::cout<<res[ans[i]][j] + 1<<" \n"[j == res[ans[i]].size() - 1];
            vis[ans[i]] = 1;
        }
    }

    return 0;
}
