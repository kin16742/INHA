// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.14
// command line argument�� �̿��� �� ���� ���ڸ� �޾�
// ù ��° ���ڴ� file��, �� ��° ���ڴ� ���� ���� �ɼ�����
// file descriptor�� return�ϴ� �Լ�

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	// argv[0] = ./hw2_14  ,  argv[1] = file��  ,  argv[2] = ���� ���� �ɼ� ���ڿ�
	
	int fd;		// file descriptor�� ������ ����

	if(argc != 3){
		// ���� ������ ������ ���� ��
		printf("Parameter Error!!!\n");
		return -1;
	}
	else{
		// ���� ������ �˸°� ������ ��

		char* fname = argv[1];	// file��
		char* mode = argv[2];	// ���� ���� �ɼ�

		if(mode[0] == 'r'){
			if(mode[1] == 'w')
				// mode = "rw"
				fd = open(fname, O_RDWR);		// �б�/��������� open
			else
				// mode = "r"
				fd = open(fname, O_RDONLY);		// �б������ open
		}
		else if(mode[0] == 'w'){
			// mode = "w"
			fd = open(fname, O_WRONLY);			// ��������� open
		}
		else if(mode[0] == 'a'){
			// mode = "a"
			fd = open(fname, O_APPEND);			// �����̱�(append)�� open
		}
		else{
			// �߸��� mode ���ڿ� �Է� ��
			printf("No Matching Command For Input...\n");
			return -1;
		}
		
		if(fd == -1) printf("File Not Exist. \n");		// file�� �������� ���� -> open ����
		else printf("File Descriptor is %d. \n", fd);	// file open ���� -> descriptor ���
		
		return fd;										// file descriptor ��ȯ
	}
}
	
