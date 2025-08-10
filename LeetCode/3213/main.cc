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
    int minimumCost(string target, vector<string> &words, vector<int> &costs)
    {
        int ret = -1;

        vector<string> vecW;
        vector<int> vecC;
        {
            unordered_map<string, int> mp;
            for (size_t i = 0; i < words.size(); i++)
            {
                string key = words[i];
                auto it = mp.find(key);
                if (it != mp.end())
                {
                    if (it->second > costs[i])
                    {
                        mp[key] = costs[i];
                    }
                }
                else
                {
                    mp.insert({key, costs[i]});
                }
            }

            vecW.resize(mp.size());
            vecC.resize(mp.size());

            int idx;
            unordered_map<string, int>::iterator it;
            for (it = mp.begin(), idx = 0; it != mp.end(); it++, idx++)
            {
                vecW[idx] = it->first;
                vecC[idx] = it->second;
            }
        }

        vector< bitset<50000> > flags(vecW.size());
        int pi[100002];

        vector<int> dp(target.length(), -1);
        // 计算 每个 word 在 target 中的位置
        
        for (int idx = 0; idx < vecW.size(); idx ++)
        {
            {
                string cur = vecW[idx] + '#' + target;
                int sz1 = target.size(), sz2 = vecW[idx].size();
                int n = (int)cur.length();
                memset(pi, 0, sizeof(pi));

                for (int i = 1; i < n; i++)
                {
                    int j = pi[i - 1];
                    while (j > 0 && cur[i] != cur[j])
                        j = pi[j - 1];
                    if (cur[i] == cur[j])
                        j++;
                    pi[i] = j;
                }

                for (int i = sz2 + 1; i <= sz1 + sz2; i++)
                {
                    if (pi[i] == sz2)
                        flags[idx][i - 2 * sz2] = 1;
                }
            }

            if (flags[idx][0])
            {
                dp[vecW[idx].length() - 1] = vecC[idx];
            }
        }

        for (size_t i = 1; i < target.length(); i++)
        {
            if (0 < dp[i - 1])
            {
                for (int idx = 0; idx < vecW.size(); idx++)
                {
                    if (flags[idx][i])
                    {
                        if (0 > dp[i + vecW[idx].length() - 1] || dp[i + vecW[idx].length() - 1] > dp[i - 1] + vecC[idx])
                        dp[i + vecW[idx].length() - 1] = dp[i - 1] + vecC[idx];
                    }
                }
            }
        }

        ret = dp[target.length() - 1];

        return ret;
    }
};

int main()
{
    string target;
    cin >> target;

    int n;
    cin >> n;

    vector<string> words;
    vector<int> costs;

    for (size_t i = 0; i < n; i++)
    {
        string word;
        cin >> word;
        words.push_back(word);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        int cost;
        cin >> cost;
        costs.push_back(cost);
    }
    
    Solution s;
    cout << s.minimumCost(target, words, costs) << endl;

    return 0;
}
