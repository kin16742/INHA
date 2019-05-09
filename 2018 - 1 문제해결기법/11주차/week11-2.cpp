/*#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int t, sero, garo, garoSum, num, maxV, carpet[500][500];
char ef;

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;

	while (t--) {
		maxV = 0;

		memset(carpet, 0, sizeof(carpet));
		cin >> sero >> garo;

		for (int i = 0; i < sero; i++) {
			garoSum = 0;
			while (garoSum != garo) {
				cin >> num >> ef;
				if (ef == 'f') {
					for (int j = garoSum; j < garoSum + num; j++) {
						carpet[i][j] = 1;
					}
				}
				garoSum += num;
			}
		}

		for (int i = 1; i < sero; i++) {
			for (int j = 0; j < garo; j++) {
				if (carpet[i][j] != 0) {
					carpet[i][j] += carpet[i - 1][j];
				}
			}
		}

		for (int i = 0; i < sero; i++) {
			for (int j = 0; j < garo; j++) {
				int height = carpet[i][j], width = carpet[i][j];

				for (int k = j - 1; k >= 0; k--) {
					if (carpet[i][k] < height) {
						break;
					}
					else {
						width += height;
					}
				}

				for (int k = j + 1; k < garo; k++) {
					if (carpet[i][k] < height) {
						break;
					}
					else {
						width += height;
					}
				}

				maxV = max(maxV, width);
			}
		}

		cout << maxV << '\n';
	}

	return 0;
}*/