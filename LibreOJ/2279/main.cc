// https://loj.ac/p/2279
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

vector<int> rs;
vector<int> ys;

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
/*
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
*/
    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int y, r;
        cin >> y >> r;

        ys.push_back(y);
        rs.push_back(r);
    }

    // init ST
    SparseTable<int> stbl(rs);

    int m;
    cin >> m;

    for (size_t i = 0; i < m; i++)
    {
        int y, x;
        cin >> y >> x;

        vector<int>::iterator itY = lower_bound(ys.begin(), ys.end(), y);
        int idxY = -1;
        if (itY != ys.end())
        {
            idxY = itY - ys.begin();
        }

        vector<int>::iterator itX = lower_bound(ys.begin(), ys.end(), x);
        int idxX = -1;
        if (itX != ys.end())
        {
            idxX = itX - ys.begin();
        }

        if (0 > idxY)
        {
            cout << "maybe\n";
        }
        else
        {
            if (y == ys[idxY])
            {
                if (0 <= idxX && x == ys[idxX])
                {
                    if (idxY < idxX)
                    {
                        int max = stbl.query(idxY + 1, idxX);
                        if (max == rs[idxX])
                        {
                            if ((idxY + 1) <= (idxX - 1) && max == stbl.query(idxY + 1, idxX - 1))
                            {
                                cout << "false\n";
                            }
                            else
                            {
                                if (max > rs[idxY])
                                {
                                    cout << "false\n";
                                }
                                else
                                {
                                    if (x - y == idxX - idxY)
                                    {
                                        cout << "true\n";
                                    }
                                    else
                                    {
                                        cout << "maybe\n";
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << "false\n";
                        }
                    }
                    else
                    {
                        cout << "false\n";
                    }
                }
                else
                {
                    int ed = -1;
                    if (0 > idxX)
                    {
                        ed = rs.size() - 1;
                    }
                    else
                    {
                        ed = idxX - 1;
                    }

                    if (0 > ed)
                    {
                        cout << "maybe\n";
                    }
                    else
                    {
                        if (idxY < ed)
                        {
                            int max = stbl.query(idxY + 1, ed);
                            if (max >= rs[idxY])
                            {
                                cout << "false\n";
                            }
                            else
                            {
                                cout << "maybe\n";
                            }
                        }
                        else
                        {
                            cout << "maybe\n";
                        }
                    }
                }
            }
            else
            {
                if (0 <= idxX && x == ys[idxX])
                {
                    int max = stbl.query(idxY, idxX);
                    if (max == rs[idxX])
                    {
                        if (idxY <= (idxX - 1) && max == stbl.query(idxY, idxX - 1))
                        {
                            cout << "false\n";
                        }
                        else
                        {
                            cout << "maybe\n";
                        }
                    }
                    else
                    {
                        cout << "false\n";
                    }
                }
                else
                {
                    cout << "maybe\n";
                }
            }
        }
    }

    return 0;
}
