/*
#include <iostream>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false); 
	int T, p, n, cnt = 0;
	int coin[14];
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> p >> n;
		for (int j = 0; j < n; j++) {
			cin >> coin[j];
		}
		p = 10000 - p;
		if (p % coin[0] == 0) {
			for (int j = n - 1; j >= 0; j--) {
				while (p != 0) {
					if (p >= coin[j]) {
						p -= coin[j];
						cnt++;
					}
					else
						break;
				}
			}
		}
		cout << cnt << endl;
		cnt = 0;
	}
	return 0;
}
*/