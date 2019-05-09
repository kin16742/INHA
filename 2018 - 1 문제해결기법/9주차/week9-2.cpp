/*#include <iostream>
#include <algorithm>
#include <string.h>
#include <fstream>
using namespace std;

int t, n, x, l, result;
int place[10001], pencil[1000001];
bool leftP[10001], rightP[10001];

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);
	fstream in("input.txt");

	in >> t;
	while (t--) {
		in >> n;

		memset(place, 0, sizeof(place));
		memset(pencil, 0, sizeof(pencil));
		memset(leftP, 0, sizeof(leftP));
		memset(rightP, 0, sizeof(rightP));
		place[0] = -1;
		pencil[-1] = 0;

		for (int i = 1; i <= n; i++) {
			in >> x >> l;
			place[i] = x;
			pencil[x] = l;
		}

		for (int i = 1; i < n; i++) {
			if (place[i] - pencil[place[i]] > place[i - 1]) {
				leftP[i] = true;
			}
			if (place[i] + pencil[place[i]] < place[i + 1]) {
				rightP[i] = true;
			}
		}

		result = pencil[place[n]];
		for (int i = 1; i < n; i++) {
			if (leftP[i]) {
				result += pencil[place[i]];
				rightP[i] = false;
			}
			if (rightP[i]) {
				if (leftP[i + 1]) {
					if (place[i] + pencil[place[i]] == place[i + 1] - pencil[place[i + 1]]) {
						if (pencil[place[i + 1]] >= pencil[place[i]]) {
							result += pencil[place[i + 1]];
							leftP[i + 1] = false;
							rightP[i + 1] = false;
						}
						else {
							result += pencil[place[i]];
							leftP[i + 1] = false;
						}
					}
					else if (place[i] + pencil[place[i]] > place[i + 1] - pencil[place[i + 1]]) {
						if (pencil[place[i]] > pencil[place[i + 1]]) {
							result += pencil[place[i]];
							leftP[i + 1] = false;
						}
						else if (pencil[place[i]] <= pencil[place[i + 1]]) {
							result += pencil[place[i + 1]];
							leftP[i + 1] = false;
							rightP[i + 1] = false;
						}
					}
					else {
						if (pencil[place[i]] > pencil[place[i + 1]]) {
							result += pencil[place[i]];
							leftP[i + 1] = false;
						}
						else if (pencil[place[i]] <= pencil[place[i + 1]]) {
							result += pencil[place[i + 1]];
							leftP[i + 1] = false;
							rightP[i + 1] = false;
						}
					}
				}
				else {
					result += pencil[place[i]];
				}
			}
		}
		cout << result << '\n';
	}
	
	return 0;
}*/