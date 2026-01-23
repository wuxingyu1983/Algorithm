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
        memset(p, 0, sizeof(p));
        string sp = preprocString(s);



        int start = 0, max = 1;

        string ret(s.begin() + start, s.begin() + start + max);
        return ret;
    }

private:
    string preprocString(string s)
    {
        string ret = "^";
        int len = s.length();
        for (int i = 0; i < len; i++)
        {
            ret += '#';
            ret += s.at(i);
        }
        ret += "#$";

        return ret;
    }

private:
    int p[2005];
};

int main()
{
    string str;
    cin >> str;

    Solution s;
    cout << s.longestPalindrome(str) << endl;

    return 0;
}
