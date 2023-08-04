// https://www.luogu.com.cn/problem/P4262

#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <bitset>

using namespace std;

#define DEBUG       0
#define MAX_MN      18
#define BITS        1
#define MASK        1
#define QS_SIZE     132000

#define getState(ST, POS) ((ST) >> ((POS) * BITS)) & MASK

#define setState(ST, POS, VAL)       \
    ST &= ~((MASK) << ((POS)*BITS)); \
    ST |= (VAL) << ((POS)*BITS);

int n, m;
unsigned char cells[MAX_MN][MAX_MN];

class Record
{
public:
    int state;   // 轮廓线状态
    int sums[MAX_MN][MAX_MN];

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];

unordered_map<int, int> cnts[2];
int act = 0;                  // 当前生效的 map

int main()
{
    cin >> n >> m;

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= m; j++)
        {
            cin >> cells[i][j];
        }
    }

    

    return 0;
}
