// 12141540 박영창
// OS 1차 과제
// Second Program - lowest
#include <stdio.h>
#include <pthread.h>

int arr[100];							// input 값을 저장할 배열 - ( ppt에 input 최대 개수가 없어서 임의로 100으로 지정했습니다 )
int result[3];							// arr 배열을 3개의 각 thread가 나눠서 탐색해 각각의 최소값을 저장할 배열
int lowestValue;						// arr 전체의 최소값을 저장할 int형 변수
int resultIndex = 0;					// sorting 함수에서 result에 접근할 인덱스

typedef struct _index {					// pthread_create의 인자로 넘겨줄 구조체
	int start;							// 배열을 나눌 때, 나눠진 배열의 시작점(start)과 끝점(end)
	int end;
	int check;							// spin-lock을 걸기 위한 변수 ( thread 종료 전에 1로 바꿔서 수행되었음을 표시 )
}index;

index param[3];							// thread를 3개 생성하므로 각 thread에 넘겨줄 인자의 배열을 생성

void *sorting(void *_p) {					// sorting thread
	index *param = (index *)_p;				// 인자로 구조체 _p를 받는다
	int start = param->start;				// _p의 start, end를 통해 나눠진 배열의 구간을 알 수 있다
	int end = param->end;
	int i, j, temp;							// 반복문을 위한 i, j, 정렬을 위한 temp
	for (i = start; i <= end; i++) {		// start의 인덱스부터 end의 인덱스까지 정렬
		for (j = start; j < end; j++) {
			if (arr[i] < arr[j]) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	result[resultIndex++] = arr[start];		// 위 반복문의 결과로 정렬된 구간의 첫 번째 값이 최소이므로 그 값을 result 배열의 resultIndex 인덱스에 삽입과 동시에 resultIndex를 증가시킨다
	param->check = 1;						// 위의 모든 작업이 수행되면 _p의 check를 1로 세팅
	pthread_exit(0);						// pthread_exit 함수 호출
}

void *merge() {
	while (param[0].check == 0 || param[1].check == 0 || param[2].check == 0);	
										// spin-lock : 배열을 나눠 각각의 최소값을 찾는 thread의 인자로 받았던 _p의 check이 모두 1로 바뀌지 않으면 아무 수행도 하지 않는다

	int i, low = 100000;				// 반복문을 위한 i, 최소값을 저장할 low

	for (i = 0; i < 3; i++) {			// result 배열의 가장 작은 값을 low에 저장
		if (result[i] < low)
			low = result[i];
	}

	lowestValue = low;					// 전역변수 lowestValue에 low를 저장

	pthread_exit(0);					// pthread_exit 함수 호출
}

int main() {	
	FILE * input;													// 파일 입출력을 위한 변수
	int data;														// 파일로부터 입력받을 데이터를 임시로 저장할 변수
	int num = 0;													// 파일로부터 입력받을 데이터의 개수

	input = fopen("input.txt", "r");								// input.txt 라는 텍스트 파일을 입력받는다

	if (input == NULL)												// 파일 입력 오류 시 출력
		printf("File error!");

	while (fscanf(input, "%d", &data) != EOF) {						// 파일로부터 데이터를 arr 배열에 입력받는다
		arr[num] = data;
		num++;
	}

	pthread_t tid[4];												// 실행할 4개의 thread id 설정  													

	param[0].start = 0;												// 각각의 thread에 넘길 인자의 start, end 설정
	param[0].end = num / 3 - 1;										
	param[1].start = num / 3;
	param[1].end = num / 3 * 2 - 1;
	param[2].start = num / 3 * 2;
	param[2].end = num - 1;

	pthread_create(&tid[0], NULL, sorting, (void *)&param[0]);		// 4개의 thread 생성
	pthread_create(&tid[1], NULL, sorting, (void *)&param[1]);		// 위에서부터 3개의 thread는 인자로 sorting 함수와 index타입의 param 구조체를 넘겨 시작점과 끝점을 설정
	pthread_create(&tid[2], NULL, sorting, (void *)&param[2]);
	pthread_create(&tid[3], NULL, merge, NULL);						// 마지막 thread는 인자로 merge 함수를 넘기고, spin-lock을 걸어두었기 때문에 위 3개의 thread가 끝나야 수행

	pthread_join(tid[0], NULL);										// thread가 종료되기를 기다린다
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	printf("Lowest : %d\n ", lowestValue);							// merge thread의 결과로 result 배열의 최대값이 lowestValue라는 변수에 저장되어 있으므로 이를 출력

	fclose(input);													// 파일 입출력 close

	return 0;
}