#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>

using namespace std;

#define DEBUG       0
#define MAX_N       6001

class Staff
{
public:
    int r;
    int sum[2];     // 0 - not in, 1 - in
    Staff * superior;
    vector<Staff *> subordinates;

    Staff()
    {
        superior = NULL;
    }
};

void getSum(Staff * staff)
{
    for (vector<Staff *>::iterator it = staff->subordinates.begin(); it != staff->subordinates.end(); it++)
    {
        getSum(*it);
    }

    staff->sum[1] = staff->r;
    for (vector<Staff *>::iterator it = staff->subordinates.begin(); it != staff->subordinates.end(); it++)
    {
        staff->sum[1] += (*it)->sum[0];

        if ((*it)->sum[0] > (*it)->sum[1])
        {
            staff->sum[0] += (*it)->sum[0];
        }
        else
        {
            staff->sum[0] += (*it)->sum[1];
        }
    }
}

Staff staffs[MAX_N];

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n;
#if DEBUG
    inFile >> n;
#else
    cin >> n;
#endif

    for (size_t i = 1; i <= n; i++)
    {
#if DEBUG
        inFile >> staffs[i].r;
#else
        cin >> staffs[i].r;
#endif
    }

    for (size_t i = 1; i < n; i++)
    {
        unsigned int l, k;
#if DEBUG
        inFile >> l >> k;
#else
        cin >> l >> k;
#endif

        staffs[l].superior = &staffs[k];
        staffs[k].subordinates.push_back(&staffs[l]);
    }

    // find root
    Staff * boss = &staffs[1];
    while (boss->superior)
    {
        boss = boss->superior;
    }

    getSum(boss);

    if (boss->sum[0] > boss->sum[1]) 
    {
        cout << boss->sum[0] << endl;
    }
    else
    {
        cout << boss->sum[1] << endl;
    }

#if DEBUG
    inFile.close();
#endif

    return 0;
}
