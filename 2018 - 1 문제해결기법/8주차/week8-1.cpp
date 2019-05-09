/*#include <iostream>
#include <algorithm>
using namespace std;

int t, n, m, std1, std2;
int student[51][51];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> t;
	while (t--) {
		bool valid = true;

		cin >> n >> m;

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				student[i][j] = 1000;
			}
		}

		for (int i = 0; i < m; i++) {
			cin >> std1 >> std2;
			student[std1][std2] = 1;
		}

		for (int k = 1; k <= n; k++) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (student[i][j] > student[i][k] + student[k][j]) {
						student[i][j] = student[i][k] + student[k][j];
						if (student[j][i] != 1000) {
							valid = false;
							break;
						}
					}
				}
				if (!valid)break;
			}
			if (!valid)break;
		}

		if (valid) {
			for (int i = 1; i <= n; i++) {
				int better = 0, worse = 0;

				for (int j = 1; j <= n; j++) {
					if (student[j][i] != 1000)
						better++;
				}

				for (int j = 1; j <= n; j++) {
					if (student[i][j] != 1000)
						worse++;
				}

				cout << better << ' ' << worse << '\n';
			}
		}
		else {
			cout << "-1\n";
		}
	}
	return 0;
}*/