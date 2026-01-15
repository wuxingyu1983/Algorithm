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

constexpr int M = 1e9 + 7;
constexpr int B = 233;

int power[MAX_LEN];
int hashS[MAX_LEN];
int hashP[MAX_LEN];

void initHash(const string& str, int arr[])
{
    memset(arr, 0, sizeof(int) * MAX_LEN);

    int len = str.length();

    arr[0] = str.at(0);

    for (int i = 1; i < len; i++)
    {
        arr[i] = str.at(i) + arr[i - 1] * B;
        arr[i] %= M;
    }
}

int getHash(int arr[], int l, int r)
{
    int ret = 0;

    ret = M + arr[r];
    if (0 < l)
    {
        ret -= (arr[l - 1] * power[r - l + 1]) % M;
    }
    ret %= M;

    return ret;
}

void getDiffCnt(string& s, int startS, string& p, int startP, int len, int& cnt)
{
    int hshs = getHash(hashS, startS, startS + len - 1);
    int hshp = getHash(hashP, startP, startP + len - 1);

    if (hshs != hshp)
    {
        int midS = startS + (len >> 1);
        int midP = startP + (len >> 1);

        if (s.at(midS) != p.at(midP))
        {
            cnt ++;
        }

        if (3 >= cnt)
        {
            if (startS < midS)
            {
                getDiffCnt(s, startS, p, startP, midS - startS + 1, cnt);
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
                    cnt ++;
                }
            }
        }

        cout << cnt << endl;
    }

    return 0;
}
