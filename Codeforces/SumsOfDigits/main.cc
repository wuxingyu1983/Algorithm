// https://codeforces.com/problemset/problem/509/C

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

string func(int b, string preA)
{
    string ret;
    int len = preA.length();

    if (0 == len)
    {
        while (0 < b)
        {
            if (9 < b)
            {
                ret += '9';
                b -= 9;
            }
            else
            {
                ret += b + '0';
                b = 0;
            }
        }
        
    }
    else
    {
        vector<int> sum(len, 0);
        for (int pos = 0; pos < len; pos++)
        {
            int d = preA.at(pos) - '0';
            if (0 == pos)
            {
                sum[pos] = d;
            }
            else
            {
                sum[pos] = sum[pos - 1] + d;
            }
        }
        
        for (int pos = len - 1; pos >= 0; pos --)
        {
            if (sum[pos] < b)
            {
                int diff = b - sum[pos];
                int d = preA.at(pos) - '0';
                if (len - 1 == pos)
                {
                    if (9 >= d + diff)
                    {
                        ret += '0' + d + diff;
                        for (int i = pos - 1; i >= 0; i--)
                        {
                            ret += preA.at(i);
                        }
                        
                        break;
                    }
                }
                else
                {
                    if (9 > d)
                    {
                        for (int num = d + 1; num < 10; num++)
                        {
                            diff -= 1;
                            if (diff <= 9 * (len - 1 - pos))
                            {
                                for (int i = len - 1; i > pos; i--)
                                {
                                    if (9 < diff)
                                    {
                                        ret += '9';
                                        diff -= 9;
                                    }
                                    else
                                    {
                                        ret += '0' + diff;
                                        diff = 0;
                                    }
                                }

                                ret += '0' + num;
                                for (int i = pos - 1; i >= 0; i--)
                                {
                                    ret += preA.at(i);
                                }

                                break;
                            }
                        }
                    }
                }
                
            }
        }
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

int main()
{
    int n;
    cin >> n;

    string a;
    for (size_t i = 0; i < n; i++)
    {
        int b;
        cin >> b;

        a = func(b, a);
        cout << a << endl;
    }

    return 0;
}
