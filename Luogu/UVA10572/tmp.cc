#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define SF scanf
#define PF printf
#define MAXNODE 200100
#define MAXN 12
#define MOD 199999
#define update dp[cur^1].push(encode(),cc,dp[cur].f[k],i*m+j,k,c);
using namespace std;
int n,m,ex,ey,cur;
int a[MAXN],num[MAXN],pre[MAXN*MAXN][MAXNODE],op[MAXN*MAXN][MAXNODE];
char mat[MAXN][MAXN];
struct hash{
    int sz,adj[MAXNODE],next[MAXNODE];
    int state[MAXNODE],f[MAXNODE],col[MAXNODE];
    void clr(){
        sz=0;
        memset(adj,-1,sizeof (adj));
    }
    void push(int s,int c,int val,int id,int fa,int o){
        int u=s%MOD;
        for(int i=adj[u];~i;i=next[i])
            if(state[i]==s&&col[i]==c){
                f[i]+=val;
                return ;
            }
        state[sz]=s;
        f[sz]=val;
        col[sz]=c;
        pre[id][sz]=fa;
        op[id][sz]=o;
        next[sz]=adj[u];
        adj[u]=sz++;
    }
}dp[2];

void decode(int s){
    for(int i=m-1;i>=0;i--){
        a[i]=s&7;
        s>>=3;
    }
}
int encode(){
    memset(num,-1,sizeof num);
    int k=-1;
    int ret=0;
    for(int i=0;i<m;i++){
        if(num[a[i]]==-1)
            num[a[i]]=++k;
        ret=(ret<<3)|num[a[i]];
    }
    return ret;
}
void change(int x,int y){
    for(int i=0;i<m;i++)
        if(a[i]==x)
            a[i]=y;
}
void dpblank(int i,int j,int c){
    for(int k=0;k<dp[cur].sz;k++){
        int cc=dp[cur].col[k];
        int U=0,L=0,UL;
        if(i>0)
            U=(cc>>j&1)==c;
        if(j>0)
            L=(cc>>(j-1)&1)==c;
        UL=(cc>>m)==c;
        if(L&&UL&&U)
        	continue;
        if(i==n-1&&j==m-1&&!U&&!L&&UL)
            continue;
        decode(dp[cur].state[k]);
        if(i>0&&U==0){
        	int s1=0,s2=0;
        	for(int t=0;t<m;t++){
                if(a[t]==a[j])
                    s1++;
                if((cc>>t&1)!=c)
                    s2++;
        	}
        	if(s1==1){
                if(s2>1||i<n-1||j<m-2)
                    continue;
        	}
		}
		if(U&&L){
            if(a[j]!=a[j-1])
                change(a[j],a[j-1]);
		}
		else if(!U&&L)
            a[j]=a[j-1];
        else if(!U&&!L)
            a[j]=m;
        if(cc&(1<<j))
            cc|=1<<m;
        else
            cc&=~(1<<m);
        if(c)
            cc|=1<<j;
        else
            cc&=~(1<<j);
        update
    }
}
void print(int k){
    for(int i=n-1;i>=0;i--)
        for(int j=m-1;j>=0;j--){
            if(op[i*m+j][k])
                mat[i][j]='#';
            else
                mat[i][j]='o';
            k=pre[i*m+j][k];
        }
    for(int i=0;i<n;i++)
        PF("%s\n",mat[i]);
}
void work(){
    cur=0;
    dp[0].clr();
    dp[0].push(0,0,1,0,0,0);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            dp[cur^1].clr();
            if(mat[i][j]!='#')
                dpblank(i,j,0);
            if(mat[i][j]!='o')
                dpblank(i,j,1);
            cur^=1;
        }
    int ret=0,k;
    for(int i=0;i<dp[cur].sz;i++){
        int maxi=0;
        decode(dp[cur].state[i]);
        for(int j=0;j<m;j++)
            maxi=max(maxi,a[j]);
        if(maxi>1)
            continue;
        ret+=dp[cur].f[i];
        k=i;
    }
    PF("%d\n",ret);
    if(ret)
        print(k);
}
int main(){
    int tt;
    SF("%d",&tt);
    while(tt--){
        SF("%d%d",&n,&m);
        memset(mat,0,sizeof mat);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                SF(" %c",&mat[i][j]);
        work();
        PF("\n");
    }
}
