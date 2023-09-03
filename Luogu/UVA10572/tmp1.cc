#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bit(x) (1<<(x))
using namespace std;
typedef long long ll;
const int mod = 233333;
const int M = mod + 5;
const int N = 20;

int read(){
	int s=0,w=1; char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch))s=s*10+(ch^48),ch=getchar();
	return s*w;
}

int a[N],num[N],pre[100][mod+5];
char mp[N][N],op[100][mod+5];
int T,n,m,now;

struct Hash_map{
	int nex[M],head[M];
	int sta[M],col[M],val[M];//二进制表示 col ，八进制表示 sta
	int siz;
	
	void clear(){
		memset(head,0,sizeof(head));
		siz=0;
	}
	void insert(int s,int c,int v,int id,int fa,char o){
		for(int i=head[s%mod];i;i=nex[i])
			if(sta[i]==s&&col[i]==c)
				return val[i]+=v,void();
		sta[++siz]=s,col[siz]=c,val[siz]=v;
		pre[id][siz]=fa,op[id][siz]=o;
		nex[siz]=head[s%mod],head[s%mod]=siz; 
	}
}dp[2];

void decode(int s){//解码
	for(int i=m-1;~i;--i)
		a[i]=s&7,s>>=3;
}
int encode(){//最小表示法
	memset(num,-1,sizeof(num));
	int k=-1,res=0;
	for(int i=0;i<m;++i){
		if(num[a[i]]==-1)num[a[i]]=++k;
		res=(res<<3)|num[a[i]];
	}
	return res;
}
void change(int x,int y){//刷颜色
	for(int i=0;i<m;++i)
		if(a[i]==x)a[i]=y;
}
void DP(int i,int j,int c){
	for(int k=1;k<=dp[now].siz;++k){
		int cc=dp[now].col[k];
		int u=i?(cc>>j&1)==c:0;
		int l=j?(cc>>(j-1)&1)==c:0;//边界直接认为不相同
		int lu=(cc>>m)==c;// 二进制第 m 位存放 (i-1,j-1)
		if(u&&l&&lu)continue;
		if(i==n-1&&j==m-1&&!u&&!l&&lu)continue;
		decode(dp[now].sta[k]);
		if(i&&!u){
			int s1=0,s2=0;
			for(int t=0;t<m;++t)
				s1+=a[t]==a[j],s2+=((cc>>t&1)!=c);
            //s1：连通性相同格子个数, s2: 与 u 颜色相同个数
			if(s1==1){
				if(s2>1)continue;
				if(i<n-1||j<m-2)continue;
			}
		}
		
		if(u&&l){
			if(a[j]!=a[j-1])
				change(a[j],a[j-1]);
		}else if(!u&&l)a[j]=a[j-1];
		else if(!u&&!l)a[j]=m;
		if(cc&(1<<j))cc|=1<<m; else cc&=~(1<<m);
		if(c)cc|=1<<j; else cc&=~(1<<j);
		
		dp[now^1].insert(encode(),cc,dp[now].val[k],i*m+j,k,c?'#':'o');
	}
}
void print(int k){
	for(int i=n-1;i>=0;--i)
		for(int j=m-1;j>=0;--j)
			mp[i][j]=op[i*m+j][k],
			k=pre[i*m+j][k];
	for(int i=0;i<n;++i)puts(mp[i]);
}

signed main(){
	T=read();
	while(T--){
		n=read(),m=read();
		memset(mp,0,sizeof(mp));
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
				scanf(" %c",&mp[i][j]);
		now=0,dp[0].clear(),dp[0].insert(0,0,1,0,0,0);
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j){
				dp[now^1].clear();
				if(mp[i][j]!='#')DP(i,j,0);
				if(mp[i][j]!='o')DP(i,j,1);
				now^=1;
			}
		int ans=0,k;
		for(int i=1;i<=dp[now].siz;++i){
			int mx=0;
			decode(dp[now].sta[i]);
			for(int j=0;j<m;++j)
				mx=max(mx,a[j]);
			if(mx>1)continue;
			ans+=dp[now].val[i];
			k=i;
		}
		printf("%d\n",ans);
		if(ans)print(k);
		puts("");//UVA 神奇要求
	}	
	return 0;
}
