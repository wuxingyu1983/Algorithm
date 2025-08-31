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
#include <bitset>

using namespace std;

class Item
{
public:
    int state;
    vector<char> idxs;

    Item(int _n)
    {
        state = 0;
        idxs.resize(_n, 0);
    }
};

class Solution
{
public:
    vector<int> concatenatedDivisibility(vector<int> &nums, int k)
    {
        vector<int> ret;
        vector<string> strNums;
        int totalDigit = 0;     // 总的位数

        for (size_t i = 0; i < nums.size(); i++)
        {
            string str = to_string(nums[i]);

            strNums.push_back(str);
            totalDigit += str.length();
        }

        vector<int> mods(totalDigit);
        for (int i = 0, tmp = 1; i < totalDigit; i++)
        {
            mods[i] = tmp;
            tmp *= 10;
            tmp %= k;
        }

        vector< vector<Item> > dp(totalDigit, vector<Item>(k, Item(nums.size())));

        

        return ret;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> nums;
    for (size_t i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        nums.push_back(num);
    }

    int k;
    cin >> k;

    Solution s;
    vector<int> result = s.concatenatedDivisibility(nums, k);

    for (size_t i = 0; i < n; i++)
    {
        cout << result[i] << endl;
    }

    return 0;
}
