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
#include <unordered_set>
#include <queue>
#include <stack>
#include <map>

using namespace std;

const int MAX_N = 1048576;
const unsigned long long M1 = 1e9 + 7;
const unsigned long long M2 = 998244353;
const unsigned long long B = 9973;
unsigned long long power1[2 * MAX_N + 2];
unsigned long long power2[2 * MAX_N + 2];
unsigned long long hashs1[2 * MAX_N + 2];
unsigned long long hashs2[2 * MAX_N + 2];
string strRes;

unsigned long long getHash(unsigned long long arr[], unsigned long long power[], int l, int r, unsigned long long M)
{
    unsigned long long ret = M + arr[r];
    if (0 < l)
        ret -= (arr[l - 1] * power[r - l + 1]) % M;
    ret %= M;

    return ret;
}

void initHash(const string &str, unsigned long long arr[], unsigned long long M)
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

        unsigned long long x = 0;
        for (size_t i = 0; i < MAX_N; i++)
        {
            x = x * 487237 + 1011807;
            x %= MAX_N;

            if (1 & __builtin_popcount(x))
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

        power1[0] = 1;
        power2[0] = 1;
        for (int i = 1; i < 2 * MAX_N; i++)
        {
            power1[i] = (power1[i - 1] * B) % M1;
            power2[i] = (power2[i - 1] * B) % M2;
        }

        initHash(strRes, hashs1, M1);
        initHash(strRes, hashs2, M2);
    }

    {
        // get min len
        int l = 3, r = MAX_N, len;
        unordered_set<unsigned long long> st;

        while (l <= r)
        {
            len = l + (r - l) / 2;
            st.clear();
            int pos;
            for (pos = 0; pos < MAX_N; pos++)
            {
                unsigned long long hash1 = getHash(hashs1, power1, pos, pos + len - 1, M1);
                unsigned long long hash2 = getHash(hashs2, power2, pos, pos + len - 1, M2);
                unsigned long long key = (hash1 << 32) + hash2;
                auto it = st.find(key);
                if (it != st.end())
                {
                    l = len + 1;
                    break;
                }
                else
                {
                    st.insert(key);
                }
            }

            if (MAX_N == pos)
            {
                r = len - 1;
            }
        }

        cout << "min len is " << len << endl;
    }

    return 0;
}
