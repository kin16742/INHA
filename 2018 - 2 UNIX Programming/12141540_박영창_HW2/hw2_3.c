// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.3
// 처음에 creat를 사용하여 한 화일을 생성하고, 이어 close를 부르지 않고 open 시스템 호출로
// 읽기와 쓰기용으로 개방하는 짤막한 프로그램

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int t = creat("text.txt", 0644);	// text.txt라는 파일을 0644의 권한으로 생성
	int fd = open("text.txt", O_RDWR);	// 위에서 생성한 파일을 읽기/쓰기용으로 개방

	if(fd == -1) printf("FAIL\n");		// text.txt open 실패 시 fd가 -1이 되므로 실패
	else printf("SUCCESS\n");			// 그렇지 않으면 성공

	return 0;
}

