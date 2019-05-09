// 12141540 박영창
// 연습문제 3.6
// 주어진 화일에 대해 읽기/쓰기/수행 접근이 허용되는지 확인

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		// 인자의 개수가 2개가 아닌 경우
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// 인자의 개수가 2개인 경우
		if(access(argv[1],R_OK) != -1) printf("Can Read\n");	// 읽기 권한 확인
		else perror("Can`t Read\n");

		if(access(argv[1],W_OK) != -1) printf("Can Write\n");	// 쓰기 권한 확인
		else perror("Can`t Write\n");
		
		if(access(argv[1],X_OK) != -1) printf("Can Execute\n");	// 수행 권한 확인
		else perror("Can`t Execute\n");

		return 0;
	}
}
