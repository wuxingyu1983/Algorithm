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

#define MAX_N2  16384

class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size();
        init();

        for (size_t i = 0; i < n; i++)
        {
            for (vector<int>::iterator it = digits[i].begin(); it != digits[i].end(); it++)
            {
                for (size_t b = 0; b < n; b++)
                {
                    if (0 == (*it & (1 << b)))
                    {
                        int newI = *it | (1 << b);
                        int newSum = dp[*it] + (nums1[i] ^ nums2[b]);

                        if (0 > dp[newI] || dp[newI] > newSum)
                        {
                            dp[newI] = newSum;
                        }
                    }
                }
            }
        }

        return dp[(1 << n) - 1];
    }

private:
    void init() {
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;

        digits[0].push_back(0);

        for (size_t i = 1; i < (1 << n); i++)
        {
            int cnt = 0;
            for (size_t bit = 1; bit <= i; bit <<= 1)
            {
                if (i & bit)
                {
                    cnt ++;
                }
            }

            digits[cnt].push_back(i);
        }
    }

    int dp[MAX_N2];
    int n;
    vector<int> digits[15];
};

int main()
{
    vector<int> vec1, vec2;

    int tmp;
    while (cin >> tmp)
    {
        vec1.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }

    while (cin >> tmp)
    {
        vec2.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }
/*
    for (vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    
    for (vector<int>::iterator it = vec2.begin(); it != vec2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
*/
    Solution s;
    cout << s.minimumXORSum(vec1, vec2) << endl;

    return 0;
}