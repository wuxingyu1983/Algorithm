/*
    This code has been written by MinakoKojima, feel free to ask me question. Blog: https://www.shuizilong.com/house
    Template Date: 2015.10.12
    Note: ...
*/

#pragma comment(linker, "/STACK:36777216")
// #pragma GCC optimize ("O2")
#define LOCAL
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <cstring>
#include <climits>
#include <cassert>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <ctime>
#include <list>
#include <set>
#include <map>

// #include <tr1/unordered_set>
// #include <tr1/unordered_map>
// #include <array>

using namespace std;

#define REP(i, n) for (int i = 0; i < n; ++i)
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define DWN(i, b, a) for (int i = b - 1; i >= a; --i)
#define REP_1(i, n) for (int i = 1; i <= n; ++i)
#define FOR_1(i, a, b) for (int i = a; i <= b; ++i)
#define DWN_1(i, b, a) for (int i = b; i >= a; --i)
#define REP_C(i, n) for (int n____ = n, i = 0; i < n____; ++i)
#define FOR_C(i, a, b) for (int b____ = b, i = a; i < b____; ++i)
#define DWN_C(i, b, a) for (int a____ = a, i = b - 1; i >= a____; --i)
#define REP_N(i, n) for (i = 0; i < n; ++i)
#define FOR_N(i, a, b) for (i = a; i < b; ++i)
#define DWN_N(i, b, a) for (i = b - 1; i >= a; --i)
#define REP_1_C(i, n) for (int n____ = n, i = 1; i <= n____; ++i)
#define FOR_1_C(i, a, b) for (int b____ = b, i = a; i <= b____; ++i)
#define DWN_1_C(i, b, a) for (int a____ = a, i = b; i >= a____; --i)
#define REP_1_N(i, n) for (i = 1; i <= n; ++i)
#define FOR_1_N(i, a, b) for (i = a; i <= b; ++i)
#define DWN_1_N(i, b, a) for (i = b; i >= a; --i)
#define REP_C_N(i, n) for (int n____ = (i = 0, n); i < n____; ++i)
#define FOR_C_N(i, a, b) for (int b____ = (i = 0, b); i < b____; ++i)
#define DWN_C_N(i, b, a) for (int a____ = (i = b - 1, a); i >= a____; --i)
#define REP_1_C_N(i, n) for (int n____ = (i = 1, n); i <= n____; ++i)
#define FOR_1_C_N(i, a, b) for (int b____ = (i = a, b); i <= b____; ++i)
#define DWN_1_C_N(i, b, a) for (int a____ = (i = b, a); i >= a____; --i)

#define ECH(it, A) for (__typeof((A).begin()) it = (A).begin(); it != (A).end(); ++it)
#define rECH(it, A) for (__typeof((A).rbegin()) it = (A).rbegin(); it != (A).rend(); ++it)
#define REP_S(i, str) for (char *i = str; *i; ++i)
#define REP_L(i, hd, suc) for (int i = hd; i; i = suc[i])
#define REP_G(i, u) REP_L(i, hd[u], suc)
#define REP_SS(x, s) for (int x = s; x; x = (x - 1) & s)
#define DO(n) for (int ____n = n; ____n-- > 0;)
#define REP_2(i, j, n, m) REP(i, n) REP(j, m)
#define REP_2_1(i, j, n, m) REP_1(i, n) REP_1(j, m)
#define REP_3(i, j, k, n, m, l) REP(i, n) REP(j, m) REP(k, l)
#define REP_3_1(i, j, k, n, m, l) REP_1(i, n) REP_1(j, m) REP_1(k, l)
#define REP_4(i, j, k, ii, n, m, l, nn) REP(i, n) REP(j, m) REP(k, l) REP(ii, nn)
#define REP_4_1(i, j, k, ii, n, m, l, nn) REP_1(i, n) REP_1(j, m) REP_1(k, l) REP_1(ii, nn)

#define ALL(A) A.begin(), A.end()
#define LLA(A) A.rbegin(), A.rend()
#define CPY(A, B) memcpy(A, B, sizeof(A))
#define INS(A, P, B) A.insert(A.begin() + P, B)
#define ERS(A, P) A.erase(A.begin() + P)
#define LBD(A, x) (lower_bound(ALL(A), x) - A.begin())
#define UBD(A, x) (upper_bound(ALL(A), x) - A.begin())
#define CTN(T, x) (T.find(x) != T.end())
#define SZ(A) int((A).size())
#define PB push_back
#define MP(A, B) make_pair(A, B)
#define PTT pair<T, T>
#define Ts *this
#define rTs return Ts
#define fi first
#define se second
#define re real()
#define im imag()

