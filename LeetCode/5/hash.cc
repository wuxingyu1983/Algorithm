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
    static long long power[1001];
    static long long hashS[1001];
    static long long hashR[1001];

    static long long M;
    static long long B;
    static int len;

    static vector<int> idx;

    string longestPalindrome(string s)
    {
        init(s);

        int start = 0, max = 1;
        int mid = len >> 1;
        for (int pos = 0; pos <= mid; pos++)
        {
            // [0 -- (pos - 1)],pos,[(pos + 1) -- 2 * pos]
            if (0 < pos)
            {
                auto cmp = [](const int &a, const int &pos)
                {
                    int hs = getHash(hashS, a, pos);
                    int hr = getHash(hashR, len - 1 - 2 * pos + a, len - 1 - pos);

                    if (hs != hr)
                        return true;
                    else
                        return false;
                };

                auto it = lower_bound(idx.begin(), idx.begin() + pos, pos, cmp);
                if (it != idx.begin() + pos)
                {
                    int tmp = 2 * (pos - (*it)) + 1;
                    if (max < tmp)
                    {
                        max = tmp;
                        start = *it;
                    }
                }
            }

            // [0 -- pos][(pos + 1) -- (2 * pos + 1)]
            if (pos != mid || 0 == (len & 1))
            {
                auto cmp = [](const int &a, const int &pos)
                {
                    int hs = getHash(hashS, a, pos);
                    int hr = getHash(hashR, len - 1 - 2 * pos + a, len - 1 - pos);

                    if (hs != hr)
                        return true;
                    else
                        return false;
                };

                auto it = lower_bound(idx.begin(), idx.begin() + pos, pos, cmp);
                if (it != idx.begin() + pos)
                {
                    int tmp = 2 * (pos - (*it));
                    if (max < tmp)
                    {
                        max = tmp;
                        start = *it;
                    }
                }
            }
        }


        string ret(s.begin() + start, s.begin() + start + max);
        return ret;
    }

    static int getHash(long long arr[], int l, int r)
    {
        int ret = M + arr[r];
        if (0 < l)
            ret -= (arr[l - 1] * power[r - l + 1]) % M;
        ret %= M;

        return ret;
    }

    static void initHash(const string &str, long long arr[])
    {
        arr[0] = str.at(0);

        for (int i = 1; i < len; i++)
        {
            arr[i] = str.at(i) + arr[i - 1] * B;
            arr[i] %= M;
        }
    }

    static void init(string &s)
    {
        len = s.length();

        string revs(s);
        reverse(revs.begin(), revs.end());

        power[0] = 1;
        idx.push_back(0);
        for (int i = 1; i < 1001; i++)
        {
            power[i] = (power[i - 1] * B) % M;
            idx.push_back(i);
        }

        initHash(s, hashS);
        initHash(revs, hashR);
    }
};

long long Solution::M = 1e9 + 7;
long long Solution::B = 233;
int Solution::len = 0;
long long Solution::power[1001] = {0};
long long Solution::hashS[1001] = {0};
long long Solution::hashR[1001] = {0};
vector<int> Solution::idx;

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.longestPalindrome(str) << endl;

    return 0;
}
