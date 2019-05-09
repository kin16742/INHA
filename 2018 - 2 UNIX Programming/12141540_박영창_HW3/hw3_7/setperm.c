// 12141540 �ڿ�â
// �������� 3.7
// �� ���� ���ڸ� �޾� ȭ���� permission�� ����

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
	int perm = 0;

	if(argc != 3){
		// ������ ������ 3���� �ƴ� ���
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// ������ ������ 3���� ���
		if(open(argv[1], O_RDWR) == -1){
			// ù ��° ������ ���ϸ��� �������� �ʴ� ���
			perror("No Such File\n");
			return -1;
		}

		if(argv[2][0] >= '0' && argv[2][0] <= '9'){
			// �� ��° ���ڷ� �޴� permission�� 8������ ���
			perm = (argv[2][0] - '0') * 64 + (argv[2][1] - '0') * 8 + (argv[2][2] - '0');	
		}
		else{
			// �� ��° ���ڷ� �޴� permission�� ls ��Ÿ���� ���
			int a[3] = {0,0,0};
			for(int i=0;i<3;i++){
				if(argv[2][i*3] == 'r') a[i] += 4;
				if(argv[2][i*3+1] == 'w') a[i] += 2;
				if(argv[2][i*3+2] == 'x') a[i] += 1;
			}
			perm = a[0] * 64 + a[1] * 8 + a[2];
		}

		if(chmod(argv[1],perm)==-1){
			// ù ��° ���� ������ ������ ������ ����� �������� �ٲ���
			perror("chmod error\n");
			return -1;
		}

		printf("Success\n");
		return 0;
	}
}
