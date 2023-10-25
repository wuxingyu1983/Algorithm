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
    unsigned short state;
    bignum cnt;
    unsigned int minUnused;

    Record() {}
};

Record qs[2][QS_SIZE];
int qTail[2];
int h, w;
unordered_map<unsigned short, unsigned int> cnts[2]; // state => index

int act = 0; // 当前生效的 map
int now_x, now_y;
unsigned short gMask = 0;

bignum ans = 0;

#define getVal4St(ST, POS) ((ST) >> ((POS)*ST_BITS)) & ST_MASK

#define setVal4St(NEW, OLD, POS, VAL)                           \
    NEW = OLD;                                                  \
    NEW &= ~(((unsigned long long)ST_MASK) << ((POS)*ST_BITS)); \
    NEW |= ((unsigned long long)(VAL)) << ((POS)*ST_BITS);

inline void addSts(unsigned short st, bignum cnt, int idx)
{
    if (w == now_y)
    {
        st &= gMask;
    }

    int bb[10];
    memset(bb, -1, sizeof(bb));

    unsigned short key = st;

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

    unordered_map<unsigned short, unsigned int>::iterator it = cnts[idx].find(key);
    if (it == cnts[idx].end())
    {
        int pInQ = qTail[idx];
        // 加入队尾
        qs[idx][pInQ].state = key;
        qs[idx][pInQ].cnt = cnt;
        qs[idx][pInQ].minUnused = bn;

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

    gMask = 1 << (w * ST_BITS);
    gMask -= 1;

    cnts[0].clear();
    cnts[1].clear();

    qs[act][0].state = 0;
    qs[act][0].cnt = 1;
    qs[act][0].minUnused = 1;

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

        if (1 == w)
        {
            ans = 1;
            for (size_t i = 0; i < h - 1; i++)
            {
                ans += ans;
            }

            cout << ans << endl;
        }
        else
        {
            h--;
            w--;

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
                    unsigned short st = qs[act][iQ].state;
                    bignum cnt = qs[act][iQ].cnt;
                    unsigned int minUnused = qs[act][iQ].minUnused;

                    if (1 == now_y)
                    {
                        st <<= ST_BITS;
                    }

                    int left = getVal4St(st, now_y - 1);
                    int up = getVal4St(st, now_y);

                    if (1 == now_x && 1 == now_y)
                    {
                        {
                            addSts(st, 2, nAct);
                        }

                        {
                            unsigned short newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 1);
                            addSts(newSt, 3, nAct);
                        }

                        {
                            unsigned short newSt = st;
                            setVal4St(newSt, newSt, now_y, 1);
                            addSts(newSt, 3, nAct);
                        }

                        {
                            unsigned short newSt = st;
                            setVal4St(newSt, newSt, now_y - 1, 1);
                            setVal4St(newSt, newSt, now_y, 1);
                            addSts(newSt, 4, nAct);
                        }
                    }
                    else if (1 == now_y || 1 == now_x)
                    {
                        int val = left + up;
                        if (val)
                        {
                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, cnt, nAct);
                            }

                            bignum tmp = cnt;
                            tmp += cnt;
                            
                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, val);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, tmp, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, val);
                                addSts(newSt, tmp, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, val);
                                setVal4St(newSt, newSt, now_y, val);
                                addSts(newSt, tmp, nAct);
                            }
                        }
                        else
                        {
                            {
                                addSts(st, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, minUnused);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, minUnused);
                                addSts(newSt, cnt, nAct);
                            }

                            bignum tmp = cnt;
                            tmp += cnt;

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, minUnused);
                                setVal4St(newSt, newSt, now_y, minUnused);
                                addSts(newSt, tmp, nAct);
                            }
                        }
                    }
                    else
                    {
                        if (left && up)
                        {
                            if (left != up)
                            {
                                // up ==> left
                                for (int i = 0; i <= w; i++)
                                {
                                    int tmp = getVal4St(st, i);
                                    if (tmp == up)
                                    {
                                        setVal4St(st, st, i, left);
                                    }
                                }
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, left);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, left);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, left);
                                setVal4St(newSt, newSt, now_y, left);
                                addSts(newSt, cnt, nAct);
                            }
                        }
                        else if (left || up)
                        {
                            int val = left + up;

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, val);
                                setVal4St(newSt, newSt, now_y, 0);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, 0);
                                setVal4St(newSt, newSt, now_y, val);
                                addSts(newSt, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, val);
                                setVal4St(newSt, newSt, now_y, val);
                                addSts(newSt, cnt, nAct);
                            }
                        }
                        else
                        {
                            // 0 == left && 0 == up
                            {
                                addSts(st, cnt, nAct);
                            }

                            {
                                unsigned short newSt = st;
                                setVal4St(newSt, newSt, now_y - 1, minUnused);
                                setVal4St(newSt, newSt, now_y, minUnused);
                                addSts(newSt, cnt, nAct);
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
    }

    return 0;
}
