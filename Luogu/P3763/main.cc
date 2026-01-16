// https://www.luogu.com.cn/problem/P3763

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

const int MAX_LEN = 100001;

constexpr long long M = 1e9 + 7;
constexpr long long B = 233;

long long power[MAX_LEN];
long long hashS[MAX_LEN];
long long hashP[MAX_LEN];

void initHash(const string &str, long long arr[])
{
    memset(arr, 0, sizeof(long long) * MAX_LEN);

    int len = str.length();

    arr[0] = str.at(0);

    for (int i = 1; i < len; i++)
    {
        arr[i] = str.at(i) + arr[i - 1] * B;
        arr[i] %= M;
    }
}

#define getHash(RET, ARR, L, R)                         \
    {                                                   \
        RET = M + ARR[R];                               \
        if (0 < L)                                      \
            RET -= (ARR[L - 1] * power[R - L + 1]) % M; \
        RET %= M;                                       \
    }

void getDiffCnt(string &s, int startS, string &p, int startP, int len, int &cnt)
{
    int hshs = 0, hshp = 0;
    getHash(hshs, hashS, startS, (startS + len - 1));
    getHash(hshp, hashP, startP, (startP + len - 1));

    if (hshs != hshp)
    {
        int midS = startS + (len >> 1);
        int midP = startP + (len >> 1);

        if (3 == cnt)
        {
            cnt++;
            return;
        }

        if (s.at(midS) != p.at(midP))
        {
            cnt++;
        }

        if (3 >= cnt)
        {
            if (startS < midS)
            {
                getDiffCnt(s, startS, p, startP, midS - startS, cnt);
            }

            if (3 >= cnt && midS < startS + len - 1)
            {
                getDiffCnt(s, midS + 1, p, midP + 1, startP + len - midP - 1, cnt);
            }
        }
    }
}

int main()
{
    int t;
    cin >> t;

    // init
    {
        power[0] = 1;
        for (int i = 1; i < MAX_LEN; i++)
        {
            power[i] = (power[i - 1] * B) % M;
        }
    }

    for (int i = 0; i < t; i++)
    {
        string s, p;
        cin >> s;
        cin >> p;

        int cnt = 0;
        int lenS = s.length();
        int lenP = p.length();

        if (lenS >= lenP)
        {
            initHash(s, hashS);
            initHash(p, hashP);

            for (int pos = 0; pos <= lenS - lenP; pos++)
            {
                int diffs = 0;
                getDiffCnt(s, pos, p, 0, lenP, diffs);
                if (3 >= diffs)
                {
                    cnt++;
                }
            }
        }

        cout << cnt << endl;
    }

    return 0;
}
