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

class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        n = nums.size();
        init();

        int ans = 0;
        int act = 0;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t st = 0; st < (1 << (2 * numSlots)); st++)
            {
                if (0 <= dp[act][st])
                {
                    for (size_t slot = 0; slot < numSlots; slot++)
                    {
                        int cnt = (st >> (2 * slot)) & 3;
                        if (2 > cnt)
                        {
                            int newSt = st + (1 << (2 * slot));
                            short newSum = dp[act][st] + (nums[i] & (slot +1));

                            if (newSum > dp[1 - act][newSt])
                            {
                                dp[1 - act][newSt] = newSum;
                                if (ans < newSum)
                                {
                                    ans = newSum;
                                }
                            }
                        }
                    }
                }
            }

            memset(dp[act], -1, sizeof(dp[act]));
            act = 1 - act;
        }

        return ans;
    }

private:
    int n;
    short dp[2][262144];

    void init() {
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0; 
    }
};

int main()
{
    vector<int> vec;

    int tmp;
    while (cin >> tmp)
    {
        vec.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }

    int slots;
    cin >> slots;

    Solution s;
    cout << s.maximumANDSum(vec, slots) << endl;

    return 0;
}