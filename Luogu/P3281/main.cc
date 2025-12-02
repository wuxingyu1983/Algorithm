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
long long seqCnt[maxLen];

long long func(vector<int> &vec)
{
    long long ret = 0;

    return ret;
}

int main()
{
    int b;
    cin >> b;

    // init
    {
        powers[0] = 1;
        for (size_t i = 1; i < maxLen; i++)
        {
            powers[i] = powers[i - 1] * b;
            powers[i] %= mod;
        }
        
        long long s = b * (b - 1) / 2;
        s %= mod;

        sums[0] = b * (b - 1) / 2;  // 0 + 1 + 2 + ... + b - 1
        sums[0] %= mod;
        seqs[0] = sums[0];
        seqCnt[0] = b;

        for (size_t i = 1; i < maxLen; i++)
        {
            seqCnt[i] = seqCnt[i - 1] * b + b;
            seqCnt[i] %= mod;

            seqs[i] = seqs[i - 1] * ((b * b) % mod) + seqCnt[i - 1] * s + s;
            seqs[i] %= mod;

            sums[i] = sums[i - 1] + seqs[i];
            sums[i] %= mod;
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

    return 0;
}
