#include <iostream>
#include <cstring>

struct student {
    std::string name;   // 姓名
    int age;            // 平均成绩
    int ageClass;       // 班级评议成绩
    char cadre;         // 是否为学生干部
    char west;          // 是否为西部学生
    int thesis;         // 论文数
};

int scholarship(student stu, int &money) {
    if (stu.age > 80 && stu.thesis >=1)
        money += 8000;
    if (stu.age > 85 && stu.ageClass > 80)
        money += 4000;
    if (stu.age > 90)
        money += 2000;
    if (stu.west == 'Y')
        money += 1000;
    if (stu.ageClass > 80 && stu.cadre == 'Y')
        money += 850;
    return 0;
}

int main() {
    int n;
    std::cin >> n;
    student stu[n];
    int money[n];
    memset(money, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        std::cin >> stu[i].name >> stu[i].age >> stu[i].ageClass
                 >> stu[i].cadre >> stu[i].west >> stu[i].thesis;
        scholarship(stu[i], money[i]);
    }
    return 0;
}
