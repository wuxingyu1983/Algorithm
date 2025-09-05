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
    int stoneGameV(vector<int> &stoneValue)
    {
        int ret = 0;

        return ret;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> vals;
    for (size_t i = 0; i < n; i++)
    {
        int v;
        cin >> v;

        vals.push_back(v);
    }
    
    Solution s;
    cout << s.stoneGameV(vals) << endl;

    return 0;
}
