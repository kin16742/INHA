// 12141540 �ڿ�â
// OS 2�� ����
// Scheduler simulation
#include <stdio.h>

typedef struct _task {	// task�� ������ ������ ����ü
	int priority;	// �켱����
	int taskNum;	// task�� ��ȣ
	int runtime;	// task�� ���� �ð�(CPU burst time)
}task;

typedef struct _ctask {	// task �� conventional class�� �� task�� ������ ������ ����ü
	int priority;	// �켱����
	int taskNum;	// task�� ��ȣ
	int runtime;	// task�� ���� �ð�
	double weight;	// task�� ����
	double vruntime;// task�� vruntime
}ctask;
	
task tempT;					// task ����ü�� ���꿡 ���� �ӽ� task ����ü ����
ctask tempCT;				// ctask ����ü�� ���꿡 ���� �ӽ� ctask ����ü ����
task taskList[100];			// �Է¹��� ��� task�� ������ ������ task ����ü �迭 -> ������ �־��� ������ ���� �ִ� 100������ task�� �Է� �����ϵ��� �����߽��ϴ�.
task realTime[101];			// task�� priority�� 0~99�� task���� ������ real-time RR class�� ��Ÿ���� �迭
ctask conventional[101];	// task�� priority�� 100~139�� task���� ������ conventional class�� ��Ÿ���� �迭

int tasks = 0;				// �Է¹��� task�� �� ����

int timeQuantam = 2;		// real-time RR class���� ����� time quantam
int pIndex;					// real-time RR class, conventional class�� �����ϰ� ������ �� ���� �ε���

int rIndex = 0;				// real-time RR class �� �ִ� task�� ��

int cIndex = 0;				// conventional class �� �ִ� task�� ��

