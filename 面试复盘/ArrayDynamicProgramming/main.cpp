#include<iostream>
#include<vector>

int fibonacci(int n) {
    if(n==0)
        return 0;
    std::vector<int> dp(n+1,0);
    dp[1] = 1;
    for (int i = 2; i<=n ;i++) {
        dp[i] = dp[i-1]+dp[i-2];
    }
    return dp[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << fibonacci(n);
    return 0;
}

// ============================

//#include<iostream>
//
//#define N 1010
//
//int main() {
//    int n,m;    //物品总数为n个，背包的总容量为m
//    int dp[N];
//    int v[N],w[N];  //物品的体积和价值
//    std::cin >> n >> m;
//    for(int i = 0;i < n;i++)
//        std::cin >> v[i] >> w[i];
//
//    for(int i = 0;i < n;i++)
//        for(int j = m;j >= v[i];j--)
//            dp[j] = std::max(dp[j],dp[j - v[i]] + w[i]);//从不选和选中选中较大值
//
//    std::cout << dp[m] << std::endl;
//
//    return 0;
//}

// ===============================

//#include <iostream>
//
//#define N 20        //台阶数为20
//int dp[N];          //全局数组，存放决策表
//
//int func(int n) {      //返回台阶数为n的走法
//    if (n == 1 || n == 2)
//        return n;
//    dp[n-1] = func(n-1);        //若不为1或2则进行递归计算
//    dp[n-2] = func(n-2);
//    dp[n] = dp[n-1]+dp[n-2];   //状态转移方程
//    return dp[n];
//}
//
//int main()
//{
//    func(N);
//    std::cout << dp[15] << std::endl;        //输出15阶的走法
//    return 0;
//}