#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct loc {
	// ���� ���� ����ü
	int locNum;				 // ���� ��ȣ
	char locName[20];		 // ������
	bool flood;				 // ħ�� ����
	bool operator< (loc l) { // ���� ��ȣ�� �����ϱ� ���� ������ �����ε�
		return this->locNum < l.locNum; 
	}	
};

struct edge {
	// ���� ���� ����ü
	int to;					 // ���� ���� ��
	int from;			 	 // ��� ���� ��
	int weight;				 // ���� ����ġ
};

int n, m, q;										// �Է� ���� ���� ����, ���� ����, ���� ����
char command;										// ���� Ŀ�ǵ�

loc location[100005];								// ���� ���� �迭
int locIdx[1000005];								// ���� ������ ���� ��ȣ�� ���� ���� �迭 ���� �ε����� ������ �迭

vector<edge> tree;									// tree set
priority_queue<pair<int, pair<int, int>>> fringe;	// fringe set
bool inTree[100005];								// tree set�� �� �ִ����� ������ �迭
int dist[100005];									// tree set�� ���� ���� ���ŵǴ� �ִ� ��� �迭

vector<vector<pair<int, int>>> navi;				// 2���� ���ͷ� ������ ���� ����Ʈ �׷���

void shortestLength(int, int);						// �ִ� ����� ���̸� ����ϴ� �Լ�
void shortestPath(int, int);						// �ִ� ��θ� ����ϴ� �Լ�
void dijkstra(int, int);							// �ִ� ��θ� ���ϴ� ���ͽ�Ʈ�� �˰����� �����ϴ� �Լ�

int main(){
	cin >> n >> m >> q;

	navi.resize(n + 1);

	// ����(����) ���� �Է�
	for (int i = 1; i <= n; i++) {
		cin >> location[i].locNum >> location[i].locName >> location[i].flood;
	}

	// ���� ������ ���� ��ȣ ������ ����
	sort(location + 1, location + n + 1);

	// �� ���� ��ȣ�� �ε����� ����
	for (int i = 1; i <= n; i++) {
		locIdx[location[i].locNum] = i;
	}

	// ���� ���� �Է�
	for (int i = 1; i <= m; i++) {
		int start, end, weight;

		cin >> start >> end >> weight;

		// ���� �׷����̹Ƿ� ���� ������ ��� �߰�
		navi[locIdx[start]].push_back({ locIdx[end],weight });
		navi[locIdx[end]].push_back({ locIdx[start],weight });
	}

	// ����
	while (q--) {
		int source, destination;

		cin >> command >> source >> destination;

		if (command == 'A')	// �ִ� ��� ����
			shortestLength(locIdx[source], locIdx[destination]);
		if (command == 'B') // �ִ� ���
			shortestPath(locIdx[source], locIdx[destination]);
	}

	return 0;
}

void shortestLength(int s, int d) {
	dijkstra(s, d);	// s -> d �� �ִ� ��θ� ���Ѵ�

	if (dist[d] == 0 || dist[d] > 1000000) 
		// ħ���Ǿ��ų� ����� ���̰� 10^6�� �ʰ��ϴ� ���
		cout << "None" << endl;
	else 
		cout << tree.size() << ' ' << dist[d] << ' ' << location[s].locName << ' ' << location[d].locName << endl;
		// ��������� ���������� �ִ� ��θ� ����ϴ� ���� tree set�� �� ���� ����, �ִ� ����� ����, ��� ������, ���� ������ ���
}

void shortestPath(int s, int d) {
	dijkstra(s, d); // s -> d �� �ִ� ��θ� ���Ѵ�

	if (dist[d] == 0 || dist[d] > 1000000) 
		// ħ���Ǿ��ų� ����� ���̰� 10^6�� �ʰ��ϴ� ���
		cout << "None" << endl;
	else {
		stack<int> s;	// �ִ� ��� ���� ���� ��ȣ���� ������ ����

		int next = d;
		while (next != 0) {
			// tree set�� ����� ���� �������� ���� �ִ� ����� ���� ��ȣ���� �����Ѵ�
			s.push(location[next].locNum);
			for (int i = 0; i < tree.size(); i++) {
				if (tree[i].to == next) {
					next = tree[i].from;
					break;
				}
			}
		}
		cout << tree.size() << ' '; 
		// ��������� ���������� �ִ� ��θ� ����ϴ� ���� tree set�� �� ���� ���� ���
		while (!s.empty()) {
			// ���� ���� ���� ��ȣ ���
			cout << s.top() << ' ';
			s.pop();
		}
		cout << endl;
	}
}

void dijkstra(int s, int d) {
	// ���� ���� �ʱ�ȭ
	tree.clear();

	while (fringe.size())
		fringe.pop();

	memset(inTree, 0, sizeof(inTree));
	memset(dist, 0, sizeof(dist));


	// tree set�� ��� ������ �߰�
	tree.push_back({ s,0,0 });
	inTree[s] = true;

	// ��� ���� �������� ����ϴ� �������� ������ fringe set�� �߰�
	for (int i = 0; i < navi[s].size(); i++) {
		if (!location[s].flood && !location[navi[s][i].first].flood) {
			// ����� �Ǵ� �������� ħ���Ǿ��ٸ� �߰����� ����
			fringe.push({ -navi[s][i].second, { -navi[s][i].first, s} });
		}
	}
	
	while (fringe.size()) {
		pair<int, pair<int, int>> minV = fringe.top();	
		// fringe set���� ����ġ�� ���� �۰�, ����ġ�� ���ٸ� �������� ��ȣ�� ���� ���� ������ ����

		int minWeight = -minV.first;		// ���õ� ������ ����ġ
		int minIdx = -minV.second.first;	// ���õ� ������ ������
		int minFrom = minV.second.second;	// ���õ� ������ �����
		
		if (!inTree[minIdx]) {
			// ���õ� ������ �������� tree set�� ������� ���� ���
			tree.push_back({ minIdx, minFrom, minWeight });		// tree set�� �������� �߰� 
			dist[minIdx] = minWeight;							// �߰��� ������������ �ִ� ��� ����
			inTree[minIdx] = true;
		}
		else {
			// �̹� tree set�� ����ִ� ���
			fringe.pop();
			continue;
		}

		if (minIdx == d) break;	// ������������ �ִ� ��ΰ� ���ŵǸ� ����

		
		// ���õ� ������ ���������� ����ϴ� �������� ������ fringe set�� �߰�
		for (int i = 0; i < navi[minIdx].size(); i++) {
			if (!location[minIdx].flood && !location[navi[minIdx][i].first].flood) {
				// ����� �Ǵ� �������� ħ������ �ʰ�
				if (!inTree[navi[minIdx][i].first]) {
					// �̹� tree set�� ������� �ʴٸ� �߰�
					fringe.push({ -(navi[minIdx][i].second + dist[minIdx]), { -navi[minIdx][i].first, minIdx } });
				}
			}
		}

		fringe.pop();
	}
}