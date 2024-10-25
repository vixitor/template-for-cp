//
//  main.cpp
//  P3374 【模板】树状数组 1
//
//  Created by William on 2023/12/7.
//

// #include<iostream>
// #include<vector>
// #include<algorithm>
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};
// std::vector<long long> sum;
// int n,m;
// long long lowbit(int x)
// {
//     return x & (-x);
// }
// int getsum(int u)
// {
//     int res = 0;
//     while(u)
//     {
//         res += sum[u];
//         u -= lowbit(u);
//     }
//     return res;
// }
// void add(int u,int k)
// {
//     while(u <= n)
//     {
//         sum[u] += k;
//         u += lowbit(u);
//     }
// }
// int main()
// {
//     std::cin>>n>>m;
//     sum.resize(n + 1);
//     for(int i = 1;i <= n;i++)
//     {
//         int a;
//         std::cin>>a;
//         add(i,a);
//     }
// //    for(int i = 1;i <= n;i++)
// //    {
// //        std::cout<<getsum(i)<<std::endl;
// //    }
//     while(m--)
//     {
//         int op,a,b;
//         std::cin>>op>>a>>b;
//         if(op == 1)
//         {
//             add(a,b);
//         }
//         else
//         {
//             std::cout<<getsum(b) - getsum(a - 1)<<std::endl;
//         }
//     }
//     return 0;
// }

