// https://codeforces.com/contest/417/problem/D

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
#define MAX_N   100
#define MAX_M   20
#define MAX_2M  1048576
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 2000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

unsigned short n, m;
unsigned long long b;

class Friend
{
public:
    unsigned long long x;   // the desired amount of money
    unsigned long long k;   // monitors
    unsigned int canSolve;  // the numbers of problems that the friend can solve 

    Friend() { canSolve = 0; }
};

Friend friends[MAX_N];

int main()
{
    cin >> n >> m >> b;

    for (size_t i = 0; i < n; i++)
    {
        int slv;

        cin >> friends[i].x >> friends[i].k >> slv;

        for (size_t j = 0; j < slv; j++)
        {
            int problem;

            cin >> problem;
            problem --;

            setVal4St(friends[i].canSolve, problem, 1, ST_BITS, ST_MASK); 
        }
    }
    

    return 0;
}
