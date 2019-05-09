/*#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	int T, p, n;
	int coin[500];
	int dp[10001] = { 0 };
	cin >> T;
	for (int i = 0; i < T; i++) {
		for (int j = 1; j < 10001; j++) {
			dp[j] = 100000;
		}
		cin >> p >> n;
		for (int j = 0; j < n; j++) {
			cin >> coin[j];
		}
		p = 10000 - p;
		for (int j = 0; j < n; j++) {
			for (int k = coin[j]; k <= p; k++) {
				dp[k] = min(dp[k], dp[k-coin[j]] + 1);
			}
		}
		if (dp[p] >= 100000) 
			cout << 0 << endl;
		else
			cout << dp[p] << endl;

	}
	return 0;
}*/