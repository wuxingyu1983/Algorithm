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

int getDiffCnt(int startS, int startP, int len)
{
    int ret = 0;

    return ret;
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
                int diffs = getDiffCnt(pos, 0, lenP);
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
