// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.11
// getoccupier, freeroom, addguest, findfree 자료 화일을 유지하는 유틸리티 프로그램
// <printf를 호출하는 대화형 프로그램>

//		listfile에서 비어있는 방을 공백 3개의 문자열로 표시하기 때문에
//		listfile에 내용이 존재해야만 모든 함수가 실행 가능합니다.. 

//		Makefile을 make를 통해 병합시킵니다.

#include "hotel.h"
#include "getoccupier.h"
#include "findfree.h"
#include "freeroom.h"
#include "addguest.h"
#include <stdio.h>

#ifndef NROOMS
#define NROOMS 10
#endif

int main(){
	char* name;		// 문자열을 저장할 변수
	int cmd = 0;	// 실행할 command의 번호
	
	while(cmd != 5){
		printf("--------------------------------------\n");
		printf("              FRONTDESK               \n");
		printf("--------------------------------------\n");
		printf("1 : View all Guests                   \n");
		printf("2 : Find Empty Room                   \n");
		printf("3 : Free Room                         \n");
		printf("4 : Add Guest                         \n");
		printf("5 : Exit                              \n");
		printf("--------------------------------------\n");
		printf("Input : ");
		scanf("%d", &cmd);

		if(cmd == 1){	
			// getoccupier를 사용해 모든 투숙객의 정보 확인

			printf("-----------------LIST-----------------\n");
			for(int i = 1;i <= NROOMS;i++){
				if(name = getoccupier(i))
					printf("Room %d, %s \n", i, name);
				else
					fprintf(stderr, "Error on calling 'getoccupier'\n");
			}
		}
		else if(cmd == 2){
			// findfree를 사용해 비어있는 가장 빠른 방 번호 확인

			int freen = findfree();

			if(freen <= 10)
				printf("Room  %d is empty.\n",freen);
			else
				printf("No Room`s empty.\n");
		}
		else if(cmd == 3){
			// freeroom을 사용해 입력받은 방 번호의 방을 비움

			int a;
			
			printf("Room # to be Free : ");
			scanf("%d", &a);
			freeroom(a);
		}
		else if(cmd == 4){
			// addguest를 사용해 입력받은 방 번호에 입력받은 투숙객의 정보를 추가
			
			int a;
			char* name[LINELENGTH];
			
			printf("Room # to be Used : ");
			scanf("%d", &a);
			printf("Guest`s Name : ");
		    scanf("%s", name);
			addguest(a,name);
		}
		else if(cmd == 5){
			// 종료
			break;
		}
		else{
			// 입력이 잘못된 경우
			printf("         Command Not Exist          \n");
			printf("Input : ");
			scanf("%d", &cmd);
		}
	}
	return 0;
}
