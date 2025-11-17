// https://codeforces.com/problemset/problem/1143/B

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
#include <unordered_map>
#include <bitset>

using namespace std;

int dp[9];

int main()
{
    int n;
    cin >> n;

    dp[0] = 9;
    for (size_t i = 1; i < 9; i++)
    {
        dp[i] = dp[i - 1] * 9;
    }
    
    int max = 0;

    string str = to_string(n);

    if (1 == str.length())
    {
        max = n;
    }
    else
    {
        int pre = 1;
        reverse(str.begin(), str.end());

        for (int pos = str.length() - 1; pos >= 0; pos --)
        {
            int digit = str.at(pos) - '0';
            if (0 == pos)
            {
                if (pre * digit > max)
                {
                    max = pre * digit;
                }
            }
            else
            {
                if (0 == digit)
                {
                    break;
                }
                else
                {
                    if (pos == str.length() - 1 && 1 == digit)
                    {
                        max = dp[pos - 1];
                    }
                    else
                    {
                        if (max < pre * (digit - 1) * dp[pos - 1])
                        {
                            max = pre * (digit - 1) * dp[pos - 1];
                        }
                    }

                    pre *= digit;
                }
            }
        }
    }

    cout << max << endl;

    return 0;
}
