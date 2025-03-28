// https://www.codechef.com/COOK126A/problems/ANDPREF?tab=statement

#include <cmath>
#include <cstdio>
#include <vector>
#include <deque>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits.h>

using namespace std;

const int maxSt = 1048576;

long long dp[21][maxSt];
long long cnt[maxSt];
int t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t;

    for (size_t iT = 0; iT < t; iT++)
    {
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0, sizeof(cnt));

        int n;
        cin >> n;

        for (size_t iN = 0; iN < n; iN++)
        {
            int tmp = 0;
            cin >> tmp;
            cnt[tmp] ++;
        }

        // init, 计算 mask 超集的个数
        for (int i = 0; i < 20; ++i)
        {
            for (int mask = 0; mask < maxSt; ++mask)
            {
                if (0 == (mask & (1 << i)))
                {
                    cnt[mask] += cnt[mask ^ (1 << i)];
                }
            }
        }

        long long ans = 0;

        // 初始状态
        for (long long st = 1; st < maxSt; st++)
        {
            if (cnt[st])
            {
                if (n == cnt[st] && dp[0][st] > ans)
                {
                    ans = cnt[st] * st;
                }
                else
                {
                    dp[0][st] = cnt[st] * st;
                }
            }
        }
        
        for (size_t i = 0; i < 20; i++)
        {
            for (long long st = 1; st < maxSt; st++)
            {
                if (dp[i][st])
                {
                    bool flag = false;

                    for (long long subSt = st - 1; subSt > 0; subSt--)
                    {
                        if (subSt == (subSt & st))
                        {
                            long long tmp = dp[i][st] + subSt * (cnt[subSt] - cnt[st]);
                            if (tmp > dp[i + 1][subSt])
                            {
                                if (n == cnt[subSt] && tmp > ans)
                                {
                                    ans = tmp;
                                }
                                else
                                {
                                    dp[i + 1][subSt] = tmp;
                                }
                            }
                        }
                    }
                   
                    if (false == flag)
                    {
                        if (dp[i][st] > ans)
                        {
                            ans = dp[i][st];
                        }
                    }
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
