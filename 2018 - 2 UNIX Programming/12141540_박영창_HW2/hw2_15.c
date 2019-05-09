// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.15
// command line argument�� �̿��� �μ��� �ִ��� �����ϰ�
// �μ��� �����ϸ� �� �μ��� file������ ����� ������ �о�� ǥ�� ������� ���
// �μ��� �������� ������ ǥ�� �Է��� �޾� ���

//		�� ���α׷��� �ڽ��� �� �� ���� ���� ( ������ ���� ���� ) �� ���� ���մϴ�..

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int fd;					// file descriptor
	int nread;				// ���� ���� read�� return���� ������ ����
	int nwrite;				// write�� return���� ������ ����
	char buffer[1024];		// ���� ������ ����� buffer
	
	if(argc == 1){
		// ���ڰ� ���� ���

		char tbuffer[1024]; // ǥ�� �Է����� ���� file���� ������ ����
		int tread;			// ǥ�� �Է� read�� return���� ������ ����

		while (1) {
			tread = read(0, tbuffer, 1024);	// ǥ�� �Է����� �о�� tbuffer�� ����
			tbuffer[tread - 1] = '\0';		// [�Է¹��� byte �� - 1]�� �����̹Ƿ� NULL�� �ٲ� ���ڿ��� ������ ǥ��
			fd = open(tbuffer, O_RDONLY);	// tbuffer�� ����� file���� open�� file descriptor ����

			if (fd == -1) {
				// file open ����
				printf("File no Exist!\n");
			}
			else {
				// file open ����
				while (1) {
					nread = read(fd, buffer, 1024);		// file�κ��� ������ �о�� buffer�� ����
					nwrite = write(1, buffer, nread);	// buffer�� ����� ������ ǥ�� ���
					if (nread <= 0) break;				// read�� ������ ���ٸ� break
				}
				close(fd);								// file close
			}
		}
	}
	else{
		// ���ڰ� �ִ� ���

		for(int i = 1;i < argc;i++){			
			fd = open(argv[i], O_RDONLY);					// i��° ���ڸ� file������ open
			
			if (fd == -1) {
				// file open ����
				printf("File %d doesn`t Exist!!\n", i);
			}
			else {
				while (1) {
					nread = read(fd, buffer, 1024);			// file�κ��� ������ �о�� buffer�� ����
					nwrite = write(1, buffer, nread);		// buffer�� ����� ������ ǥ�� ���
					if (nread <= 0) break;					// read�� ������ ���ٸ� break
				}
			}
			close(fd);										// file close
		}
	}
	return 0;
}
