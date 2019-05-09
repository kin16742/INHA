// 12141540 �ڿ�â
// �������� 3.6
// �־��� ȭ�Ͽ� ���� �б�/����/���� ������ ���Ǵ��� Ȯ��

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		// ������ ������ 2���� �ƴ� ���
		perror("Parameter Error\n");
		return -1;
	}
	else{
		// ������ ������ 2���� ���
		if(access(argv[1],R_OK) != -1) printf("Can Read\n");	// �б� ���� Ȯ��
		else perror("Can`t Read\n");

		if(access(argv[1],W_OK) != -1) printf("Can Write\n");	// ���� ���� Ȯ��
		else perror("Can`t Write\n");
		
		if(access(argv[1],X_OK) != -1) printf("Can Execute\n");	// ���� ���� Ȯ��
		else perror("Can`t Execute\n");

		return 0;
	}
}