#define Rush for (int ____T = RD(); ____T--;)
#define Display(A, n, m)                 \
    {                                    \
        REP(i, n)                        \
        {                                \
            REP(j, m - 1)                \
                cout << A[i][j] << " ";  \
            cout << A[i][m - 1] << endl; \
        }                                \
    }
#define Display_1(A, n, m)              \
    {                                   \
        REP_1(i, n)                     \
        {                               \
            REP_1(j, m - 1)             \
                cout << A[i][j] << " "; \
            cout << A[i][m] << endl;    \
        }                               \
    }

typedef long long LL;
// typedef long double DB;
typedef double DB;
typedef unsigned uint;
typedef unsigned long long uLL;

typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<string> VS;
typedef vector<LL> VL;
typedef vector<DB> VF;
typedef set<int> SI;
typedef set<string> SS;
typedef map<int, int> MII;
typedef map<string, int> MSI;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef vector<VII> VVII;

template <class T>
inline T &RD(T &);
template <class T>
inline void OT(const T &);
// inline int RD(){int x; return RD(x);}
inline LL RD()
{
    LL x;
    return RD(x);
}
inline DB &RF(DB &);
inline DB RF()
{
    DB x;
    return RF(x);
}
inline char *RS(char *s);
inline char &RC(char &c);
inline char RC();
inline char &RC(char &c)
{
    scanf(" %c", &c);
    return c;
}
inline char RC()
{
    char c;
    return RC(c);
}
// inline char& RC(char &c){c = getchar(); return c;}
// inline char RC(){return getchar();}

template <class T>
inline T &RDD(T &);
inline LL RDD()
{
    LL x;
    return RDD(x);
}

template <class T0, class T1>
inline T0 &RD(T0 &x0, T1 &x1)
{
    RD(x0), RD(x1);
    return x0;
}
template <class T0, class T1, class T2>
inline T0 &RD(T0 &x0, T1 &x1, T2 &x2)
{
    RD(x0), RD(x1), RD(x2);
    return x0;
}
template <class T0, class T1, class T2, class T3>
inline T0 &RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3)
{
    RD(x0), RD(x1), RD(x2), RD(x3);
    return x0;
}
template <class T0, class T1, class T2, class T3, class T4>
inline T0 &RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4)
{
    RD(x0), RD(x1), RD(x2), RD(x3), RD(x4);
    return x0;
}
template <class T0, class T1, class T2, class T3, class T4, class T5>
inline T0 &RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4, T5 &x5)
{
    RD(x0), RD(x1), RD(x2), RD(x3), RD(x4), RD(x5);
    return x0;
}
template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline T0 &RD(T0 &x0, T1 &x1, T2 &x2, T3 &x3, T4 &x4, T5 &x5, T6 &x6)
{
    RD(x0), RD(x1), RD(x2), RD(x3), RD(x4), RD(x5), RD(x6);
    return x0;
}
template <class T0, class T1>
inline void OT(const T0 &x0, const T1 &x1) { OT(x0), OT(x1); }
template <class T0, class T1, class T2>
inline void OT(const T0 &x0, const T1 &x1, const T2 &x2) { OT(x0), OT(x1), OT(x2); }
template <class T0, class T1, class T2, class T3>
inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3) { OT(x0), OT(x1), OT(x2), OT(x3); }
template <class T0, class T1, class T2, class T3, class T4>
inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4) { OT(x0), OT(x1), OT(x2), OT(x3), OT(x4); }
template <class T0, class T1, class T2, class T3, class T4, class T5>
inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5) { OT(x0), OT(x1), OT(x2), OT(x3), OT(x4), OT(x5); }
template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline void OT(const T0 &x0, const T1 &x1, const T2 &x2, const T3 &x3, const T4 &x4, const T5 &x5, const T6 &x6) { OT(x0), OT(x1), OT(x2), OT(x3), OT(x4), OT(x5), OT(x6); }
inline char &RC(char &a, char &b)
{
    RC(a), RC(b);
    return a;
}
inline char &RC(char &a, char &b, char &c)
{
    RC(a), RC(b), RC(c);
    return a;
}
inline char &RC(char &a, char &b, char &c, char &d)
{
    RC(a), RC(b), RC(c), RC(d);
    return a;
}
inline char &RC(char &a, char &b, char &c, char &d, char &e)
{
    RC(a), RC(b), RC(c), RC(d), RC(e);
    return a;
}
inline char &RC(char &a, char &b, char &c, char &d, char &e, char &f)
{
    RC(a), RC(b), RC(c), RC(d), RC(e), RC(f);
    return a;
}
inline char &RC(char &a, char &b, char &c, char &d, char &e, char &f, char &g)
{
    RC(a), RC(b), RC(c), RC(d), RC(e), RC(f), RC(g);
    return a;
}
inline DB &RF(DB &a, DB &b)
{
    RF(a), RF(b);
    return a;
}
inline DB &RF(DB &a, DB &b, DB &c)
{
    RF(a), RF(b), RF(c);
    return a;
}
inline DB &RF(DB &a, DB &b, DB &c, DB &d)
{
    RF(a), RF(b), RF(c), RF(d);
    return a;
}
inline DB &RF(DB &a, DB &b, DB &c, DB &d, DB &e)
{
    RF(a), RF(b), RF(c), RF(d), RF(e);
    return a;
}
inline DB &RF(DB &a, DB &b, DB &c, DB &d, DB &e, DB &f)
{
    RF(a), RF(b), RF(c), RF(d), RF(e), RF(f);
    return a;
}
inline DB &RF(DB &a, DB &b, DB &c, DB &d, DB &e, DB &f, DB &g)
{
    RF(a), RF(b), RF(c), RF(d), RF(e), RF(f), RF(g);
    return a;
}
inline void RS(char *s1, char *s2) { RS(s1), RS(s2); }
inline void RS(char *s1, char *s2, char *s3) { RS(s1), RS(s2), RS(s3); }
template <class T0, class T1>
inline T0 &RDD(T0 &a, T1 &b)
{
    RDD(a), RDD(b);
    return a;
}
template <class T0, class T1, class T2>
inline T1 &RDD(T0 &a, T1 &b, T2 &c)
{
    RDD(a), RDD(b), RDD(c);
    return a;
}

