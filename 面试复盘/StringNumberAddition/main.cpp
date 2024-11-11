#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string addBigNumbers(string num1, string num2) {
    // 确保num1是较长的数字
    if (num1.length() < num2.length()) {
        swap(num1, num2);
    }

    int len1 = num1.length();
    int len2 = num2.length();
    int carry = 0;
    string result = "";

    // 从右向左逐位相加
    for (int i = 0; i < len1; i++) {
        int digit1 = num1[len1 - 1 - i] - '0';
        int digit2 = (i < len2) ? (num2[len2 - 1 - i] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    // 处理最后的进位
    if (carry) {
        result.push_back(carry + '0');
    }

    // 反转结果字符串
    reverse(result.begin(), result.end());

    return result;
}

string MyAddBigNumbers(string num1, string num2) {
    if (num1.size() == 0 || num2.size() == 0) {
        return num1 + num2;
    }
    std::string sum = MyAddBigNumbers(num1.substr(0, num1.size() - 1), num2.substr(0, num2.size() - 1));
    auto add = std::to_string(std::stoi(num1.substr(num1.size() - 1)) + std::stoi(num2.substr(num2.size() - 1)));
    if (add.size() > 1) {
        return MyAddBigNumbers(sum + "0", add);
    } else {
        return sum + add;
    }
}

int main() {
    string num1, num2;

    cout << "请输入第一个大数: ";
    cin >> num1;

    cout << "请输入第二个大数: ";
    cin >> num2;

    string sum = addBigNumbers(num1, num2);
    cout << "两数之和为: " << sum << endl;

    return 0;
}