/*#include <iostream>
using namespace std;

int main() {
	std::ios::sync_with_stdio(false);
	int t, n, num;

	scanf("%d", &t);

	while (t--) {
		int arr[1000001] = { 0 };
		int cnt = 0;
		
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", &num);
			arr[num / 30] += (1 << (num % 30));
		}

		for (int i = 0; i < n; i++) {
			scanf("%d", &num);
			if ((arr[num / 30] & (1 << (num % 30))) == 0) {
				printf("%d ", num);
				cnt++;
			}
		}

		if (cnt)
			printf("\n");
		else
			printf("0\n");
	}
	return 0;
}*/