//#include <iostream>
//
//static int xy[5000][5000] = {0};
//
//int main() {
//    int n, m, b, g;
//    int x, y;
//    int sum = 0;
//    std::cin >> n >> m >> b >> g;
//
//    while (b--) {
//        std::cin >> x >> y;
//        for (int i = x - 1; i <= y - 1; i++) {
//            for (int j = 0; j < m; j++) {
//                xy[i][j]++;
//            }
//        }
//    }
//    while (g--) {
//        std::cin >> x >> y;
//        for (int i = 0; i < n; i++) {
//            for (int j = x - 1; j <= y - 1; j++) {
//                xy[i][j]++;
//            }
//        }
//    }
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            if (xy[i][j] == 0) sum++;
//        }
//    }
//    std::cout << n * m - sum << std::endl;
//    return 0;
//}

#include <iostream>
#include <cstring>

static int xy[5000] = {0};

int main() {
    int n, m, b, g;
    int x, y;
    int result_x = 0, result_y = 0;
    std::cin >> n >> m >> b >> g;
    while (b--) {
        std::cin >> x >> y;
        for (int i = x - 1; i <= y - 1; i++) {
            xy[i]++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (xy[i] == 0) result_x++;
    }

    memset(xy, 0, n * sizeof(int));
    while (g--) {
        std::cin >> x >> y;
        for (int i = x - 1; i <= y - 1; i++) {
            xy[i]++;
        }
    }
    for (int i = 0; i < m; i++) {
        if (xy[i] == 0) result_y++;
    }
    std::cout << (n * m) - (result_x * result_y) << std::endl;
    return 0;
}
