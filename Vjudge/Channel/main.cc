// https://vjudge.net/problem/UVALive-4789
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=257&page=show_problem&problem=3535

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
#define MAX_H 21
#define MAX_W 10
#define QS_SIZE 1000000

const unsigned int ST1_BITS = 2;
const unsigned long long ST1_MASK = 3;

#define getVal4St1(ST, POS) (((ST) >> ((POS) * ST1_BITS)) & ST1_MASK)

#define setVal4St1(ST, POS, VAL)             \
    ST &= ~(ST1_MASK << ((POS) * ST1_BITS)); \
    if (VAL)                                 \
        ST |= (VAL) << ((POS) * ST1_BITS);

#define getVal4St2(ST, POS) (((ST) >> (POS)) & 1)

#define setVal4St2(ST, POS, VAL) \
    ST &= ~(1 << (POS));         \
    if (VAL)                     \
        ST |= (VAL) << (POS);

class Record
{
public:
    unsigned int key;
    unsigned int state1;
    unsigned short state2;
    unsigned short len; 

    char cache[MAX_H][MAX_W];

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts;
int act = 0; // 当前生效的 queue 
int now_x, now_y;
unsigned short st2Mask;

inline void init()
{
    act = 0;

    now_x = 0;
    now_y = w;

    st2Mask = (1 << w) - 1;

    cnts.clear();

    qs[act][0].state1 = 0;
    qs[act][0].state2 = 0;
    qs[act][0].key = 0;
    qs[act][0].len = 0;
    memset(qs[act][0].cache, 0, sizeof(qs[act][0].cache));

    qTail[0] = 1;
    qTail[1] = 0;
}

int main()
{
    scanf("%d %d", &h, &w);

    if (0 < h && 0 < w)
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                scanf("%c", &(cells[row][col]));
            }
        }

        init();


    }

    return 0;
}
