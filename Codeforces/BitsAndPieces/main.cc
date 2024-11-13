// https://codeforces.com/problemset/problem/1208/F

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
#include <functional>

using namespace std;

#define MAX_M 21
#define MAX_2M 2097151
#define MAX_N 1000000

int max1st[MAX_2M + 1];     // 最大的 index
int max2nd[MAX_2M + 1];     // 第二大的 index
int min1st[MAX_2M + 1];     // 最小的 index

int a[MAX_N];
int indexs[MAX_N];

template <typename T>
class SparseTable
{
    using VT = vector<T>;
    using VVT = vector<VT>;
    using func_type = function<T(const T &, const T &)>;

    VVT ST;

    static T default_func(const T &t1, const T &t2) { return max(t1, t2); }

    func_type op;

public:
    SparseTable(const vector<T> &v, func_type _func = default_func)
    {
        op = _func;
        int len = v.size(), l1 = ceil(log2(len)) + 1;
        ST.assign(len, VT(l1, 0));
        for (int i = 0; i < len; ++i)
        {
            ST[i][0] = v[i];
        }
        for (int j = 1; j < l1; ++j)
        {
            int pj = (1 << (j - 1));
            for (int i = 0; i + pj < len; ++i)
            {
                ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r)
    {
        int lt = r - l + 1;
        int q = floor(log2(lt));
        return op(ST[l][q], ST[r - (1 << q) + 1][q]);
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // init
    memset(max1st, -1 ,sizeof(max1st));
    memset(max2nd, -1 ,sizeof(max2nd));
    memset(min1st, -1 ,sizeof(min1st));

    for (size_t i = 0; i < n; i++)
    {
        if (0 > min1st[a[i]])
        {
            min1st[a[i]] = i;
        }
    }
    
    for (int i = n - 1; i >= 0; i--)
    {
        if (0 > max1st[a[i]])
        {
            max1st[a[i]] = i;
        }
        else if (0 > max2nd[a[i]])
        {
            max2nd[a[i]] = i;
        }
    }
    
    // st 的超集的最大、第二大的index
    for (int i = 0; i < MAX_M; ++i)
    {
        for (int st = 0; st <= MAX_2M; ++st)
        {
            if (0 == (st & (1 << i)))
            {
                int othSt = st ^ (1 << i);

                if (max1st[st] >= max1st[othSt])
                {
                    if (max2nd[st] < max1st[othSt])
                    {
                        max2nd[st] = max1st[othSt];
                    }
                }
                else
                {
                    // max1st[st] < max1st[othSt]
                    if (max1st[st] >= max2nd[othSt])
                    {
                        max2nd[st] = max1st[st];
                    }
                    else
                    {
                        max2nd[st] = max2nd[othSt];
                    }

                    max1st[st] = max1st[othSt];
                }
            }
        }
    }

    // 只要处理 min1st 和 max2nd 这两个数组
    memset(indexs, -1, sizeof(indexs));

    for (int st = 0; st <= MAX_2M; ++st)
    {
        if (0 <= max2nd[st])
        {
            indexs[max2nd[st]] = st;
        }
    }

    

    int ans = -1;
/*
    for (int st = 0; st <= MAX_2M; ++st)
    {
        if (0 <= min1st[st] && 0 <= max2nd[st])
        {
            if (min1st[st] < max2nd[st])
            {
                ans = MAX_2M - st;
                break;
            }
        }
    }
*/
    cout << ans << endl;

    return 0;
}
