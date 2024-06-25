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
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {

    }
};

int main()
{
    vector<int> vec1, vec2;

    int tmp;
    while (cin >> tmp)
    {
        vec1.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }

    while (cin >> tmp)
    {
        vec2.push_back(tmp);
        if (cin.get() == '\n')
            break;
    }
/*
    for (vector<int>::iterator it = vec1.begin(); it != vec1.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    
    for (vector<int>::iterator it = vec2.begin(); it != vec2.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
*/
    Solution s;
    cout << s.minimumXORSum(vec1, vec2) << endl;

    return 0;
}