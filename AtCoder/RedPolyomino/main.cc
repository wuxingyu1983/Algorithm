// https://atcoder.jp/contests/abc211/tasks/abc211_e

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
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

#define DEBUG 0
#define MAX_N 8
#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 60000

int n, k;
int h, w;
char cells[MAX_N][MAX_N];

class Record
{
public:
    unsigned int state; // 轮廓线段状态
    unsigned long long cnt[MAX_N];

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned long long sum = 0;

#define getST(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setSt(ST, POS, VAL)              \
    ST &= ~(ST_MASK << ((POS)*ST_BITS)); \
    ST |= (VAL) << ((POS)*ST_BITS);

int main()
{
    cin >> n;
    h = w = n;
    cin >> k;

    for (size_t row = 0; row < h; row++)
    {
        for (size_t col = 0; col < w; col++)
        {
            cin >> cells[row][col];
        }
    }



    return 0;
}
