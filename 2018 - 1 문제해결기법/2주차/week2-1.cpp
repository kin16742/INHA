/*#include <iostream>
#include <string.h>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	char arr1[80], arr2[80];
	int t;

	cin >> t;

	for (int i = 0; i < t; i++) {
		bool empty = true;

		cin >> arr1 >> arr2;

		for (int j = 0; j < strlen(arr1); j++) {
			bool used = false;
			for (int k = 0; k < strlen(arr2); k++) {
				if (arr2[k] == arr1[j]) {
					arr2[k] = '0';
					used = true;
				}
			}
			if (used)
				arr1[j] = '0';
		}

		for (int j = 0; j < strlen(arr2); j++) {
			if (arr2[j] != '0') {
				empty = false;
				break;
			}
		}

		for (int j = 0; j < strlen(arr1); j++) {
			if (arr1[j] != '0') {
				empty = false;
				break;
			}
		}

		if (empty)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}*/