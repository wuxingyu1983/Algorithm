// https://atcoder.jp/contests/abc369/tasks/abc369_f

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
#include <map>

using namespace std;

class Cell
{
public:
    int r, c;
};

bool myfunc(Cell &x, Cell &y)
{
    bool bRet = false;

    if (x.r < y.r)
    {
        bRet = true;
    }
    else if (x.r == y.r)
    {
        if (x.c < y.c)
        {
            bRet = true;
        }
    }

    return bRet;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, n;
    cin >> h >> w >> n;

    vector<Cell> cells;
    for (size_t i = 0; i < n; i++)
    {
        int r, c;
        cin >> r >> c;

        Cell cell;
        cell.r = r;
        cell.c = c;

        cells.push_back(cell);
    }
    
    sort(cells.begin(), cells.end(), myfunc);
    
    return 0;
}
