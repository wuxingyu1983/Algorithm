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

        int sum[20000];
        sum[0] = height[0];
        for (size_t i = 1; i < height.size(); i++)
        {
            sum[i] = sum[i - 1] + height[i];
        }

        stack<int> stk;

        for (size_t i = 0; i < height.size(); i++)
        {
            int h = height[i];

            if (0 < h)
            {
                if (0 == stk.size())
                {
                    stk.push(i);
                }
                else
                {
                    int last = stk.top();
                    if (height[last] > h)
                    {
                        stk.push(i);
                    }
                    else
                    {
                        do
                        {
                            last = stk.top();
                            if (height[last] > h)
                            {
                                break;
                            }
                            else
                            {
                                stk.pop();
                            }
                        } while (0 < stk.size());
                       
                        if (0 == stk.size())
                        {
                            ret += (i - last - 1) * height[last] - (sum[i - 1] - sum[last]);
                        }

                        stk.push(i);
                    }
                }
            }
        }

        if (1 < stk.size())
        {
            int i = stk.top();
            stk.pop();

            int j = stk.top();
            stk.pop();

            ret += (i - j - 1) * height[i] - (sum[i - 1] - sum[j]);

            while (0 < stk.size())
            {
                i = j;
                j = stk.top();
                stk.pop();

                ret += (i - j - 1) * height[i] - (sum[i - 1] - sum[j]);
            }
        }

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