int main(void) {
	int data;
	FILE * input;													// �Է¹޴� ������ ���� ����� ����
	FILE * output;													// ����� ������ ���� ����� ����

	input = fopen("input.txt", "r");								// input.txt ��� �ؽ�Ʈ ������ �Է��� ���� ����
	output = fopen("output.txt", "w");								// output.txt��� �ؽ�Ʈ ������ ����� ���� ���� 

	if (input == NULL)												// ���� �Է� ���� �� ���
		printf("File error!\n");
	else {
		// ���Ϸκ��� �����͸� �Է¹޾� �� task�� priority, taskNum, runtime�� �����Ѵ�
		while (fscanf(input, "%d", &data) != EOF) {						 
			taskList[tasks].priority = data;
			fscanf(input, "%d", &data);
			taskList[tasks].taskNum = data;
			fscanf(input, "%d", &data);
			taskList[tasks].runtime = data;
			tasks++;
		}
		for (int i = 0; i < tasks; i++) {
			// task�� priority�� 0~99�� �� �ش� task�� real-time RR class�� ����
			if (taskList[i].priority < 100) {												
				realTime[rIndex++] = taskList[i];
			}

			// task�� priority�� 100~139�� �� �ش� task�� conventional class�� ����
			else if (taskList[i].priority < 140) {											
				conventional[cIndex].priority = taskList[i].priority;
				conventional[cIndex].taskNum = taskList[i].taskNum;
				conventional[cIndex].runtime = taskList[i].runtime;

				//�� task�� �켱������ ���� ����(weight)�� ����
				if (taskList[i].priority < 110) conventional[cIndex].weight = 10.0;			// 100 < priority < 109 -> weight = 10
				else if (taskList[i].priority < 120) conventional[cIndex].weight = 8.0;		// 110 < priority < 119 -> weight = 8
				else if (taskList[i].priority < 130) conventional[cIndex].weight = 6.0;		// 120 < priority < 129 -> weight = 6
				else if (taskList[i].priority < 140) conventional[cIndex].weight = 4.0;		// 130 < priority < 139 -> weight = 4
				cIndex++;
			}
		}

		// real-time RR class�� ����Ǿ� �ִ� task���� priority�� �������� �����Ѵ�
		for (int i = 0; i < rIndex; i++) {									
			for (int j = 0; j < rIndex - 1; j++) {
				if (realTime[j].priority > realTime[j + 1].priority) {
					tempT = realTime[j];
					realTime[j] = realTime[j + 1];
					realTime[j + 1] = tempT;
				}
			}
		}

		// conventional class�� ����Ǿ� �ִ� task���� priority�� �������� �����Ѵ�
		for (int i = 0; i < cIndex; i++) {									
			for (int j = 0; j < cIndex - 1; j++) {
				if (conventional[j].priority > conventional[j + 1].priority) {
					tempCT = conventional[j];
					conventional[j] = conventional[j + 1];
					conventional[j + 1] = tempCT;
				}
			}
		}

		pIndex = 0;	// real-time RR class�� ù ��° task�� �����ϱ� ���� 0���� �ʱ�ȭ

		// real-time RR class�� conventional class �߿� �켱������ �� ���� real-time class�� task����� ó���Ѵ�
		while (pIndex != rIndex) {		
			int temp = pIndex;
			int totalRuntime = 0;
			int sameIndex = 1;

			// temp�� �ε����� ����Ǿ� �ִ� task�� priority�� ���� task�� ���� �ľ��Ѵ�
			while (1) {											
				if (realTime[temp].priority == realTime[temp + 1].priority) {
					sameIndex++;
					temp++;
				}
				else break;
			}

			// real-time RR class�� ����Ǿ� �ִ� task�� �� ���� priority�� ���� task���� �� runtime�� ���Ѵ�
			for (int i = pIndex; i < pIndex + sameIndex; i++) {					
				totalRuntime += realTime[i].runtime;
			}

			// ���� priority�� ���� task���� RR ������� ����Ѵ�
			while (totalRuntime != 0) {							
				temp = pIndex;
				for (int i = 0; i < sameIndex; i++) {
					for (int j = 0; j < timeQuantam; j++) {
						if (realTime[temp + i].runtime > 0) {													// runtime�� 0���� ū��(�����ؾ� �� �ð��� �����ִ���) Ȯ���Ѵ�
							fprintf(output, "%d %d ", realTime[temp + i].priority, realTime[temp + i].taskNum); // task�� priority, taskNum�� ����ϰ�
							realTime[temp + i].runtime--;														// �ش� task�� runtime�� 1 ���ҽ�Ų ��
							totalRuntime--;																		// ���� priority�� �� ����ð��� 1 ���ҽ�Ų��
						}
					}
				}
			}
			fprintf(output, "\n");	// priority�� ����� �� ����
			pIndex += sameIndex;	// ó���� task�� �� ��ŭ pIndex�� ������Ų��
		}

		pIndex = 0;					// conventional class�� ù ��° task�� �����ϱ� ���� 0���� �ʱ�ȭ
		int totalRuntime = 0;		// conventional class ���� �����ϴ� ��� task�� �� ����ð�
		int totalCurrentRuntime = 0;// ���� ������ �ð�
		double totalWeight = 0;		// conventional class ���� �����ϴ� ��� task�� ������ ����
		
		// conventional class ���� task�� �����Ѵٸ�, conventional class�� �����Ѵ�
		if (conventional[pIndex].priority > 0) {
			// conventional class ���� �����ϴ� task���� �� ����ð���, ������ ������ ���Ѵ�
			for (int i = 0; i < cIndex; i++) {
				totalRuntime += conventional[i].runtime;
				totalWeight += conventional[i].weight;
			}

			// task���� CFS ������� ����Ѵ� (���� ����ð��� �� ����ð��� ������ �� ����)
			while (totalRuntime != totalCurrentRuntime) {
				pIndex = 0; // ���� ���� ����Ǿ�� �� task�� �ε����� ������ pIndex

				// vruntime�� ���� ���� task���� �����ؾ� �ϹǷ� pIndex�� vruntime�� ���� ���� task�� �ε��� ����
				// ���� ���� task�� vruntime�� ���ٸ�, priority�� ���� task���� �����Ѵ�. conventional �迭�� priority ������ ���ĵǾ� �����Ƿ� ���ʴ�� Ȯ���Ѵ�
				for (int i = 1; i < cIndex; i++) {
					if (conventional[i].vruntime < conventional[pIndex].vruntime && conventional[i].runtime > 0) {
						pIndex = i;
					}
				}

				// vruntime�� ���� ���� task�� runtime�� �����ִ� ���
				if (conventional[pIndex].runtime > 0) {
					if (tempCT.priority != 0 && tempCT.priority != conventional[pIndex].priority) fprintf(output, "\n");	// priority�� �ٲ���ٸ� �����Ѵ�
					fprintf(output, "%d %d ", conventional[pIndex].priority, conventional[pIndex].taskNum);					// task�� priority�� taskNum�� ���
					tempCT = conventional[pIndex];																			// ������ ����� task�� ���� ������ task�� priority�� ���ϱ� ���� taskCT�� ���� ������ task�� �����Ѵ�
					totalCurrentRuntime++;																					// ���� ����ð� 1 ����
					conventional[pIndex].runtime--;																			// ����� task�� runtime 1 ����
					conventional[pIndex].vruntime += 1024 / conventional[pIndex].weight;									// vruntime += ��� / (����) * (����ð�)
																															// �ѹ� ����� ������ vruntime�� Ȯ���� �ֹǷ� �� ���� ����� vruntime�� �����Ų��
				}

				// vruntime�� ���� ���� task�� runtime�� �������� ���� ���
				else {
					ctask tempCT2;
					
					// �ش� task�� �迭�� �� �ڷ� �о��
					for (int i = pIndex; i < cIndex - pIndex; i++) {
						tempCT2 = conventional[i];
						conventional[i] = conventional[i + 1];
						conventional[i + 1] = tempCT2;
					}

					// conventional class �� task ���� 1 ���ҽ�Ų�� -> �� ������ conventional class���� ������ ���� task�� �����ϴ� �Ͱ� ����
					cIndex--;
				}
			}
		}
	}
	return 0;
}