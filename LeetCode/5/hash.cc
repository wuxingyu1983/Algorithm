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
    string longestPalindrome(string s)
    {
        string revs(s);
        reverse(revs.begin(), revs.end());
        
        // init
        {
            power[0] = 1;
            for (int i = 1; i < 1001; i++)
            {
                power[i] = (power[i - 1] * B) % M;
            }

            initHash(s, hashS);
            initHash(revs, hashR);
        }

        

//        string ret(s.begin() + start, s.begin() + start + max);
//        return ret;
    }

private:
    void initHash(const string &str, long long arr[])
    {
        int len = str.length();

        arr[0] = str.at(0);

        for (int i = 1; i < len; i++)
        {
            arr[i] = str.at(i) + arr[i - 1] * B;
            arr[i] %= M;
        }
    }

private:
    long long power[1001];
    long long hashS[1001];
    long long hashR[1001];

    const long long M = 1e9 + 7;
    const long long B = 233;
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.longestPalindrome(str) << endl;

    return 0;
}
