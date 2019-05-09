// 12141540 박영창
// 유닉스 프로그래밍 001

// 연습문제 2.5
// command line argument를 사용해 파일 이름을 입력받아
// 공백, 탭, 개행으로 구분되는 단어의 개수를 출력하는 프로그램

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int count = 0;					// 단어의 개수		
	int fd = open(argv[1], O_RDWR);	// command line argument로 받은 file명인 argv[1]의 file descriptor
	int byte;						// read의 return값을 담을 변수							
	char buffer[10];				// file 내의 문자를 저장할 buffer
	char temp;						// 문자 비교를 위한 임시 변수

	if(fd != -1){					
		// file open에 성공
		byte = read(fd, buffer, 1);											// buffer에 file로부터 한 문자를 읽어와 저장
		while(1){
			temp = buffer[0];												// temp에 buffer에 저장된 값 복사
			byte = read(fd, buffer, 1);										// buffer에 file로부터 한 문자를 읽어와 저장

			if(buffer[0] == 9 ||  buffer[0] == 10 ||  buffer[0] == 32){		// 읽어온 문자가 공백, 탭, 개행이고
				if(temp != 9 && temp != 10 && temp != 32){					// 바로 전 문자가 공백, 탭, 개행이 아니라면
					count++;												// 하나의 구분되는 단어가 나타난 것이므로 개수를 증가시킨다
				}
			}
			if(byte <= 0){													// file에서 읽어온 문자가 없다면
				close(fd);													// file을 close하고 반복문 탈출
				break;
			}
		}
		printf("%d\n", count);												// 개수 출력
	}
	else{
		// file open 실패
		printf("FILE OPEN FAIL\n");
	}
	return 0;
}
