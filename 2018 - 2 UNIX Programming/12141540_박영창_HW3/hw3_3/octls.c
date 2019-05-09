// 12141540 �ڿ�â
// �������� 3.3
// ls�� ���� �����Ǵ� permission ���� -> ������������ ���

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	if(argc != 2){
		// ������ ������ 2���� �ƴ� ���
		printf("Parameter Error\n");
		return -1;
	}
	else{
		// ������ ������ 2���� ���
		for(int i=0;i<3;i++){
			int res = 0;
			if(argv[1][i*3] == 'r') res += 4;	// read ������ �ִ� ���
			if(argv[1][i*3+1] == 'w') res += 2;	// write ������ �ִ� ���
			if(argv[1][i*3+2] == 'x') res += 1;	// execute ������ �ִ� ���
			printf("%d",res);	
		}
		printf("\n");
		return 0;
	}
}