template <class T>
inline void RST(T &A) { memset(A, 0, sizeof(A)); }
template <class T>
inline void FLC(T &A, int x) { memset(A, x, sizeof(A)); }
template <class T>
inline void CLR(T &A) { A.clear(); }

template <class T0, class T1>
inline void RST(T0 &A0, T1 &A1) { RST(A0), RST(A1); }
template <class T0, class T1, class T2>
inline void RST(T0 &A0, T1 &A1, T2 &A2) { RST(A0), RST(A1), RST(A2); }
template <class T0, class T1, class T2, class T3>
inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3) { RST(A0), RST(A1), RST(A2), RST(A3); }
template <class T0, class T1, class T2, class T3, class T4>
inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4) { RST(A0), RST(A1), RST(A2), RST(A3), RST(A4); }
template <class T0, class T1, class T2, class T3, class T4, class T5>
inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5) { RST(A0), RST(A1), RST(A2), RST(A3), RST(A4), RST(A5); }
template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline void RST(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6) { RST(A0), RST(A1), RST(A2), RST(A3), RST(A4), RST(A5), RST(A6); }
template <class T0, class T1>
inline void FLC(T0 &A0, T1 &A1, int x) { FLC(A0, x), FLC(A1, x); }
template <class T0, class T1, class T2>
inline void FLC(T0 &A0, T1 &A1, T2 &A2, int x) { FLC(A0, x), FLC(A1, x), FLC(A2, x); }
template <class T0, class T1, class T2, class T3>
inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, int x) { FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x); }
template <class T0, class T1, class T2, class T3, class T4>
inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, int x) { FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x); }
template <class T0, class T1, class T2, class T3, class T4, class T5>
inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, int x) { FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x), FLC(A5, x); }
template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline void FLC(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6, int x) { FLC(A0, x), FLC(A1, x), FLC(A2, x), FLC(A3, x), FLC(A4, x), FLC(A5, x), FLC(A6, x); }
template <class T>
inline void CLR(priority_queue<T> &Q)
{
    while (!Q.empty())
        Q.pop();
}
template <class T>
inline void CLR(stack<T> &S)
{
    while (!S.empty())
        S.pop();
}
template <class T>
inline void CLR(queue<T> &Q)
{
    while (!Q.empty())
        Q.pop();
}

