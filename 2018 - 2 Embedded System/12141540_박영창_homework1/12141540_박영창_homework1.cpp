#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#define ll long long int
using namespace std;

ll n, m, k, a, b, c, sTree[4000000];

ll update(ll idx,ll val,ll node,ll left,ll right) {
	if (idx < left || idx > right) return sTree[node];
	if (left == right) return sTree[node] = val;
	ll mid = (left + right) / 2;
	return sTree[node] = update(idx, val, node * 2, left, mid) + update(idx, val, node * 2 + 1, mid + 1, right);
}

ll query(ll start, ll end, ll node, ll left, ll right) {
	if (left >= start && right <= end) return sTree[node];
	if (left > end || right < start) return 0;
	ll mid = (left + right) / 2;
	return query(start, end, node * 2, left, mid) + query(start, end, node * 2 + 1, mid + 1, right);
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		cin >> a;
		update(i, a, 1, 1, n);
	}
	for (int i = 0; i < k; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c;
			update(b, c, 1, 1, n);
		}
		if (a == 2) {
			cin >> b >> c;
			cout << query(b, c, 1, 1, n) << '\n';
		}
	}
	return 0;
}