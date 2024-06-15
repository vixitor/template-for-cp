#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
#include<random>
#include<cmath>
int main()
{
    static std::default_random_engine e;
    struct Node
    {
        int l = 0,r = 0;
        int size = 0,cnt = 0;
        int key,val;
    };
    int root,idx = 0;
    std::vector<Node> tr;
    auto new_node = [&](int key) -> int
    {
        idx++;
        tr[idx].key = key;
        tr[idx].cnt = 1;
        tr[idx].size = 1;
        tr[idx].val = e();
        return idx;
    };
    auto pushup = [&](int u) -> void
    {
        tr[u].size = tr[tr[u].l].size + tr[tr[u].r].size + tr[u].cnt;
    };
    auto zig = [&](int &p) -> void
    {
        int q = tr[p].l;
        tr[p].l = tr[q].r;
        tr[q].r = p;
        p = q;
        pushup(tr[p].r);
        pushup(p);
    };
    auto zag = [&](int &p) -> void
    {
        int q = tr[p].r;
        tr[p].r = tr[q].l;
        tr[q].l = p;
        p = q;
        pushup(tr[p].l);
        pushup(p);
    };
    auto build = [&]() -> void
    {
        new_node(INT32_MIN);
        new_node(INT32_MAX);
        root = 1;
        tr[1].r = 2;
        if(tr[1].val < tr[2].val)zag(root);
    };
    auto insert = [&](auto self,int &u,int key) -> void
    {
        if(u == 0)u = new_node(key);
        else if(tr[u].key == key)tr[u].cnt++;
        else if(tr[u].key > key)
        {
            self(self,tr[u].l,key);
            if(tr[tr[u].l].val > tr[u].val)zig(u);
        }
        else
        {
            self(self,tr[u].r,key);
            if(tr[tr[u].r].val > tr[u].val)zag(u);
        }
        pushup(u);
    };
    auto remove = [&](auto self,int &u,int key) -> void
    {
        if(u == 0)return;
        if(tr[u].key == key)
        {
            if(tr[u].cnt > 1)tr[u].cnt--;
            else if(tr[u].r || tr[u].l)
            {
                if(tr[u].r == 0 || tr[tr[u].l].val > tr[tr[u].r].val)
                {
                    zig(u);
                    self(self,tr[u].r,key);
                }
                else
                {
                    zag(u);
                    self(self,tr[u].l,key);
                }
            }
            else u = 0;
        }
        else
        {
            if(tr[u].key > key)self(self,tr[u].l,key);
            else self(self,tr[u].r,key);
        }
        pushup(u);
    };
    auto get_key_by_rank = [&](auto self,int u,int rank) -> int
    {
        if(u == 0)return INT32_MAX;
        if(tr[tr[u].l].size >= rank)return self(self,tr[u].l,rank);
        if(tr[tr[u].l].size + tr[u].cnt >= rank)return tr[u].key;
        return self(self,tr[u].r,rank - tr[tr[u].l].size - tr[u].cnt);
    };
    auto get_rank_by_key = [&](auto self,int u,int key) -> int
    {
        if(u == 0)return 1;
        if(tr[u].key == key)return tr[tr[u].l].size + 1;
        if(key > tr[u].key)return self(self,tr[u].r,key) + tr[tr[u].l].size + tr[u].cnt;
        return self(self,tr[u].l,key);
    };
    auto get_pre = [&](auto self,int u,int key) -> int
    {
        if(u == 0)return INT32_MIN;
        if(tr[u].key >= key)
            return self(self,tr[u].l,key);
        else
            return std::max(tr[u].key,self(self,tr[u].r,key));
    };
    auto get_suc = [&](auto self,int u,int key) -> int
    {
        if(u == 0)return INT32_MAX;
        if(tr[u].key <= key)
            return self(self,tr[u].r,key);
        else return std::min(tr[u].key,self(self,tr[u].l,key));
    };
    int n;
    std::cin>>n;
    
    tr.resize(n + 2);
    build();
//    std::cout<<tr[root].size<<std::endl;
//    insert(insert,root,10);
//    insert(insert,root,20);
//    insert(insert,root,30);
//    for(int i = 1;i <= 5;i++)
//        std::cout<<get_key_by_rank(get_key_by_rank, root, i)<<std::endl;
//
    for(int i = 0;i < n;i++)
    {
        int op,x;
        std::cin>>op>>x;
        if(op == 1)insert(insert,root,x);
        else if(op == 2)remove(remove,root,x);
        else if(op == 3)
            std::cout<<get_rank_by_key(get_rank_by_key,root,x) - 1<<std::endl;
        else if(op == 4)
            std::cout<<get_key_by_rank(get_key_by_rank,root,x + 1)<<std::endl;
        else if(op == 5)std::cout<<get_pre(get_pre,root,x)<<std::endl;
        else std::cout<<get_suc(get_suc,root,x)<<std::endl;
    }
    return 0;
}
