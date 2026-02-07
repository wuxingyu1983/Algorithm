// https://codeforces.com/contest/1200/problem/E

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

const int MAX_N = 1000006;
const long long M = 1e9 + 7;
const long long B = 233;
long long power[MAX_N];
long long hashs[MAX_N];

int getHash(long long arr[], int l, int r)
{
    int ret = M + arr[r];
    if (0 < l)
        ret -= (arr[l - 1] * power[r - l + 1]) % M;
    ret %= M;

    return ret;
}

void initHash(const string &str, long long arr[], int from)
{
    if (0 == from)
    {
        arr[0] = str.at(0);
        from ++;
    }

    for (int i = from; i < str.length(); i++)
    {
        arr[i] = str.at(i) + arr[i - 1] * B;
        arr[i] %= M;
    }
}

int main()
{
    int n;
    cin >> n;

    string item;
    vector<string> words;

    // 默认按空格分割
    while (getline(cin, item, ' '))
    {
        words.push_back(item);
    }

    // init
    {
        power[0] = 1;
        for (int i = 1; i < MAX_N; i++)
        {
            power[i] = (power[i - 1] * B) % M;
        }
    }

    string ans(words[0]);
    if (1 < words.size())
    {
        ans.append(words[1]);

        initHash(ans, hashs, 0);

        int len0 = words[0].length();
        int len1 = words[1].length();

        int len = min(len0, len1);
        int l = len0, r = len0 + len1 - 1;
        int mid, max = 0;
        while (l <= r)
        {
            mid = l + (r - l) / 2;
            
            long long hash1 = getHash(hashs, l, mid);
            long long hash0 = getHash(hashs, 2 * l - mid - 1, l - 1);

            if (hash0 == hash1)
            {
                max = mid - l + 1;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
