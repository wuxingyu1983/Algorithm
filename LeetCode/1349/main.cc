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
    int maxStudents(vector<vector<char>>& seats) {

    }
};

int main()
{
    int m, n;       // row, col
    cin >> m >> n;

    char seat;
    vector<vector<char>> seats;

    for (size_t row = 0; row < m; row++)
    {
        seats.push_back(vector<char>());

        for (size_t col = 0; col < n; col++)
        {
            cin >> seat;
            seats[row].push_back(seat);
        }
    }

    Solution s;
    cout << s.maxStudents(seats) << endl;

    return 0;
}
