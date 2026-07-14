// https://tlx.toki.id/problems/icpc-jakarta-2022/A

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
#include <unordered_map>
#include <utility>

using namespace std;

const int MAX_N = 100;
char cells[MAX_N][3];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    int usable = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> cells[j][i];

            if ('.' == cells[j][i])
            {
                usable ++;
            }
        }

        cin.ignore();
    }

    if (usable < k)
    {
        cout << -1 << "\n";
        return 0;
    }

    
    

    return 0;
}
