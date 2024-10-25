#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstdint>
#include <array>
#include <cmath>
#include <queue>
#include <map>
class HLPP { 
    std::vector<std::vector<long long>> g;
    std::vector<int> h;
    std::function<bool(int ,int)> cmp;
    std::priority_queue<int,std::vector<int>,decltype(cmp)> heap;
    std::vector<long long> e;
    int n;
    int bfs(int s,int t){
        h[t] = 0;
        std::vector<bool> vis(n);
        vis[t] = 1;
        std::queue<int> q;
        q.push(t);
        while(q.size()){
            int p = q.front();
            q.pop();
            for(int i = 0;i < n;i++){
                if(g[i][p] > 0 && vis[i] == 0){
                    vis[i] = 1;
                    h[i] = h[p] + 1;
                    q.push(i);
                }
            }
        }
        return h[s] != INT32_MAX;
    }
public : 
    HLPP (int n){
        
        g.assign(n,std::vector<long long>(n));
        h.resize(n);
        e.resize(n);
        this -> n = n;
        cmp = [&](int a,int b){
            return h[a] < h[b];
        };
        heap = std::priority_queue<int,std::vector<int>,decltype(cmp)>(cmp);
    }
    long long work(int s,int t){
        std::vector<bool> vis(n);
        auto relabel = [&](int u){
            h[u] = INT32_MAX;
            for(int i = 0;i < n;i++){
                if(g[u][i] > 0 && h[i] + 1 < h[u]){
                    h[u] = h[i] + 1;
                }
            }
        };
        auto push = [&](int u){
            for(int i = 0;i < n;i++){
                if(g[u][i] && h[i] + 1 == h[u]){
                    int d = std::min(e[u],g[u][i]);
                    g[u][i] -= d;
                    g[i][u] += d;
                    e[u] -= d;
                    e[i] += d;
                    if(i != s && i != t && vis[i] == 0){
                        vis[i] = 1;
                        heap.push(i);
                    }
                    if(e[u] == 0){
                        break;
                    }
                }
            }
        };
        int n = g.size();
        std::vector<int> h(n,INT32_MAX);
        
        if(bfs(s,t) == 0){
            return 0;
        }
        std::vector<int> gap(n + 1);
        h[s] = n;
        for(int i = 0;i < n;i++){
            gap[h[i]]++;
        }
        
        for(int i = 0;i < n;i++){
            if(g[s][i]){
                g[i][s] += g[s][i];
                e[i] += g[s][i];
                e[s] -= g[s][i];
                g[s][i] = 0;
                if(i != s && i != t && vis[i] == 0){
                    vis[i] = 1;
                    heap.push(i);
                }
            }
        }
        while(heap.size()){
            int u = heap.top();
            heap.pop();
            push(u);
            if(e[u]){
                gap[h[u]]--;
                
            }
        }
    }
};
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    return 0;
}
