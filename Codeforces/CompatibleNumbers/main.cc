// https://codeforces.com/problemset/problem/165/E

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

#define MAX_N   1000000
#define MAX_A   4000002

#define ST_BITS 1
#define ST_MASK 1

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

class Node
{
public:
    Node * ptr0;
    Node * ptr1;
    unsigned int val;

    Node() {ptr0 = NULL; ptr1 = NULL; val = 0;}
};

Node root;
int n;
vector<int> as;
int cmpNums[MAX_A];

int main()
{
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        as.push_back(a);
    }

    // init
    memset(cmpNums, -1, sizeof(cmpNums));

    // build tree
    for (size_t i = 0; i < n; i++)
    {
        int a = as[i];

        Node * curr = &root;
        for (size_t pos = 0; pos < 22; pos++)
        {
            if (getVal4St(a, pos, ST_BITS, ST_MASK))
            {
                // 1
                if (NULL == curr->ptr1)
                {
                    curr->ptr1 = new Node();

                    if (a < (1 << (pos + 1)))
                    {
                        // pos 已经是最高位了
                        curr->val = a;
                        break;
                    }
                    else
                    {
                        curr = curr->ptr1;
                    }
                }
            }
            else
            {
                // 0
                if (NULL == curr->ptr0)
                {
                    curr->ptr0 = new Node();
                    curr = curr->ptr0;
                }
            }
        }
    }
    

    return 0;
}
