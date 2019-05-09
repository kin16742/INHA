/*#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

int t;
char arr[101];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	while (t--) {
		cin >> arr;
		int length = strlen(arr);
		int idx1, idx2;
		char *ptr;
		bool desc = 1;

		for (int i = 0; i < length - 1; i++) {
			if (arr[i] < arr[i + 1]) {
				desc = false;
			}
		}

		if (!desc) {
			for (int i = 0; i < length - 1; i++) {
				if (arr[i] < arr[i + 1])
					idx1 = i;
			}

			for (int i = idx1 + 1; i < length; i++) {
				if (arr[i] > arr[idx1])
					idx2 = i;
			}

			swap(arr[idx1], arr[idx2]);

			ptr = &arr[idx1 + 1];

			for (int i = 0; i < strlen(ptr) / 2; i++) {
				swap(ptr[i], ptr[strlen(ptr) - i - 1]);
			}
		}

		for (int i = 0; i < length; i++) {
			cout << arr[i];
		}

		cout << endl;
	}
	return 0;
}*/