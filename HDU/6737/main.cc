// https://acm.hdu.edu.cn/showproblem.php?pid=6737

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
#include <assert.h>

using namespace std;

#define MAX_HW 13
#define ST_BITS 4
#define ST_MASK 15
#define QS_SIZE 600000

#define getVal4St(ST, POS) ((ST) >> ((POS) * ST_BITS)) & ST_MASK

#define setVal4St(ST, POS, VAL)                                  \
    ST &= ~(((unsigned long long)ST_MASK) << ((POS) * ST_BITS)); \
    if (VAL)                                                     \
        ST |= ((unsigned long long)VAL) << ((POS) * ST_BITS);

char board[MAX_HW][MAX_HW];
int cost[MAX_HW][MAX_HW];
int h, w, n;
int pos[MAX_HW];

class Record
{
public:
    unsigned long long state;
    int min;

    Record() {}
};

unordered_map<unsigned long long, unsigned int> cnts;
Record qs[QS_SIZE];
int qHead, qTail;

#define IS_EMPTY    (qHead == qTail)
#define IS_FULL     (qHead == ((qTail + 1) % QS_SIZE))

int main()
{
    int ans = -1;

    cin >> n;

    h = w = n;

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> board[row][col];
            if ('.' != board[row][col])
            {
                pos[col] = row;
            }
        }
    }

    for (size_t row = 1; row <= h; row++)
    {
        for (size_t col = 1; col <= w; col++)
        {
            cin >> cost[row][col];
        }
    }

    // init
    unsigned long long st = 0;
    for (size_t i = 1; i <= w; i++)
    {
        if (pos[i])
        {
            setVal4St(st, i, pos[i]);
        }
    }

    if (0 == st)
    {
        ans = 0;
    }
    else
    {
        qs[qTail].state = st;
        qTail++;

        while (false == IS_EMPTY)
        {
            // get head
            st = qs[qHead].state;
            unsigned int min = qs[qHead].min;

            // 取出 head 后赋予一个不可能出现的状态 0xffff
            qs[qHead].state = 0xffff;
            qHead = (qHead + 1) % QS_SIZE;

            int row[MAX_HW];
            for (size_t i = 0; i <= w; i++)
            {
                row[i] = getVal4St(st, i);
            }

            int top[MAX_HW];
            top[0] = 0;
            for (size_t i = 1; i <= w; i++)
            {
                if (row[i] > top[i - 1])
                {
                    top[i] = row[i];
                }
                else
                {
                    top[i] = top[i - 1];
                }
            }

            bool flag = true;
            for (size_t left = 1; left < w; left++)
            {
                for (size_t right = left + 1; right <= w; right++)
                {
                    if (0 < row[left] && row[left] < row[right] && top[left - 1] < row[left] && top[right - 1] < row[right])
                    {
                        if (board[row[left]][left] != board[row[right]][right])
                        {
                            flag = false;

                            unsigned long long newSt = st;
                            // find new left row
                            int newRow;
                            for (newRow = row[left] - 1; newRow >= 1; newRow--)
                            {
                                if ('.' != board[newRow][left])
                                {
                                    break;
                                }
                            }
                            setVal4St(newSt, left, newRow);

                            // find new right row
                            for (newRow = row[right] - 1; newRow >= 1; newRow--)
                            {
                                if ('.' != board[newRow][right])
                                {
                                    break;
                                }
                            }
                            setVal4St(newSt, right, newRow);

                            int tmp = min + abs(cost[row[left]][left] - cost[row[right]][right]);
                            // add newSt, abs(cost[row[left]][left] - cost[row[right]][right])
                            unordered_map<unsigned long long, unsigned int>::iterator it = cnts.find(newSt);
                            if (cnts.end() == it || newSt != qs[it->second].state)
                            {
                                // 重新插入

                                assert(false == IS_FULL);

                                qs[qTail].state = newSt;
                                qs[qTail].min = tmp;
                                cnts[newSt] = qTail;
                                qTail = (qTail + 1) % QS_SIZE;
                            }
                            else
                            {
                                if (tmp < qs[it->second].min)
                                {
                                    qs[it->second].min = tmp;
                                }
                            }

                            if (0 == newSt)
                            {
                                if (0 > ans || ans > tmp)
                                {
                                    ans = tmp;
                                }
                            }
                        }
                    }
                }
            }

            if (flag)
            {
                // 没有合适的一对B和W，只能选一个
                for (size_t idx = 1; idx <= w; idx++)
                {
                    if (0 < row[idx] && top[idx - 1] < row[idx])
                    {
                        unsigned long long newSt = st;
                        // find new left row
                        int newRow;
                        for (newRow = row[idx] - 1; newRow >= 1; newRow--)
                        {
                            if ('.' != board[newRow][idx])
                            {
                                break;
                            }
                        }
                        setVal4St(newSt, idx, newRow);

                        int tmp = min + cost[row[idx]][idx];

                        unordered_map<unsigned long long, unsigned int>::iterator it = cnts.find(newSt);
                        if (cnts.end() == it || newSt != qs[it->second].state)
                        {
                            // 重新插入

                            assert(false == IS_FULL);

                            qs[qTail].state = newSt;
                            qs[qTail].min = tmp;
                            cnts[newSt] = qTail;
                            qTail = (qTail + 1) % QS_SIZE;
                        }
                        else
                        {
                            if (tmp < qs[it->second].min)
                            {
                                qs[it->second].min = tmp;
                            }
                        }

                        if (0 == newSt)
                        {
                            if (0 > ans || ans > tmp)
                            {
                                ans = tmp;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}
