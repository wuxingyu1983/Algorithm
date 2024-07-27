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
    int minimumIncompatibility(vector<int> &nums, int k)
    {
    }
};

int main()
{
    int k;
    cin >> k;

    vector<int> nums;
    int num;
    while (cin >> num)
    {
        nums.push_back(num);
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.minimumIncompatibility(nums, k) << endl;

    return 0;
}
