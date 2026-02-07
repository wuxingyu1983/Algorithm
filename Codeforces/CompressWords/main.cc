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
long long hashs[10][MAX_N];

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

    

    return 0;
}
