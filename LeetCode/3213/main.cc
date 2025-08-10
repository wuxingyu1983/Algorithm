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
#include <map>
#include <bitset>

using namespace std;

class Solution
{
public:
    int minimumCost(string target, vector<string> &words, vector<int> &costs)
    {
        int ret = -1;

        map<string, int> mp;
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

        vector< bitset<50000> > flags(mp.size());

        vector<int> dp(target.length(), -1);
        // 计算 每个 word 在 target 中的位置
        int idx;
        map<string, int>::iterator it;
        for (it = mp.begin(), idx = 0; it != mp.end(); it ++, idx ++)
        {
            find_occurrences(target, it->first, flags[idx]);

            if (flags[idx][0])
            {
                dp[it->first.length() - 1] = it->second;
            }
        }

        for (size_t i = 1; i < target.length(); i++)
        {
            if (0 < dp[i - 1])
            {
                for (it = mp.begin(), idx = 0; it != mp.end(); it++, idx++)
                {
                    if (flags[idx][i])
                    {
                        if (0 > dp[i + it->first.length() - 1] || dp[i + it->first.length() - 1] > dp[i - 1] + it->second)
                        dp[i + it->first.length() - 1] = dp[i - 1] + it->second;
                    }
                }
            }
        }

        ret = dp[target.length() - 1];

        return ret;
    }

private:
    vector<int> prefix_function(string s)
    {
        int n = (int)s.length();
        vector<int> pi(n);
        for (int i = 1; i < n; i++)
        {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }

    void find_occurrences(string text, string pattern, bitset<50000> &flags)
    {
        string cur = pattern + '#' + text;
        int sz1 = text.size(), sz2 = pattern.size();
        vector<int> lps = prefix_function(cur);
        for (int i = sz2 + 1; i <= sz1 + sz2; i++)
        {
            if (lps[i] == sz2)
                flags[i - 2 * sz2] = 1;
        }
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
