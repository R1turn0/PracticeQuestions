# include <iostream>

int n, a[1010][5], sum[1010];
int cnt;

int main() {
    scanf_s("%d", &n);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i][1] >> a[i][2] >> a[i][3];
        sum[i] = a[i][1] + a[i][2] + a[i][3];
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (abs(a[i][1] - a[j][1]) <= 5 &&
                abs(a[i][2] - a[j][2]) <= 5 &&
                abs(a[i][3] - a[j][3]) <= 5 &&
                abs(sum[i] - sum[j]) <= 10)
                cnt++;
    std::cout << cnt << std::endl;
    return 0;
}