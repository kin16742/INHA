// 12141540 박영창
// 연습문제 3.7
// 두 개의 인자를 받아 화일의 permission을 설정

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
	int perm = 0;

	if(argc != 3){
		// 인자의 개수가 3개가 아닌 경우
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// 인자의 개수가 3개인 경우
		if(open(argv[1], O_RDWR) == -1){
			// 첫 번째 인자의 파일명이 존재하지 않는 경우
			perror("No Such File\n");
			return -1;
		}

		if(argv[2][0] >= '0' && argv[2][0] <= '9'){
			// 두 번째 인자로 받는 permission이 8진수인 경우
			perm = (argv[2][0] - '0') * 64 + (argv[2][1] - '0') * 8 + (argv[2][2] - '0');	
		}
		else{
			// 두 번째 인자로 받는 permission이 ls 스타일인 경우
			int a[3] = {0,0,0};
			for(int i=0;i<3;i++){
				if(argv[2][i*3] == 'r') a[i] += 4;
				if(argv[2][i*3+1] == 'w') a[i] += 2;
				if(argv[2][i*3+2] == 'x') a[i] += 1;
			}
			perm = a[0] * 64 + a[1] * 8 + a[2];
		}

		if(chmod(argv[1],perm)==-1){
			// 첫 번째 인자 파일의 권한을 위에서 계산한 권한으로 바꿔줌
			perror("chmod error\n");
			return -1;
		}

		printf("Success\n");
		return 0;
	}
}
