#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 11
using namespace std;

const int A[]={1,3,9,27,81,243,729,2187,6561,19683,59049};
int n,m,g[N][N],dp[N][N][59049];

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int main(){
	while(~scanf("%d%d",&n,&m)&&n+m){
		memset(g,0,sizeof(g));
		memset(dp,0x3f,sizeof(dp));
		for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)g[i][j]=read();
		
		dp[0][m][0]=0;
		for(int i=1;i<=n;++i){
			for(int j=0;j<A[m];++j)//A[m]
				dp[i][0][j*3]=dp[i-1][m][j];
			for(int j=1;j<=m;++j){
				for(int k=0;k<A[m+1];++k){//A[m+1]
					if (j==m&&k>=A[m]) break;
					int a=(k/A[j-1])%3,b=(k/A[j])%3;
					if(g[i][j]==1){
						if(a==0&&b==0) dp[i][j][k]=dp[i][j-1][k];
					}else if(g[i][j]==2){//min,+1
						if(a==1&&b==0) dp[i][j][k]=dp[i][j-1][k-A[j-1]]+1;
						else if(a==0&&b==1) dp[i][j][k]=dp[i][j-1][k-A[j]]+1;
						else if(a==0&&b==0) dp[i][j][k]=min(dp[i][j-1][k+A[j-1]],dp[i][j-1][k+A[j]])+1;
					}else if(g[i][j]==3){
						if(a==2&&b==0) dp[i][j][k]=dp[i][j-1][k-2*A[j-1]]+1;
						else if(a==0&&b==2) dp[i][j][k]=dp[i][j-1][k-2*A[j]]+1;
						else if(a==0&&b==0) dp[i][j][k]=min(dp[i][j-1][k+2*A[j-1]],dp[i][j-1][k+2*A[j]])+1;
					}
					else if(g[i][j]==0){
						if(a==0&&b==0) dp[i][j][k]=min(dp[i][j-1][k],min(dp[i][j-1][k+A[j]+A[j-1]]+1,dp[i][j-1][k+2*A[j]+2*A[j-1]]+1));
						else if(a==0&&b>0) dp[i][j][k]=min(dp[i][j-1][k],dp[i][j-1][k+b*A[j-1]-b*A[j]])+1;
						else if(a>0&&b==0) dp[i][j][k]=min(dp[i][j-1][k],dp[i][j-1][k+a*A[j]-a*A[j-1]])+1;
						else if(a&&b&&a==b) dp[i][j][k]=dp[i][j-1][k-a*A[j]-a*A[j-1]]+1;
					}
					if (i==n&&j==m) break;
				}
			}
		}
		if(dp[n][m][0]<0x3f3f3f3f) printf("%d\n",dp[n][m][0]-2);
		else printf("0\n");
	}
	return 0;
}

