/*#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int t, n, m, place[1050], dp[1050][1050];

int getDist(int idx1, int idx2) {
	return abs(place[idx1] - place[idx2]);
}

int repair(int aIndex, int bIndex, int count) {
	if (count == m + 2)
		return 0;

	int &ret = dp[aIndex][bIndex];

	if (ret != -1)
		return ret;
	
	ret = min(repair(count, bIndex, count + 1) + getDist(aIndex, count), repair(count, aIndex, count + 1) + getDist(bIndex, count));;

	return ret;
}

int main() {
	cin >> t;
	while (t--) {
		memset(dp, -1, sizeof(dp));
		cin >> n >> m;
		place[0] = 0;
		place[1] = n;
		for (int i = 2; i <= m + 1; i++) {
			cin >> place[i];
		}
		printf("%d\n", repair(0, 1, 2));
	}
	return 0;
}*/