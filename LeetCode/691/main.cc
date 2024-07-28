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
    int minStickers(vector<string> &stickers, string target)
    {
        // init

    }

private:
    int **dp;
    int finalSt;
};

int main()
{
    string target;
    cin >> target;

    vector<string> stickers;
    string str;
    while (cin >> str)
    {
        stickers.push_back(str);
        if (cin.get() == '\n')
            break;
    }

    Solution s;
    cout << s.minStickers(stickers, target) << endl;

    return 0;
}
