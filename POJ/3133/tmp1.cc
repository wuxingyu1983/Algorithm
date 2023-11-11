#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int STATE=1000000+10;
const int HASH =10007;
const int MAXD=15;
int N,M;
int cur;
int mp[MAXD][MAXD];
int code[MAXD];
int sum;//记录最终的最小值
struct HASHMAP
{
	int size,head[HASH],next[STATE];//next[i]=j表示第i个状态后面链接着第j个状态
	int state[STATE];//state[i]=S表第i个状态是S
	int f[STATE];//f[i]=x表第i个状态的最小长度
	void init()
	{
		memset(head,-1,sizeof(head));
		size=0;
	}
	void push(int st, int num)
	{
		int h = st%HASH;
		int i;
		for(i=head[h]; i!=-1; i=next[i])
		{
			if(state[i]==st)
			{
				f[i]=min(num,f[i]);
				return ;
			}
		}
		next[size]=head[h];
		head[h]=size;
		f[size]=num;
		state[size]=st;
		size++;
		if(size>STATE)
		{
			printf("哈希表的空间快用完了\n");
		}
	}
}hm[2];
void decode(int *code,int st)//st->code
{
	for(int i=M; i>=0; i--)
	{
		code[i]=st&3;
		st>>=2;//此处的状态是4进制，因为只需要表示3种插头，0,2,3
	}
}
int encode(int *code)//code->st
{
	int st=0;
	for(int i=0; i<=M; i++)
	{
		st<<=2;
		st|=code[i];
	}
	return st;
}
void shift(int *code)//处理完了一行的最后一列,将code整体右移一位,首位添0
{
	for(int i=M; i>=1; i--)
		code[i]=code[i-1];
	code[0]=0;
}
void dpblock(int i,int j)//坏格
{
	for(int k=0; k<hm[cur].size; k++)
	{
		int st=hm[cur].state[k];
		int code[MAXD];
		decode(code,st);
		int left=code[j-1] ,up=code[j];
		if(left==0&&up==0)//全无插头时,才能生成新状态
		{
			if(j==M)//j为当前行最后一列,需要右移一位
				shift(code);
			hm[1-cur].push(encode(code),hm[cur].f[k]);
		}
	}
}
void dpblank(int i,int j)//好格
{
	for(int k=0; k<hm[cur].size; k++)
	{
		int st=hm[cur].state[k];
		int num = hm[cur].f[k];
		int code[MAXD];
		decode(code,st);
		int left=code[j-1] ,up=code[j];
		if(left>0&&up>0)//都有插头
		{
			if(left==up)//合并两个相同的连通分量
			{
				code[j-1]=code[j]=0;
				if(j==M)shift(code);//j为当前行最后一列,需要右移一位
				hm[1-cur].push( encode(code),num+1);
			}
		}
		else if(left>0||up>0)//其中一个有插头另一个没有
		{
			if(mp[i][j+1]==1 || left+up==mp[i][j+1])//(i,j)右边对应插头的连通分量
								//left+up==mp[i][j+1]  这个的意思是要求上左的那个插头是2或3 右插头也是2或3
			{
				code[j-1]=0;
				code[j]=left+up;
				if(j==M)shift(code);//j为当前行最后一列,需要右移一位
				hm[1-cur].push( encode(code),num+1);
			}

			if(mp[i+1][j]==1 || left+up==mp[i+1][j])//(i,j)下面对应插头的连通分量
								//left+up==mp[i+1][j]  这个的意思是要求上左的那个插头是2或3 下插头也是2或3
			{
				code[j-1]=left+up;
				code[j]=0;
				if(j==M)shift(code);//j为当前行最后一列,需要右移一位
				hm[1-cur].push( encode(code),num+1);
			}
		}
		else//两个都没插头
		{
			code[j-1]=code[j]=0;//可以选择不放
			if(j==M)shift(code);
			hm[1-cur].push( encode(code),num );

			//放2号插头的连通分量
			if( (mp[i][j+1]==1&&mp[i+1][j]==1) || (mp[i][j+1]==2&&mp[i+1][j]==1) || (mp[i][j+1]==1&&mp[i+1][j]==2)  )
			{
				code[j-1]=code[j]=2;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}

			//放3号插头的连通分量
			if( (mp[i][j+1]==1&&mp[i+1][j]==1) || (mp[i][j+1]==3&&mp[i+1][j]==1) || (mp[i][j+1]==1&&mp[i+1][j]==3)  )
			{
				code[j-1]=code[j]=3;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}
		}
	}
}
void dp_2(int i,int j)//特殊处理2号格
{
	for(int k=0; k<hm[cur].size; k++)
	{
		int st=hm[cur].state[k];
		int num = hm[cur].f[k];
		int code[MAXD];
		decode(code,st);
		int left=code[j-1] ,up=code[j];
		if( (left==2&&up==0) || (left==0&&up==2) )//只有一个2插头
		{
			code[j-1]=code[j]=0;
			if(j==M)shift(code);
			hm[1-cur].push( encode(code),num+1);
		}
		else if(left==0&&up==0)//没有插头
		{
			if(mp[i][j+1]==1||mp[i][j+1]==2)//右边能插
			{
				code[j-1]=0;
				code[j]=2;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}
			if(mp[i+1][j]==1||mp[i+1][j]==2)//下边能插
			{
				code[j-1]=2;
				code[j]=0;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}
		}
	}
}
void dp_3(int i,int j)//特殊处理3号格
{
	for(int k=0; k<hm[cur].size; k++)
	{
		int st=hm[cur].state[k];
		int num = hm[cur].f[k];
		int code[MAXD];
		decode(code,st);
		int left=code[j-1] ,up=code[j];
		if( (left==3&&up==0) || (left==0&&up==3) )//只有一个3插头
		{
			code[j-1]=code[j]=0;
			if(j==M)shift(code);
			hm[1-cur].push( encode(code),num+1);
		}
		else if(left==0&&up==0)//没有插头
		{
			if(mp[i][j+1]==1||mp[i][j+1]==3)//右边能插
			{
				code[j-1]=0;
				code[j]=3;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}
			if(mp[i+1][j]==1||mp[i+1][j]==3)//下边能插
			{
				code[j-1]=3;
				code[j]=0;
				if(j==M)shift(code);
				hm[1-cur].push( encode(code),num+1);
			}
		}
	}
}
void init()
{
	memset(mp,0,sizeof(mp));
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			scanf("%d",&mp[i][j]);
			if(mp[i][j]==1)
				mp[i][j]=0;//障碍
			else if(mp[i][j]==0)
				mp[i][j]=1;//可行
					   //还有为2和3的格
		}
	}
}
void solve()
{
	cur=0;
	hm[cur].init();
	hm[cur].push(0,0);
	for(int i=1; i<=N; i++)
		for(int j=1; j<=M; j++)
		{
			hm[1-cur].init();
			if(mp[i][j]==1)
				dpblank(i,j);
			else if(mp[i][j]==2)
				dp_2(i,j);
			else if(mp[i][j]==3)
				dp_3(i,j);
			else
				dpblock(i,j);
			cur=1-cur;
		}
	sum =1e5;
	for(int i=0;i<hm[cur].size;i++)
		sum=min(sum ,hm[cur].f[i]);
	if(sum!=1e5)sum-=2;//两条线的长度是指距离  不是指连着多少格  所以每条线要减1
	printf("%d\n",sum==1e5?0:sum);
}
int main()
{
	while(scanf("%d%d",&N,&M)==2&&N&&M)
	{
		init();
		solve();
	}
	return 0;
}

