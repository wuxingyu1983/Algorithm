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

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        int ret = 0;

        return ret;
    }
};

int main()
{
    vector<int> hs;

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int h;
        cin >> h;

        hs.push_back(h);
    }
   
    Solution s;

    cout << s.trap(hs) << endl;

    return 0;
}
