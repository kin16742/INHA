/*#include <iostream>
using namespace std;

struct man {
	man *up;
	int docNum;
};

man team[100001];
man *goal;
int n, depth1, depth2;

void searchGoal(int, int);
void document(int, int, int);
void under(int, int);
void kinds(int, int);

int main() {
	std::ios::sync_with_stdio(false);
	int k, r, a, b, c;
	
	cin >> n >> k;

	team[1].up = NULL;
	team[1].docNum = 0;
	for (int i = 2; i <= n; i++) {
		team[i].up = &team[1];
		team[i].docNum = 1;
	}

	for (int i = 0; i < k; i++) {
		cin >> r;
		if (r == 1) {
			cin >> a >> b >> c;
			document(a, b, c);
		}
		if (r == 2) {
			cin >> a >> b;
			under(a, b);
		}
		if (r == 3) {
			cin >> a >> b;
			kinds(a, b);
		}
	}
	return 0;
}

void searchGoal(int sIndex1, int sIndex2) {
	man *t1 = &team[sIndex1];
	man *t2 = &team[sIndex2];
	int tempD1, tempD2;
	depth1 = 0;
	depth2 = 0;

	while (t1->up != NULL) {
		depth1++;
		t1 = t1->up;
	}
	while (t2->up != NULL) {
		depth2++;
		t2 = t2->up;
	}

	if (sIndex1 == 1 || sIndex2 == 1) {
		goal = &team[1];
		return;
	}

	t1 = &team[sIndex1];
	t2 = &team[sIndex2];
	tempD1 = depth1;
	tempD2 = depth2;
	if (tempD1 > tempD2) {
		while (tempD1 - tempD2 > 0) {
			t1 = t1->up;
			tempD1--;
		}
		while (tempD1--) {
			if (t1->up == t2->up) {
				goal = t1->up;
				return;
			}
			t1 = t1->up;
			t2 = t2->up;
		}
	}
	else if (tempD2 > tempD1) {
		while (tempD2 - tempD1 > 0) {
			t2 = t2->up;
			tempD2--;
		}
		while (tempD2--) {
			if (t1->up == t2->up) {
				goal = t1->up;
				return;
			}
			t1 = t1->up;
			t2 = t2->up;
		}
	}
	else {
		while (tempD1--) {
			if (t1->up == t2->up) {
				goal = t1->up;
				break;
			}
			t1 = t1->up;
			t2 = t2->up;
		}
	}
}
void document(int sIndex1, int sIndex2, int doc) {
	man *t1 = &team[sIndex1];
	man *t2 = &team[sIndex2];
	searchGoal(sIndex1, sIndex2);
	int tempD1 = depth1, tempD2 = depth2;

	if (tempD1 > tempD2) {
		while (tempD1 - tempD2 > 0) {
			t1->docNum = doc;
			t1 = t1->up;
			tempD1--;
		}
		if (t1 == t2) return;
		while (tempD1--) {
			t1->docNum = doc;
			t2->docNum = doc;

			if (t1->up == t2->up) return;

			t1 = t1->up;
			t2 = t2->up;
		}
	}
	else if (tempD2 > tempD1) {
		while (tempD2 - tempD1 > 0) {
			t2->docNum = doc;
			t2 = t2->up;
			tempD2--;
		}
		if (t1 == t2) return;
		while (tempD2--) {
			t1->docNum = doc;
			t2->docNum = doc;

			if (t1->up == t2->up) return;

			t1 = t1->up;
			t2 = t2->up;
		}
	}
	else {
		if (t1 == t2) return;
		while (tempD1--) {
			t1->docNum = doc;
			t2->docNum = doc;

			if (t1->up == t2->up) return;

			t1 = t1->up;
			t2 = t2->up;
		}
	}
}
void under(int sIndex1, int sIndex2) {
	team[sIndex1].up = &team[sIndex2];
}
void kinds(int sIndex1, int sIndex2) {
	man *t1 = &team[sIndex1];
	man *t2 = &team[sIndex2]; 
	searchGoal(sIndex1, sIndex2);
	int tempD1 = depth1, tempD2 = depth2;

	int docs[101] = { 0 };
	int kinds = 0;

	team[1].docNum = 0;

	if (t1 == t2) {
		cout << 0 << endl;
		return;
	}
	while (tempD1 != tempD2) {
		if (tempD1 > tempD2) {
			docs[t1->docNum]++;
			t1 = t1->up;
			tempD1--;
		}
		else if (tempD2 > tempD1) {
			docs[t2->docNum]++;
			t2 = t2->up;
			tempD2--;
		}
	}

	if (t1 != t2) {
		while (t1 != goal) {
			docs[t1->docNum]++;
			docs[t2->docNum]++;
			t1 = t1->up;
			t2 = t2->up;
		}
	}

	for (int i = 1; i <= 100; i++) {
		if (docs[i] > 0)
			kinds++;
	}

	cout << kinds << endl;
}*/