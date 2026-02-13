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
const long long B = 9973;
long long power[MAX_N];
long long hashs[MAX_N];

#define getHash(RET, ARR, L, R)                     \
    RET = M + ARR[R];                               \
    if (0 < L)                                      \
        RET -= (ARR[L - 1] * power[R - L + 1]) % M; \
    RET %= M;

void initHash(const string &str, long long arr[], int from)
{
    if (0 == from)
    {
        arr[0] = str.at(0);
        from++;
    }

    for (int i = from; i < str.length(); i++)
    {
        arr[i] = str.at(i) + arr[i - 1] * B;
        arr[i] %= M;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    string item;
    vector<string> words;

    // 默认按空格分割
    while (getline(cin, item, ' '))
    {
        item.erase(remove(item.begin(), item.end(), '\n'), item.end());
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

    string ans;
    ans.reserve(MAX_N);
    ans.append(words[0]);
    if (1 < words.size())
    {
        {
            ans.append(words[1]);
            initHash(ans, hashs, 0);

            int len0 = words[0].length();
            int len1 = words[1].length();

            int len = min(len0, len1);
            int idx = len0 + len - 1;
            int max = 0;
            while (idx >= len0)
            {
                long long hash1;
                getHash(hash1, hashs, len0, idx);
                long long hash0;
                getHash(hash0, hashs, (2 * len0 - idx - 1), (len0 - 1));

                if (hash0 == hash1)
                {
                    max = idx - len0 + 1;
                    break;
                }

                idx --;
            }

            if (0 < max)
            {
                ans.resize(len0);
                ans.append(words[1], max, len1 - max);

                initHash(ans, hashs, len0);
            }
        }

        for (int i = 2; i < n; i++)
        {
            int len0 = ans.length();
            int len1 = words[i].length();

            ans.append(words[i]);
            initHash(ans, hashs, len0);

            int len = min(len0, len1);
            int idx = len0 + len - 1;
            int max = 0;
            while (idx >= len0)
            {
                long long hash1;
                getHash(hash1, hashs, len0, idx);
                long long hash0;
                getHash(hash0, hashs, (2 * len0 - idx - 1), (len0 - 1));

                if (hash0 == hash1)
                {
                    max = idx - len0 + 1;
                    break;
                }
                
                idx --;
            }

            if (0 < max)
            {
                ans.resize(len0);
                ans.append(words[i], max, len1 - max);

                initHash(ans, hashs, len0);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}
