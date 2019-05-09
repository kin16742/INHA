/*#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, s, n, m;
vector<int> cakeN, cakeM;

int main() {
	std::ios::sync_with_stdio(false);
	scanf_s("%d", &t);
	while (t--) {
		int totalN = 0, totalM = 0, total = 0, cnt = 0, temp;
		bool avail = true;
		
		scanf_s("%d %d %d", &s, &n, &m);
		
		for (int i = 0; i < n; i++) {
			scanf_s("%d", &temp);
			cakeN.push_back(temp);
			totalN += temp;
		}
		for (int i = 0; i < m; i++) {
			scanf_s("%d", &temp);
			cakeM.push_back(temp);
			totalM += temp;
		}
		total = totalN + totalM;

		if (s > total) {
			printf("0\n");
			avail = false;
		}
		
		if (avail) {
			int sum;

			cakeN.push_back(0);
			for (int i = 0; i < n; i++) {
				sum = cakeN[i];
				for (int j = i + 1; j < i + n - 1; j++) {
					sum += cakeN[j%n];
					cakeN.push_back(sum);
				}
			}
			cakeN.push_back(totalN);

			cakeM.push_back(0);
			for (int i = 0; i < m; i++) {
				sum = cakeM[i];
				for (int j = i + 1; j < i + m - 1; j++) {
					sum += cakeM[j%m];
					cakeM.push_back(sum);
				}
			}
			cakeM.push_back(totalM);

			sort(cakeN.begin(), cakeN.end());
			sort(cakeM.begin(), cakeM.end());

			for (int i = 0; i < cakeM.size(); i++) {
				if (cakeM[i] > s) break;
				cnt += (int)(upper_bound(cakeN.begin(), cakeN.end(), s - cakeM[i]) - lower_bound(cakeN.begin(), cakeN.end(), s - cakeM[i]));
			}

			printf("%d\n", cnt);

			cakeN.clear();
			cakeM.clear();
		}
	}
	return 0;
}*/