// https://community.topcoder.com/stat?c=problem_statement&pm=10524
// https://archive.topcoder.com/ProblemStatement/pm/10524

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
#include <unordered_set>

using namespace std;

#define MAX_NM  22
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 1000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

unordered_set<unsigned long long> cnts[MAX_NM][MAX_NM];

int row, col;
unsigned int sts[MAX_NM + 1];
unsigned int endSt;

inline bool addSts(unsigned int curr, unsigned int next, int r, int c)
{
    if (endSt == curr)
    {
        // 当前行已经没有空白位置了
        // 找到下一个还有空白位置的 行
        while (curr == endSt && (++r) <= (row - 1))
        {
            c = 0;
            curr = next;
            next = sts[r + 1];
        }

        if (r == row)
        {
            return true;
        }
    }

    while (getVal4St(curr, c, ST_BITS, ST_MASK))
    {
        c++;
    }

    unsigned long long key = (((unsigned long long)curr) << MAX_NM) + next;
    auto it = cnts[r][c].find(key);
    if (it == cnts[r][c].end())
    {
        cnts[r][c].insert(key);
    }

    return false;
}

class BrickPuzzle
{
public:
    int leastShapes(vector<string> &board)
    {
        int ret = -1;

        row = board.size();
        col = board[0].length();

        endSt = (1 << col) - 1;

        memset(sts, 0, sizeof(sts));

        int whiteCnt = 0;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if ('X' == board[i].at(j))
                {
                    // black
                    setVal4St(sts[i], j, 1, ST_BITS, ST_MASK);
                }
                else
                {
                    // white
                    whiteCnt ++;
                }
            }
        }
         
        if (0 == (whiteCnt % 4))
        {
            for (size_t i = row; i <= MAX_NM; i++)
            {
                sts[i] = endSt;
            }
            

        }

        return ret;
    }

private:
};

int main()
{
    vector<string> strs = {"..XX....", "....X..X", "XX..XXXX"};

    BrickPuzzle s;
    cout << s.leastShapes(strs) << endl;


    return 0;
}
