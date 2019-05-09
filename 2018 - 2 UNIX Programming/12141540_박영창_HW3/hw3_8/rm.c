// 12141540 박영창
// 연습문제 3.8
// unlink를 사옹해 rm을 구현

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	char cmd;
	if(argc != 2){
		// 인자의 개수가 2개가 아닌 경우
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// 인자의 개수가 2개인 경우
		if(access(argv[1], W_OK) != -1){	 // 첫 번째 인자로 받은 파일명의 읽기 권한 확인
			printf("Remove File? ( 'y' to remove ) : ");
			scanf("%c",&cmd);				// 삭제할지 안할지 결정하는 커맨드를 입력
			if(cmd == 'y'){
				if(unlink(argv[1])==-1){	// 첫 번째 인자로 받은 파일을 unlink
					perror("Unlink Failed\n");
					return -1;
				}
				printf("Success\n");
			}
		}
		else{
			// 읽기 권한이 없을 경우
			perror("Can`t Write\n");
			return -1;
		}
		return 0;
	}
}
