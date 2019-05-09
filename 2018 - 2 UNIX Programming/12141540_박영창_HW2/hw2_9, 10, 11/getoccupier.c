// 12141540 박영창
// 유닉스 프로그래밍 001

// 실습 시간에 사용한 예제 코드 - getoccupier.c
// 인자로 받은 방 번호의 투숙객을 return하는 함수

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "getoccupier.h"

char buffer[LINELENGTH];	// 알맞는 투숙객의 정보를 읽어와 저장할 buffer

char *getoccupier(int roomno){
	off_t offset;	// roomno에 따른 offset이 저장될 변수
	ssize_t nread;	// read의 return값을 저장할 변수

	if(listfiledes == -1 && (listfiledes = open(listfile, O_RDONLY))==-1){
		// listfile을 open, 실패 시 Error 출력과 NULL return
		fprintf(stderr, "Error on opening list file \n");
		return NULL;
	}

	offset = (roomno - 1) * LINELENGTH; // offset 계산

	if(lseek(listfiledes, offset, SEEK_SET) == -1){
		// 계산한 offset으로 file pointer 이동, 실패 시 Error 출력과 NULL return
		fprintf(stderr, "Error on setting offset \n");
		return NULL;
	}

	if((nread = read(listfiledes, buffer, LINELENGTH))<0){
		// file pointer에서부터 buffer에 listfile의 내용 읽어와 저장, 실패 시 Error 출력과 NULL return
		fprintf(stderr, "Error on reading ofset \n");
		return NULL;
	}

	buffer[LINELENGTH - 1] = '\0'; // buffer의 마지막을 NULL로 바꿔 문자열의 끝임을 나타냄

	return buffer;
}
