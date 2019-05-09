/*#include <iostream>
#include <string.h>
using namespace std;

char arr[7];
char res[7];
int num1, num2, t;

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		int idx = 0;
		bool chk = true;
		num1 = 0;
		num2 = 0;
		memset(arr, 0, sizeof(arr));
		memset(res, 0, sizeof(arr));
		cin >> arr;
		for (int i = 0; i < strlen(arr); i++) {
			num1 *= 10;
			num2 *= 10;
			num1 += arr[i] - 48;
			num2 += arr[strlen(arr) - 1 - i] - 48;
		}
		num1 += num2;
		while (num1 != 0) {
			res[idx++] = num1 % 10 + 1;
			num1 /= 10;
		}
		for (int i = 0; i < strlen(res) / 2; i++) {
			if (res[i] != res[strlen(res) - 1 - i]) {
				chk = false;
				break;
			}
		}
		if (chk) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	return 0;
}*/