// https://www.spoj.com/problems/CAKE3/en/

#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <queue>
#include <stack>
#include <climits>
#include <cfloat>
#include <limits>
#include <list>

using namespace std;

#define ST_BITS 3
#define ST_MASK 7
#define QS_SIZE 50000

namespace BIGNUM
{

    const int __base = 1e8;
    const int MAX_BUF_SIZE = 109;
    char __buf[MAX_BUF_SIZE];

    class bignum
    {
        friend istream &operator>>(istream &, bignum &);
        friend ostream &operator<<(ostream &, const bignum &);
        friend bignum operator+(const bignum &, const bignum &);
        friend bignum operator+(const bignum &, const int &);
        friend bool operator==(const bignum &, const bignum &);
        friend bool operator!=(const bignum &, const bignum &);
        friend bool operator<(const bignum &, const bignum &);
        friend bool operator>(const bignum &, const bignum &);
        friend bool operator<=(const bignum &, const bignum &);
        friend bool operator>=(const bignum &, const bignum &);
        friend bool operator==(const bignum &, const int &);
        friend bool operator!=(const bignum &, const int &);
        friend bool operator<(const bignum &, const int &);
        friend bool operator>(const bignum &, const int &);
        friend bool operator<=(const bignum &, const int &);
        friend bool operator>=(const bignum &, const int &);
        friend int do_comp(const bignum &, const int &);
        friend int do_comp(const bignum &, const bignum &);
        friend void divide(const bignum &, const bignum &, bignum &, bignum &);
        friend bignum pow(bignum, int);
        friend bignum pow(int, int);

    public:
        inline bignum(){};
        inline bignum(int s)
        {
            while (s)
                data.push_back(s % __base), s /= __base;
            if (data.empty())
                data.push_back(0);
        }

        inline bignum(long long s)
        {
            while (s)
                data.push_back(int(s % __base)), s /= __base;
            if (data.empty())
                data.push_back(0);
        }

        inline bignum(string s)
        {
            int t, i;
            data.clear();
            for (i = int(s.size()) - 8; i > 0; i -= 8)
            {
                istringstream(s.substr(i, 8)) >> t;
                data.push_back(t);
            }
            istringstream(s.substr(0, i + 8)) >> t;
            data.push_back(t);
        }

        bignum &operator=(int);
        bignum &operator=(const string &);
        bignum &operator=(const bignum &);
        bignum &operator+=(const bignum &);
        bignum &operator-=(const bignum &);
        bignum &operator*=(const bignum &);
        bignum &operator/=(const bignum &);
        bignum &operator%=(const bignum &);
        bignum &operator+=(const int &);
        bignum &operator-=(const int &);
        bignum &operator*=(const int &);
        bignum &operator/=(const int &);
        bignum &operator%=(const int &);
        bool undefined();
        int do_try(const int &);
        int do_try(const bignum &);
        void do_trim();
        list<int> data;

        int size()
        {
            list<int>::iterator it;
            int res = 0;
            for (it = data.begin(); it != data.end(); it++)
                res += 8;
            it--;
            if (*it >= 10000)
            {
                if ((*it) >= 1000000)
                {
                    if (*it >= 10000000)
                        ;
                    else
                        res--;
                }
                else
                {
                    if ((*it) >= 100000)
                        res -= 2;
                    else
                        res -= 3;
                }
            }
            else if ((*it) >= 100)
            {
                if (*it >= 1000)
                    res -= 4;
                else
                    res -= 5;
            }
            else
            {
                if ((*it) >= 10)
                    res -= 6;
                else
                    res -= 7;
            }

            return res;
        }

        void do_reserve(int a)
        {
            if (a <= 0)
                return;
            list<int>::iterator it;
            for (it = data.begin(); it != data.end() && a > 0; it++)
                a -= 8;
            if (it == data.end() && a >= 0)
                return;
            a += 8, it--;
            int f = 1;
            for (int i = 0; i < a; i++)
                f *= 10;
            (*it) %= f;
            data.erase(++it, data.end());
            do_trim();
        }
    };

    inline bignum &bignum::operator=(const bignum &a)
    {
        data.clear();
        for (list<int>::const_iterator i = a.data.begin(); i != a.data.end(); i++)
        {
            data.push_back(*i);
        }
        return *this;
    }
    inline bignum &bignum::operator=(const string &a)
    {
        return *this = bignum(a);
    }
    inline bignum &bignum::operator=(int a)
    {
        return *this = bignum(a);
    }

