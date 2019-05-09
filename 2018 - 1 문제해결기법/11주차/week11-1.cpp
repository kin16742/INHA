/*#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int t, sero, garo, garoSum, num, result, maxV;
char ef, carpet[50][50];

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
				for (int j = garoSum; j < garoSum + num; j++) {
					carpet[i][j] = ef;
				}
				garoSum += num;
			}
		}

		for (int i = 0; i < sero; i++) {
			for (int j = 0; j < garo; j++) {
				if (carpet[i][j] == 'f') {

					for (int k = i; k < sero; k++) {
						for (int l = j; l < garo; l++) {
							if (carpet[k][l] == 'f') {

								bool d = true;
								result = 0;

								for (int z = i; z <= k; z++) {
									for (int x = j; x <= l; x++) {
										if (carpet[z][x] == 'f')
											result++;
										else {
											d = false;
											break;
										}
									}
									if (!d) break;
									else maxV = max(maxV, result);
								}
							}
						}
					}
				}
			}
		}
		cout << maxV << '\n';
	}
	return 0;
}*/