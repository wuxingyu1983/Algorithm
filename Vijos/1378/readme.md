题目地址：https://vijos.org/p/1378
# 思路

知识点：区间DP，高精度

## 区间DP

对于每一行，比如第k行，第L次取数：
dp[i][j] = max{matrix[k][i - 1] * C + dp[i - 1][j], matrix[k][j + 1] * C + dp[i][j + 1]}，其中 C 就是第L次取数的系数 C = 2^L

最终结果就是：
取完全部后，每一行最大的 max{matrix[k][i] * C + dp[i][i]}，相加起来就是最终结果。