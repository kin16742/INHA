/*#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

int T, n, m, a, b, t, fastR, maxR, route[1001], FRoute[1001];
bool visit[1001];

class R {
public:
	int end;
	int dist;
	R() {};
	R(int b, int t) {
		end = b;
		dist = t;
	}
};
class RR {
public:
	int start;
	int end;
	int dist;
	bool fastRoute;
	RR() {};
	RR(int a, int b, int t) {
		start = a;
		end = b;
		dist = t;
		fastRoute = false;
	}
};

vector<R> VR[1001];
vector<RR> VRR;

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	while (T--) {
		maxR = 0;
		cin >> n >> m;
		
		memset(visit, 0, sizeof(visit));
		memset(FRoute, 0, sizeof(FRoute));

		for (int i = 2; i <= n; i++) {
			route[i] = 200000000;
		}

		for (int i = 0; i < m; i++) {
			cin >> a >> b >> t;
			if (a < b) {
				RR tempRR(a, b, t);
				VRR.push_back(tempRR);
			}
			else {
				RR tempRR(b, a, t);
				VRR.push_back(tempRR);
			}
		}
		for (int i = 0; i < m; i++) {
			R tempR1(VRR[i].start, VRR[i].dist);
			R tempR2(VRR[i].end, VRR[i].dist);
			VR[VRR[i].end].push_back(tempR1);
			VR[VRR[i].start].push_back(tempR2);
		}

		for (int i = 0; i < VR[1].size(); i++) {
			route[VR[1][i].end] = VR[1][i].dist;
			FRoute[VR[1][i].end] = 1;
		}
		visit[1] = 1;

		for (int i = 2; i <= n; i++) {
			int L = 200000001, idx;
			for (int j = 2; j <= n; j++) {
				if (route[j] < L && !visit[j]) {
					L = route[j];
					idx = j;
				}
			}
			for (int j = 0; j < VR[idx].size(); j++) {
				if (route[VR[idx][j].end] > route[idx] + VR[idx][j].dist) {
					route[VR[idx][j].end] = route[idx] + VR[idx][j].dist;
					FRoute[VR[idx][j].end] = idx;
				}
			}
			visit[idx] = 1;
		}

		int next = FRoute[n], curr = n;
		while (curr != 1) {
			for (int i = 0; i < VRR.size(); i++) {
				if (VRR[i].start == next && VRR[i].end == curr)
					VRR[i].fastRoute = true;
			}
			curr = FRoute[curr];
			next = FRoute[next];
		}

		fastR = route[n];

		for (int i = 1; i <= n; i++) VR[i].clear();

		for (int i = 0; i < m; i++) {
			if (VRR[i].fastRoute) {
				for (int j = 0; j < m; j++) {
					if (j != i) {
						R tempR1(VRR[j].start, VRR[j].dist);
						R tempR2(VRR[j].end, VRR[j].dist);
						VR[VRR[j].end].push_back(tempR1);
						VR[VRR[j].start].push_back(tempR2);
					}
				}

				memset(visit, 0, sizeof(visit));
				for (int i = 2; i <= n; i++) {
					route[i] = 200000000;
				}

				for (int i = 0; i < VR[1].size(); i++) {
					route[VR[1][i].end] = VR[1][i].dist;
				}
				visit[1] = 1;

				for (int i = 2; i <= n; i++) {
					int L = 200000001, idx;
					for (int j = 2; j <= n; j++) {
						if (route[j] < L && !visit[j]) {
							L = route[j];
							idx = j;
						}
					}
					for (int j = 0; j < VR[idx].size(); j++) {
						route[VR[idx][j].end] = min(route[VR[idx][j].end], route[idx] + VR[idx][j].dist);
					}
					visit[idx] = 1;
				}

				maxR = max(route[n], maxR);

				for (int j = 1; j <= n; j++) VR[j].clear();
			} 
		}
		VRR.clear();

		if (maxR == 200000000) cout << -1 << endl;
		else cout << maxR - fastR << endl;
	}
	return 0;
}*/