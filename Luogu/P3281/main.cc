// https://www.luogu.com.cn/problem/P3281

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

const int mod = 20130427;
const int maxLen = 100001;

long long powers[maxLen];   // 1, b, b*b, b*b*b ...
vector<int> ls, rs;

// 0 ...  [b-1][b-1][b-1] 全部的和
long long sums[maxLen];
long long seqs[maxLen];
long long sumb[maxLen];
long long seqb[maxLen];

long long dp[maxLen];

int b;

long long func(vector<int> &vec)
{
    long long ret = 0;

    int len = vec.size();
    long long sum = 0;
    long long seq = 0;
    long long s = b * (b - 1) / 2;
    s %= mod;

    for (size_t i = 0; i < len; i++)
    {
        int d = vec[i];

        if (0 < d)
        {
            // 处理(1)部分
            {
                int up = d - 1;
                if (len - 1 == i)
                {
                    up = d;
                }

                ret += (sum * (up + 1) * powers[len - 1 - i]) % mod;
                ret %= mod;
            }

            // 处理(2)部分
            {
                if (i < len - 1)
                {
                    int up = d;
                    if (0 == i)
                    {
                        up = d - 1;
                    }

                    ret += sumb[len - 1 - i - 1] * up;
                    ret %= mod;
                }
            }

            // 处理跨(1)和(2)部分
            {
                int down = 0, up = d - 1;
                if (0 == i)
                {
                    down = 1;
                }
                if (len - 1 == i)
                {
                    up = d;
                }

                long long SEQ = seq * b * (up - down + 1) + (i + 1) * ((up - down + 1) * (up + down) / 2);
                SEQ %= mod;
                SEQ *= powers[len - 1 - i];
                SEQ %= mod;

                ret += (SEQ * dp[len - 1 - i]) % mod;
                ret %= mod;
            }
        }

        if (0 == i)
        {
            seq = d;
        }
        else
        {
            seq = seq * b + 2 * d;
            seq %= mod;
        }
        sum += seq;
        sum %= mod;
    }
    
    return ret;
}

int main()
{
    cin >> b;

    // init
    {
        powers[0] = 1;
        dp[0] = 1;
        for (size_t i = 1; i < maxLen; i++)
        {
            powers[i] = powers[i - 1] * b;
            powers[i] %= mod;

            dp[i] = dp[i - 1] + ((powers[i] * (powers[i] - 1) / 2) % mod);
        }
        
        long long s = b * (b - 1) / 2;
        s %= mod;

        sums[0] = b * (b - 1) / 2;  // 0 + 1 + 2 + ... + b - 1
        sums[0] %= mod;
        seqs[0] = sums[0];

        sumb[0] = sums[0];
        seqb[0] = seqs[0];

        long long tmp = 0;
        for (size_t i = 1; i < maxLen; i++)
        {
            tmp += powers[i - 1] * (i + 1);
            tmp %= mod;

            seqs[i] = seqs[i - 1] * ((b * b) % mod) + tmp * ((s * (b - 1)) % mod) + s;
            seqs[i] %= mod;
            seqb[i] = seqb[i - 1] * ((b * b) % mod) + (((i + 1) * powers[i]) % mod) * s;
            seqb[i] %= mod;

            sums[i] = sums[i - 1] * b + seqs[i];
            sums[i] %= mod;
            sumb[i] = sumb[i - 1] * b + seqb[i];
            sumb[i] %= mod;
        }
    }

    int n;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        int digit;
        cin >> digit;

        ls.push_back(digit);
    }

    int m;
    cin >> m;
    for (size_t i = 0; i < m; i++)
    {
        int digit;
        cin >> digit;

        rs.push_back(digit);
    }
    
    long long retL = func(ls);
    long long retR = func(rs);

    long long ans = 0;
//    cout << sums[m - 1] << endl;
    cout << ans << endl;

    return 0;
}
