/*#include <iostream>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;

int n, m, fruitNum, temp, curOrderNum, maxFruit;
int fruit[8], templist[8];
bool fruitlist[256];
queue<int> orderList[256];
char r;


void fruitUpdate() {
	int maxFruit = 0;

	memset(fruitlist, 0, sizeof(fruitlist));

	for (int i = 0; i < 8; i++) {
		if(fruit[i] > 0) maxFruit += (1 << i);
	}
	for (int i = 0; i < 256; i++) {
		if (i > maxFruit) break;
		if ((maxFruit & i) == i) {
			fruitlist[i] = true;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(fruit, 0, sizeof(fruit));

	cin >> n;

	while (n--) {
		cin >> r;
		if(r=='D'){
			cin >> m;
			fruit[m]++;
			fruitUpdate();

			int priority = 1000001;
			int pIndex;
			for (int i = 0; i < 256; i++) {
				if (fruitlist[i] && orderList[i].size() > 0) {
					if (orderList[i].front() < priority) {
						priority = orderList[i].front();
						pIndex = i;
					}
				}
			}
			if (priority != 1000001) {
				cout << orderList[pIndex].front() << '\n';
				temp = pIndex;
				for (int i = 0; i < 8; i++) {
					if (temp & (1 << i) != 0 && temp >= i) {
						fruit[i]--;
					}
				}
				orderList[pIndex].pop();
				fruitUpdate();
			}
		}
		else if(r=='O'){
			bool avail = true;

			cin >> fruitNum;

			for (int i = 0; i < fruitNum; i++) {
				cin >> templist[i];
				if (fruit[templist[i]] == 0) avail = false;
			}

			if (!avail) {
				int fruits = 0;

				for (int i = 0; i < fruitNum; i++) {	
					fruits += (1 << (templist[i]));
				}
				orderList[fruits].push(curOrderNum);
			}
			else {
				for (int i = 0; i < fruitNum; i++) {
					fruit[templist[i]]--;
				}
				fruitUpdate();
				cout << curOrderNum << '\n';
			}
			curOrderNum++;
		}
	}
	return 0;
}*/