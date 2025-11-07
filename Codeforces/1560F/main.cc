// https://codeforces.com/problemset/problem/1560/F1
// https://codeforces.com/problemset/problem/1560/F2

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

#pragma GCC target("popcnt")

int findMinOne(int flag, int after)
{
    int ret = -1;

    for (size_t i = after; i < 10; i++)
    {
        if (flag & (1 << i))
        {
            ret = i;
            break;
        }
    }

    return ret;
}

string func(string num, int idx, int k, int flag)
{
    string ret = "";

    int n = num.at(idx) - '0';

    if (flag & (1 << n))
    {
        ret = '0' + n;
        if (idx < num.length() - 1)
        {
            string postRet = func(num, idx + 1, k, flag);
            if (postRet.empty())
            {
                if (__builtin_popcount(flag) == k)
                {
                    int newN = findMinOne(flag, n + 1);
                    if (0 > newN)
                    {
                        ret = "";
                        return ret;
                    }

                    ret = '0' + newN;
                    int minN = findMinOne(flag, 0);
                    for (size_t i = idx + 1; i < num.length(); i++)
                    {
                        ret += '0' + minN;
                    }
                }
                else
                {
                    ret = '0' + n + 1;
                    int newFlag = flag | (1 << (n + 1));
                    if (__builtin_popcount(newFlag) == k)
                    {
                        int minN = findMinOne(newFlag, 0);
                        for (size_t i = idx + 1; i < num.length(); i++)
                        {
                            ret += '0' + minN;
                        }
                    }
                    else
                    {
                        int minN = 0;
                        for (size_t i = idx + 1; i < num.length(); i++)
                        {
                            ret += '0' + minN;
                        }
                    }
                }
            }
            else
            {
                ret += postRet;
            }
        }
    }
    else
    {
        if (__builtin_popcount(flag) == k)
        {
            int newN = findMinOne(flag, n);
            if (0 > newN)
            {
                ret = "";
                return ret;
            }

            ret = '0' + newN;
            int minN = findMinOne(flag, 0);
            for (size_t i = idx + 1; i < num.length(); i++)
            {
                ret += '0' + minN;
            }
        }
        else
        {
            ret = '0' + n;
            if (idx < num.length() -1)
            {
                string postRet = func(num, idx + 1, k, flag | (1 << n));
                if (postRet.empty())
                {
                    ret = '0' + n + 1;
                    int newFlag = flag | (1 << (n + 1));
                    if (__builtin_popcount(newFlag) == k)
                    {
                        int minN = findMinOne(newFlag, 0);
                        for (size_t i = idx + 1; i < num.length(); i++)
                        {
                            ret += '0' + minN;
                        }
                    }
                    else
                    {
                        int minN = 0;
                        for (size_t i = idx + 1; i < num.length(); i++)
                        {
                            ret += '0' + minN;
                        }
                    }
                }
                else
                {
                    ret += postRet;
                }
            }
        }
    }

    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    for (size_t i = 0; i < t; i++)
    {
        int n, k;
        cin >> n >> k;

        string num = to_string(n);

        cout << func(num, 0, k, 0) << "\n";
    }

    return 0;
}
