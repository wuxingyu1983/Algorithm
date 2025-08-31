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
