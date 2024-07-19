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

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {

    }

private:
    
};

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> vec;

    for (size_t i = 0; i < n; i++)
    {
        int hat;
        while (cin >> hat)
        {
            vec[i].push_back(hat);
            if (cin.get() == '\n')
                break;
        }
    }

    Solution s;
    cout << s.numberWays(vec) << endl;

    return 0;
}