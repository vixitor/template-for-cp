#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdint>
class MinimumSpinningTree{
    std::vector<std::vector<std::pair<int,long long>>> adj;
public :
    MinimumSpinningTree (int n) {
        adj.resize(n);
    }
    void addEdge(int u,int v,long long w){
        adj[u].push_back({v,w});
    }
    long long work(){
        long long res = 0;
        std::vector<long long> dist(adj.size(),INT64_MAX);
        std::vector<bool> vis(adj.size());
        dist[0] = 0;
        int cnt = 0;
        while(cnt < adj.size()){
            int cur = -1;
            for(int i = 0;i < adj.size();i++){
                if(vis[i])continue;
                if(cur == -1 || dist[cur] > dist[i])cur = i;
            }
            if(dist[cur] == INT64_MAX)return -1;
            res += dist[cur];
            vis[cur] = 1;
            cnt++;
                for(auto [x,y] : adj[cur]){
                    if(dist[x] > y){
                        dist[x] = y;
                    }
                }
        }
        return res;
    }
};
int main(){
    int n,m;
    std::cin>>n>>m;
    MinimumSpinningTree tr(n);
    for(int i = 0;i < m;i++){
        int x,y;
        long long z;
        std::cin>>x>>y>>z;
        x--;y--;
        tr.addEdge(x,y,z);
        tr.addEdge(y,x,z);
    }
    long long t = tr.work();
    if(t == -1)std::cout<<"orz\n";
    else std::cout<<t<<"\n";
    return 0;
}
