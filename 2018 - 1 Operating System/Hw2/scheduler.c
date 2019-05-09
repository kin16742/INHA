// 12141540 박영창
// OS 2차 과제
// Scheduler simulation
#include <stdio.h>

typedef struct _task {	// task의 정보를 저장할 구조체
	int priority;	// 우선순위
	int taskNum;	// task의 번호
	int runtime;	// task의 수행 시간(CPU burst time)
}task;

typedef struct _ctask {	// task 중 conventional class에 들어갈 task의 정보를 저장할 구조체
	int priority;	// 우선순위
	int taskNum;	// task의 번호
	int runtime;	// task의 수행 시간
	double weight;	// task의 비중
	double vruntime;// task의 vruntime
}ctask;
	
task tempT;					// task 구조체의 연산에 사용될 임시 task 구조체 변수
ctask tempCT;				// ctask 구조체의 연산에 사용될 임시 ctask 구조체 변수
task taskList[100];			// 입력받은 모든 task의 정보를 저장할 task 구조체 배열 -> 문제에 주어진 내용이 없어 최대 100개까지 task를 입력 가능하도록 설정했습니다.
task realTime[101];			// task의 priority가 0~99인 task들을 저장할 real-time RR class를 나타내는 배열
ctask conventional[101];	// task의 priority가 100~139인 task들을 저장할 conventional class를 나타내는 배열

int tasks = 0;				// 입력받은 task의 총 개수

int timeQuantam = 2;		// real-time RR class에서 사용할 time quantam
int pIndex;					// real-time RR class, conventional class에 접근하고 연산할 때 사용될 인덱스

int rIndex = 0;				// real-time RR class 에 있는 task의 수

int cIndex = 0;				// conventional class 에 있는 task의 수

