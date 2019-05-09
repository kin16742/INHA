/*#include <iostream>
#include <algorithm>
using namespace std;

int t, k, c, teamA, teamB, gap, remain;

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		cin >> k >> c;
		for (int i = 0; i < c; i++) {
			bool chk = 0;
			cin >> teamA >> teamB;

			if (teamA == teamB) {
				chk = 1;
			}
			else if (teamA > teamB) {
				gap = teamA - teamB;
				remain = k - teamA;
				if (gap - remain <= 2) chk = 1;
			}
			else {
				gap = teamB - teamA;
				remain = k - teamB;
				if (gap - remain <= 1) chk = 1;
			}

			if (!chk) {
				cout << "0\n";
			}
			else {
				cout << "1\n";
			}
		}
	}
	return 0;
}*/