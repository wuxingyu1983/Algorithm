#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <set>
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

#define ll long long
#define re register
#define cs const

using std::cerr;
using std::cout;

int mod;
inline int add(int a,int b){a+=b-mod;return a+(a>>31&mod);}
inline int dec(int a,int b){a-=b;return a+(a>>31&mod);}
inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;}
inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
inline void Mul(int &a,int b){a=mul(a,b);}

class BearDestroys{
	private:
		static cs int SIZE=1<<15|1;
		int f[2][SIZE],g[2][SIZE],*pf,*nf,*pg,*ng;//pre now
		// f ：该状态的推倒的树的计数
		// g : 到达该状态的方案数计数 
		//状态定义 : dp[state] DP到当前格子，轮廓线状态为state
		//轮廓线压当前格子上方所有格子和左列下方所有格子 
		// state : 1 自由，0 禁用
		inline int get(int s,int t){if(t<0)return 0;return s>>t&1;}
		inline int set(int s,int t,int p){if(t<0)return s;return (s>>t&1)==p?s:(s^(1<<t));}
		int u[55],d[55],n,m,S;
	public:
		BearDestroys(){pf=f[0],nf=f[1],pg=g[0],ng=g[1];}
		int sumUp(int M,int N,int Mod){
			n=N,m=M,mod=Mod,S=1<<(n+1);
			for(int re i=0;i<m;++i)u[i]=0;
			for(int re i=m;i<n+m-1;++i)u[i]=i-m+1;
			for(int re i=n+m-2;i>=n-1;--i)d[i]=n-1;
			for(int re i=0;i<n-1;++i)d[i]=i;
			ng[0]=1;nf[0]=0;
			//不允许更改确定了状态的格子 
			for(int re i=0;i<n+m-1;++i){//枚举对角线 
				//在转移一条新的对角线之前刷新状态,扣掉最后一维无用状态并状态平移 
				std::swap(ng,pg);std::swap(nf,pf);
				memset(ng,0,sizeof(int)*S);
				memset(nf,0,sizeof(int)*S);
				for(int re s=0;s<S;++s)if(pg[s]||pf[s]){
					//最后一个自由格子的方案需要算入贡献
					int t=get(s,n); 
					Inc(ng[set(s,n,0)<<1],pg[s]);
					Inc(nf[set(s,n,0)<<1],pf[s]);
					if(t){
						Inc(ng[set(s,n,0)<<1],pg[s]);
						Inc(nf[set(s,n,0)<<1],pf[s]);
					}
				}
				for(int re j=0;j<n;++j){
					std::swap(ng,pg),std::swap(nf,pf);
					memset(ng,0,sizeof(int)*S);
					memset(nf,0,sizeof(int)*S);
					for(int re s=0;s<S;++s)if(pf[s]||pg[s]){
						int f=pf[s],g=pg[s];
						if(j<u[i]||d[i]<j){
							Inc(nf[set(s,j,0)],f);
							Inc(ng[set(s,j,0)],g);
							continue;
						}
						int t1=get(s,j-1),t2=get(s,j),t3=get(s,j+1);//右上，正上，左侧
						if(!t2){
						//正上格子禁用 
							if(t3){
							//左侧格子可用 
								//左侧格子决策为右，禁用左侧格子和当前格子 
								{//禁用了当前格子，需要算上当前格子的决策*2 
									int t=set(s,j,0);t=set(t,j+1,0);
									Inc(nf[t],add(add(f,f),add(g,g)));
									Inc(ng[t],add(g,g));
								}
								//左侧格子决策为下，考虑是否为最后一行
								{
									//如果是最后一行，必须右转，转移和上面一样 
									if(j==n-1){
										int t=set(s,j,0);t=set(t,j+1,0);
										Inc(nf[t],add(add(f,f),add(g,g)));
										Inc(ng[t],add(g,g));
									}
									//否则，这个格子自由了
									else {
										int t=set(s,j,1);
										Inc(nf[t],f);
										Inc(ng[t],g);
									}
								}
							}else {
							//左侧格子禁用，这个格子自由了 
								int t=set(s,j,1);
								Inc(nf[t],f);
								Inc(ng[t],g);
							} 
						}
						else {
							//这时候一定是正上方格子来压住这个格子,该格子禁用，需要计算该格子的贡献 
							int t=set(s,j,0);Inc(f,f),Inc(g,g);
							if(!t1){
							//如果右上方的格子禁用，则正上方格子可以任意，需要*2 
								Inc(nf[t],add(add(f,f),add(g,g)));
								Inc(ng[t],add(g,g));
							}else {
							//否则正上方格子只能是向下。
								Inc(nf[t],add(f,g));
								Inc(ng[t],g);
							}
						} 
					}
				} 
			}
			int ans=0;
			Inc(ans,nf[0]);
			Inc(ans,mul(2,nf[1<<n-1]));
			Inc(ans,mul(2,nf[1<<n]));
			Inc(ans,mul(4,nf[3<<n-1])); 
			return ans;
		}
};

BearDestroys Solver;

signed main(int argc, char** argv)
{
		int n, m, mod;

		m = atoi(argv[1]);
		n = atoi(argv[2]);
		mod = atoi(argv[3]);

		std::cout << Solver.sumUp(m, n, mod) << "\n";
		return 0;
}
