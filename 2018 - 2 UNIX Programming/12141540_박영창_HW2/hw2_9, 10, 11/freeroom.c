// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.10
// 인자로 방 번호를 받아 방을 비워주는 함수

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "freeroom.h"

void freeroom(int roomno){
	off_t offset;										// roomno에 따른 offset이 저장될 변수
	ssize_t nwrite;										// write의 return값이 저장될 변수
	char buffer[LINELENGTH] = {' ', ' ', ' ', '\n'};	// 빈 방(공백 3개)을 타나내는 문자열

	if(listfiledes == -1 && (listfiledes = open(listfile, O_RDWR)) == -1){
		// listfile을 open, 실패 시 Error 출력
		fprintf(stderr, "Error on opening list file \n");
	}

	offset = (roomno - 1) * LINELENGTH; // offset 계산

	if(lseek(listfiledes, offset, SEEK_SET) == -1){
		// 계산한 offset으로 file pointer 이동, 실패 시 Error 출력
		fprintf(stderr, "Error on setting offset \n");
	}
	
	if((nwrite = write(listfiledes, buffer, LINELENGTH))<0){
		// file pointer에서부터 buffer의 내용을 write, 실패 시 Error 출력
		fprintf(stderr, "Error on writing offset \n");
	}
}
