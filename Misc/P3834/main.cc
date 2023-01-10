#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#define DEBUG 0

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

    vector<int> raw(n);

    for (size_t i_n = 0; i_n < n; i_n++)
    {
#if DEBUG
        inFile >> raw[i_n];
#else
        cin >> raw[i_n];
#endif
    }

    // sort
    sort(raw.begin(), raw.end());

    vector<int> nums;

    // duplicate removal
    for (vector<int>::iterator it = raw.begin(), pre = raw.end(); it != raw.end(); it ++)
    {
        if (pre == raw.end() || *pre != *it)
        {
            nums.push_back(*it);
        }

        pre = it; 
    }
    


#if DEBUG
    inFile.close();
#endif

    return 0;
}
