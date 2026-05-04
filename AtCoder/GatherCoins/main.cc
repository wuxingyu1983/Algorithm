// https://atcoder.jp/contests/abc369/tasks/abc369_f

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

using namespace std;

const int MAX_HW = 200000;
const int MASK = 262143;
const int BITS = 18;
unordered_map<long long, long long> froms;

class Cell
{
public:
    int r, c;
};

bool myfunc(Cell &x, Cell &y)
{
    bool bRet = false;

    if (x.r < y.r)
    {
        bRet = true;
    }
    else if (x.r == y.r)
    {
        if (x.c < y.c)
        {
            bRet = true;
        }
    }

    return bRet;
}

// 合并左右子树的最大值
void push_up(vector<long long> &tree, int p)
{
    tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
}

void updateMax(vector<long long> &tree, int idx, long long c, int l, int r, int p)
{
    if (idx == l && idx == r)
    {
        tree[p] = c;
        return;
    }

    int mid = (l + r) >> 1;
    if (idx <= mid)
        updateMax(tree, idx, c, l, mid, p << 1);
    else
        updateMax(tree, idx, c, mid + 1, r, p << 1 | 1);
    push_up(tree, p);
}

// 区间查询：查询[L, R]内的最大值
long long getMax(vector<long long> &tree, int L, int R, int l, int r, int p)
{
    if (L > R)
        return 0;
    if (L <= l && r <= R)
        return tree[p]; // 完全覆盖
    int mid = (l + r) >> 1;
    long long res = 0;
    if (L <= mid)
        res = max(res, getMax(tree, L, R, l, mid, p << 1));
    if (R > mid)
        res = max(res, getMax(tree, L, R, mid + 1, r, p << 1 | 1));
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, n;
    cin >> h >> w >> n;

    vector<Cell> cells;
    for (size_t i = 0; i < n; i++)
    {
        int r, c;
        cin >> r >> c;

        Cell cell;
        cell.r = r;
        cell.c = c;

        cells.push_back(cell);
    }

    sort(cells.begin(), cells.end(), myfunc);

    vector<long long> tree(MAX_HW * 18, 0);
    int maxLen = 0;

    for (size_t i = 0; i < cells.size(); i++)
    {
        // get MAX from col 1 - cells[i].c
        int coins = getMax(tree, 1, cells[i].c, 1, MAX_HW, 1);

    }
    

    return 0;
}
