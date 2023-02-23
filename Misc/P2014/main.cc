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
#define MAX_M       301

class Subject
{
public:
    int credit;
    int prerequisite;
    vector<int> followups;
    int sum[2][MAX_M];  // 0 - not chose, 1 - chose 

    Subject
    {
        credit = prerequisite = 0;
    }
};

Subject subs[MAX_N];

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



#if DEBUG
    inFile.close();
#endif

    return 0;
}
