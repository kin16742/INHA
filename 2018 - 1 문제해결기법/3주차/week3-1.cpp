/*#include <iostream>
using namespace std;
int white, black;
int image[256][256];
void bw(int x, int y, int length);

int main() {
	std::ios::sync_with_stdio(false);
	int t, n;

	cin >> t;

	for (int i = 0; i < t; i++) {
		white = 0;
		black = 0;

		cin >> n;

		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				cin >> image[j][k];
			}
		}
		
		bw(0, 0, n);

		cout << white << " " << black << endl;
	}
	return 0;
}

void bw(int x, int y, int length) {
	bool sameColor = true;
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1; j++) {
			if (image[i + x][j + y] != image[i + x][j + y + 1] || image[i + x][j + y] != image[i + x + 1][j + y] || image[i + x][j + y] != image[i + x + 1][j + y + 1]) {
				sameColor = false;
			}
			if (!sameColor) {
				bw(x, y, length / 2);
				bw(x + length / 2, y, length / 2);
				bw(x + length / 2, y + length / 2, length / 2);
				bw(x, y + length / 2, length / 2);
				return;
			}
		}
	}
	if (sameColor) {
		if (image[x][y] == 0)
			white++;
		else
			black++;
	}
}*/