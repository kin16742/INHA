// 12141540 박영창
// OS 1차 과제
// First Program - Highest
#include <stdio.h>
#include <pthread.h>

int arr[9][9];								// input 값을 저장할 배열
int res[9];									// 각 subgrid의 최대값을 구하는 thread에서 최대값을 저장할 배열
int resIndex = 0;							// highestSubgrids 함수에서 res 배열에 접근할 인덱스
int Result;									// 입력받은 배열의 최대값(결과값)을 저장할 변수

typedef struct _index {						// pthread_create의 인자로 넘겨줄 구조체
	int x;									// subgrid의 크기는 3x3으로 정해져 있으므로 시작점의 x, y좌표를 구조체에 저장
	int y;
}index;

index param[9];								// 9개의 highestSubgrids thread에 넘겨줄 인자의 배열

void setIndex(index *p, int _x, int _y) {	// index 구조체의 멤버 변수 설정 함수
	p->x = _x;
	p->y = _y;
}

void * highestSubgrids(void *dt) {					// 3x3 subgrid 내의 최대값을 구해 res 배열에 저장하는 함수
	index *nparam = (index *)dt;					// 입력받은 인자를 nparam에 저장
	int yIndex = nparam->y;
	int xIndex = nparam->x;
	int i, j, highest = 0;							// 반복문을 위한 i, j, 최대값을 저장할 변수 highest

	for (i = yIndex; i < yIndex + 3; i++) {			// subgrid의 값을 확인하며 최대값을 highest에 저장
		for (j = xIndex; j < xIndex + 3; j++) {
			if (arr[i][j] > highest)
				highest = arr[i][j];
		}
	}
	res[resIndex++] = highest;						// res 배열의 resIndex 인덱스에 highest를 저장함과 동시에 resIndex를 증가시켜준다
	pthread_exit(0);								// thread_exit 함수 호출
}

void * highestResult() {							// res 배열 내의 최대값을 구해 Result 변수에 저장하는 함수
	int highest = 0, i;								// 최대값을 저장할 변수 highest, 반복문을 위한 i

	for (i = 0; i < 9; i++) {						// res 배열의 최대값을 highest에 저장
		if (res[i] > highest) {
			highest = res[i];
		}
	}

	Result = highest;								// 전역변수 Result에 highest를 저장

	pthread_exit(0);								// thread_exit 함수 호출
}

int main() {
	FILE * input;																// 파일 입출력을 위한 변수
	int i, j;																	// 반복문을 위한 i, j
	pthread_t tid[10];															// 실행할 10개 thread의 id 설정

	input = fopen("input.txt", "r");											// input.txt 라는 텍스트 파일을 입력받는다

	if (input == NULL)															// 파일 입력 오류 시 출력
		printf("File error!");

	for (i = 0; i < 9; i++) {													// 파일로부터 데이터를 arr 배열에 입력받는다
		for (j = 0; j < 9; j++) {
			fscanf(input, "%d", &arr[i][j]);
		}
	}

	setIndex(&param[0], 0, 0);													// 각각의 thread의 넘길 인자의 x, y 설정
	setIndex(&param[1], 3, 0);	
	setIndex(&param[2], 6, 0);
	setIndex(&param[3], 0, 3);	
	setIndex(&param[4], 3, 3);	
	setIndex(&param[5], 6, 3);
	setIndex(&param[6], 0, 6);	
	setIndex(&param[7], 3, 6);	
	setIndex(&param[8], 6, 6);

	for (i = 0; i < 9; i++) {													// 9개의 highestSubgrids thread 생성
		pthread_create(&tid[i], NULL, highestSubgrids, (void *)&param[i]);
	}
	
	for (i = 0; i < 9; i++) {													// 9개의 thread가 종료되길
		pthread_join(tid[i], NULL);
	}

	pthread_create(&tid[9], NULL, highestResult, NULL);							// highestResult thread 생성
	pthread_join(tid[9], NULL);													// thread가 종료되길 기다림

	printf("Highest number : %d\n", Result);									// Result값 출력

	fclose(input);																// 파일 입출력 close

	return 0;
}