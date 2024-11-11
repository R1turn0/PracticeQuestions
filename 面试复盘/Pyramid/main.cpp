#include <iostream>

int main() {
    int n;  // 金字塔高度n
    std::cout << "输入金字塔高度:";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i; j++) {
            std::cout << " ";   // 输出n-i个空格
        }
        for (int j = 0; j < 2 * i - 1; j++) {
            std::cout << "*";   // 输出2i-1个砖块
        }
        std::cout << std::endl;
    }
    return 0;
}