int main(void) {
	int data;
	FILE * input;													// 입력받는 파일을 위해 사용할 변수
	FILE * output;													// 출력할 파일을 위해 사용할 변수

	input = fopen("input.txt", "r");								// input.txt 라는 텍스트 파일을 입력을 위해 연다
	output = fopen("output.txt", "w");								// output.txt라는 텍스트 파일을 출력을 위해 연다 

	if (input == NULL)												// 파일 입력 오류 시 출력
		printf("File error!\n");
	else {
		// 파일로부터 데이터를 입력받아 각 task의 priority, taskNum, runtime에 저장한다
		while (fscanf(input, "%d", &data) != EOF) {						 
			taskList[tasks].priority = data;
			fscanf(input, "%d", &data);
			taskList[tasks].taskNum = data;
			fscanf(input, "%d", &data);
			taskList[tasks].runtime = data;
			tasks++;
		}
		for (int i = 0; i < tasks; i++) {
			// task의 priority가 0~99일 때 해당 task를 real-time RR class에 저장
			if (taskList[i].priority < 100) {												
				realTime[rIndex++] = taskList[i];
			}

			// task의 priority가 100~139일 때 해당 task를 conventional class에 저장
			else if (taskList[i].priority < 140) {											
				conventional[cIndex].priority = taskList[i].priority;
				conventional[cIndex].taskNum = taskList[i].taskNum;
				conventional[cIndex].runtime = taskList[i].runtime;

				//각 task의 우선순위에 따라 비중(weight)를 저장
				if (taskList[i].priority < 110) conventional[cIndex].weight = 10.0;			// 100 < priority < 109 -> weight = 10
				else if (taskList[i].priority < 120) conventional[cIndex].weight = 8.0;		// 110 < priority < 119 -> weight = 8
				else if (taskList[i].priority < 130) conventional[cIndex].weight = 6.0;		// 120 < priority < 129 -> weight = 6
				else if (taskList[i].priority < 140) conventional[cIndex].weight = 4.0;		// 130 < priority < 139 -> weight = 4
				cIndex++;
			}
		}

		// real-time RR class에 저장되어 있는 task들을 priority를 기준으로 정렬한다
		for (int i = 0; i < rIndex; i++) {									
			for (int j = 0; j < rIndex - 1; j++) {
				if (realTime[j].priority > realTime[j + 1].priority) {
					tempT = realTime[j];
					realTime[j] = realTime[j + 1];
					realTime[j + 1] = tempT;
				}
			}
		}

		// conventional class에 저장되어 있는 task들을 priority를 기준으로 정렬한다
		for (int i = 0; i < cIndex; i++) {									
			for (int j = 0; j < cIndex - 1; j++) {
				if (conventional[j].priority > conventional[j + 1].priority) {
					tempCT = conventional[j];
					conventional[j] = conventional[j + 1];
					conventional[j + 1] = tempCT;
				}
			}
		}

		pIndex = 0;	// real-time RR class의 첫 번째 task에 접근하기 위해 0으로 초기화

		// real-time RR class와 conventional class 중에 우선순위가 더 높은 real-time class의 task들부터 처리한다
		while (pIndex != rIndex) {		
			int temp = pIndex;
			int totalRuntime = 0;
			int sameIndex = 1;

			// temp의 인덱스에 저장되어 있는 task와 priority가 같은 task의 수를 파악한다
			while (1) {											
				if (realTime[temp].priority == realTime[temp + 1].priority) {
					sameIndex++;
					temp++;
				}
				else break;
			}

			// real-time RR class에 저장되어 있는 task들 중 같은 priority를 갖는 task들의 총 runtime을 구한다
			for (int i = pIndex; i < pIndex + sameIndex; i++) {					
				totalRuntime += realTime[i].runtime;
			}

			// 같은 priority를 갖는 task들을 RR 방식으로 출력한다
			while (totalRuntime != 0) {							
				temp = pIndex;
				for (int i = 0; i < sameIndex; i++) {
					for (int j = 0; j < timeQuantam; j++) {
						if (realTime[temp + i].runtime > 0) {													// runtime이 0보다 큰지(수행해야 할 시간이 남아있는지) 확인한다
							fprintf(output, "%d %d ", realTime[temp + i].priority, realTime[temp + i].taskNum); // task의 priority, taskNum을 출력하고
							realTime[temp + i].runtime--;														// 해당 task의 runtime을 1 감소시킨 뒤
							totalRuntime--;																		// 같은 priority의 총 수행시간을 1 감소시킨다
						}
					}
				}
			}
			fprintf(output, "\n");	// priority가 변경될 때 개행
			pIndex += sameIndex;	// 처리된 task의 수 만큼 pIndex를 증가시킨다
		}

		pIndex = 0;					// conventional class의 첫 번째 task에 접근하기 위해 0으로 초기화
		int totalRuntime = 0;		// conventional class 내에 존재하는 모든 task의 총 수행시간
		int totalCurrentRuntime = 0;// 현재 수행한 시간
		double totalWeight = 0;		// conventional class 내에 존재하는 모든 task의 비중의 총합
		
		// conventional class 내에 task가 존재한다면, conventional class에 접근한다
		if (conventional[pIndex].priority > 0) {
			// conventional class 내에 존재하는 task들의 총 수행시간과, 비중의 총합을 구한다
			for (int i = 0; i < cIndex; i++) {
				totalRuntime += conventional[i].runtime;
				totalWeight += conventional[i].weight;
			}

			// task들을 CFS 방식으로 출력한다 (현재 수행시간과 총 수행시간이 같아질 때 까지)
			while (totalRuntime != totalCurrentRuntime) {
				pIndex = 0; // 가장 먼저 실행되어야 할 task의 인덱스를 저장할 pIndex

				// vruntime이 가장 작은 task부터 실행해야 하므로 pIndex에 vruntime이 가장 작은 task의 인덱스 저장
				// 만약 여러 task의 vruntime이 같다면, priority가 높은 task부터 실행한다. conventional 배열이 priority 순으로 정렬되어 있으므로 차례대로 확인한다
				for (int i = 1; i < cIndex; i++) {
					if (conventional[i].vruntime < conventional[pIndex].vruntime && conventional[i].runtime > 0) {
						pIndex = i;
					}
				}

				// vruntime이 가장 작은 task의 runtime이 남아있는 경우
				if (conventional[pIndex].runtime > 0) {
					if (tempCT.priority != 0 && tempCT.priority != conventional[pIndex].priority) fprintf(output, "\n");	// priority가 바뀌었다면 개행한다
					fprintf(output, "%d %d ", conventional[pIndex].priority, conventional[pIndex].taskNum);					// task의 priority와 taskNum을 출력
					tempCT = conventional[pIndex];																			// 다음에 수행될 task와 현재 수행한 task의 priority를 비교하기 위해 taskCT에 현재 수행한 task를 저장한다
					totalCurrentRuntime++;																					// 현재 수행시간 1 증가
					conventional[pIndex].runtime--;																			// 수행된 task의 runtime 1 감소
					conventional[pIndex].vruntime += 1024 / conventional[pIndex].weight;									// vruntime += 상수 / (비중) * (수행시간)
																															// 한번 수행될 때마다 vruntime을 확인해 주므로 이 식을 사용해 vruntime을 변경시킨다
				}

				// vruntime이 가장 작은 task의 runtime이 남아있지 않은 경우
				else {
					ctask tempCT2;
					
					// 해당 task를 배열의 맨 뒤로 밀어내고
					for (int i = pIndex; i < cIndex - pIndex; i++) {
						tempCT2 = conventional[i];
						conventional[i] = conventional[i + 1];
						conventional[i + 1] = tempCT2;
					}

					// conventional class 의 task 수를 1 감소시킨다 -> 이 과정은 conventional class에서 수행이 끝난 task를 삭제하는 것과 같다
					cIndex--;
				}
			}
		}
	}
	return 0;
}