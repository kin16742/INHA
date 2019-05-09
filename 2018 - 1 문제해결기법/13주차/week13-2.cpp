/*#include <iostream>
#include <algorithm>
using namespace std;

int t, n, x, y, minX, minY, maxX, maxY;

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> t;
	while (t--) {
		cin >> n;
		minX = 10001;
		minY = 10001;
		maxX = -10001;
		maxY = -10001;
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			minX = min(x, minX);
			minY = min(y, minY);
			maxX = max(x, maxX);
			maxY = max(y, maxY);
		}
		
		cout << (maxX - minX)*(maxY - minY) << '\n';
	}
	return 0;
}*/