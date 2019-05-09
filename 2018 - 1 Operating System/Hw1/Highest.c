// 12141540 �ڿ�â
// OS 1�� ����
// First Program - Highest
#include <stdio.h>
#include <pthread.h>

int arr[9][9];								// input ���� ������ �迭
int res[9];									// �� subgrid�� �ִ밪�� ���ϴ� thread���� �ִ밪�� ������ �迭
int resIndex = 0;							// highestSubgrids �Լ����� res �迭�� ������ �ε���
int Result;									// �Է¹��� �迭�� �ִ밪(�����)�� ������ ����

typedef struct _index {						// pthread_create�� ���ڷ� �Ѱ��� ����ü
	int x;									// subgrid�� ũ��� 3x3���� ������ �����Ƿ� �������� x, y��ǥ�� ����ü�� ����
	int y;
}index;

index param[9];								// 9���� highestSubgrids thread�� �Ѱ��� ������ �迭

void setIndex(index *p, int _x, int _y) {	// index ����ü�� ��� ���� ���� �Լ�
	p->x = _x;
	p->y = _y;
}

void * highestSubgrids(void *dt) {					// 3x3 subgrid ���� �ִ밪�� ���� res �迭�� �����ϴ� �Լ�
	index *nparam = (index *)dt;					// �Է¹��� ���ڸ� nparam�� ����
	int yIndex = nparam->y;
	int xIndex = nparam->x;
	int i, j, highest = 0;							// �ݺ����� ���� i, j, �ִ밪�� ������ ���� highest

	for (i = yIndex; i < yIndex + 3; i++) {			// subgrid�� ���� Ȯ���ϸ� �ִ밪�� highest�� ����
		for (j = xIndex; j < xIndex + 3; j++) {
			if (arr[i][j] > highest)
				highest = arr[i][j];
		}
	}
	res[resIndex++] = highest;						// res �迭�� resIndex �ε����� highest�� �����԰� ���ÿ� resIndex�� ���������ش�
	pthread_exit(0);								// thread_exit �Լ� ȣ��
}

void * highestResult() {							// res �迭 ���� �ִ밪�� ���� Result ������ �����ϴ� �Լ�
	int highest = 0, i;								// �ִ밪�� ������ ���� highest, �ݺ����� ���� i

	for (i = 0; i < 9; i++) {						// res �迭�� �ִ밪�� highest�� ����
		if (res[i] > highest) {
			highest = res[i];
		}
	}

	Result = highest;								// �������� Result�� highest�� ����

	pthread_exit(0);								// thread_exit �Լ� ȣ��
}

int main() {
	FILE * input;																// ���� ������� ���� ����
	int i, j;																	// �ݺ����� ���� i, j
	pthread_t tid[10];															// ������ 10�� thread�� id ����

	input = fopen("input.txt", "r");											// input.txt ��� �ؽ�Ʈ ������ �Է¹޴´�

	if (input == NULL)															// ���� �Է� ���� �� ���
		printf("File error!");

	for (i = 0; i < 9; i++) {													// ���Ϸκ��� �����͸� arr �迭�� �Է¹޴´�
		for (j = 0; j < 9; j++) {
			fscanf(input, "%d", &arr[i][j]);
		}
	}

	setIndex(&param[0], 0, 0);													// ������ thread�� �ѱ� ������ x, y ����
	setIndex(&param[1], 3, 0);	
	setIndex(&param[2], 6, 0);
	setIndex(&param[3], 0, 3);	
	setIndex(&param[4], 3, 3);	
	setIndex(&param[5], 6, 3);
	setIndex(&param[6], 0, 6);	
	setIndex(&param[7], 3, 6);	
	setIndex(&param[8], 6, 6);

	for (i = 0; i < 9; i++) {													// 9���� highestSubgrids thread ����
		pthread_create(&tid[i], NULL, highestSubgrids, (void *)&param[i]);
	}
	
	for (i = 0; i < 9; i++) {													// 9���� thread�� ����Ǳ�
		pthread_join(tid[i], NULL);
	}

	pthread_create(&tid[9], NULL, highestResult, NULL);							// highestResult thread ����
	pthread_join(tid[9], NULL);													// thread�� ����Ǳ� ��ٸ�

	printf("Highest number : %d\n", Result);									// Result�� ���

	fclose(input);																// ���� ����� close

	return 0;
}