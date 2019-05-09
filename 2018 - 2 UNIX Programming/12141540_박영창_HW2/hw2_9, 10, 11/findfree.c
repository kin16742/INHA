// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.9
// 비어있는 방 중에 가장 방 번호가 빠른 방을 찾는 함수

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "findfree.h"

#ifndef NROOMS
#define NROOMS 10		// 방의 개수
#endif

char buffer[LINELENGTH];// 투숙객 정보를 저장할 buffer

int findfree(){
	int fd;				// file descriptor를 저장할 변수
	int nread;			// read의 return값이 저장될 변수
	int roomno = 1;		// 방 번호

	fd = open(listfile, O_RDONLY);	// listfile을 읽기 전용으로 open

	while(roomno <= 10){	
		// 1번 방부터 10번 방까지 반복

		nread = read(fd, buffer, LINELENGTH);	// 현재 file pointer로부터 LINELENGTH만큼 읽어와 buffer에 저장
		
		if(buffer[0] == ' ') return roomno;		// 방이 비어있다면 현재 roomno return		

		roomno++;								// 비어있지 않다면 roomno를 증가시킨다.
	}

	// 반복문 내에서 빈 방을 찾지 못한 경우
	printf("NO Empty Room!!\n");			
	return -1;
}
