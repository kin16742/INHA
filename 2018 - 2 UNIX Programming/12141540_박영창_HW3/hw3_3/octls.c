// 12141540 박영창
// 연습문제 3.3
// ls에 의해 지정되는 permission 집합 -> 팔진수값으로 출력

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	if(argc != 2){
		// 인자의 개수가 2개가 아닌 경우
		printf("Parameter Error\n");
		return -1;
	}
	else{
		// 인자의 개수가 2개인 경우
		for(int i=0;i<3;i++){
			int res = 0;
			if(argv[1][i*3] == 'r') res += 4;	// read 권한이 있는 경우
			if(argv[1][i*3+1] == 'w') res += 2;	// write 권한이 있는 경우
			if(argv[1][i*3+2] == 'x') res += 1;	// execute 권한이 있는 경우
			printf("%d",res);	
		}
		printf("\n");
		return 0;
	}
}
