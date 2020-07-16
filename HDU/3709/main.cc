#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

#define LL long long
LL dp[20][20][2000];
int dis[20];

LL dfs(int len, int pos, int sum, bool flag)
{
    if(len < 0)
        return sum?0:1;
    if(sum < 0)
        return 0;
    if(!flag && dp[len][pos][sum] != -1)
        return dp[len][pos][sum];
    LL ans = 0;
    int end = flag?dis[len]:9;
    for(int i=0; i<=end; i++)
    {
        ans += dfs(len-1, pos, sum+(len-pos)*i, flag&&i==end);
    }

    if(!flag)
        dp[len][pos][sum] = ans;
    return ans;
}

LL solve(LL n)
{
    int len = 0;
    while(n)
    {
        dis[len++] = n%10;
        n /= 10;
    }
    LL ans = 0;
    for(int i=0; i<len; i++)
        ans += dfs(len-1, i, 0, 1);
    return ans - (len-1);
}

int main()
{
    int T;
    scanf("%d", &T);
    memset(dp, -1, sizeof(dp));
    while(T--)
    {
        LL l, r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(r) - solve(l-1));
    }
    return 0;
}
