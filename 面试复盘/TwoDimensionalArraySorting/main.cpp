#include<iostream>

#define row 3
#define col 3

void funcSort(int *a)
{
    int temp, sum;
    sum = row * col;
    for (int i = 0; i < sum - 1; i++) { // 冒泡排序
        for (int j = 0; j < sum - i - 1; j++) {
            if(*(a + j) > *(a + j + 1)) {
                temp = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = temp;
            }
        }
    }
}


int main() {
    int a[3][3] = {
            {6, 3, 5},
            {7, 1, 9},
            {2, 8, 4}
    };
//    int a[row][col];
//    for (auto & i : a) {
//        for (int & j : i) {
//            std::cin >> j;
//        }
//    }
    for (auto & i : a) {    // 遍历输出数组a
        for(int j : i)
            std::cout << j << '\t';
        std::cout << std::endl;
    }
    std::cout << std::endl;

    funcSort(&a[0][0]);

    for (auto & i : a) {    // 遍历输出数组a
        for (int j : i)
            std::cout << j << '\t';
        std::cout << std::endl;
    }
    return 0;
}
