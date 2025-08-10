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

using namespace std;

class Solution
{
public:
    int minimumCost(string target, vector<string> &words, vector<int> &costs)
    {
        int ret = 1;

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

        const int maxLen = 50001;
        vector<vector<int>> flag(mp.size(), vector<int>(maxLen, 0));

        // 计算 每个 word 在 target 中的位置

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

    void find_occurrences(string text, string pattern, vector<int> &flags)
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
    cout << s.minimumCost(target, words, costs);

    return 0;
}
