// https://www.luogu.com.cn/problem/P3959
// 状压DP

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
#include <cstring>

using namespace std;

#define MAX_N 12
#define MAX_2N 4096
#define MAX_M 1000
#define QS_SIZE 100000

class Line
{
public:
    int connect;
    int length;

    Line(int _connect, int _length) : connect(_connect), length(_length) {}
};

vector<Line> lines[MAX_N + 1];

class Record
{
public:
    int state;  // layer + st1 + st2;
    int cost;
    
    Record() {}
};

Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY (qHead == qTail)
#define IS_FULL (qHead == ((qTail + 1) % QS_SIZE))

unordered_map<int, int> mps[MAX_N];

int n, m;

int main()
{
    cin >> n >> m;

    for (size_t i = 0; i < m; i++)
    {
        int src, dst, len;
        cin >> src >> dst >> len;

        lines[src].push_back(Line(dst, len));
        lines[dst].push_back(Line(src, len));
    }

    // init
    for (size_t i = 0, st = 1; i < n; i++, st <<= 1)
    {
        qs[qTail].state = st | (st << n);
        qTail++;
    }

    int ans = -1;

    cout << ans << endl;

    return 0;
}
