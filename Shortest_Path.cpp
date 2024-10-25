//
//  main.cpp
//  competitiveprogramming_xcode
//
//  Created by William on 2024/6/24.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstring>
#include <queue>
class Shortest_Path{
    std::vector<std::vector<std::pair<int,long long> > > adj;
public : 
    Shortest_Path(int n){
        adj.resize(n);
    }
    void addEdge(int u,int v,long long w){
        adj[u].push_back({v,w});
    }
    std::vector<long long> work(int s){
        std::vector<long long> dist(adj.size(),INT64_MAX);
        std::vector<bool> vis(adj.size());
        dist[s] = 0;
        vis[s] = 1;
        std::priority_queue<std::pair<long long,int>,std::vector<std::pair<long long,int>>,std::greater<std::pair<long long,int>>> q;
        q.push({0,s});
        while(q.size()){
            auto [x,y] = q.top();
            q.pop();
            vis[y] = 0;
            for(auto [v,w] : adj[y]){
                if(dist[v] > dist[y] + w){
                    dist[v] = dist[y] + w;
                    if(vis[v] == 0){
                        vis[v] = 1;
                        q.push({dist[v],v});
                    }
                }
            }
        }
        return dist;
    }
};
int main(){
    int n,m;
    std::cin>>n>>m;
    Shortest_Path sp(n);
    for(int i = 0;i < m;i++){
        int x,y,z;
        std::cin>>x>>y>>z;
        x--;y--;
        sp.addEdge(x,y,z);
    }
    auto res = sp.work(0);
    std::cout<<(res[n - 1] >= INT32_MAX ? -1 : res[n - 1])<<"\n";
    return 0;
}
