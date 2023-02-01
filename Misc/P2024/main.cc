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

#define DEBUG 1

int main()
{
#if DEBUG
    ifstream inFile;
    inFile.open("input.txt");
#endif

    unsigned int n, k;
#if DEBUG
    inFile >> n >> k;
#else
    cin >> n >> k;
#endif

    unsigned int cnt = 0;
    for (size_t i_k = 0; i_k < k; i_k++)
    {
        unsigned int op, x, y;
#if DEBUG
        inFile >> op >> x >> y;
#else
        cin >> op >> x >> y;
#endif

        if (n < x || n < y)
        {
            cnt ++;
            continue;
        }

        if (1 == op)
        {
            if (x != y)
            {
                
            }
        }
        else
        {
            if (x == y)
            {
                cnt ++;
                continue;
            }
        }
    }

    cout << cnt << endl;

#if DEBUG
    inFile.close();
#endif

    return 0;
}