template <class T0, class T1>
inline void CLR(T0 &A0, T1 &A1) { CLR(A0), CLR(A1); }
template <class T0, class T1, class T2>
inline void CLR(T0 &A0, T1 &A1, T2 &A2) { CLR(A0), CLR(A1), CLR(A2); }
template <class T0, class T1, class T2, class T3>
inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3) { CLR(A0), CLR(A1), CLR(A2), CLR(A3); }
template <class T0, class T1, class T2, class T3, class T4>
inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4) { CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4); }
template <class T0, class T1, class T2, class T3, class T4, class T5>
inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5) { CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4), CLR(A5); }
template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline void CLR(T0 &A0, T1 &A1, T2 &A2, T3 &A3, T4 &A4, T5 &A5, T6 &A6) { CLR(A0), CLR(A1), CLR(A2), CLR(A3), CLR(A4), CLR(A5), CLR(A6); }
template <class T>
inline void CLR(T &A, int n) { REP(i, n)
                               CLR(A[i]); }

template <class T>
inline bool EPT(T &a) { return a.empty(); }
template <class T>
inline T &SRT(T &A)
{
    sort(ALL(A));
    return A;
}
template <class T, class C>
inline T &SRT(T &A, C cmp)
{
    sort(ALL(A), cmp);
    return A;
}
template <class T>
inline T &RVS(T &A)
{
    reverse(ALL(A));
    return A;
}
template <class T>
inline T &UNQQ(T &A)
{
    A.resize(unique(ALL(A)) - A.begin());
    return A;
}
template <class T>
inline T &UNQ(T &A)
{
    SRT(A);
    return UNQQ(A);
}
template <class T, class C>
inline T &UNQ(T &A, C cmp)
{
    SRT(A, cmp);
    return UNQQ(A);
}

//}

/** Constant List .. **/ //{

const int MOD = int(1e9) + 7;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fLL;
const DB EPS = 1e-9;
const DB OO = 1e20;
const DB PI = acos(-1.0); // M_PI;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, 1, -1};

//}

/** Add On .. **/ //{
// <<= '0. Nichi Joo ., //{

template <class T>
inline bool checkMin(T &a, const T b) { return b < a ? a = b, 1 : 0; }
template <class T>
inline bool checkMax(T &a, const T b) { return a < b ? a = b, 1 : 0; }
template <class T, class C>
inline bool checkUpd(T &a, const T b, C c) { return c(b, a) ? a = b, 1 : 0; }
template <class T>
inline T min(T a, T b, T c) { return min(min(a, b), c); }
template <class T>
inline T max(T a, T b, T c) { return max(max(a, b), c); }
template <class T>
inline T min(T a, T b, T c, T d) { return min(min(a, b), min(c, d)); }
template <class T>
inline T max(T a, T b, T c, T d) { return max(max(a, b), max(c, d)); }
template <class T>
inline T min(T a, T b, T c, T d, T e) { return min(min(min(a, b), min(c, d)), e); }
template <class T>
inline T max(T a, T b, T c, T d, T e) { return max(max(max(a, b), max(c, d)), e); }
template <class T>
inline T sqr(T a) { return a * a; }
template <class T>
inline T cub(T a) { return a * a * a; }
template <class T>
inline T ceil(T x, T y) { return (x - 1) / y + 1; }
template <class T>
T abs(T x) { return x > 0 ? x : -x; }
inline int sgn(DB x) { return x < -EPS ? -1 : x > EPS; }
inline int sgn(DB x, DB y) { return sgn(x - y); }

inline DB cos(DB a, DB b, DB c) { return (sqr(a) + sqr(b) - sqr(c)) / (2 * a * b); }
inline DB cot(DB x) { return 1. / tan(x); };
inline DB sec(DB x) { return 1. / cos(x); };
inline DB csc(DB x) { return 1. / sin(x); };

//}

//}

