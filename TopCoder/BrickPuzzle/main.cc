// https://community.topcoder.com/stat?c=problem_statement&pm=10524
// https://archive.topcoder.com/ProblemStatement/pm/10524

#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

#define MAX_NM  22
#define ST_BITS 1
#define ST_MASK 1
#define QS_SIZE 20000000

#define getVal4St(ST, POS, BITS, MASK) (((ST) >> (POS) * BITS) & MASK)

#define setVal4St(ST, POS, VAL, BITS, MASK) \
    ST &= ~(MASK << ((POS) * BITS));        \
    if (VAL)                                \
        ST |= (VAL) << ((POS) * BITS);

class Record
{
public:
    unsigned int curr;
    unsigned int next;
    unsigned int cnt;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
unordered_map<unsigned long long, unsigned int> cnts[2];
int act = 0; // 当前生效的 map

int row, col;
unsigned int sts[MAX_NM];
unsigned int endSt;

inline bool addSts(unsigned int curr, unsigned int next, unsigned int cnt, unsigned int idx)
{
    unsigned long long key = (((unsigned long long)curr) << MAX_NM) + next;
    unordered_map<unsigned long long, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].curr = curr;
        qs[idx][pInQ].next = next;
        qs[idx][pInQ].cnt = cnt;

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        if (cnt < qs[idx][it->second].cnt)
        {
            qs[idx][it->second].cnt = cnt;
        }
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

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if ('X' == board[i].at(j))
                {
                    // black
                    setVal4St(sts[i], j, 1, ST_BITS, ST_MASK);
                }
            }
        }

        // init
        qTail[0] = 0;
        qTail[1] = 0;

        cnts[0].clear();
        cnts[1].clear();

        qs[act][0].curr = 0;
        if (1 < row)
        {
            qs[act][0].next = 0;
        }
        else
        {
            qs[act][0].next = endSt;
        }
        qs[act][0].cnt = 0;

        qTail[act]++;

        int nowR = 0, nowC = 0;

        while (qTail[act])
        {
            int nAct = 1 - act;

            if (nowR == row)
            {
                for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                {
                    unsigned int cnt = qs[act][iQ].cnt;
                    if (0 > ret || ret > cnt)
                    {
                        ret = cnt;
                    }
                }
                break;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int curr = qs[act][iQ].curr; // nowR th row
                unsigned int next = qs[act][iQ].next; // nowR+1 th row
                unsigned int cnt = qs[act][iQ].cnt;

                if (getVal4St((curr | sts[nowR]), nowC, ST_BITS, ST_MASK))
                {
                    // 可以什么都不做 传给下一个
                    if (nowC == col - 1)
                    {
                        // 已经是最后一列了
                        if (nowR + 1 < row)
                        {
                            addSts(next, 0, cnt, nAct);
                        }
                        else
                        {
                            addSts(next, endSt, cnt, nAct);
                        }
                    }
                    else
                    {
                        addSts(curr, next, cnt, nAct);
                    }
                }

                // 0000
                {
                    if (nowC + 3 < col)
                    {
                        bool check = true;
                        int blacks = 0;
                        for (size_t pos = nowC; pos <= nowC + 3; pos++)
                        {
                            if (getVal4St(curr, pos, ST_BITS, ST_MASK))
                            {
                                // 已经被 brick 覆盖了
                                check = false;
                                break;
                            }

                            if (getVal4St(sts[nowR], pos, ST_BITS, ST_MASK))
                            {
                                blacks ++;
                            }
                        }

                        if (check && 4 > blacks)
                        {
                            unsigned int newCurr = curr;
                            for (size_t pos = nowC; pos <= nowC + 3; pos++)
                            {
                                setVal4St(newCurr, pos, 1, ST_BITS, ST_MASK);
                            }

                            addSts(newCurr, next, cnt + 1, nAct);
                        }
                    }
                }

                {
                    if (nowR + 1 < row)
                    {
                        //      00
                        //      00
                        if (nowC + 1 < col)
                        {
                            bool check = true;
                            int blacks = 0;
                            for (size_t pos = nowC; pos <= nowC + 1; pos++)
                            {
                                if (getVal4St(curr, pos, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }

                                if (getVal4St(next, pos, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }

                                if (getVal4St(sts[nowR], pos, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }

                                if (getVal4St(sts[nowR + 1], pos, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }
                            }

                            if (check && 4 > blacks)
                            {
                                unsigned int newCurr = curr;
                                unsigned int newNext = next;
                                for (size_t pos = nowC; pos <= nowC + 1; pos++)
                                {
                                    setVal4St(newCurr, pos, 1, ST_BITS, ST_MASK);
                                    setVal4St(newNext, pos, 1, ST_BITS, ST_MASK);
                                }

                                addSts(newCurr, newNext, cnt + 1, nAct);
                            }
                        }

                        //  00
                        //   00
                        if (nowC + 2 < col)
                        {
                            bool check = true;
                            int blacks = 0;
                            for (size_t pos = nowC; pos <= nowC + 1; pos++)
                            {
                                if (getVal4St(curr, pos, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }
                                
                                if (getVal4St(sts[nowR], pos, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }

                                if (getVal4St(next, pos + 1, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }
                                
                                if (getVal4St(sts[nowR + 1], pos + 1, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }
                            }

                            if (check && 4 > blacks)
                            {
                                unsigned int newCurr = curr;
                                unsigned int newNext = next;
                                for (size_t pos = nowC; pos <= nowC + 1; pos++)
                                {
                                    setVal4St(newCurr, pos, 1, ST_BITS, ST_MASK);
                                    setVal4St(newNext, pos + 1, 1, ST_BITS, ST_MASK);
                                }

                                addSts(newCurr, newNext, cnt + 1, nAct);
                            }
                        }

                        //   00
                        //  00
                        if (0 < nowC && nowC + 1 < col)
                        {
                            bool check = true;
                            int blacks = 0;
                            for (size_t pos = nowC; pos <= nowC + 1; pos++)
                            {
                                if (getVal4St(curr, pos, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }
                                
                                if (getVal4St(sts[nowR], pos, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }

                                if (getVal4St(next, pos - 1, ST_BITS, ST_MASK))
                                {
                                    // 已经被 brick 覆盖了
                                    check = false;
                                    break;
                                }
                                
                                if (getVal4St(sts[nowR + 1], pos - 1, ST_BITS, ST_MASK))
                                {
                                    blacks ++;
                                }
                            }

                            if (check && 4 > blacks)
                            {
                                unsigned int newCurr = curr;
                                unsigned int newNext = next;
                                for (size_t pos = nowC; pos <= nowC + 1; pos++)
                                {
                                    setVal4St(newCurr, pos, 1, ST_BITS, ST_MASK);
                                    setVal4St(newNext, pos - 1, 1, ST_BITS, ST_MASK);
                                }

                                addSts(newCurr, newNext, cnt + 1, nAct);
                            }
                        }
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;

            if (nowC + 1 < col)
            {
                nowC ++;
            }
            else
            {
                nowC = 0;
                nowR ++;
            }
        }

        return ret;
    }

private:
};

std::vector<std::string> splitString(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delimiter))
    {
        tokens.push_back(item);
    }

    return tokens;
}

int main()
{
    string raw;
    cin >> raw;

    vector<string> strs = splitString(raw, ',');

    BrickPuzzle s;
    cout << s.leastShapes(strs) << endl;

    return 0;
}
