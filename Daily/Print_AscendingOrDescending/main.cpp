class Solution {
    static void printAscending(int num) {
        if (num == 0)
            return;
        printAscending(num / 10);
        std::cout << num % 10 << " ";
    }

    static void printDescending(int num) {
        if (num == 0)
            return;
        std::cout << num % 10 << " ";
        printDescending(num / 10);
    }
};

int main() {
    Solution::printAscending(123456);
    Solution::printDescending(123456);
	return 0;
}
