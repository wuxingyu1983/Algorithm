// https://oj.uz/problem/view/CEOI06_connect

#include <cmath>
#include <cstdio>
#include <vector>
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
#define MAX_H 80
#define MAX_W 26
#define ST_BITS 2
#define ST_MASK 3
#define QS_SIZE 600000

class Record
{
public:
    unsigned int state;
    unsigned int score;

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)            \
    ST &= ~(ST_MASK << ((POS) * ST_BITS)); \
    if (VAL)                               \
        ST |= (VAL) << ((POS) * ST_BITS);

int main()
{
    bool bSwitch = false;    

    cin >> h >> w;

    if (h < w)
    {
        swap(h, w);
        bSwitch = true;

        for (size_t col = 1; col <= w; col++)
        {
            for (size_t row = 1; row <= h; row++)
            {
                cin >> cells[row][col];
            }
        }
    }
    else
    {
        for (size_t row = 1; row <= h; row++)
        {
            for (size_t col = 1; col <= w; col++)
            {
                cin >> cells[row][col];
            }
        }
    }

    return 0;
}
