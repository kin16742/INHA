// 12141540 �ڿ�â
// ���н� ���α׷��� 001

// �������� 2.10
// ���ڷ� �� ��ȣ�� �޾� ���� ����ִ� �Լ�

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "hotel.h"
#include "freeroom.h"

void freeroom(int roomno){
	off_t offset;										// roomno�� ���� offset�� ����� ����
	ssize_t nwrite;										// write�� return���� ����� ����
	char buffer[LINELENGTH] = {' ', ' ', ' ', '\n'};	// �� ��(���� 3��)�� Ÿ������ ���ڿ�

	if(listfiledes == -1 && (listfiledes = open(listfile, O_RDWR)) == -1){
		// listfile�� open, ���� �� Error ���
		fprintf(stderr, "Error on opening list file \n");
	}

	offset = (roomno - 1) * LINELENGTH; // offset ���

	if(lseek(listfiledes, offset, SEEK_SET) == -1){
		// ����� offset���� file pointer �̵�, ���� �� Error ���
		fprintf(stderr, "Error on setting offset \n");
	}
	
	if((nwrite = write(listfiledes, buffer, LINELENGTH))<0){
		// file pointer�������� buffer�� ������ write, ���� �� Error ���
		fprintf(stderr, "Error on writing offset \n");
	}
}
