// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.10
// 인자로 방 번호와 투숙객 이름을 받아
// 방이 비어있는지 확인하고
// 비어있다면 투숙객을 추가하는 함수

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "addguest.h"
#include "getoccupier.h"

void addguest(int roomno, char name[LINELENGTH]){
	off_t offset;	// roomno에 따른 offset이 저장될 변수
	ssize_t nwrite;	// write의 return값을 저장할 변수
	char* buffer;	// 입력받은 방의 투숙객 정보를 저장할 변수

	buffer = getoccupier(roomno);	// buffer에 getoccupier 함수를 호출해 투숙객 정보 저장

	if(buffer[0] != ' '){
		// 투숙객이 존재하는 경우
		printf("Room %d is not empty!\n", roomno);
	}
	else{
		// 투숙객이 존재하지 않는 경우
		if(listfiledes == -1 && (listfiledes = open(listfile, O_RDWR))==-1){
			// listfile을 open, 실패 시 Error 출력
			fprintf(stderr, "Error on opening list file \n");
		}

		offset = (roomno - 1) * LINELENGTH;	// offset 계산
	
		if(lseek(listfiledes, offset, SEEK_SET) == -1){
			// 계산한 offset으로 file pointer 이동, 실패 시 Error 출력
			fprintf(stderr, "Error on setting offset \n");
		}

		if((nwrite = write(listfiledes, name, LINELENGTH - 1))<0){ 
			// file pointer에서부터 입력받은 투숙객 이름을 write, 실패 시 Error 출력
			fprintf(stderr, "Error on writing offset \n");
		}
	}
}
