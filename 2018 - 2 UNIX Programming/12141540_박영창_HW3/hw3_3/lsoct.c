// 12141540 박영창
// 연습문제 3.3
// ls에 의해 지정되는 팔진수값 -> permission 집합으로 출력

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		// 인자의 개수가 2개가 아닌 경우
		printf("Parameter Error\n");
		return -1;
	}
	else{
		// 2개인 경우
		for(int i=0;i<3;i++){
			switch(argv[1][i] - 48){	// user, group, others의 경우에 따라 출력
				case 0: printf("---"); break;
				case 1: printf("--x"); break;
				case 2: printf("-w-"); break;
				case 3: printf("-wx"); break;
				case 4: printf("r--"); break;
				case 5: printf("r-x"); break;
				case 6: printf("rw-"); break;
				case 7: printf("rwx"); break;
			}
		}
		printf("\n");
		return 0;
	}
}	
