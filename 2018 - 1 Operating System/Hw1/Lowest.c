// 12141540 �ڿ�â
// OS 1�� ����
// Second Program - lowest
#include <stdio.h>
#include <pthread.h>

int arr[100];							// input ���� ������ �迭 - ( ppt�� input �ִ� ������ ��� ���Ƿ� 100���� �����߽��ϴ� )
int result[3];							// arr �迭�� 3���� �� thread�� ������ Ž���� ������ �ּҰ��� ������ �迭
int lowestValue;						// arr ��ü�� �ּҰ��� ������ int�� ����
int resultIndex = 0;					// sorting �Լ����� result�� ������ �ε���

typedef struct _index {					// pthread_create�� ���ڷ� �Ѱ��� ����ü
	int start;							// �迭�� ���� ��, ������ �迭�� ������(start)�� ����(end)
	int end;
	int check;							// spin-lock�� �ɱ� ���� ���� ( thread ���� ���� 1�� �ٲ㼭 ����Ǿ����� ǥ�� )
}index;

index param[3];							// thread�� 3�� �����ϹǷ� �� thread�� �Ѱ��� ������ �迭�� ����

void *sorting(void *_p) {					// sorting thread
	index *param = (index *)_p;				// ���ڷ� ����ü _p�� �޴´�
	int start = param->start;				// _p�� start, end�� ���� ������ �迭�� ������ �� �� �ִ�
	int end = param->end;
	int i, j, temp;							// �ݺ����� ���� i, j, ������ ���� temp
	for (i = start; i <= end; i++) {		// start�� �ε������� end�� �ε������� ����
		for (j = start; j < end; j++) {
			if (arr[i] < arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	result[resultIndex++] = arr[start];		// �� �ݺ����� ����� ���ĵ� ������ ù ��° ���� �ּ��̹Ƿ� �� ���� result �迭�� resultIndex �ε����� ���԰� ���ÿ� resultIndex�� ������Ų��
	param->check = 1;						// ���� ��� �۾��� ����Ǹ� _p�� check�� 1�� ����
	pthread_exit(0);						// pthread_exit �Լ� ȣ��
}

void *merge() {
	while (param[0].check == 0 || param[1].check == 0 || param[2].check == 0);	
										// spin-lock : �迭�� ���� ������ �ּҰ��� ã�� thread�� ���ڷ� �޾Ҵ� _p�� check�� ��� 1�� �ٲ��� ������ �ƹ� ���൵ ���� �ʴ´�

	int i, low = 100000;				// �ݺ����� ���� i, �ּҰ��� ������ low

	for (i = 0; i < 3; i++) {			// result �迭�� ���� ���� ���� low�� ����
		if (result[i] < low)
			low = result[i];
	}

	lowestValue = low;					// �������� lowestValue�� low�� ����

	pthread_exit(0);					// pthread_exit �Լ� ȣ��
}

int main() {	
	FILE * input;													// ���� ������� ���� ����
	int data;														// ���Ϸκ��� �Է¹��� �����͸� �ӽ÷� ������ ����
	int num = 0;													// ���Ϸκ��� �Է¹��� �������� ����

	input = fopen("input.txt", "r");								// input.txt ��� �ؽ�Ʈ ������ �Է¹޴´�

	if (input == NULL)												// ���� �Է� ���� �� ���
		printf("File error!");

	while (fscanf(input, "%d", &data) != EOF) {						// ���Ϸκ��� �����͸� arr �迭�� �Է¹޴´�
		arr[num] = data;
		num++;
	}

	pthread_t tid[4];												// ������ 4���� thread id ����  													

	param[0].start = 0;												// ������ thread�� �ѱ� ������ start, end ����
	param[0].end = num / 3 - 1;										
	param[1].start = num / 3;
	param[1].end = num / 3 * 2 - 1;
	param[2].start = num / 3 * 2;
	param[2].end = num - 1;

	pthread_create(&tid[0], NULL, sorting, (void *)&param[0]);		// 4���� thread ����
	pthread_create(&tid[1], NULL, sorting, (void *)&param[1]);		// ���������� 3���� thread�� ���ڷ� sorting �Լ��� indexŸ���� param ����ü�� �Ѱ� �������� ������ ����
	pthread_create(&tid[2], NULL, sorting, (void *)&param[2]);
	pthread_create(&tid[3], NULL, merge, NULL);						// ������ thread�� ���ڷ� merge �Լ��� �ѱ��, spin-lock�� �ɾ�ξ��� ������ �� 3���� thread�� ������ ����

	pthread_join(tid[0], NULL);										// thread�� ����Ǳ⸦ ��ٸ���
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	printf("Lowest : %d\n ", lowestValue);							// merge thread�� ����� result �迭�� �ִ밪�� lowestValue��� ������ ����Ǿ� �����Ƿ� �̸� ���

	fclose(input);													// ���� ����� close

	return 0;
}