/** I/O Accelerator Interface .. **/ //{
#define g (c = getchar())
#define d isdigit(g)
#define p x = x * 10 + c - '0'
#define n x = x * 10 + '0' - c
#define pp l /= 10, p
#define nn l /= 10, n
template <class T>
inline T &RD(T &x)
{
    char c;
    while (!d)
        ;
    x = c - '0';
    while (d)
        p;
    return x;
}
template <class T>
inline T &RDD(T &x)
{
    char c;
    while (g, c != '-' && !isdigit(c))
        ;
    if (c == '-')
    {
        x = '0' - g;
        while (d)
            n;
    }
    else
    {
        x = c - '0';
        while (d)
            p;
    }
    return x;
}
inline DB &RF(DB &x)
{
    // scanf("%lf", &x);
    char c;
    while (g, c != '-' && c != '.' && !isdigit(c))
        ;
    if (c == '-')
        if (g == '.')
        {
            x = 0;
            DB l = 1;
            while (d)
                nn;
            x *= l;
        }
        else
        {
            x = '0' - c;
            while (d)
                n;
            if (c == '.')
            {
                DB l = 1;
                while (d)
                    nn;
                x *= l;
            }
        }
    else if (c == '.')
    {
        x = 0;
        DB l = 1;
        while (d)
            pp;
        x *= l;
    }
    else
    {
        x = c - '0';
        while (d)
            p;
        if (c == '.')
        {
            DB l = 1;
            while (d)
                pp;
            x *= l;
        }
    }
    return x;
}
#undef nn
#undef pp
#undef n
#undef p
#undef d
#undef g
inline char *RS(char *s)
{
    // gets(s);
    scanf("%s", s);
    return s;
}

LL last_ans;
int Case;
template <class T>
inline void OT(const T &x)
{
    // printf("Case #%d: ", ++Case);
    // printf("%lld\n", x);
    // printf("%I64d\n", x);
    // printf("%.9f\n", x);
    // printf("%d\n", x);
    cout << x << endl;
    // last_ans = x;
}

//}/* .................................................................................................................................. */

// <<= 'Bignum ., //{
namespace BIGNUM
{

    const int __base = 1e8;
    const int P10[] = {1, 10, int(1e2), int(1e3), int(1e4), int(1e5), int(1e6), int(1e7), int(1e8), int(1e9)};
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
                data.PB(s % __base), s /= __base;
            if (data.empty())
                data.PB(0);
        }

        inline bignum(long long s)
        {
            while (s)
                data.PB(int(s % __base)), s /= __base;
            if (data.empty())
                data.PB(0);
        }

        inline bignum(string s)
        {
            int t, i;
            CLR(data);
            for (i = int(s.size()) - 8; i > 0; i -= 8)
            {
                istringstream(s.substr(i, 8)) >> t;
                data.PB(t);
            }
            istringstream(s.substr(0, i + 8)) >> t;
            data.PB(t);
        }
/*
        void input()
        {
            CLR(data);
            RS(__buf);
            int t = 0, c = 0;
            DWN(i, strlen(__buf), 0)
            {
                t += P10 * (int(__buf[i]) - '0'), ++c;
                if (c == 8)
                    data.PB(t), c = t = 0;
            }
            if (c)
                data.PB(t);
        }
*/
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
            data.PB(*i);
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
            a.data.PB(t);
        }
        istringstream(s.substr(0, i + 8)) >> t;
        a.data.PB(t);
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
            data.PB(t + *j);
            t = data.back() / __base;
            data.back() %= __base;
            j++;
        }
        if (t != 0)
            data.PB(t);
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
            c.data.PB(t + *i + *j);
            t = c.data.back() / __base;
            c.data.back() %= __base;
        }
        while (i != a.data.end())
        {
            c.data.PB(t + *i);
            t = c.data.back() / __base;
            c.data.back() %= __base;
            i++;
        }
        while (j != b.data.end())
        {
            c.data.PB(t + *j);
            t = c.data.back() / __base;
            c.data.back() %= __base;
            j++;
        }
        if (t != 0)
            c.data.PB(t);
        return c;
    }

    inline bignum operator+(const bignum &a, const int &b)
    {
        return a + bignum(b);
    }

}
using namespace BIGNUM;
//}

typedef int T_state;
typedef bignum T_key;
const int N = 8;
int n, m;

// 5*3 = 15
// 4321 = 10

const int Offset = 3, Mask = (1 << Offset) - 1;
bool ok[N][N], okk[N][N], _ok[N];

