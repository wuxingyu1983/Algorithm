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
    string largestMultipleOfThree(vector<int> &digits)
    {
        string strRet;

        return strRet;
    }
};

int main()
{
    int n;
    cin >> n;

    vector<int> digits;
    for (size_t i = 0; i < n; i++)
    {
        int d;
        cin >> d;

        digits.push_back(d);
    }

    Solution s;
    cout << s.largestMultipleOfThree(digits) << endl;
    
    return 0;
}
