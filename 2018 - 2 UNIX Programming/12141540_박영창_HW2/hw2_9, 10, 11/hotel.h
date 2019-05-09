// 12141540 박영창
// 유닉스 프로그래밍 001

// hotel.c의 헤더 파일

#ifndef LINELENGTH
#define LINELENGTH 4	// 투숙객의 이름 크기인 LINELENGTH를 4로 정의
#endif

static int listfiledes = -1;			// file descriptor
static char listfile[] = "listfile";	// file 명
