// https://atcoder.jp/contests/dp/tasks/dp_y

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
#include <unordered_map>
#include <deque>

using namespace std;

const int MAXN = 200002;
const long long MOD = 1e9 + 7;

// 阶乘、乘法逆元
long long fact[MAXN];     // 阶乘数组 fact[i] = i! % MOD
long long inv_fact[MAXN]; // 阶乘逆元数组 inv_fact[i] = (i!)^-1 % MOD

// 快速幂计算 a^b % mod
long long quick_pow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void init_factorial() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    
    // 计算最大阶乘的逆元: (MAXN-1)! 的逆元
    inv_fact[MAXN - 1] = quick_pow(fact[MAXN - 1], MOD - 2, MOD);
    
    // 倒推计算其他阶乘的逆元: (i-1)!^-1 = i!^-1 * i
    for (int i = MAXN - 2; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

// O(1) 查询组合数
long long get_comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    // C(n, k) = n! * (k!)^-1 * ((n-k)!)^-1
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

class Square
{
public:
    int r, c;

    Square(int _r, int _c) : r(_r), c(_c) {}
    Square() : r(0), c(0) {}
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, n;
    cin >> h >> w >> n;

    vector<Square> squares(n);
    for (int i = 0; i < n; i++)
    {
        cin >> squares[i].r >> squares[i].c;
    }

    // init
    init_factorial();

    vector<vector<int>> can_reach(
        n,
        vector<int>()
    );

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && squares[i].r <= squares[j].r && squares[i].c <= squares[j].c)
            {
                can_reach[i].push_back(j);
            }
        }
    }

    long long ans = 0;


    cout << ans << "\n";

    return 0;
}
