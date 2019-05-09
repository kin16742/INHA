// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.10
// ���ڷ� �� ��ȣ�� ������ �̸��� �޾�
// ���� ����ִ��� Ȯ���ϰ�
// ����ִٸ� �������� �߰��ϴ� �Լ�

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "addguest.h"
#include "getoccupier.h"

void addguest(int roomno, char name[LINELENGTH]){
	off_t offset;	// roomno�� ���� offset�� ����� ����
	ssize_t nwrite;	// write�� return���� ������ ����
	char* buffer;	// �Է¹��� ���� ������ ������ ������ ����

	buffer = getoccupier(roomno);	// buffer�� getoccupier �Լ��� ȣ���� ������ ���� ����

	if(buffer[0] != ' '){
		// �������� �����ϴ� ���
		printf("Room %d is not empty!\n", roomno);
	}
	else{
		// �������� �������� �ʴ� ���
		if(listfiledes == -1 && (listfiledes = open(listfile, O_RDWR))==-1){
			// listfile�� open, ���� �� Error ���
			fprintf(stderr, "Error on opening list file \n");
		}

		offset = (roomno - 1) * LINELENGTH;	// offset ���
	
		if(lseek(listfiledes, offset, SEEK_SET) == -1){
			// ����� offset���� file pointer �̵�, ���� �� Error ���
			fprintf(stderr, "Error on setting offset \n");
		}

		if((nwrite = write(listfiledes, name, LINELENGTH - 1))<0){ 
			// file pointer�������� �Է¹��� ������ �̸��� write, ���� �� Error ���
			fprintf(stderr, "Error on writing offset \n");
		}
	}
}
