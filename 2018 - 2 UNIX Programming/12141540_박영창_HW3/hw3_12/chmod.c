// 12141540 박영창
// 연습문제 3.12
// chmod 구현

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
	int perm = 0;			// 설정할 권한
	int arr[3] = {0,0,0};	// 원래 파일의 8진수형 권한을 저장할 배열
	int opeidx = 0;			// 연산자의 위치를 저장할 인덱스
	int temp = 0;			// 임시 권한을 저장할 변수
	struct stat buf;		// 파일의 stat을 받아올 구조체

	if(argc != 3){
		// 인자의 개수가 3개가 아닐 경우
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// 인자의 개수가 3개일 경우
		if(open(argv[2], O_RDWR) == -1){
			// 두 번째 인자로 받은 파일을 오픈
			perror("No Such File\n");
			return -1;
		}
		
		if(argv[1][0] >= '0' && argv[1][0] <= '9'){
			// 첫 번째 인자로 받은 권한이 8진수일 경우
			perm = (argv[1][0] - '0') * 64 + (argv[1][1] - '0') * 8 + argv[1][2] -'0';
		}
		else if(argv[1][0] == 'r' || argv[1][0] == '-'){
			// 첫 번째 인자로 받은 권한이 ls 형식일 경우
			for(int i=0;i<3;i++){
				if(argv[1][i*3]=='r') arr[i]+=4;
				if(argv[1][i*3+1]=='w') arr[i]+=2;
				if(argv[1][i*3+2]=='x') arr[i]+=1;
			}
			perm = arr[0] * 64 + arr[1] * 8 + arr[2];
		}
		else{
			// 첫 번째 인자로 받은 권한이 연산자를 포함하는 형식일 경우
			if(stat(argv[2], &buf) == -1){
				// stat 함수를 통해 정보를 받아온다.
				perror("Can`t call stat\n");
				return -1;
			}

			while(argv[1][opeidx] != '+' && argv[1][opeidx] != '-' && argv[1][opeidx] != '=') opeidx++;
			// 연산자의 위치를 찾아낸다.

			if(buf.st_mode & S_IRUSR) arr[0] += 4;
			if(buf.st_mode & S_IWUSR) arr[0] += 2;
			if(buf.st_mode & S_IXUSR) arr[0] += 1;
			if(buf.st_mode & S_IRGRP) arr[1] += 4;
			if(buf.st_mode & S_IWGRP) arr[1] += 2;
			if(buf.st_mode & S_IXGRP) arr[1] += 1;
			if(buf.st_mode & S_IROTH) arr[2] += 4;
			if(buf.st_mode & S_IWOTH) arr[2] += 2;
			if(buf.st_mode & S_IXOTH) arr[2] += 1;
			// 파일의 현재 권한을 8진수 형식으로 받아온다.

			for(int i=opeidx+1;i<strlen(argv[1]);i++){
				// 수정할 임시 권한을 설정한다.
				if(argv[1][i] == 'r') temp += 4;
				if(argv[1][i] == 'w') temp += 2;
				if(argv[1][i] == 'x') temp += 1;
			}

			for(int i=0;i<opeidx;i++){
				// 연산자 앞의 문자인 수정할 권한의 대상에 따라 수정한다.
				if(argv[1][i] == 'u'){
					// user를 수정해야 하는 경우
					if(argv[1][opeidx] == '=') arr[0] = temp;		// 지정
					if(argv[1][opeidx] == '+') arr[0] |= temp;		// 추가
					if(argv[1][opeidx] == '-') arr[0] &= (7 - temp);// 제거
				}
				if(argv[1][i] == 'g'){
					// group을 수정해야 하는 경우
					if(argv[1][opeidx] == '=') arr[1] = temp;		// 지정
					if(argv[1][opeidx] == '+') arr[1] |= temp;		// 추가
					if(argv[1][opeidx] == '-') arr[1] &= (7-temp);	// 제거
				}
				if(argv[1][i] == 'o'){
					// 그 외의 others를 수정해야 하는 경우
					if(argv[1][opeidx] == '=') arr[2] = temp;		// 지정
					if(argv[1][opeidx] == '+') arr[2] |= temp;		// 추가
					if(argv[1][opeidx] == '-') arr[2] &= (7-temp);	// 제거
				}
			
			}
			perm = arr[0] * 64 + arr[1] * 8 + arr[2];
		}
		if(chmod(argv[2], perm)== -1){
			// 두 번째 인자로 받은 파일의 권한을 변경
			perror("chmod fail\n");
			return -1;
		}
		printf("Success\n");
		return 0;
	}
}