int b[N + 2], bb[N + 3];
T_state encode()
{
    T_state s = 0;
    memset(bb, -1, sizeof(bb));
    int bn = 1;
    bb[0] = 0;
#define bi bb[b[i]]
#define bj bb[b[j]]
    DWN(i, m, 0)
    {
        if (!~bi)
            bi = bn++;
    }

    memset(okk, 1, sizeof(okk));
    // cout << "b: "; FOR(i, 0, m) cout << b[i] << " "; cout << endl;
    REP(i, m)
    if (b[i])
    {
        REP(j, i)
        if (b[j])
        {
            okk[bi][bj] = okk[bj][bi] = ok[b[i]][b[j]];
        }
    }
    DWN(i, m + 1, 2)
    DWN(j, i, 1)
    {
        s <<= 1;
        s |= !okk[i][j];
    }
    DWN(i, m, 0)
    {
        s <<= Offset;
        s |= bi;
    }
    return s;
}
void decode(T_state s)
{
    REP(i, m)
    {
        b[i] = s & Mask;
        s >>= Offset;
    }
    memset(ok, 1, sizeof(ok));
    FOR(i, 2, m + 1)
    FOR(j, 1, i)
    {
        ok[i][j] = ok[j][i] = !(s & 1);
        s >>= 1;
    }
}
const int Prime = 9979, MaxSZ = 1 << 20;
T_key d;
template <class T_state, class T_key>
struct hashTable
{
    int head[Prime];
    int next[MaxSZ], sz;
    T_state state[MaxSZ];
    T_key key[MaxSZ];
    void clear()
    {
        sz = 0;
        memset(head, -1, sizeof(head));
    }
    void push(T_state s)
    {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i])
        {
            if (state[i] == s)
            {
                key[i] += d;
                return;
            }
        }
        state[sz] = s, key[sz] = d;
        next[sz] = head[x], head[x] = sz++;
    }
};
hashTable<T_state, T_key> H[2], *H0, *H1;

//
// 64 // 32 16 8 // . . .

int j, lf, up;
void push(int t)
{
    b[j] = t;
    // assert(ok[t][lf] == ok[lf][t]);
    // assert(ok[t][up] == ok[up][t]);
    bool ok_lf = ok[t][lf], ok_up = ok[t][up];
    ok[t][lf] = ok[lf][t] = ok[t][up] = ok[up][t] = 0;
    H1->push(encode());
    ok[t][lf] = ok[lf][t] = ok_lf;
    ok[t][up] = ok[up][t] = ok_up;
}
void push()
{
    H1->push(encode());
}

void init()
{
    cin >> n >> m;
    if (m > n)
        swap(n, m);
}
void solve()
{
    H0 = H, H1 = H + 1, H1->clear(), d = 1, H1->push(0);

    REP(i, n)
    {
        REP(j, m)
        {
            ::j = j;
            swap(H0, H1), H1->clear();
            REP(u, H0->sz)
            {
                decode(H0->state[u]);
                d = H0->key[u];
                lf = j ? b[j - 1] : 0, up = b[j];

                /*cout << H0->state[u] << ": " << d << endl;
                REP(i, m) cout << b[i] << " "; cout << endl;
                cout << "c: "; FOR(i, 1, m+1) FOR(j, 1, i) cout << ok[i][j] << " "; cout << endl;
*/

                push(m + 1);
                if (lf && up)
                {
                    push(lf);
                    if (lf != up)
                    {
                        push(up);
                        if (ok[lf][up])
                        {
                            // if (lf > up) swap(lf, up);
                            REP(i, m)
                            if (b[i] == up) b[i] = lf;
                            FOR(t, 1, m + 1)
                            {
                                _ok[t] = ok[lf][t];
                                if (ok[lf][t] && !ok[up][t])
                                {
                                    ok[lf][t] = ok[t][lf] = 0;
                                }
                            }
                            push();
                            FOR(t, 1, m + 1)
                            ok[lf][t] = ok[t][lf] = _ok[t];
                        }
                    }
                }
                else if (lf | up)
                {
                    push(lf | up);
                }
            }
        }
        // H1->roll();
    }

    /*H0 = H1;
    REP(u, H0->sz) {
        decode(H0->state[u]); d = H0->key[u];
        cout << H0->state[u] << ": " << d << endl;
        REP(i, m) cout << b[i] << " "; cout << endl;
    }*/
}
void print()
{
    T_key z = 0;
    REP(i, H1->sz)
    z += H1->key[i];
    cout << z << endl;
}
int main()
{
#ifndef ONLINE_JUDGE
    ////freopen("in.txt", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--)
    {
        init();
        solve();
        print();
    }
}
