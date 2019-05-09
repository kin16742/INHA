// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.15
// command line argument를 이용해 인수가 있는지 조사하고
// 인수가 존재하면 각 인수를 file명으로 취급해 내용을 읽어와 표준 출력으로 출력
// 인수가 존재하지 않으면 표준 입력을 받아 출력

//		이 프로그램은 자신이 열 수 없는 파일 ( 권한이 없는 파일 ) 을 열지 못합니다..

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int fd;					// file descriptor
	int nread;				// 파일 내용 read의 return값을 저장할 변수
	int nwrite;				// write의 return값을 저장할 변수
	char buffer[1024];		// 파일 내용이 저장될 buffer
	
	if(argc == 1){
		// 인자가 없는 경우

		char tbuffer[1024]; // 표준 입력으로 받은 file명을 저장할 변수
		int tread;			// 표준 입력 read의 return값을 저장할 변수

		while (1) {
			tread = read(0, tbuffer, 1024);	// 표준 입력으로 읽어와 tbuffer에 저장
			tbuffer[tread - 1] = '\0';		// [입력받은 byte 수 - 1]가 개행이므로 NULL로 바꿔 문자열의 끝임을 표시
			fd = open(tbuffer, O_RDONLY);	// tbuffer에 저장된 file명을 open해 file descriptor 저장

			if (fd == -1) {
				// file open 실패
				printf("File no Exist!\n");
			}
			else {
				// file open 성공
				while (1) {
					nread = read(fd, buffer, 1024);		// file로부터 내용을 읽어와 buffer에 저장
					nwrite = write(1, buffer, nread);	// buffer에 저장된 내용을 표준 출력
					if (nread <= 0) break;				// read한 내용이 없다면 break
				}
				close(fd);								// file close
			}
		}
	}
	else{
		// 인자가 있는 경우

		for(int i = 1;i < argc;i++){			
			fd = open(argv[i], O_RDONLY);					// i번째 인자를 file명으로 open
			
			if (fd == -1) {
				// file open 실패
				printf("File %d doesn`t Exist!!\n", i);
			}
			else {
				while (1) {
					nread = read(fd, buffer, 1024);			// file로부터 내용을 읽어와 buffer에 저장
					nwrite = write(1, buffer, nread);		// buffer에 저장된 내용을 표준 출력
					if (nread <= 0) break;					// read한 내용이 없다면 break
				}
			}
			close(fd);										// file close
		}
	}
	return 0;
}
