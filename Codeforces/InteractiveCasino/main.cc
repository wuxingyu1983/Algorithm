// https://codeforces.com/problemset/gymProblem/100917/I

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

using namespace std;

const int MAX_N = 1048576;
const long long M = 1e9 + 7;
const long long B = 233;
long long power[2 * MAX_N + 2];
long long hashs[2 * MAX_N + 2];
string strRes;

int getHash(long long arr[], int l, int r)
{
    int ret = M + arr[r];
    if (0 < l)
        ret -= (arr[l - 1] * power[r - l + 1]) % M;
    ret %= M;

    return ret;
}

void initHash(const string &str, long long arr[])
{
    arr[0] = str.at(0);

    for (int i = 1; i < str.length(); i++)
    {
        arr[i] = str.at(i) + arr[i - 1] * B;
        arr[i] %= M;
    }
}

int main()
{
    // init
    {
        strRes.reserve(2 * MAX_N + 2);

        long long x = 0;
        for (size_t i = 0; i < MAX_N; i++)
        {
            x = x * 487237 + 1011807;
            x %= MAX_N;

            if (1 & x)
            {
                // odd
                strRes += '1';
            }
            else
            {
                strRes += '0';
            }
        }

        strRes += strRes;

        power[0] = 1;
        for (int i = 1; i < 2 * MAX_N; i++)
        {
            power[i] = (power[i - 1] * B) % M;
        }

        initHash(strRes, hashs);
    }

    

    return 0;
}
