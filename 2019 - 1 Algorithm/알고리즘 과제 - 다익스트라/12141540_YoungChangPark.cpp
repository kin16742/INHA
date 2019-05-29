#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct loc {
	// 지역 정보 구조체
	int locNum;				 // 지역 번호
	char locName[20];		 // 지역명
	bool flood;				 // 침수 여부
	bool operator< (loc l) { // 지역 번호로 정렬하기 위한 연산자 오버로딩
		return this->locNum < l.locNum; 
	}	
};

struct edge {
	// 간선 정보 구조체
	int to;					 // 도착 정점 값
	int from;			 	 // 출발 정점 값
	int weight;				 // 정점 가중치
};

int n, m, q;										// 입력 받을 정점 개수, 간선 개수, 질의 개수
char command;										// 질의 커맨드

loc location[100005];								// 지역 정보 배열
int locIdx[1000005];								// 지역 정보의 지역 번호를 지역 정보 배열 내의 인덱스와 매핑할 배열

vector<edge> tree;									// tree set
priority_queue<pair<int, pair<int, int>>> fringe;	// fringe set
bool inTree[100005];								// tree set에 들어가 있는지를 저장한 배열
int dist[100005];									// tree set에 들어감에 따라 갱신되는 최단 경로 배열

vector<vector<pair<int, int>>> navi;				// 2차원 벡터로 구현한 인접 리스트 그래프

void shortestLength(int, int);						// 최단 경로의 길이를 출력하는 함수
void shortestPath(int, int);						// 최단 경로를 출력하는 함수
void dijkstra(int, int);							// 최단 경로를 구하는 다익스트라 알고리즘을 진행하는 함수

int main(){
	cin >> n >> m >> q;

	navi.resize(n + 1);

	// 정점(지역) 정보 입력
	for (int i = 1; i <= n; i++) {
		cin >> location[i].locNum >> location[i].locName >> location[i].flood;
	}

	// 지역 정보를 지역 번호 순으로 정렬
	sort(location + 1, location + n + 1);

	// 각 지역 번호와 인덱스를 매핑
	for (int i = 1; i <= n; i++) {
		locIdx[location[i].locNum] = i;
	}

	// 간선 정보 입력
	for (int i = 1; i <= m; i++) {
		int start, end, weight;

		cin >> start >> end >> weight;

		// 무향 그래프이므로 양쪽 정점에 모두 추가
		navi[locIdx[start]].push_back({ locIdx[end],weight });
		navi[locIdx[end]].push_back({ locIdx[start],weight });
	}

	// 질의
	while (q--) {
		int source, destination;

		cin >> command >> source >> destination;

		if (command == 'A')	// 최단 경로 길이
			shortestLength(locIdx[source], locIdx[destination]);
		if (command == 'B') // 최단 경로
			shortestPath(locIdx[source], locIdx[destination]);
	}

	return 0;
}

void shortestLength(int s, int d) {
	dijkstra(s, d);	// s -> d 의 최단 경로를 구한다

	if (dist[d] == 0 || dist[d] > 1000000) 
		// 침수되었거나 경로의 길이가 10^6을 초과하는 경우
		cout << "None" << endl;
	else 
		cout << tree.size() << ' ' << dist[d] << ' ' << location[s].locName << ' ' << location[d].locName << endl;
		// 출발점부터 도착점까지 최단 경로를 계산하는 동안 tree set에 들어간 정점 개수, 최단 경로의 길이, 출발 지역명, 도착 지역명 출력
}

void shortestPath(int s, int d) {
	dijkstra(s, d); // s -> d 의 최단 경로를 구한다

	if (dist[d] == 0 || dist[d] > 1000000) 
		// 침수되었거나 경로의 길이가 10^6을 초과하는 경우
		cout << "None" << endl;
	else {
		stack<int> s;	// 최단 경로 내의 지역 번호들을 저장할 스택

		int next = d;
		while (next != 0) {
			// tree set에 저장된 간선 정보들을 통해 최단 경로의 지역 번호들을 저장한다
			s.push(location[next].locNum);
			for (int i = 0; i < tree.size(); i++) {
				if (tree[i].to == next) {
					next = tree[i].from;
					break;
				}
			}
		}
		cout << tree.size() << ' '; 
		// 출발점부터 도착점까지 최단 경로를 계산하는 동안 tree set에 들어간 정점 개수 출력
		while (!s.empty()) {
			// 스택 내의 지역 번호 출력
			cout << s.top() << ' ';
			s.pop();
		}
		cout << endl;
	}
}

void dijkstra(int s, int d) {
	// 전역 변수 초기화
	tree.clear();

	while (fringe.size())
		fringe.pop();

	memset(inTree, 0, sizeof(inTree));
	memset(dist, 0, sizeof(dist));


	// tree set에 출발 지역을 추가
	tree.push_back({ s,0,0 });
	inTree[s] = true;

	// 출발 지역 정점에서 출발하는 간선들의 정보를 fringe set에 추가
	for (int i = 0; i < navi[s].size(); i++) {
		if (!location[s].flood && !location[navi[s][i].first].flood) {
			// 출발점 또는 도착점이 침수되었다면 추가하지 않음
			fringe.push({ -navi[s][i].second, { -navi[s][i].first, s} });
		}
	}
	
	while (fringe.size()) {
		pair<int, pair<int, int>> minV = fringe.top();	
		// fringe set에서 가중치가 가장 작고, 가중치가 같다면 도착점의 번호가 가장 낮은 간선을 선택

		int minWeight = -minV.first;		// 선택된 간선의 가중치
		int minIdx = -minV.second.first;	// 선택된 간선의 도착점
		int minFrom = minV.second.second;	// 선택된 간선의 출발점
		
		if (!inTree[minIdx]) {
			// 선택된 간선의 도착점이 tree set에 들어있지 않은 경우
			tree.push_back({ minIdx, minFrom, minWeight });		// tree set에 도착점을 추가 
			dist[minIdx] = minWeight;							// 추가된 도착점으로의 최단 경로 갱신
			inTree[minIdx] = true;
		}
		else {
			// 이미 tree set에 들어있는 경우
			fringe.pop();
			continue;
		}

		if (minIdx == d) break;	// 목적지까지의 최단 경로가 갱신되면 종료

		
		// 선택된 간선의 도착점에서 출발하는 간선들의 정보를 fringe set에 추가
		for (int i = 0; i < navi[minIdx].size(); i++) {
			if (!location[minIdx].flood && !location[navi[minIdx][i].first].flood) {
				// 출발점 또는 도착점이 침수되지 않고
				if (!inTree[navi[minIdx][i].first]) {
					// 이미 tree set에 들어있지 않다면 추가
					fringe.push({ -(navi[minIdx][i].second + dist[minIdx]), { -navi[minIdx][i].first, minIdx } });
				}
			}
		}

		fringe.pop();
	}
}