    inline istream &operator>>(istream &input, bignum &a)
    {
        string s;
        int t, i;
        input >> s;
        a.data.clear();
        for (i = int(s.size()) - 8; i > 0; i -= 8)
        {
            istringstream(s.substr(i, 8)) >> t;
            a.data.push_back(t);
        }
        istringstream(s.substr(0, i + 8)) >> t;
        a.data.push_back(t);
        return input;
    }

    inline ostream &operator<<(ostream &output, const bignum &a)
    {
        list<int>::const_reverse_iterator i = a.data.rbegin();
        output << *i;
        for (i++; i != a.data.rend(); i++)
        {
            if (*i >= 10000)
            {
                if (*i >= 1000000)
                {
                    if (*i >= 10000000)
                        cout << *i;
                    else
                        cout << 0 << *i;
                }
                else
                {
                    if (*i >= 100000)
                        cout << "00" << *i;
                    else
                        cout << "000" << *i;
                }
            }
            else
            {
                if (*i >= 100)
                {
                    if (*i >= 1000)
                        cout << "0000" << *i;
                    else
                        cout << "00000" << *i;
                }
                else
                {
                    if (*i >= 10)
                        cout << "000000" << *i;
                    else
                        cout << "0000000" << *i;
                }
            }
        }
        return output;
    }

    inline bool bignum::undefined()
    {
        return data.empty();
    }

    inline int do_comp(const bignum &a, const bignum &b)
    {
        if (a.data.size() < b.data.size())
            return -1;
        if (a.data.size() > b.data.size())
            return 1;
        list<int>::const_reverse_iterator i;
        list<int>::const_reverse_iterator j;
        for (i = a.data.rbegin(), j = b.data.rbegin(); j != b.data.rend(); i++, j++)
        {
            if (*i < *j)
                return -1; //!!!!
            if (*i > *j)
                return 1;
        }
        return 0;
    }
    inline int do_comp(const bignum &a, const int &b)
    {
        return do_comp(a, bignum(b));
    }

    inline bool operator==(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) == 0;
    }
    inline bool operator!=(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) != 0;
    }
    inline bool operator<(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) == -1;
    }
    inline bool operator>(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) == 1;
    }
    inline bool operator<=(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) != 1;
    }
    inline bool operator>=(const bignum &a, const bignum &b)
    {
        return do_comp(a, b) != -1;
    }

    inline bool operator==(const bignum &a, const int &b)
    {
        return do_comp(a, b) == 0;
    }
    inline bool operator!=(const bignum &a, const int &b)
    {
        return do_comp(a, b) != 0;
    }
    inline bool operator<(const bignum &a, const int &b)
    {
        return do_comp(a, b) == -1;
    }
    inline bool operator>(const bignum &a, const int &b)
    {
        return do_comp(a, b) == 1;
    }
    inline bool operator<=(const bignum &a, const int &b)
    {
        return do_comp(a, b) != 1;
    }
    inline bool operator>=(const bignum &a, const int &b)
    {
        return do_comp(a, b) != -1;
    }

    inline void bignum::do_trim()
    {
        while (data.size() > 1 && data.back() == 0)
            data.pop_back();
    }

    inline bignum &bignum::operator+=(const bignum &a)
    {
        list<int>::iterator i;
        list<int>::const_iterator j;
        int t = 0;
        for (i = data.begin(), j = a.data.begin(); i != data.end() && j != a.data.end(); i++, j++)
        {
            *i += *j + t;
            t = *i / __base;
            *i %= __base;
        }
        while (i != data.end())
        {
            *i += t;
            t = *i / __base;
            *i %= __base;
            i++;
        }
        while (j != a.data.end())
        {
            data.push_back(t + *j);
            t = data.back() / __base;
            data.back() %= __base;
            j++;
        }
        if (t != 0)
            data.push_back(t);
        return *this;
    }

    inline bignum &bignum::operator+=(const int &a)
    {
        return (*this) += bignum(a);
    }

    inline bignum operator+(const bignum &a, const bignum &b)
    {
        list<int>::const_iterator i, j;
        bignum c;
        int t = 0;
        for (i = a.data.begin(), j = b.data.begin(); i != a.data.end() && j != b.data.end(); i++, j++)
        {
            c.data.push_back(t + *i + *j);
            t = c.data.back() / __base;
            c.data.back() %= __base;
        }
        while (i != a.data.end())
        {
            c.data.push_back(t + *i);
            t = c.data.back() / __base;
            c.data.back() %= __base;
            i++;
        }
        while (j != b.data.end())
        {
            c.data.push_back(t + *j);
            t = c.data.back() / __base;
            c.data.back() %= __base;
            j++;
        }
        if (t != 0)
            c.data.push_back(t);
        return c;
    }

    inline bignum operator+(const bignum &a, const int &b)
    {
        return a + bignum(b);
    }
}

