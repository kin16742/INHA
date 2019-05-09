// 12141540 �ڿ�â
// �������� 3.3
// ls�� ���� �����Ǵ� �������� -> permission �������� ���

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		// ������ ������ 2���� �ƴ� ���
		printf("Parameter Error\n");
		return -1;
	}
	else{
		// 2���� ���
		for(int i=0;i<3;i++){
			switch(argv[1][i] - 48){	// user, group, others�� ��쿡 ���� ���
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
