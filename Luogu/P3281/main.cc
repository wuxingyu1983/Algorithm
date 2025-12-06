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
        int digit = vec[i];

        if (len - 1 == i)
        {
            ret += sum * digit;
            ret %= mod;

            seq *= b;
            seq %= mod;
            seq *= digit;
            seq %= mod;
            seq += digit * (digit - 1) / 2 + digit * (digit - 1) / 2;
            seq %= mod;

            sum += seq;
            sum %= mod;

            ret += sum;
            ret %= mod;
        }
        else
        {
            if (0 < digit)
            {

            }

            seq *= b;
            seq %= mod;
            seq += digit + digit;
            seq %= mod;

            sum += seq;
            sum %= mod;
        }
    }
    
    return ret;
}

int main()
{
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

        long long tmp = 0;
        for (size_t i = 1; i < maxLen; i++)
        {
            tmp += powers[i - 1] * (i + 1);
            tmp %= mod;

            seqs[i] = seqs[i - 1] * ((b * b) % mod) + tmp * ((s * (b - 1)) % mod) + s;
            seqs[i] %= mod;

            sums[i] = sums[i - 1] * b + seqs[i];
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
/*    
    long long retL = func(ls);
    long long retR = func(rs);
*/

    cout << sums[m - 1] << endl;

    return 0;
}
