// https://vjudge.net/problem/HDU-3958
// https://acm.hdu.edu.cn/showproblem.php?pid=3958

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
#define MAX_W 10
#define MAX_H 21
#define ST1_BITS 2
#define ST1_MASK 3
#define ST2_BITS 1
#define ST2_MASK 1
#define QS_SIZE 60000

class Record
{
public:
    unsigned int state1;   // 轮廓线段状态
    unsigned short state2; // 轮廓cells状态
    unsigned int len;
    char grid[MAX_H][MAX_W]; // 满足当前 state 状态下的 一组 可能的 grid

    Record() {}
};

char cells[MAX_H][MAX_W];
Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map
int now_x, now_y;

int main()
{


    return 0;
}
