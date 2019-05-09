/*#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	int t, n, m;

	cin >> t;

	for (int i = 0; i < t; i++) {
		int result = 800001;
		int price[100][100], restaurant[100][100];

		cin >> n >> m;

		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				cin >> price[j][k];
				restaurant[j][k] = 800001;
			}
		}

		for (int j = 0; j < n; j++)
			restaurant[j][0] = price[j][0];

		for (int k = 1; k < m; k++) {
			for (int j = 0; j < n; j++) {
				for (int l = 0; l < n; l++) {
					if(j!=l)
						restaurant[j][k] = min(restaurant[j][k], restaurant[l][k - 1] + price[j][k]);
				}
			}
		}

		for (int j = 0; j < n; j++)
			result = min(result, restaurant[j][m-1]);
		
		cout << result << endl;
	}
	return 0;
}*/