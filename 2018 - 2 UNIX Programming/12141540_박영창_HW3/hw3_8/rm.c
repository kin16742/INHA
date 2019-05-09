// 12141540 �ڿ�â
// �������� 3.8
// unlink�� ����� rm�� ����

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	char cmd;
	if(argc != 2){
		// ������ ������ 2���� �ƴ� ���
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// ������ ������ 2���� ���
		if(access(argv[1], W_OK) != -1){	 // ù ��° ���ڷ� ���� ���ϸ��� �б� ���� Ȯ��
			printf("Remove File? ( 'y' to remove ) : ");
			scanf("%c",&cmd);				// �������� ������ �����ϴ� Ŀ�ǵ带 �Է�
			if(cmd == 'y'){
				if(unlink(argv[1])==-1){	// ù ��° ���ڷ� ���� ������ unlink
					perror("Unlink Failed\n");
					return -1;
				}
				printf("Success\n");
			}
		}
		else{
			// �б� ������ ���� ���
			perror("Can`t Write\n");
			return -1;
		}
		return 0;
	}
}
