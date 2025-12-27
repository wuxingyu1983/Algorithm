// https://www.codechef.com/problems/DGTCNT

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <bitset>

using namespace std;

#pragma GCC target("popcnt")

long long sum[18];
long long C[19][19];    // C[n][m]

int init(int st, vector<int> &vec, int maxLen)
{
    int ret = 0;

    int needLen = 0;
    for (int n = 0; n < 10; n++)
    {
        if (st & (1 << n))
        {
            needLen += vec[n];
        }
    }

    if (18 < maxLen)
    {
        maxLen = 18;
    }

    if (maxLen < needLen)
    {
        return -1;
    }

    memset(sum, 0, sizeof(sum));

    for (int len = needLen; len <= 18; len++)
    {
        if (1 == len)
        {
            for (int n = 0; n < 10; n++)
            {
                if (st && (1 << n) && 1 == vec[n])
                {
                    // 排除 a = 0 的情况
                    sum[len - 1] ++;
                }
            }
        }
        else
        {
            // 最高位不能为0
            for (int n = 1; n < 10; n++)
            {
                vector<int> tmpVec(vec);
                if (st & (1 << n))
                {
                    if (0 == tmpVec[n])
                    {
                        // 数字n 不应该出现的
                        continue;
                    }
                    tmpVec[n] -= 1;
                }

                int remain = len - 1;
                long long tmpS = 1;

                for (int i = 0; i < 10; i++)
                {
                    if (st & (1 << n))
                    {
                        tmpS *= C[remain][tmpVec[n]];
                        remain -= tmpVec[n];
                    }
                }

                if (0 < remain)
                {
                    tmpS *= pow((10 - __builtin_popcount(st)), remain);
                }

                sum[len - 1] += tmpS;
            }
        }

        if (1 < len)
        {
            sum[len - 1] += sum[len - 2];
        }
    }
    
    return ret;
}

long long func(string strN, int st, vector<int> &vec)
{
    long long ret = 0;

    int needLen = 0;
    for (int n = 0; n < 10; n++)
    {
        if (st & (1 << n))
        {
            needLen += vec[n];
        }
    }

    int len = strN.length();
    if (len < needLen)
    {
        return 0;
    }

    vector<int> used(10, 0);
    for (int pos = 0; pos < len; pos++)
    {
        int d = strN.at(pos) - '0';
        int down = 0, up = d - 1;

        if (0 == pos)
        {
            down = 1;

            if (len > 1)
            {
                ret += sum[len - 2];
            }
        }

        if (len - 1 == pos)
        {
            up = d;
        }

        for (int n = down; n <= up; n++)
        {
            used[n] ++;
            if (len - 1 == pos)
            {
                int i;
                for (i = 0; i < 10; i++)
                {
                    if (st & (1 << i))
                    {
                        if (used[i] != vec[i])
                        {
                            break;
                        }
                    }
                }

                if (10 == i)
                {
                    ret ++;
                }
            }
            else
            {
                int remain = pos;
                long long tmpS = 1;
                for (int i = 0; i < 10; i++)
                {
                    if (st & (1 << i))
                    {
                        if (used[i] > vec[i])
                        {
                            remain = -1;
                            break;
                        }

                        // used[i] <= vec[i]
                        tmpS *= C[remain][vec[i] - used[i]];
                        remain -= vec[i] - used[i];
                        if (0 > remain)
                        {
                            break;
                        }
                    }
                }
                if (0 < remain)
                {
                    tmpS *= pow((10 - __builtin_popcount(st)), remain);
                    ret += tmpS;
                }
            }
            used[n] --;
        }

        // proc array used
        {
            used[d] ++;
            
            if (st & (1 << d))
            {
                if (used[d] > vec[d])
                {
                    return 0;
                }
            }
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    // init
    {
        for (size_t n = 0; n < 19; n++)
        {
            for (size_t m = 0; m <= n; m++)
            {
                if (0 == m || m == n)
                {
                    C[n][m] = 1;
                }
                else
                {
                    C[n][m] = C[n - 1][m] + C[n - 1][m - 1];
                }
            }
        }
    }

    for (size_t i = 0; i < t; i++)
    {
        long long l, r;
        cin >> l >> r;
        l--;

        vector<int> vecA;
        for (size_t n = 0; n < 10; n++)
        {
            int a;
            cin >> a;
            vecA.push_back(a);
        }

        string strL = to_string(l);
        string strR = to_string(r);
        long long cntL = 0, cntR = 0;
        for (int st = 1; st < 1024; st++)
        {
            if (0 == init(st, vecA, strR.length()))
            {
                if (1 & __builtin_popcount(st))
                {
                    cntL += func(strL, st, vecA);
                    cntR += func(strR, st, vecA);
                }
                else
                {
                    cntL -= func(strL, st, vecA);
                    cntR -= func(strR, st, vecA);
                }
            }
        }

        cout << (r - cntR) - (l - cntL) << "\n";
    }

    return 0;
}
