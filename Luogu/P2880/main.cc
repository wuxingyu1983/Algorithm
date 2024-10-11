// https://www.luogu.com.cn/problem/P2880

// Sparse Table : https://oi-wiki.org/ds/sparse-table/

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

int min_func(const int &t1, const int &t2) { return min(t1, t2); }

vector<int> cows;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    for (size_t i = 0; i < n; i++)
    {
        int h;
        cin >> h;

        cows.push_back(h);
    }
    
    // init ST
    SparseTable<int> stblMax(cows);
    SparseTable<int> stblMin(cows, min_func);

    for (size_t i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;

        int max = stblMax.query(a, b);
        int min = stblMin.query(a, b);

        cout << max - min << "\n";
    }

    return 0;
}
