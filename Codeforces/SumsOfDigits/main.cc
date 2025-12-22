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

    if (0 == preA.length())
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
