// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.5
// command line argument�� ����� ���� �̸��� �Է¹޾�
// ����, ��, �������� ���еǴ� �ܾ��� ������ ����ϴ� ���α׷�

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int count = 0;					// �ܾ��� ����		
	int fd = open(argv[1], O_RDWR);	// command line argument�� ���� file���� argv[1]�� file descriptor
	int byte;						// read�� return���� ���� ����							
	char buffer[10];				// file ���� ���ڸ� ������ buffer
	char temp;						// ���� �񱳸� ���� �ӽ� ����

	if(fd != -1){					
		// file open�� ����
		byte = read(fd, buffer, 1);											// buffer�� file�κ��� �� ���ڸ� �о�� ����
		while(1){
			temp = buffer[0];												// temp�� buffer�� ����� �� ����
			byte = read(fd, buffer, 1);										// buffer�� file�κ��� �� ���ڸ� �о�� ����

			if(buffer[0] == 9 ||  buffer[0] == 10 ||  buffer[0] == 32){		// �о�� ���ڰ� ����, ��, �����̰�
				if(temp != 9 && temp != 10 && temp != 32){					// �ٷ� �� ���ڰ� ����, ��, ������ �ƴ϶��
					count++;												// �ϳ��� ���еǴ� �ܾ ��Ÿ�� ���̹Ƿ� ������ ������Ų��
				}
			}
			if(byte <= 0){													// file���� �о�� ���ڰ� ���ٸ�
				close(fd);													// file�� close�ϰ� �ݺ��� Ż��
				break;
			}
		}
		printf("%d\n", count);												// ���� ���
	}
	else{
		// file open ����
		printf("FILE OPEN FAIL\n");
	}
	return 0;
}
