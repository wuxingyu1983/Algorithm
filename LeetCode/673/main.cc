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

class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        int ret = 0;
        unordered_map<int, int> indexs;

        cnt = 0;
        const int MAX_N = 2001;
        // root 表示整棵线段树的根结点；cnt 表示当前结点个数
        root.resize(MAX_N, 0);
        sum.resize(MAX_N * 2 * 11, 0);
        ls.resize(MAX_N * 2 * 11, 0);
        rs.resize(MAX_N * 2 * 11, 0);

        vector<int> tmp(nums);
        // 去重
        std::sort(tmp.begin(), tmp.end());               // 先对vector进行排序
        auto last = std::unique(tmp.begin(), tmp.end()); // 去除重复的元素
        tmp.erase(last, tmp.end());                      // 删除多余的元素

        for (size_t i = 0; i < tmp.size(); i++)
        {
            indexs.insert({tmp[i], 1 + i});
        }

        vector<int> d(MAX_N * 11, 0);
        int n = tmp.size();
        int maxLen = 0;

        for (size_t i = 0; i < nums.size(); i++)
        {
            int idx = indexs[nums[i]];

            // 获取 1 - (idx - 1) 的最长len
            int len = getMax(d, 1, idx - 1, 1, n, 1);
            updateMax(d, idx, len + 1, 1, n, 1);

            maxLen = max(maxLen, len + 1);

            // 更新 sum
            int preSum = getSum(root[len], 1, n, 1, idx - 1);
            if (0 == preSum)
            {
                preSum = 1;
            }
            updateSum(root[len + 1], 1, n, idx, preSum);
        }

        ret = getSum(root[maxLen], 1, n, 1, n);

        return ret;
    }

private:
    int cnt;
    vector<int> root, sum, ls, rs;

    // 用法：update(root, 1, n, x, f); 其中 x 为待修改节点的编号
    void updateSum(int &p, int s, int t, int x, int f)
    { // 引用传参
        if (!p)
            p = ++cnt; // 当结点为空时，创建一个新的结点
        if (s == t)
        {
            sum[p] += f;
            return;
        }
        int m = s + ((t - s) >> 1);
        if (x <= m)
            updateSum(ls[p], s, m, x, f);
        else
            updateSum(rs[p], m + 1, t, x, f);
        sum[p] = sum[ls[p]] + sum[rs[p]]; // pushup
    }

    // 用法：getSum(root, 1, n, l, r);
    int getSum(int p, int s, int t, int l, int r)
    {
        if (!p)
            return 0; // 如果结点为空，返回 0
        if (s >= l && t <= r)
            return sum[p];
        int m = s + ((t - s) >> 1), ans = 0;
        if (l <= m)
            ans += getSum(ls[p], s, m, l, r);
        if (r > m)
            ans += getSum(rs[p], m + 1, t, l, r);
        return ans;
    }

    // 合并左右子树的最大值
    void push_up(vector<int> &tree, int p)
    {
        tree[p] = max(tree[p << 1], tree[p << 1 | 1]);
    }

    void updateMax(vector<int> &tree, int idx, int c, int l, int r, int p)
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
    int getMax(vector<int> &tree, int L, int R, int l, int r, int p)
    {
        if (L > R)
            return 0;
        if (L <= l && r <= R)
            return tree[p]; // 完全覆盖
        int mid = (l + r) >> 1;
        int res = 0;
        if (L <= mid)
            res = max(res, getMax(tree, L, R, l, mid, p << 1));
        if (R > mid)
            res = max(res, getMax(tree, L, R, mid + 1, r, p << 1 | 1));
        return res;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums;
    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    Solution s;
    cout << s.findNumberOfLIS(nums) << endl;

    return 0;
}
