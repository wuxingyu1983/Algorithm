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
    int maximumANDSum(vector<int>& nums, int numSlots) {
        
    }
};

int main()
{
    vector<int> vec;

    int tmp;
    while (cin >> tmp)
    {
        vec.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }

    int slots;
    cin >> slots;

    Solution s;
    cout << s.maximumANDSum(vec, slots) << endl;

    return 0;
}