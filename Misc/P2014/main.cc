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
#define MAX_N       301
#define MAX_M       302

class Subject
{
public:
    int credit;
    int prerequisite;
    vector<int> followups;
    int sum[MAX_M];  // 0 - not chose, 1 - chose

    Subject()
    {
        credit = prerequisite = 0;
    }
};

Subject subs[MAX_N];

void func(Subject * sub, int m)
{
    sub->sum[1] = sub->credit;

    for (vector<int>::iterator it = sub->followups.begin(); it != sub->followups.end(); it ++)
    {
        func(&subs[*it], m);
    }

    if (0 == sub->credit)
    {
        m += 1;
    }

    for (vector<int>::iterator it = sub->followups.begin(); it != sub->followups.end(); it++)
    {
        for (size_t i_m = m; i_m >= 2; i_m --)
        {
            for (size_t j = 1; j <= i_m - 1; j ++)
            {
                int tmp = sub->sum[i_m - j] + subs[*it].sum[j];
                if (tmp > sub->sum[i_m])
                {
                    sub->sum[i_m] = tmp;
                }
            }
        }
    }
}

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    int n, m;
#if DEBUG
    inFile >> n >> m;
#else
    cin >> n >> m;
#endif

    for (size_t i = 1; i <= n; i++)
    {
        int k, s;
#if DEBUG
        inFile >> k >> s;
#else
        cin >> k >> s;
#endif

        subs[i].prerequisite = k;
        subs[i].credit = s;
        subs[k].followups.push_back(i);
    }

    func(&subs[0], m);

    cout << subs[0].sum[m + 1] << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
