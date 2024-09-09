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
#include <unordered_map>

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

class Record
{
public:
    unsigned int curr;  // 当前行
    unsigned int next;  // 下一行 

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map

class BrickPuzzle
{
public:
    int leastShapes(vector<string> &board)
    {
        int ret = -1;

        row = board.size();
        col = board[0].length();

        int endSt = (1 << col) - 1;

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
            
        }

        return ret;
    }

private:
    int row, col;
    unsigned int sts[MAX_NM];
};

int main()
{
    vector<string> strs = {"..XX....", "....X..X", "XX..XXXX"};

    BrickPuzzle s;
    cout << s.leastShapes(strs) << endl;


    return 0;
}
