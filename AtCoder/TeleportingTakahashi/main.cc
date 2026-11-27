// https://atcoder.jp/contests/abc240/tasks/abc240_g

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
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <deque>
#include <bitset>

using namespace std;

const long long MOD = 998244353;
const int MAXN = 10000001;

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y, z;
    cin >> n >> x >> y >> z;

    // init
    init_factorial();

    

    return 0;
}
