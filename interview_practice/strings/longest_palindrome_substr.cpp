/*Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
*/

#include <iostream>

using namespace std;

void longest_palindrome_substr(char ch_arr[], int length, char *sub_arr) {
    int i = 0, j;
    for (i = 0; i<length - 1; i++) {
        for (j = length - 1; j>i; j--) {
            if (ch_arr[i] == ch_arr[j]) {
                int low = i;
                int high = j;
                while (low < high && ch_arr[low++] == ch_arr[high--]);
                if (low >= high && ch_arr[low] == ch_arr[high]) {
                    int k;
                    for (k = i; k <= j; k++) {
                        sub_arr[k - i] = ch_arr[k];
                    }
                    sub_arr[k-i] = '\0';
                    return;
                }
            }
        }
    }
    sub_arr[0] = '\0';
}

int main() {
    char pal[] = "cbbd\0";
    char new_pal[100];

    int length = 0, i = 0;

    while (pal[length++] != '\0');
    length--;
    longest_palindrome_substr(pal, length, new_pal);

    cout << "Sub palindrome is = ";
    while (new_pal[i] != '\0') {
        cout << new_pal[i++];
    }

    return 0;
}