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
    int longestValidParentheses(string s)
    {
        int ret = 0;

        stack<int> stk;

        for (size_t i = 0; i < s.length(); i++)
        {
            if ('(' == s.at(i))
            {
                stk.push(i);
            }
            else
            {
                // ')'
                if (0 == stk.size() || '(' != s.at(stk.top()))
                {
                    stk.push(i);
                }
                else
                {
                    stk.pop();
                    int top = -1;
                    if (0 < stk.size())
                    {
                        top = stk.top();
                    }
                    if ((i - top) > ret)
                    {
                        ret = i - top;
                    }
                }
            }
        }

        return ret;
    }
};

int main()
{
    string str;
    cin >> str;

    Solution s;

    cout << s.longestValidParentheses(str) << endl;

    return 0;
}
