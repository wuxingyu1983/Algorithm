// https://atcoder.jp/contests/arc136/tasks/arc136_d

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
#include <functional>

using namespace std;

int dp[1000010];

inline int getIndex(int x1, int x2, int x3, int x4, int x5, int x6)
{
    return x1 + 10 * x2 + 100 * x3 + 1000 * x4 + 10000 * x5 + 100000 * x6;
}

int main()
{
    int n;
    cin >> n;

    vector<int> a;
    for (size_t i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        a.push_back(tmp);

        dp[tmp] ++;
    }

    for (size_t x1 = 1; x1 <= 9; x1++)
        for (size_t x2 = 0; x2 <= 9; x2++)
            for (size_t x3 = 0; x3 <= 9; x3++)
                for (size_t x4 = 0; x4 <= 9; x4++)
                    for (size_t x5 = 0; x5 <= 9; x5++)
                        for (size_t x6 = 0; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1 - 1, x2, x3, x4, x5, x6)];
                        }
    
    for (size_t x1 = 0; x1 <= 9; x1++)
        for (size_t x2 = 1; x2 <= 9; x2++)
            for (size_t x3 = 0; x3 <= 9; x3++)
                for (size_t x4 = 0; x4 <= 9; x4++)
                    for (size_t x5 = 0; x5 <= 9; x5++)
                        for (size_t x6 = 0; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1, x2 - 1, x3, x4, x5, x6)];
                        }
 
    for (size_t x1 = 0; x1 <= 9; x1++)
        for (size_t x2 = 0; x2 <= 9; x2++)
            for (size_t x3 = 1; x3 <= 9; x3++)
                for (size_t x4 = 0; x4 <= 9; x4++)
                    for (size_t x5 = 0; x5 <= 9; x5++)
                        for (size_t x6 = 0; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1, x2, x3 - 1, x4, x5, x6)];
                        }
 
    for (size_t x1 = 0; x1 <= 9; x1++)
        for (size_t x2 = 0; x2 <= 9; x2++)
            for (size_t x3 = 0; x3 <= 9; x3++)
                for (size_t x4 = 1; x4 <= 9; x4++)
                    for (size_t x5 = 0; x5 <= 9; x5++)
                        for (size_t x6 = 0; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1, x2, x3, x4 - 1, x5, x6)];
                        }
 
    for (size_t x1 = 0; x1 <= 9; x1++)
        for (size_t x2 = 0; x2 <= 9; x2++)
            for (size_t x3 = 0; x3 <= 9; x3++)
                for (size_t x4 = 0; x4 <= 9; x4++)
                    for (size_t x5 = 1; x5 <= 9; x5++)
                        for (size_t x6 = 0; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1, x2, x3, x4, x5 - 1, x6)];
                        }
 
    for (size_t x1 = 0; x1 <= 9; x1++)
        for (size_t x2 = 0; x2 <= 9; x2++)
            for (size_t x3 = 0; x3 <= 9; x3++)
                for (size_t x4 = 0; x4 <= 9; x4++)
                    for (size_t x5 = 0; x5 <= 9; x5++)
                        for (size_t x6 = 1; x6 <= 9; x6++)
                        {
                            dp[getIndex(x1, x2, x3, x4, x5, x6)] += dp[getIndex(x1, x2, x3, x4, x5, x6 - 1)];
                        }

    long long ans = 0;

    for (size_t i = 0; i < n; i++)
    {
        int tmp = a[i];
        bool flag = true;

        int x1, x2, x3, x4, x5, x6;
        x1 = tmp % 10;
        if (x1 >= 5)
            flag = false;
        tmp /= 10;
        x2 = tmp % 10;
        if (x2 >= 5)
            flag = false;
        tmp /= 10;
        x3 = tmp % 10;
        if (x3 >= 5)
            flag = false;
        tmp /= 10;
        x4 = tmp % 10;
        if (x4 >= 5)
            flag = false;
        tmp /= 10;
        x5 = tmp % 10;
        if (x5 >= 5)
            flag = false;
        tmp /= 10;
        x6 = tmp % 10;
        if (x6 >= 5)
            flag = false;

        ans += dp[getIndex(9 - x1, 9 - x2, 9 - x3, 9 - x4, 9 - x5, 9 - x6)];
        
        // 排除自己
        if (flag)
            ans --;
    }

    cout << ans / 2 << endl; 

    return 0;
}
