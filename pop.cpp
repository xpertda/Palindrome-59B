#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printMatrix(const vector<vector<bool>>& table, const string& str, int i = -1, int j = -1) {
    int n = str.size();
    cout << "Palindrome Table (T = True, F = False)\n    ";

    for (char ch : str)
        cout << setw(3) << ch;
    cout << "\n";

    for (int r = 0; r < n; r++) {
        cout << setw(3) << str[r] << " ";
        for (int c = 0; c < n; c++) {
            if (r == i && c == j)
                cout << "[" << (table[r][c] ? "T" : "F") << "]";
            else
                cout << setw(4) << (table[r][c] ? "T" : "F");
        }
        cout << "\n";
    }
}

int visualizePalindromePartition(string s) {
    int n = s.length();
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
    vector<int> dp(n, 0);

    for (int end = 0; end < n; end++) {
        int minCuts = end;

        for (int start = 0; start <= end; start++) {
            if (s[start] == s[end] && (end - start < 2 || isPalindrome[start + 1][end - 1])) {
                isPalindrome[start][end] = true;
                minCuts = (start == 0) ? 0 : min(minCuts, dp[start - 1] + 1);
            }

            clearScreen();
            cout << " Checking substring: \"" << s.substr(start, end - start + 1) << "\"\n";
            printMatrix(isPalindrome, s, start, end);
            sleep_for(milliseconds(300));
        }

        dp[end] = minCuts;
    }

    cout << "\n Minimum cuts needed to partition \"" << s << "\" into palindromes: " << dp[n - 1] << "\n";
    return dp[n - 1];
}

int main() {
    string input;
    cout << "Enter to visualize palindrome : ";
    cin >> input;

    visualizePalindromePartition(input);
    return 0;
}
