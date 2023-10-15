// https://vjudge.net/problem/ZOJ-2125

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

#define LL long long
using namespace std;

int n=9,m=6,mask[15];
char mp[15][15];
set<LL>st[2];

LL encode(int pos)
{
    LL ret = 0;
    static int id[15]={},cnt,siz[15]={};
    memset(siz,0,sizeof siz),memset(id,-1,sizeof id),id[0]=0,id[1]=cnt=1;
    for(int i=pos;i>=0;i--)
        siz[id[mask[i]]==-1?id[mask[i]]=++cnt:id[mask[i]]]++;
    siz[1] = 20 , siz[0] = 20;
    for(int i=pos;i>=0;i--)
        ret=ret<<4|(siz[id[mask[i]]]==1?0:id[mask[i]]);
    if(pos == n-1) ret <<= 4;
    return ret;
}
void decode(LL ret){ for(int i=0;i<=n;i++) mask[i]=ret&15,ret>>=4; }

void dp(int i,int j,int now)
{
    for(set<LL>::iterator it=st[now^1].begin();it!=st[now^1].end();it++)
    {    decode(*it);
        
        bool flag = 0;
        for(int k=0;k<=n;k++)
            if(mask[k] == 1)
                flag = 1;
        if(!flag) continue;
        
        mp[i][j] = 'T';
        if(mp[i][j] == '.')
        {
            mask[i] = mask[i+1] = 0;
            st[now].insert(encode(i==n-1?n-1:n));
        }
        if(mp[i][j] == '-')
        {
            int u = mask[i] , v = mask[i+1];
            mask[i] = v , mask[i+1] = 0;
            st[now].insert(encode(i==n-1?n-1:n));
            
            mask[i+1] = u , mask[i] = 0;
            st[now].insert(encode(i==n-1?n-1:n));
        }
        if(mp[i][j] == '+')
        {
            int u = mask[i] , v = mask[i+1];
            if(u && v)
            {
                if(u == 1)
                {
                    for(int k=0;k<=n;k++)
                        if(mask[k]==v)
                            mask[k]=u;
                }
                else
                    for(int k=0;k<=n;k++)
                        if(mask[k]==u)
                            mask[k]=v;
            }
            else if(u || v)
                mask[i] = mask[i+1] = u + v;
            else
            {
                mask[i] = mask[i+1] = 13;
            }
            st[now].insert(encode(i==n-1?n-1:n));
        }
        if(mp[i][j] == 'L')
        {
            int u = mask[i] , v = mask[i+1];
            
            mask[i+1] = 0;
            st[now].insert(encode(i==n-1?n-1:n));
            
            mask[i] = 0 , mask[i+1] = v;
            st[now].insert(encode(i==n-1?n-1:n));
            
            mask[i] = mask[i+1] = 13;
            st[now].insert(encode(i==n-1?n-1:n));
            
            if(u && v)
            {
                if(u == 1)
                {
                    for(int k=0;k<=n;k++)
                        if(mask[k]==v)
                            mask[k]=u;
                }
                else
                    for(int k=0;k<=n;k++)
                        if(mask[k]==u)
                            mask[k]=v;
            }
            mask[i] = mask[i+1] = 0;
            st[now].insert(encode(i==n-1?n-1:n));
        }
        if(mp[i][j] == 'T')
        {
            int u = mask[i] , v = mask[i+1];
            
            if(u && v)
            {
                if(u == 1)
                {
                    for(int k=0;k<=n;k++)
                        if(mask[k]==v)
                            mask[k]=u;
                }
                else
                    for(int k=0;k<=n;k++)
                        if(mask[k]==u)
                            mask[k]=v;
                mask[i+1] = 0;
                st[now].insert(encode(i==n-1?n-1:n));
                
                decode(*it);
                if(u == 1)
                {
                    for(int k=0;k<=n;k++)
                        if(mask[k]==v)
                            mask[k]=u;
                }
                else
                    for(int k=0;k<=n;k++)
                        if(mask[k]==u)
                            mask[k]=v;
                mask[i] = 0;
                st[now].insert(encode(i==n-1?n-1:n));
                
                decode(*it);
                mask[i] = mask[i+1];
                st[now].insert(encode(i==n-1?n-1:n));
                mask[i] = u;
                
                mask[i+1] = mask[i];
                st[now].insert(encode(i==n-1?n-1:n));
                mask[i+1] = v;
            }
            else if(u || v)
            {
                mask[i] = u+v , mask[i+1] = 0;
                st[now].insert(encode(i==n-1?n-1:n));
                
                mask[i+1] = u+v , mask[i] = 0;
                st[now].insert(encode(i==n-1?n-1:n));
                
                mask[i] = u , mask[i+1] = v;
                if(mask[i]) mask[i+1] = mask[i];
                else mask[i+1] = mask[i] = 13;
                st[now].insert(encode(i==n-1?n-1:n));
                
                mask[i] = u , mask[i+1] = v;
                if(mask[i+1]) mask[i] = mask[i+1];
                else mask[i+1] = mask[i] = 13;
                st[now].insert(encode(i==n-1?n-1:n));
            }
            else
            {
                mask[i] = mask[i+1] = 13;
                st[now].insert(encode(i==n-1?n-1:n));
                
                mask[i] = u ,mask[i+1] = v;
                st[now].insert(encode(i==n-1?n-1:n));
            }
        }
    }
}

int main()
{
    int d;
    d = 1;
//    for(;~scanf("%d",&d);)
    {
//        for(int i=0;i<n;i++) scanf("%s",mp[i]);
        memset(mask,0,sizeof mask);
        mask[d] = 1;
        st[0].clear();
        st[0].insert(encode(n));
        int now = 1;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                st[now].clear(),dp(j,i,now),now^=1;
        int ans = 0;
        for(set<LL>::iterator it=st[now^1].begin();it!=st[now^1].end();it++)
        {
            decode(*it);
            int cnt = 0;
            for(int k=1;k<=n;k++)
                cnt += (mask[k] == 1);
            ans = max(ans , cnt);
        }
        printf("%d\n",ans);
    }
    
}