using namespace BIGNUM;

class Record
{
public:
    unsigned int state;
    unsigned int block;
    bignum cnt;
    unsigned int nxtClr;
    unsigned char nxtBlk[8];

    Record()
    {
        memset(nxtBlk, 0, sizeof(nxtBlk));
    }
};

Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned int, unsigned int> cnts[2]; // state => index

int act = 0; // 当前生效的 map
int now_x, now_y;

bignum ans = 0;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)     \
    NEW = OLD;                            \
    NEW &= ~(ST_MASK << ((POS)*ST_BITS)); \
    NEW |= (VAL) << ((POS)*ST_BITS);

inline void addSts(unsigned int st, bignum cnt, int idx)
{
    int bb[10];
    memset(bb, -1, sizeof(bb));

    unsigned int key = st;

    int bn = 1;
    bb[0] = 0;
    for (int i = 0; i <= w; i++)
    {
        int tmp = getVal4St(st, i);
        if (0 < tmp)
        {
            if (0 > bb[tmp])
            {
                bb[tmp] = bn++;
            }
            setVal4St(key, key, i, bb[tmp]);
        }
    }

    unordered_map<unsigned int, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = key;
        qs[idx][pInQ].cnt = cnt;
        qs[idx][pInQ].nxtClr = bn;

        cnts[idx][key] = pInQ;
        qTail[idx]++;
    }
    else
    {
        qs[idx][it->second].cnt += cnt;
    }
}

inline void init()
{
    act = 0;

    qTail[0] = 0;
    qTail[1] = 0;

    now_x = 0;
    now_y = w;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state = 0;
    qs[act][0].cnt = 1;
    qs[act][0].nxtClr = 1;
    for (size_t i = 1; i <= w; i++)
    {
        qs[act][0].nxtBlk[i] = 1;
    }

    qTail[act]++;

    ans = 0;
}

int main()
{
    int t;
    cin >> t;

    while (0 < t--)
    {
        string str;
        getline(cin, str);

        cin >> h >> w;

        if (h < w)
        {
            swap(h, w);
        }

        init();

        while (0 < qTail[act])
        {
            int nAct = 1 - act;

            if (w == now_y)
            {
                now_x++;
                now_y = 1;

                if (h < now_x)
                {
                    // finished
                    for (size_t iQ = 0; iQ < qTail[act]; iQ++)
                    {
                        ans += qs[act][iQ].cnt;
                    }

                    break;
                }
            }
            else
            {
                now_y++;
            }

            for (size_t iQ = 0; iQ < qTail[act]; iQ++)
            {
                unsigned int st = qs[act][iQ].state;
                bignum cnt = qs[act][iQ].cnt;
                unsigned int blk = qs[act][iQ].block;
                unsigned int nxtClr = qs[act][iQ].nxtClr;

                int left = getVal4St(st, now_y - 1);
                int up = getVal4St(st, now_y);

                unsigned int newSt;

                bool flag = false;       // 是否能阻断 up 的 block

                if (up)
                {
                    // 当前 cell 同 up
                    if (left == up)
                    {
                        // left, up 合并
                    }
                    else
                    {
                    }

                    {
                        if (2 < qs[act][iQ].nxtBlk[up])
                        {
                            // up 颜色至少 2 个 block
                            int upBlk = getVal4St(blk, now_y);
                            int tmpCnt = 0;

                            for (size_t i = 1; i <= w; i++)
                            {
                                if (up == (getVal4St(st, i)))
                                {
                                    if (upBlk == (getVal4St(blk, i)))
                                    {
                                        tmpCnt++;
                                        if (1 < tmpCnt)
                                        {
                                            flag = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            flag = true;
                        }
                    }
                }
                else
                {
                    flag = true;
                }

                // 当前 cell 同 left
                if (left && flag)
                {

                }

                // 当前 cell 非 left, up
                if (flag)
                {
                    for (size_t clr = 1; clr <= nxtClr; clr++)
                    {
                        if (clr != left && clr != up)
                        {
                        }
                    }
                }
            }

            qTail[act] = 0;
            cnts[act].clear();
            act = nAct;
        }

        cout << ans << endl;
    }

    return 0;
}
