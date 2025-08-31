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

        vector< unordered_map<int, vector<int> > > dp(totalDigit);

        // init
        for (int i = 0; i < nums.size(); i++)
        {
            int idx = totalDigit - strNums[i].length();
            int mod = (nums[i] * mods[idx]) % k;

            int key = (1 << i) * 1000 + mod;
            vector<int> val = {i};
            dp[idx].insert({key, val});
        }

        for (int idx = totalDigit - 1; idx > 0; idx--)
        {
            if (0 < dp[idx].size())
            {
                for (unordered_map<int, vector<int> >::iterator it = dp[idx].begin(); it != dp[idx].end(); it++)
                {
                    int key = it->first;
                    int oldMod = key % 1000;
                    int state = key / 1000;

                    for (int pos = 0; pos < nums.size(); pos++)
                    {
                        if (0 == ((1 << pos) & state))
                        {
                            int newIdx = idx - strNums[pos].length();
                            int newMod = (oldMod + (nums[pos] * mods[newIdx])) % k;
                            int newSt = (1 << pos) | state;
                            int newKey = newSt * 1000 + newMod;

                            auto search = dp[newIdx].find(newKey);
                            if (search == dp[newIdx].end())
                            {
                                it->second.push_back(pos);
                                dp[newIdx].insert(make_pair(newKey, it->second));
                            }
                            else
                            {
                                // 判断 it->second 和 search->second 谁大谁小
                                
                            }
                        }
                    }
                    
                }
            }
        }

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
