// https://codeforces.com/contest/1077/problem/F1
// https://codeforces.com/contest/1077/problem/F2

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

// segment tree 效率还是太低
// 该应用场景 单调队列 即可

class DQItem
{
public:
    int pos;
    long long val;
    DQItem(int _pos, long long _val) : pos(_pos), val(_val) {}
};

void insertMQ(deque<DQItem> &mq, int pos, long long val, int k)
{
    if (0 > val)
    {
        return;
    }

    if (mq.empty())
    {
        mq.push_front(DQItem(pos, val));
    }
    else if (mq.front().val <= val)
    {
        mq.clear();
        mq.push_front(DQItem(pos, val));
    }
    else if (mq.back().val > val)
    {
        mq.push_back(DQItem(pos, val));
    }
    else
    {
        while (!mq.empty() && mq.back().val <= val)
        {
            mq.pop_back();
        }
        mq.push_back(DQItem(pos, val));
    }
}

long long getMaxMQ(deque<DQItem> &mq, int pos, int k)
{
    long long ret = -1;

    while (!mq.empty() && pos - mq.front().pos > k)
    {
        mq.pop_front();
    }

    if (!mq.empty())
    {
        ret = mq.front().val;
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, x;
    cin >> n >> k >> x;

    vector<long long> a(n + 1, 0);
    long long sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    long long ans = -1;
    if (n == x)
    {
        ans = sum;
    }
    else
    {
        /*
                bool bTest = false;
                {
                    if (5000 == n && 2500 == k && 2500 == x)
                    {
                        x = 1000;
                        bTest = true;
                    }
                }
        */
        deque<DQItem> mq;
        long long dp[2][5001];

        // init
        // j = 1
        memset(dp[0], -1, sizeof(dp[0]));
        for (int i = 1; i <= min(n, k); i++)
        {
            dp[0][i] = a[i];
            if (x == 1 && i + k > n)
            {
                ans = max(ans, a[i]);
            }
        }
        int act = 1;

        for (int j = 2; j <= x; j++)
        {
            memset(dp[act], -1, sizeof(dp[act]));
            mq.clear();

            for (int i = 1; i < j; i++)
            {
                insertMQ(mq, i, dp[1 - act][i], k);
            }

            for (int i = j; i <= n; i++)
            {
                long long max_val = getMaxMQ(mq, i, k);
                if (max_val != -1)
                {
                    dp[act][i] = max_val + a[i];

                    if (j == x && i + k > n)
                    {
                        ans = max(ans, max_val + a[i]);
                    }

                    insertMQ(mq, i, dp[1 - act][i], k);
                }
                else
                {
                    break;
                }
            }

            act = 1 - act;
        }
    }

    cout << ans << "\n";

    return 0;
}
