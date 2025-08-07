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

        // 降序
        std::sort(digits.begin(), digits.end(), [](int a, int b)
                  {
                      return a > b;
                  });

        int cnt[10];
        memset(cnt, 0, sizeof(cnt));

        for (size_t i = 0; i < digits.size(); i++)
        {
            cnt[digits[i]] ++;
        }
        
        

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
