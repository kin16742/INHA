// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.3
// ó���� creat�� ����Ͽ� �� ȭ���� �����ϰ�, �̾� close�� �θ��� �ʰ� open �ý��� ȣ���
// �б�� ��������� �����ϴ� ©���� ���α׷�

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int t = creat("text.txt", 0644);	// text.txt��� ������ 0644�� �������� ����
	int fd = open("text.txt", O_RDWR);	// ������ ������ ������ �б�/��������� ����

	if(fd == -1) printf("FAIL\n");		// text.txt open ���� �� fd�� -1�� �ǹǷ� ����
	else printf("SUCCESS\n");			// �׷��� ������ ����

	return 0;
}

