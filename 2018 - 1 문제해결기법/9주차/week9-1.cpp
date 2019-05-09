/*#include <iostream>
#include <algorithm>
using namespace std;

int t, n, m, total, maxB, first, last, middle;
int bread[10000];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
		
	cin >> t;
	while (t--) {
		cin >> n >> m;

		total = 0;
		for (int i = 0; i < n; i++) {
			cin >> bread[i];
			total += bread[i];
			maxB = max(maxB, bread[i]);
		}
		
		if (total <= m) {
			cout << total << '\n';
		}
		else {
			first = 0;
			last = maxB;
			while (first < last) {
				total = 0;
				middle = (first + last) / 2;
				for (int j = 0; j < n; j++) {
					if (bread[j] >= middle) {
						total += middle;
					}
					else {
						total += bread[j];
					}
				}
				if (total > m) {
					last = middle;
				}
				else {
					if (first == middle) break;
					first = middle;
				}
			}
			cout << total << '\n';
		}
	}
}*/