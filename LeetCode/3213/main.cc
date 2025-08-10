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
    cout << s.minimumCost(target, words, costs);

    return 0;
}
