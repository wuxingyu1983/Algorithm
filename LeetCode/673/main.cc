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

const int MAX_N = 2001;

unordered_map<int, int> indexs;

// root 表示整棵线段树的根结点；cnt 表示当前结点个数
int cnt, root[MAX_N];
int sum[MAX_N * 2 * 11], ls[MAX_N * 2 * 11], rs[MAX_N * 2 * 11];

class Solution
{
public:
    int findNumberOfLIS(vector<int> &nums)
    {
        int ret = 0;

        vector<int> tmp(nums);
        // 去重
        std::sort(tmp.begin(), tmp.end());               // 先对vector进行排序
        auto last = std::unique(tmp.begin(), tmp.end()); // 去除重复的元素
        tmp.erase(last, tmp.end());                      // 删除多余的元素

        for (size_t i = 0; i < tmp.size(); i++)
        {
            indexs.insert({tmp[i], 1 + i});
        }

        return 0;
    }

private:
    // 用法：update(root, 1, n, x, f); 其中 x 为待修改节点的编号
    void updateMax(int &p, int s, int t, int x, int f)
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
            updateMax(ls[p], s, m, x, f);
        else
            updateMax(rs[p], m + 1, t, x, f);
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
