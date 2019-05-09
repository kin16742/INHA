// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.14
// command line argument를 이용해 두 개의 인자를 받아
// 첫 번째 인자는 file명, 두 번째 인자는 파일 열기 옵션으로
// file descriptor를 return하는 함수

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	// argv[0] = ./hw2_14  ,  argv[1] = file명  ,  argv[2] = 파일 열기 옵션 문자열
	
	int fd;		// file descriptor를 저장할 변수

	if(argc != 3){
		// 인자 개수에 오류가 있을 때
		printf("Parameter Error!!!\n");
		return -1;
	}
	else{
		// 인자 개수가 알맞게 들어왔을 때

		char* fname = argv[1];	// file명
		char* mode = argv[2];	// 파일 열기 옵션

		if(mode[0] == 'r'){
			if(mode[1] == 'w')
				// mode = "rw"
				fd = open(fname, O_RDWR);		// 읽기/쓰기용으로 open
			else
				// mode = "r"
				fd = open(fname, O_RDONLY);		// 읽기용으로 open
		}
		else if(mode[0] == 'w'){
			// mode = "w"
			fd = open(fname, O_WRONLY);			// 쓰기용으로 open
		}
		else if(mode[0] == 'a'){
			// mode = "a"
			fd = open(fname, O_APPEND);			// 덧붙이기(append)로 open
		}
		else{
			// 잘못된 mode 문자열 입력 시
			printf("No Matching Command For Input...\n");
			return -1;
		}
		
		if(fd == -1) printf("File Not Exist. \n");		// file이 존재하지 않음 -> open 실패
		else printf("File Descriptor is %d. \n", fd);	// file open 성공 -> descriptor 출력
		
		return fd;										// file descriptor 반환
	}
}
	
